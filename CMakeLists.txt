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
project(something CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_VERBOSE_MAKEFILE ON)

find_package(SDL2 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

#========== Targets Configurations =============#

# Build an executable
file(GLOB SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
add_executable(something ${SOURCE_FILES})
target_link_libraries(something PRIVATE SDL2::SDL2 SDL2::SDL2main)

if(UNIX)
	target_link_libraries(something PRIVATE GL)
else() # assume Win32
	target_link_libraries(something PRIVATE OpenGL32)
endif()
