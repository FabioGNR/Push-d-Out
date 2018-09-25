# Linux
## Toolchain
Building on Linux is much easier. For this setup, we will be using Ubuntu 18.04. Install either g++ or clang++ using apt.
`sudo apt-get install clang++ g++`

## Package manager
Linux does not need a package manager, besides its own. On Ubuntu:
`sudo apt-get install libsdl2-dev`

`sudo apt-get install libbox2d-dev`

## Clion
Clion is optional, use whatever CMake-compatible IDE, or your favorite text editor if you want to. Building can be done
in the terminal.

Clion can be installed using the default settings.

# MacOS
## Toolchain
Building on Mac is nearly the same as Linux. MacOS comes with Clang as default, when
installing the XCode development tools.

When entering `gcc` into the terminal, it will open a prompt asking you if you want to install development tools.
Install them there.

## Package manager
You can use *brew* to install SDL, and CMake if you want to compile on the terminal.


`brew install sdl2`


`brew install cmake`

## Clion
Clion is optional, use whatever CMake-compatible IDE, or your favorite text editor if you want to. Building can be done
in the terminal.

Clion can be installed using the default settings.
