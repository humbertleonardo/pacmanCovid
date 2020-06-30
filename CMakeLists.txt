cmake_minimum_required(VERSION 3.0.0)
project(PacmanCovid VERSION 0.1.0)

include(CTest)
enable_testing()

set(CMAKE_MODULE_PATH build/CMakeFiles/PacmanCovid.dir)

include_directories(${SDL2_INCLUDE_DIRS})

find_package(SDL2 REQUIRED)

add_executable(PacmanCovid main.cpp lib/libraries.h lib/libraries.cpp)
target_link_libraries(PacmanCovid ${SDL2_LIBRARIES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)


