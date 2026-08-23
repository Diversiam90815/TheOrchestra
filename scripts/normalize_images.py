"""
Normalises the instrument photos into one consistent set.

This pass makes every one of them the same kind of asset:

  * RGBA PNG, so alpha edges are anti-aliased instead of 1-bit
  * background keyed out on the JPEGs, flood-filled inward from the corners
  * cropped to the actual content, then centred on a uniform square canvas
  * capped at a sane resolution

Usage:
    python scripts/normalize_images.py --dry-run
    python scripts/normalize_images.py
    python scripts/normalize_images.py --canvas 768 --tolerance 40

Requires:
    pip install pillow numpy
"""

import argparse
import sys
import numpy as np
from pathlib import Path
from PIL import Image, ImageDraw, ImageFilter

PROJECT_ROOT = Path(__file__).resolve().parents[1]
IMAGES_DIR = PROJECT_ROOT / "Assets" / "Images"

DEFAULT_CANVAS = 512
DEFAULT_PADDING = 16
DEFAULT_TOLERANCE = 32

# Flood-fill marker. Verified absent from the source before use.
SENTINEL = (255, 0, 255)


def human(num_bytes):
    value = float(num_bytes)
    for unit in ("B", "KB", "MB"):
        if value < 1024.0 or unit == "MB":
            return f"{value:.0f} {unit}" if unit == "B" else f"{value:.1f} {unit}"
        value /= 1024.0


def has_real_alpha(image):
    """True if the image carries transparency that actually varies."""
    if image.mode == "RGBA":
        return image.getchannel("A").getextrema()[0] < 255
    return "transparency" in image.info


def trim_dark_frame(image, max_fraction=0.05):
    """
    Strips a thin dark border off a photo.
    """

    pixels = np.array(image.convert("RGB"))
    height, width = pixels.shape[:2]

    limit_y = max(1, int(height * max_fraction))
    limit_x = max(1, int(width * max_fraction))

    def is_dark(line):
        return line.size > 0 and line.mean() < 128

    top, bottom, left, right = 0, height, 0, width

    while top < limit_y and is_dark(pixels[top, left:right]):
        top += 1

    while height - bottom < limit_y and is_dark(pixels[bottom - 1, left:right]):
        bottom -= 1

    while left < limit_x and is_dark(pixels[top:bottom, left]):
        left += 1

    while width - right < limit_x and is_dark(pixels[top:bottom, right - 1]):
        right -= 1

    if (top, left, bottom, right) == (0, 0, height, width):
        return image

    return image.crop((left, top, right, bottom))


