cmake_minimum_required(VERSION 3.16)
project(space_destroy)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Dodaj katalogi z plikami nagłówkowymi
include_directories(include)

# Dodaj wszystkie pliki źródłowe
file(GLOB_RECURSE SOURCES "src/*.cpp" "main.cpp")

# Dodaj pliki nagłówkowe jako źródła (opcjonalnie)
file(GLOB_RECURSE HEADERS "include/*.h" "include/*.hpp")

# Dodaj pliki zasobów (opcjonalnie)
file(GLOB_RECURSE ASSETS "Assets/*")

# Dodaj plik wykonywalny
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${ASSETS})

# Znajdź bibliotekę SFML
find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)

# Połącz z bibliotekami SFML
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system sfml-audio)

# Ustaw katalog roboczy na katalog z zasobami (opcjonalnie)
set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/Assets"
)
