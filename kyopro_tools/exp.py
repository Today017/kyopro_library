HEAD = True
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

    def expand_library(self, library_file_path: Path, library_name: Optional[str] = None) -> List[str]:
        """
        Expands a library file.

        Args:
        - library_file_path (Path): The path of the library file.
        - library_name (Optional[str]): The include name used to reference this library
          (e.g. "kyopro_library/foo.hpp"). Used for begin/end comments.

        Returns:
        - List[str]: The expanded lines of the library file.

        """
        if library_file_path in self.included:
            logger.info("already included: {}".format(library_file_path.name))
            return []
        self.included.add(library_file_path)
        logger.info("include: {}".format(library_file_path.name))

        # 展開したライブラリがどのファイル由来か分かるよう、前後にコメントを付ける
        label = library_name if library_name is not None else library_file_path.name

        library_source = open(str(library_file_path)).read()

        result = [self._scissors(label, "begin")]  # type: List[str]
        for line in library_source.splitlines():
            if self.is_ignored_line(line):
                continue

            line = line.replace("../../../../", "")
            line = line.replace("../../../", "")
            line = line.replace("../../", "")
            line = line.replace("../", "")

            # if "debug" in line:
            #     line = "//" + line
            # if "print_line" in line:
            #     line = "//" + line

            m = self.include.match(line)
            if m:
                name = m.group(1)
                result.extend(self.expand_library(self.find_library(name), name))
                continue

            result.append(line)

        result.append(self._scissors(label, "end"))
        result.append("")
        return result

    @staticmethod
    def _scissors(label: str, kind: str, width: int = 70) -> str:
        """
        file スクリプト風の切り取り線コメントを作る。
            //------>8------------------ begin xxx ------------------------->8------
        """
        text = " {} {} ".format(kind, label)
        line = "//------>8" + text.center(max(0, width - len("//------>8" + ">8------")), "-") + ">8------"
        return line

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
                name = m.group(1)
                acl_path = self.find_library(name)
                result.extend(self.expand_library(acl_path, name))
                continue

            if not HEAD:
                if "debug" in line or "print_line" in line:
                    continue

            # if line.startswith("ll ") or " ll " in line or "(ll)" in line or "<ll>" in line or "ll," in line or ",ll" in line:
            #     line=line.replace("ll","long long")

            result.append(line)
        return "\n".join(result)


# file スクリプトが入れる区切り線。これより上を「ヘッダ部」、下を「本体部」とみなす。
#   例: //------>8------------------------------------------->8------
MARKER = re.compile(r'^\s*//-+>8')


def expand_run_top(expander: "Expander", source: str) -> str:
    """
    提出コードで run()/main() を最上部に出すための組み替え展開。

    file スクリプトのマーカー行でヘッダ部（include 等）と本体部（run/main）に分け、
    本体を #ifdef TODAY_KYOPRO 側（=ファイル先頭）へ、展開済みヘッダを #else 側へ置く:

        #ifdef TODAY_KYOPRO
        <本体: run() / main()>
        #else
        <展開済みヘッダ>
        #define TODAY_KYOPRO
        #include __FILE__
        #endif

    TODAY_KYOPRO 未定義の通常コンパイルでは #else を1パス目で処理し、__FILE__ の
    再 include による2パス目で本体が有効化されるため、判定環境で正しくコンパイルされる。
    マーカーが無いソースは通常展開へフォールバックする。
    """
    lines = source.splitlines()
    idx = next((i for i, ln in enumerate(lines) if MARKER.match(ln)), None)
    if idx is None:
        return expander.expand(source)

    body = "\n".join(lines[idx + 1:]).strip("\n")
    expanded_header = expander.expand("\n".join(lines[:idx])).rstrip("\n")

    return (
        "#ifdef TODAY_KYOPRO\n\n"
        + body
        + "\n\n#else\n\n"
        + expanded_header
        + "\n\n#define TODAY_KYOPRO\n#include __FILE__\n\n#endif\n"
    )


if __name__ == "__main__":
    basicConfig(
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%H:%M:%S",
        level=getenv("LOG_LEVEL", "INFO"),
    )
    parser = argparse.ArgumentParser(description="Expander")
    parser.add_argument("source", help="Source File")
    parser.add_argument("-c", "--console", action="store_true", help="Print to Console")
    parser.add_argument("-r", "--run-top", action="store_true",
                        help="run()/main() を提出コードの最上部に出す（#include __FILE__ 方式）")
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
    if opts.run_top:
        output = expand_run_top(expander, source)
    else:
        output = expander.expand(source)

    if opts.console:
        print(output)
    else:
        with open("combined.cpp", "w") as f:
            f.write(output)

