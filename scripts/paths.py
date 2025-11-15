from pathlib import Path

ROOT_DIR            = Path(__file__).resolve().parent.parent
CMAKE_FILE          = ROOT_DIR / "CMakeLists.txt"
BUILD_DIR           = ROOT_DIR / "build"
CMAKE_INSTALL_DIR   = ROOT_DIR / "install"


def get_build_dir(architecture: str) -> Path:
    return BUILD_DIR / architecture