def key_once(image, tolerance):
    """One keying attempt at a fixed tolerance."""

    image = trim_dark_frame(image)

    rgb = image.convert("RGB")
    width, height = rgb.size

    source = np.array(rgb)

    marker = SENTINEL
    if np.any(np.all(source == marker, axis=-1)):
        marker = (254, 0, 254)  # collision, pick a neighbour

    # The Viola background runs from 254 down to 237 across the frame, so a single corner seed does
    # not describe it. Seeding all round the border lets each seed key its own neighbourhood.
    border = np.concatenate([source[0, :], source[height - 1, :], source[:, 0], source[:, width - 1]])
    reference = np.median(border, axis=0)

    step_x = max(1, width // 16)
    step_y = max(1, height // 16)

    seeds = []
    seeds += [(x, 0) for x in range(0, width, step_x)]
    seeds += [(x, height - 1) for x in range(0, width, step_x)]
    seeds += [(0, y) for y in range(0, height, step_y)]
    seeds += [(width - 1, y) for y in range(0, height, step_y)]

    work = rgb.copy()

    for x, y in seeds:
        pixel = source[y, x]

        # Only seed from pixels that actually look like the background, so a seed can never land on
        # the instrument and eat into it.
        if np.abs(pixel.astype(int) - reference).max() > tolerance:
            continue

        ImageDraw.floodfill(work, (x, y), marker, thresh=tolerance)

    filled = np.array(work)
    background = np.all(filled == marker, axis=-1)

    if not background.any():
        return image.convert("RGBA")

    alpha = np.where(background, 0, 255).astype("uint8")
    alpha_image = Image.fromarray(alpha, "L")

    # Erode by a pixel to eat the pale fringe the original matte leaves behind, then soften so the
    # cutout does not look stamped out.
    alpha_image = alpha_image.filter(ImageFilter.MinFilter(3))
    alpha_image = alpha_image.filter(ImageFilter.GaussianBlur(0.6))

    result = rgb.convert("RGBA")
    result.putalpha(alpha_image)

    return result


def key_out_background(image, tolerance, max_tolerance=96):
    """
    Keys out the background, raising the tolerance until the border is actually clear.
    """

    result = None
    attempt = tolerance

    while attempt <= max_tolerance:
        keyed = key_once(image, attempt)
        alpha = np.array(keyed.getchannel("A"))

        opaque = float((alpha > 0).mean())

        # Almost nothing left means the fill escaped through the subject; keep the previous result.
        if opaque < 0.10 and result is not None:
            break

        result = keyed

        border = np.concatenate([alpha[0, :], alpha[-1, :], alpha[:, 0], alpha[:, -1]])

        if float((border == 0).mean()) >= 0.99:
            break

        attempt += 8

    return result if result is not None else image.convert("RGBA")


def fit_to_canvas(image, canvas, padding):
    image = image.convert("RGBA")

    bbox = image.getbbox()
    if bbox:
        image = image.crop(bbox)

    inner = max(1, canvas - 2 * padding)
    scale = min(inner / image.width, inner / image.height)

    size = (max(1, round(image.width * scale)), max(1, round(image.height * scale)))
    image = image.resize(size, Image.LANCZOS)

    out = Image.new("RGBA", (canvas, canvas), (0, 0, 0, 0))
    out.paste(image, ((canvas - size[0]) // 2, (canvas - size[1]) // 2), image)

    return out


def main():
    parser = argparse.ArgumentParser(description="Normalise the instrument images.")
    parser.add_argument("--canvas", type=int, default=DEFAULT_CANVAS, help=f"Square canvas size (default {DEFAULT_CANVAS}).")
    parser.add_argument("--padding", type=int, default=DEFAULT_PADDING, help=f"Transparent margin (default {DEFAULT_PADDING}).")
    parser.add_argument("--tolerance", type=int, default=DEFAULT_TOLERANCE, help=f"Background keying tolerance (default {DEFAULT_TOLERANCE}).")
    parser.add_argument("--dry-run", action="store_true", help="Report what would change without writing.")
    args = parser.parse_args()

    if not IMAGES_DIR.is_dir():
        sys.exit(f"Image directory not found: {IMAGES_DIR}")

    sources = sorted(p for p in IMAGES_DIR.rglob("*") if p.suffix.lower() in (".png", ".jpg", ".jpeg"))

    if not sources:
        sys.exit(f"No images found under {IMAGES_DIR}")

    print(f"{len(sources)} images under {IMAGES_DIR.relative_to(PROJECT_ROOT)}")
    print()
    print(f"{'instrument':<24} {'before':<26} {'after':<20} {'keyed'}")
    print("-" * 82)

    before_total = 0
    after_total = 0
    keyed = 0

    for path in sources:
        instrument = path.parent.name
        size_before = path.stat().st_size
        before_total += size_before

        with Image.open(path) as opened:
            opened.load()
            description = f"{opened.width}x{opened.height} {opened.mode} {human(size_before)}"
            needs_keying = not has_real_alpha(opened)
            image = opened.copy()

        if needs_keying:
            image = key_out_background(image, args.tolerance)
            keyed += 1

        image = fit_to_canvas(image, args.canvas, args.padding)

        destination = path.with_name("instrument.png")

        if args.dry_run:
            print(f"{instrument:<24} {description:<26} {'(dry run)':<20} {'yes' if needs_keying else ''}")
            continue

        image.save(destination, "PNG", optimize=True)

        # The JPEGs become PNGs; drop the originals so the folder holds exactly one image.
        if path != destination:
            path.unlink()

        size_after = destination.stat().st_size
        after_total += size_after

        print(f"{instrument:<24} {description:<26} {f'{args.canvas}x{args.canvas} RGBA {human(size_after)}':<20} {'yes' if needs_keying else ''}")

    print("-" * 82)
    print(f"backgrounds keyed out : {keyed}")

    if not args.dry_run and before_total:
        print(f"total                 : {human(before_total)} -> {human(after_total)}")


if __name__ == "__main__":
    main()
