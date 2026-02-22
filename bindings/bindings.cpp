#include "effects.h"
#include <color.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <vector>

namespace py = pybind11;

PYBIND11_MODULE(FXLIB, m) {
    m.def("Zamning", [](int a, int b) { return a + b; });

    pybind11::class_<RGB>(m, "RGB")
    .def(py::init<double, double, double>())
    .def("__add__", [](const RGB& self, const RGB& other) { return self.operator+(other); })
    .def("__add__", [](const RGB& self, double& other) { return self.operator+(other); })

    .def("__sub__", [](const RGB& self, const RGB& other) { return self.operator-(other); })
    .def("__sub__", [](const RGB& self, double other) { return self.operator-(other); })

    .def("__mul__", [](const RGB& self, const RGB& other) { return self.operator*(other); })
    .def("__mul__", [](const RGB& self, double other) { return self.operator*(other); })

    .def("__truediv__", [](const RGB& self, const RGB& other) { return self.operator/(other); })
    .def("__truediv__", [](const RGB& self, double other) { return self.operator/(other); })

    .def("__str__", &RGB::str)
    .def("__repr__", &RGB::str)

    .def("from_HSV", &RGB::from_HSV)
    .def_readwrite("R", &RGB::R)
    .def_readwrite("G", &RGB::G)
    .def_readwrite("B", &RGB::B);

    pybind11::class_<NEOFX::ColorRamp>(m, "ColorRamp")
    .def(py::init<std::vector<RGB>, std::vector<double>>())
    .def("__getitem__", &NEOFX::ColorRamp::operator[]);
    
}