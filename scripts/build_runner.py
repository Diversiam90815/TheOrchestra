from pathlib import Path

from .enums import Architecture, Configuration, Platform
from .utils import BuildUtils
from .versioning import VersionManager
from .paths import *


class BuildRunner:
    def __init__(self, root_dir: Path, build_dir: Path, project_name: str) -> None:
        self.root_dir = root_dir
        self.build_dir = build_dir
        self.project_name = project_name

        self.version: str | None = None

        self.version_manager = VersionManager(CMAKE_FILE)

    # ---- Versioning ----
    def update_app_version(self) -> None:
        self.version = self.version_manager.update_build_number_in_version()

    # ---- CMake / build ----
    def create_build_generator(
        self,
        platform: Platform,
        build: bool,
        architecture: Architecture,
        configuration: Configuration,
    ) -> None:
        prepare_cmd = [
            "cmake",
            "-G", str(platform),
            "-S", str(self.root_dir),
            "-B", str(self.build_dir),
        ]  
        if platform == Platform.VS2022 or platform == Platform.VS2026:
            prepare_cmd += ["-A", str(architecture)]

        BuildUtils.execute_command(
            prepare_cmd,
            f"CMake: Generate {platform} project",
        )

        if build:
            # build
            BuildUtils.execute_command(
                [
                    "cmake",
                    "--build", str(self.build_dir),
                    "--config", str(configuration),
                    "--parallel", "8",
                ],
                f"CMake: Build {self.project_name} v{self.version or 'unknown'}",
            )

            # install
            BuildUtils.execute_command(
                [
                    "cmake",
                    "--install", str(self.build_dir),
                    "--config", str(configuration),
                    "--prefix", str(CMAKE_INSTALL_DIR),
                ],
                f"CMake: Install {self.project_name}",
            )

    def run_cpp_unit_tests(self, configuration: Configuration) -> None:
        """Build and run the GoogleTest suite.

        The tests are part of the main build tree, so they build with the default
        target and ctest runs against the same directory. The previous version
        built a `RUN_TESTS` target, which only exists for Visual Studio
        generators (Ninja is the default), and pointed ctest at a `build/tests`
        directory that is never created.
        """
        BuildUtils.execute_command(
            [
                "cmake",
                "--build", str(self.build_dir),
                "--config", str(configuration),
                "--parallel", "8",
            ],
            "CMake: Build C++ unit tests",
        )

        BuildUtils.execute_command(
            [
                "ctest",
                "--test-dir", str(self.build_dir),
                "-C", str(configuration),
                "--output-on-failure",
            ],
            "CMake: Running C++ unit tests",
        )
