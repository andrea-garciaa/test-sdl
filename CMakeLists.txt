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
project(something C)
set(CMAKE_VERBOSE_MAKEFILE ON)

find_package(SDL2 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
#find_package(freetype CONFIG REQUIRED)

if (NOT UNIX)
	find_package(GLEW REQUIRED)
endif()

#========== Targets Configurations =============#

# Build an executable
file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")
file(GLOB HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")
add_executable(something ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(something PRIVATE SDL2::SDL2 SDL2::SDL2main)
#target_link_libraries(something PRIVATE freetype)

if(UNIX)
	target_link_libraries(something PRIVATE GL)
else() # assume Win32
	target_link_libraries(something PRIVATE OpenGL32)
	target_link_libraries(something PRIVATE GLEW::GLEW)
endif()
