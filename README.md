# Test repository
To tweak with CMake, vcpkg, SDL.

## Description
Currently it's a C program that uses SDL 2 and OpenGL to display a window, draw a triangle in a 3D scene, handle keyboard inputs (arrows to move in the scene) and mouse input to move the camera, but has some quirks. Mouse warping should work correctly. Left-Click on the window to enable warping and Right-Click to disable it.

Initially you spawn inside the triangle so use back arrow to actually see it.

## Vcpkg dependencies

Vcpkg requires Visual Studio 2015 or later with english language pack. It is included as submodule in this repository. Use **one** of those commands :

* `git submodule update --init --recursive`
* `git clone https://github.com/microsoft/vcpkg`


Then initialize vcpkg and fetch required libraries :
```cmd
> .\vcpkg\bootstrap-vcpkg.bat
> .\vcpkg\vcpkg install sdl2:x64-windows opengl:x64-windows glew:x64-windows
> .\vcpkg\vcpkg integrate install
```

## Building

You have to use CMake. It is bundled with vcpkg if you don't want to install it.
