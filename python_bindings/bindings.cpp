#include <pybind11/pybind11.h>
#include "projekcikTP3.hpp"

namespace py = pybind11;

PYBIND11_MODULE(projekcikTP3, m) {
    m.doc() = "Moja biblioteka w C++";
    m.def("dodawanko", &dodawanko, "Funkcja dodająca dwa liczby");
}