"""
Re-encodes the README showcase GIF.

Usage:
    python scripts/optimize_showcase.py --dry-run
    python scripts/optimize_showcase.py
    python scripts/optimize_showcase.py --width 1100 --fps 15 --colors 256

Requires:
    ffmpeg on PATH   (winget install Gyan.FFmpeg)
"""

import argparse
import shutil
import subprocess
import sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).resolve().parents[1]
DEFAULT_SOURCE = PROJECT_ROOT / "Examples" / "Example_Showcase_2.0.gif"

DEFAULT_WIDTH = 900
DEFAULT_FPS = 12
DEFAULT_COLORS = 192


def human(num_bytes):
    value = float(num_bytes)
    for unit in ("B", "KB", "MB", "GB"):
        if value < 1024.0 or unit == "GB":
            return f"{value:.1f} {unit}"
        value /= 1024.0


def build_filter(width, fps, colors):
    return (
        f"fps={fps},"
        f"scale={width}:-1:flags=lanczos,"
        "split[s0][s1];"
        # stats_mode=diff weights the palette toward pixels that change, rather than toward the
        # large static areas of the UI.
        f"[s0]palettegen=max_colors={colors}:stats_mode=diff[p];"
        # diff_mode=rectangle limits each frame to the changed region.
        "[s1][p]paletteuse=dither=bayer:bayer_scale=5:diff_mode=rectangle"
    )


def encode(source, destination, width, fps, colors):
    command = [
        "ffmpeg",
        "-y",
        "-loglevel", "error",
        "-i", str(source),
        "-vf", build_filter(width, fps, colors),
        "-loop", "0",
        str(destination),
    ]

    result = subprocess.run(command, capture_output=True, text=True)

    if result.returncode != 0:
        raise RuntimeError(result.stderr.strip() or "ffmpeg failed")


def main():
    parser = argparse.ArgumentParser(description="Re-encode the README showcase GIF.")
    parser.add_argument("--source", type=Path, default=DEFAULT_SOURCE)
    parser.add_argument("--width", type=int, default=DEFAULT_WIDTH, help=f"Target width in pixels (default {DEFAULT_WIDTH}).")
    parser.add_argument("--fps", type=int, default=DEFAULT_FPS, help=f"Output frame rate (default {DEFAULT_FPS}).")
    parser.add_argument("--colors", type=int, default=DEFAULT_COLORS, help=f"Palette size, max 256 (default {DEFAULT_COLORS}).")
    parser.add_argument("--dry-run", action="store_true", help="Report the source stats and stop.")
    parser.add_argument("--no-backup", action="store_true", help="Do not keep the original alongside the result.")
    args = parser.parse_args()

    source = args.source

    if not source.is_file():
        sys.exit(f"Not found: {source}")

    if shutil.which("ffmpeg") is None:
        sys.exit(
            "ffmpeg is not on PATH.\n"
            "    Windows : winget install Gyan.FFmpeg\n"
            "    macOS   : brew install ffmpeg\n"
            "    Linux   : sudo apt install ffmpeg\n"
        )

    original_size = source.stat().st_size
    print(f"source : {human(original_size)}")

    if args.dry_run:
        print("Dry run: nothing written.")
        return

    if not args.no_backup:
        backup = source.with_suffix(source.suffix + ".original")
        if not backup.exists():
            shutil.copy2(source, backup)
            print(f"backup : {backup.name}")

    temporary = source.with_suffix(".tmp.gif")

    try:
        encode(source, temporary, args.width, args.fps, args.colors)
    except RuntimeError as exc:
        temporary.unlink(missing_ok=True)
        sys.exit(f"ffmpeg failed: {exc}")

    new_size = temporary.stat().st_size

    print(f"result : {args.width}px wide, {args.fps} fps, {args.colors} colours, {human(new_size)}")

    if new_size >= original_size:
        temporary.unlink()
        sys.exit("Re-encode came out no smaller - leaving the original in place.")

    temporary.replace(source)

    print(f"saved  : {human(original_size - new_size)}  ({new_size / original_size * 100.0:.1f}% of original)")

    if not args.no_backup:
        print()
        print("The original is kept as *.gif.original - delete it once you are happy with the result;")
        print("it must not be committed.")


if __name__ == "__main__":
    main()
