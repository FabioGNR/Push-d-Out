#! /bin/sh
if [ "$1" = "--fix" ]; then
    python3 external/Clang-Format/run-clang-format-fix.py engine/ game/
else
    python3 external/Clang-Format/run-clang-format.py -r engine/ game/
fi
