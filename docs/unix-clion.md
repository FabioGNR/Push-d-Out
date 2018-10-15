# Linux
## Toolchain
Building on Linux is much easier. For this setup, we will be using Ubuntu 18.04. Install either g++ or clang++ using apt.

`sudo apt-get install g++`

`sudo apt-get install cmake`

## Package manager
Linux does not need a package manager, besides its own. On Ubuntu:

`sudo apt-get install libsdl2-dev`

`sudo apt-get install libsdl2-ttf-dev`

`sudo apt-get install libsdl2-image-dev`

`sudo apt-get install libbox2d-dev`

## Clion
Clion is optional, use whatever CMake-compatible IDE, or your favorite text editor if you want to. Building can be done
in the terminal.

Clion can be installed using the default settings.

# MacOS
## Toolchain
Building on Mac is nearly the same as Linux; macOS comes with Clang, when
the Xcode development tools are installed.

Do this by running `xcode-select --install` in the terminal.

Use *brew* to install CMake.

`brew install cmake`

## Package manager
You have to use *vcpkg* for both SDL2, and Box2D.

Inside your vcpkg folder run:

`./vcpkg install sdl2`

`./vcpkg install sdl2-ttf`

`./vcpkg install box2d`

## Building
Once you have everything installed, open the project folder and run the following commands in the terminal:

1. `mkdir build`
2. `cd build`
3. `cmake .. -DCMAKE_TOOLCHAIN_FILE="<vcpkg location>/scripts/buildsystems/vcpkg.cmake"`

This will generate the necessary files to run the project. Import the project in CLion using existing sources.

## Clion
Clion is optional, use whatever CMake-compatible IDE, or your favorite text editor if you want to. Building can be done
in the terminal.

Clion can be installed using the default settings.
