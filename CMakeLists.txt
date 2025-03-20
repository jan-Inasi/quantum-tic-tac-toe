cmake_minimum_required(VERSION 3.14)
project(quantum-tic-tac-toe VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
  CACHE STRING "Vcpkg toolchain file")


include(CTest)
enable_testing()

include(./vcpkg/scripts/buildsystems/vcpkg.cmake)

if (WIN32)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_WIN32_WINNT=0x0601 /Wall")
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -pthread")
endif()


find_package(unofficial-http-parser REQUIRED)
find_package(fmt REQUIRED)
find_package(restinio REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

find_package(Catch2 CONFIG REQUIRED)

add_subdirectory(app)
add_subdirectory(tests)
add_subdirectory(lib)
