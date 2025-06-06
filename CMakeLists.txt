cmake_minimum_required(VERSION 3.16)
project(space_destroy)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

file(GLOB_RECURSE SOURCES "src/*.cpp" "main.cpp")

file(GLOB_RECURSE HEADERS "include/*.h" "include/*.hpp")

file(GLOB_RECURSE ASSETS "Assets/*")

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${ASSETS})

find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system sfml-audio)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/Assets"
)
