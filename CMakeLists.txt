cmake_minimum_required(VERSION 3.0)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
	if(DEFINED ENV{VCPKG_ROOT})
		set(VCPKG_ROOT ENV{VCPKG_ROOT})
	else()
		set(VCPKG_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
	endif()
	set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
endif()

#========== Global Configurations =============#
#----------------------------------------------#
project(test-sdl C)
set(CMAKE_VERBOSE_MAKEFILE ON)

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)

if (NOT UNIX)
	find_package(GLEW REQUIRED)
endif()

#========== Targets Configurations =============#

# Build an executable
file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")
file(GLOB HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")
add_executable(test-sdl ${SOURCE_FILES} ${HEADER_FILES})

# If find_package(SDL2) grabs the vcpkg package (by default), bind SDL2_LIBRARIES to target name
if (TARGET SDL2::SDL2 AND TARGET SDL2::SDL2main)
	set(SDL2_LIBRARIES "SDL2::SDL2 SDL2::SDL2main")
elseif(SDL2_DIR) # If SDL2 cannot be fetched from vcpkg, user should set SDL2_DIR to the fallback package embedded in this repository (in folder external), but the fallback cmake is very simple and does not register include directories, so it must be done manually
	target_include_directories(test-sdl PUBLIC ${SDL2_INCLUDE_DIRS})
	# TODO: copy SDL2.dll in exe output directory, since vcpkg is not used it is not done automatically
endif()


target_link_libraries(test-sdl PRIVATE ${SDL2_LIBRARIES})

if(UNIX)
	target_link_libraries(test-sdl PRIVATE GL)
else() # assume Win32
	target_link_libraries(test-sdl PRIVATE OpenGL32)
	target_link_libraries(test-sdl PRIVATE GLEW::GLEW)
endif()
