cmake_minimum_required(VERSION 3.10)
project(projekcikTP3)

# Dodaj folder 'include' z pybind11
include_directories(${CMAKE_SOURCE_DIR}/pybind11/include)

# Dodaj folder 'include' z Pythona (Anaconda)
include_directories("C:/Users/kb150/anaconda3/include")

# Znajdź Python3
find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

# Dodaj katalogi nagłówków Pythona
include_directories(${Python3_INCLUDE_DIRS})
link_directories(${Python3_LIBRARY_DIRS})

# Zdefiniuj bibliotekę dla modułu Pythona
add_library(projekcikTP3 MODULE python_bindings/bindings.cpp)

# Linkuj z pybind11 oraz Pythona
target_link_libraries(projekcikTP3 PRIVATE pybind11::module Python3::Python)
