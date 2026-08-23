"""
Converts the sample pack from WAV to FLAC.

Usage:
    python scripts/convert_samples.py --dry-run     # report what would happen, touch nothing
    python scripts/convert_samples.py               # convert, verify, keep the WAVs
    python scripts/convert_samples.py --delete-wav  # convert, verify, then remove each WAV

Requires:
    pip install soundfile numpy
"""

import argparse
import sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).resolve().parents[1]
SAMPLES_DIR = PROJECT_ROOT / "Assets" / "Samples"


def require_dependencies():
    try:
        import soundfile  # noqa: F401
        import numpy  # noqa: F401
    except ImportError:
        sys.exit(
            "This script needs soundfile and numpy:\n"
            "    pip install soundfile numpy\n"
        )


def human(num_bytes):
    value = float(num_bytes)
    for unit in ("B", "KB", "MB", "GB"):
        if value < 1024.0 or unit == "GB":
            return f"{value:.1f} {unit}"
        value /= 1024.0


def convert_one(wav_path, delete_wav):
    """Returns (flac_path, wav_size, flac_size) or raises on a verification failure."""
    import numpy as np
    import soundfile as sf

    flac_path = wav_path.with_suffix(".flac")

    source, sample_rate = sf.read(wav_path, dtype="int32", always_2d=True)

    info = sf.info(wav_path)
    subtype = info.subtype if info.subtype in ("PCM_16", "PCM_24") else "PCM_16"

    sf.write(flac_path, source, sample_rate, format="FLAC", subtype=subtype)

    # Decode what we just wrote and compare the samples, not the bytes.
    result, result_rate = sf.read(flac_path, dtype="int32", always_2d=True)

    if result_rate != sample_rate:
        flac_path.unlink(missing_ok=True)
        raise ValueError(f"sample rate changed: {sample_rate} -> {result_rate}")

    if result.shape != source.shape:
        flac_path.unlink(missing_ok=True)
        raise ValueError(f"shape changed: {source.shape} -> {result.shape}")

    if not np.array_equal(source, result):
        flac_path.unlink(missing_ok=True)
        raise ValueError("decoded PCM differs from the source")

    wav_size = wav_path.stat().st_size
    flac_size = flac_path.stat().st_size

    if delete_wav:
        wav_path.unlink()

    return flac_path, wav_size, flac_size


def main():
    parser = argparse.ArgumentParser(description="Convert the sample pack from WAV to FLAC.")
    parser.add_argument("--dry-run", action="store_true", help="Report what would happen without writing anything.")
    parser.add_argument("--delete-wav", action="store_true", help="Remove each WAV once its FLAC has been verified.")
    parser.add_argument("--limit", type=int, default=0, help="Only process the first N files (for a trial run).")
    args = parser.parse_args()

    if not SAMPLES_DIR.is_dir():
        sys.exit(f"Sample directory not found: {SAMPLES_DIR}")

    wav_files = sorted(SAMPLES_DIR.rglob("*.wav"))

    if args.limit:
        wav_files = wav_files[: args.limit]

    if not wav_files:
        print("No .wav files found - nothing to do.")
        return

    total_wav = sum(f.stat().st_size for f in wav_files)
    print(f"Found {len(wav_files)} WAV files, {human(total_wav)} total")

    if args.dry_run:
        print("Dry run: nothing written.")
        return

    require_dependencies()

    converted = 0
    failed = []
    sum_wav = 0
    sum_flac = 0

    for index, wav_path in enumerate(wav_files, start=1):
        try:
            _, wav_size, flac_size = convert_one(wav_path, args.delete_wav)
        except Exception as exc:  # noqa: BLE001 - report and keep going
            failed.append((wav_path, str(exc)))
            print(f"  FAILED {wav_path.relative_to(SAMPLES_DIR)}: {exc}")
            continue

        converted += 1
        sum_wav += wav_size
        sum_flac += flac_size

        if index % 100 == 0 or index == len(wav_files):
            ratio = (sum_flac / sum_wav * 100.0) if sum_wav else 0.0
            print(f"  {index}/{len(wav_files)}  {human(sum_wav)} -> {human(sum_flac)}  ({ratio:.1f}%)")

    print()
    print(f"Converted and verified : {converted}")
    print(f"Failed                 : {len(failed)}")

    if sum_wav:
        saved = sum_wav - sum_flac
        print(f"WAV                    : {human(sum_wav)}")
        print(f"FLAC                   : {human(sum_flac)}  ({sum_flac / sum_wav * 100.0:.1f}%)")
        print(f"Saved                  : {human(saved)}")

    if not args.delete_wav and converted:
        print()
        print("The WAVs are still on disk. Re-run with --delete-wav to remove the verified ones.")

    if failed:
        sys.exit(1)


if __name__ == "__main__":
    main()
