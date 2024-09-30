HEAD = False
CONST = True

#!/usr/bin/env python3

# https://github.com/atcoder/ac-library/blob/master/expander.py のコードを元にしています。

import re
import sys
import argparse
from logging import Logger, basicConfig, getLogger
from os import getenv, environ, pathsep
from pathlib import Path
from typing import List, Set, Optional


logger = getLogger(__name__)  # type: Logger



class Expander:
    """
    Expander class is responsible for expanding libraries in the source code.

    Attributes:
    - include (re.Pattern): Regular expression pattern to match #include statements.
    - lib_paths (List[Path]): List of library paths.
    - included (Set[Path]): Set of included library file paths.

    Methods:
    - is_ignored_line(line: str) -> bool: Checks if a line should be ignored during expansion.
    - find_library(library_name: str) -> Path: Finds the path of a library file.
    - expand_library(library_file_path: Path) -> List[str]: Expands a library file.
    - expand(source: str) -> str: Expands libraries in the source code.

    """

    include = re.compile(r'#include\s*["<](kyopro_library/[a-z0-9_/]*(|.hpp))[">]\s*')

    def is_ignored_line(self, line) -> bool:
        """
        Checks if a line should be ignored during expansion.

        Args:
        - line (str): The line to be checked.

        Returns:
        - bool: True if the line should be ignored, False otherwise.

        """
        if line.strip() == "#pragma once":
            return True
        #if line.strip().startswith("//"):
        #   return True
        if line.strip().startswith("using std::"):
            return True
        if line.strip() in ["#ifdef LOCAL","#include \"./debug.hpp\"","#else","#define debug(...)","#define print_line","#endif"] and not HEAD:
            return True
        if line.strip() in ["const int INF=1e9+10;","const ll INFL=4e18;"] and not CONST:
            return True

        


        return False

    def __init__(self, lib_paths: List[Path]):
        """
        Initializes an Expander object.

        Args:
        - lib_paths (List[Path]): List of library paths.

        """
        self.lib_paths = lib_paths

    included = set()  # type: Set[Path]

    def find_library(self, library_name: str) -> Path:
        """
        Finds the path of a library file.

        Args:
        - library_name (str): The name of the library file.

        Returns:
        - Path: The path of the library file.

        Raises:
        - FileNotFoundError: If the library file cannot be found.

        """
        for lib_path in self.lib_paths:
            path = lib_path / library_name
            if path.exists():
                return path
        logger.error("cannot find: {}".format(library_name))
        raise FileNotFoundError()

    def expand_library(self, library_file_path: Path) -> List[str]:
        """
        Expands a library file.

        Args:
        - library_file_path (Path): The path of the library file.

        Returns:
        - List[str]: The expanded lines of the library file.

        """
        if library_file_path in self.included:
            logger.info("already included: {}".format(library_file_path.name))
            return []
        self.included.add(library_file_path)
        logger.info("include: {}".format(library_file_path.name))

        library_source = open(str(library_file_path)).read()

        result = []  # type: List[str]
        for line in library_source.splitlines():
            if self.is_ignored_line(line):
                continue

            line = line.replace("../../../../", "")
            line = line.replace("../../../", "")
            line = line.replace("../../", "")
            # line = line.replace("../", "")

            # if "debug" in line:
            #     line = "//" + line
            # if "print_line" in line:
            #     line = "//" + line

            m = self.include.match(line)
            if m:
                name = m.group(1)
                result.extend(self.expand_library(self.find_library(name)))
                continue

            result.append(line)

        result.append("")
        return result

    def expand(self, source: str) -> str:
        """
        Expands libraries in the source code.

        Args:
        - source (str): The source code to be expanded.

        Returns:
        - str: The expanded source code.

        """
        self.included = set()
        result = []  # type: List[str]
        for line in source.splitlines():
            m = self.include.match(line)
            if m:
                acl_path = self.find_library(m.group(1))
                result.extend(self.expand_library(acl_path))
                continue

            if "debug" in line or "print_line" in line:
                continue
                
            # if line.startswith("ll ") or " ll " in line or "(ll)" in line or "<ll>" in line or "ll," in line or ",ll" in line:
            #     line=line.replace("ll","long long")

            result.append(line)
        return "\n".join(result)


if __name__ == "__main__":
    basicConfig(
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%H:%M:%S",
        level=getenv("LOG_LEVEL", "INFO"),
    )
    parser = argparse.ArgumentParser(description="Expander")
    parser.add_argument("source", help="Source File")
    parser.add_argument("-c", "--console", action="store_true", help="Print to Console")
    parser.add_argument("--lib", help="Path to Atcoder Library")
    opts = parser.parse_args()

    lib_paths = []
    if opts.lib:
        lib_paths.append(Path(opts.lib))
    if "CPLUS_INCLUDE_PATH" in environ:
        lib_paths.extend(
            map(Path, filter(None, environ["CPLUS_INCLUDE_PATH"].split(pathsep)))
        )
    lib_paths.append(Path.cwd())
    expander = Expander(lib_paths)
    source = open(opts.source).read()
    output = expander.expand(source)

    if opts.console:
        print(output)
    else:
        with open("combined.cpp", "w") as f:
            f.write(output)

