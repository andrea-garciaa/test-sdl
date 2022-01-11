# something

C/C++ test repository: tweaking with CMake and vcpkg

# vcpkg deps

VCpkg requires Visual Studio 2015 or later with english language pack.
```cmd
> git submodule update --init --recursive
```
OR
```cmd
git clone https://github.com/microsoft/vcpkg`
```
```cmd
> .\vcpkg\bootstrap-vcpkg.bat
> .\vcpkg\vcpkg install sdl2:x64-windows opengl:x64-windows glew:x64-windows
> .\vcpkg\vcpkg integrate install
```

# building

You have to use CMake. It is bundled with vcpkg if you don't want to install it.
