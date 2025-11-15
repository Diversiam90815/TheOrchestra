import os
import re
from pathlib import Path

from .enums import Environment


def update_environment_in_cmake(cmake_file: Path) -> Environment:
    branch_name = os.getenv("CI_COMMIT_REF_NAME", "") or ""

    if "release/" in branch_name:
        env = Environment.Production
    elif "beta/" in branch_name:
        env = Environment.Staging
    else:
        env = Environment.Development

    pattern = re.compile(r"set\(\s*BUILD_ENVIRONMENT\s+(.*)\)")

    with cmake_file.open("r", encoding="utf-8") as f:
        lines = f.readlines()

    with cmake_file.open("w", encoding="utf-8") as f:
        for line in lines:
            if pattern.search(line):
                f.write(f"set(BUILD_ENVIRONMENT {env.value})\n")
            else:
                f.write(line)

    return env
