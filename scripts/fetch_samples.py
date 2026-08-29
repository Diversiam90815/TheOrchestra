"""
Downloads the sample pack from a GitHub Release and extracts it into the single shared
AppData location for every build config
"""

import os
import sys
import urllib.request
import zipfile
from pathlib import Path

PROJECT_ROOT = Path(__file__).resolve().parents[1]

GITHUB_REPOSITORY   = "Diversiam90815/TheOrchestra"
SAMPLES_RELEASE_TAG = "samples-v1"

SAMPLES_ASSET_NAMES = ["Brass.zip", "Percussion.zip", "Strings.zip", "Woodwinds.zip"]
PROJECT_APPDATA_NAME = "TheOrchestra"

SAMPLES_CACHE_DIR   = PROJECT_ROOT / "libs" / "samples-cache"
VERSION_MARKER_NAME = ".samples-version"


def shared_samples_dir() -> Path:
    """The single AppData location FileManager::getDefaultSamplesFolderPath() resolves to."""
    if sys.platform == "win32":
        base = os.environ.get("PROGRAMDATA") or os.environ.get("APPDATA")
        if not base:
            raise RuntimeError("Neither %PROGRAMDATA% nor %APPDATA% is set")
        return Path(base) / PROJECT_APPDATA_NAME / "Assets" / "Samples"

    if sys.platform == "darwin":
        return Path("/Library/Application Support") / PROJECT_APPDATA_NAME / "Assets" / "Samples"

    return Path.home() / ".local" / "share" / PROJECT_APPDATA_NAME / "Assets" / "Samples"


def _is_up_to_date(samples_dir: Path) -> bool:
    marker = samples_dir / VERSION_MARKER_NAME
    return marker.is_file() and marker.read_text(encoding="utf-8").strip() == SAMPLES_RELEASE_TAG


def ensure_samples() -> None:
    """Downloads and extracts the sample pack if it isn't already present at the target tag."""
    if not GITHUB_REPOSITORY or not SAMPLES_RELEASE_TAG:
        print("\tSample pack release not configured yet (scripts/fetch_samples.py) - skipping fetch.")
        return

    samples_dir = shared_samples_dir()

    if _is_up_to_date(samples_dir):
        print(f"\tSamples already up to date ({SAMPLES_RELEASE_TAG}), skipping download.")
        return

    SAMPLES_CACHE_DIR.mkdir(parents=True, exist_ok=True)
    samples_dir.mkdir(parents=True, exist_ok=True)

    for asset_name in SAMPLES_ASSET_NAMES:
        cached_zip = SAMPLES_CACHE_DIR / f"{SAMPLES_RELEASE_TAG}-{asset_name}"

        if not cached_zip.is_file():
            url = f"https://github.com/{GITHUB_REPOSITORY}/releases/download/{SAMPLES_RELEASE_TAG}/{asset_name}"
            print(f"\tDownloading {asset_name} ({SAMPLES_RELEASE_TAG})...", end="", flush=True)
            urllib.request.urlretrieve(url, cached_zip)
            print(" Done")

        print(f"\tExtracting {asset_name} to {samples_dir}...", end="", flush=True)
        with zipfile.ZipFile(cached_zip) as archive:
            archive.extractall(samples_dir)
        print(" Done")

    (samples_dir / VERSION_MARKER_NAME).write_text(SAMPLES_RELEASE_TAG, encoding="utf-8")


if __name__ == "__main__":
    ensure_samples()
