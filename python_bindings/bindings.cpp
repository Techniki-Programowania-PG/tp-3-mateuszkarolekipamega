#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/complex.h>
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

          // Ensure DFT is a function, not a class or object
m.def("DFT", &DFT, "Oblicza i wypisuje DFT",
py::arg("input"));

m.def("I_DFT", [](const std::vector<std::pair<double, double>>& input) {
    std::vector<std::complex<double>> spectrum;
    for (const auto& [re, im] : input) {
        spectrum.emplace_back(re, im);
    }
    I_DFT(spectrum); // Nie zwraca, tylko wypisuje
});
}
 

