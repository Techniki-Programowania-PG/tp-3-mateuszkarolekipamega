cmake_minimum_required(VERSION 3.14)
project(projekcikTP3 LANGUAGES CXX)

# --- Wymagania C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(Python3_EXECUTABLE "C:/Users/kb150/anaconda3/envs/myenv/python.exe")
find_package(Python3 REQUIRED COMPONENTS Interpreter Development)


# --- Lokalna wersja pybind11
add_subdirectory(pybind11)  # nie używaj find_package(pybind11)

# --- Znajdź Pythona (do include_dirs)
find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

# --- Katalogi nagłówków
include_directories(
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/src
  ${PROJECT_SOURCE_DIR}/python_bindings
  ${Python3_INCLUDE_DIRS}
)

# --- Tworzenie modułu Pythona (.pyd)
pybind11_add_module(
  projekcikTP3
  python_bindings/bindings.cpp
  src/projekcikTP3.cpp
)

# --- Folder wyjściowy
set_target_properties(projekcikTP3 PROPERTIES
  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)
