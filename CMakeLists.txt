cmake_minimum_required(VERSION 3.10)

project(NtfsBrowser)

include("cmake/vs.cmake")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)
option(ENABLE_TESTING "Enable testing" OFF)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_subdirectory("3rdparty/gsl")
add_subdirectory("3rdparty/Catch2")
add_subdirectory("src")
if (ENABLE_TESTING)
enable_testing()
add_subdirectory("NTFSLibTests")
endif()
