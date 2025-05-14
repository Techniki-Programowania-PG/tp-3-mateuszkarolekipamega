cmake_minimum_required(VERSION 3.14)
project(projekcikTP3 LANGUAGES CXX)

# — ustawienia C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# — wskaż interpreter Pythona i nagłówki + biblioteki deweloperskie
set(Python3_EXECUTABLE "C:/Users/kb150/anaconda3/envs/myenv/python.exe")
find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

# — podprojekty: PyBind11 i Matplot++
add_subdirectory(matplotplusplus)
add_subdirectory(pybind11)

# === 1) EXE: prosty program z main.cpp
add_executable(projekcikTP3
    src/main.cpp
)
# Matplot++ samo propaguje swoje include’y dzięki add_subdirectory
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
# bindingi mogą korzystać zarówno z PyBind11, jak i z Matplot++
target_link_libraries(projekcikTP3_python
    PRIVATE 
        matplot               # jeśli w bindingach używasz Matplot++
        pybind11::module      # zapewnia link do pythonXY.lib i include’y pybind11
)

# — umieść .pyd obok exe w build/
set_target_properties(projekcikTP3_python PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)
