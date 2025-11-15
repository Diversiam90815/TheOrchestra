import re
from pathlib import Path
from subprocess import check_output
from typing import Optional


class VersionManager:

    def __init__(self, cmake_file: Path, version_var: str = "PROJECT_VERSION") -> None:
        self.cmake_file = cmake_file
        self.version_var = version_var


    def get_build_number(self) -> int:
        commit_hashes = check_output(["git", "rev-list", "HEAD"]).rstrip()
        return commit_hashes.count(b"\n") + 1


    def get_current_version(self) -> Optional[str]:
        pattern = re.compile(rf"set\({self.version_var}\s+(\d+\.\d+\.\d+)\)")

        with self.cmake_file.open("r", encoding="utf-8") as f:
            for line in f:
                match = pattern.search(line)
                if match:
                    return match.group(1)
        return None


    def _write_version(self, new_version: str) -> None:
        pattern = re.compile(rf"set\({self.version_var}\s+(\d+\.\d+\.\d+)\)")
        tmp_file = self.cmake_file.with_name(self.cmake_file.name + ".tmp")

        with self.cmake_file.open("r", encoding="utf-8") as fin, \
             tmp_file.open("w", encoding="utf-8") as fout:
            for line in fin:
                if pattern.search(line):
                    fout.write(f"set({self.version_var} {new_version})\n")
                else:
                    fout.write(line)

        tmp_file.replace(self.cmake_file)


    def update_build_number_in_version(self) -> Optional[str]:
        current_version = self.get_current_version()
        if not current_version:
            return None

        build_number = self.get_build_number()
        parts = current_version.split(".")
        parts[-1] = str(build_number)
        new_version = ".".join(parts)

        self._write_version(new_version)
        return new_version
