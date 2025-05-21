cmake_minimum_required(VERSION 3.14)
project(projekcikTP3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(Python3_EXECUTABLE "C:/Users/kb150/AppData/Local/Programs/Python/Python313/python.exe")
find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

add_subdirectory(matplotplusplus)
add_subdirectory(pybind11)

add_executable(projekcikTP3
    src/main.cpp
)

target_link_libraries(projekcikTP3
    PRIVATE matplot
)

target_include_directories(projekcikTP3
    PRIVATE
        ${PROJECT_SOURCE_DIR}/matplotplusplus/dist/include
)

pybind11_add_module(projekcikTP3_python
    python_bindings/bindings.cpp
    src/projekcikTP3.cpp
)

target_include_directories(projekcikTP3_python
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(projekcikTP3_python
    PRIVATE 
        matplot
        pybind11::module
)

set_target_properties(projekcikTP3_python PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)
