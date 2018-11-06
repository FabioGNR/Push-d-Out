import os
import sys

args = sys.argv
if '--fix' in args:
    args.remove('--fix')
    os.system("python external/Clang-Format/run-clang-format-fix.py game/ engine/")
else:
    os.system("python external/Clang-Format/run-clang-format.py -r game/ engine/")

