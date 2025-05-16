#include <pybind11/pybind11.h>
#include "projekcikTP3.hpp"

namespace py = pybind11;

PYBIND11_MODULE(projekcikTP3, m) {
    m.doc() = "Biblioteka sygnałów TP3 z generowaniem sygnałów";

    m.def("sinus", &Sinus, "Sygnał sinusoidalny",
          py::arg("frequency"), py::arg("start_time"), py::arg("end_time"), py::arg("sample_count"));

    m.def("cosinus", &Cosinus, "Sygnał cosinusoidalny",
          py::arg("frequency"), py::arg("start_time"), py::arg("end_time"), py::arg("sample_count"));

    m.def("rectangular", &Rectangular, "Sygnał prostokątny",
          py::arg("frequency"), py::arg("start_time"), py::arg("end_time"), py::arg("sample_count"));

    m.def("sawtooth", &Sawtooth, "Sygnał piłokształtny",
          py::arg("frequency"), py::arg("start_time"), py::arg("end_time"), py::arg("sample_count"));
}

