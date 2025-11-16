from pathlib import Path

from .enums import Architecture, Configuration, Environment, Platform
from .utils import BuildUtils, working_directory
from .env_config import update_environment_in_cmake
from .versioning import VersionManager
from .paths import *


class BuildRunner:
    def __init__(self, root_dir: Path, build_dir: Path, project_name: str) -> None:
        self.root_dir = root_dir
        self.build_dir = build_dir
        self.project_name = project_name

        self.env: Environment = Environment.Development
        self.version: str | None = None

        self.version_manager = VersionManager(CMAKE_FILE)

    # ---- Environment ----
    def update_environment(self) -> None:
        self.env = update_environment_in_cmake(CMAKE_FILE)

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
            "-A", str(architecture),
            "-S", str(self.root_dir),
            "-B", str(self.build_dir),
        ]  
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

    def run_cpp_unit_tests(self, configuration: Configuration, test_build_dir, target) -> None:

        with working_directory(test_build_dir):
            BuildUtils.execute_command(
                [
                    "cmake",
                    "--build", str(test_build_dir),
                    "--config", str(configuration),
                    "--target", str(target),
                ],
                "CMake: Build C++ unit tests",
            )

            BuildUtils.execute_command(
                [
                    "ctest",
                    "--test-dir", str(test_build_dir),
                    "-C", str(configuration),
                    "--output-on-failure",
                ],
                "CMake: Running C++ unit tests",
            )
