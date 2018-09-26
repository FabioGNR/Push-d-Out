# Windows - Powershell / MSVC
## Toolchain
Getting started on Windows takes a bit of effort. First off, you will need a proper compiler.
The easiest way to get started, is using Visual Studio (MSVC). Run the VS2017 installer, and install the C++ environment.

Also download and install [cmake](https://cmake.org/download/).

## Package manager
The preferred way to get SDL installed is using a package manager.
Microsoft has recently released [vcpkg](https://github.com/Microsoft/vcpkg), which we will be using for these instructions.
Other options could be [Conan](https://conan.io/), or [Hunter](https://github.com/ruslo/hunter).

1. Install vcpkg in whatever dir you want, recommended in C:\\. PowerShell:

```powershell
PS> git clone https://github.com/Microsoft/vcpkg.git
PS> cd vcpkg
PS> .\bootstrap-vcpkg.bat
```

2. Hook up integration
```powershell
PS> .\vcpkg integrate install
```

3. Install SDL
```powershell
PS> .\vcpkg install sdl2
```

## Building
Make sure to have the correct vcpkg path ready.

Inside the root directory:
```ps
PS> mkdir build
PS> cd build
PS> cmake .. -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake
PS> cmake --build .
```

The game can be found in bin/PushdOut.exe.
Copy the DLL's from `C:\vcpkg\installed\x86-windows\bin` to the executable folder.
