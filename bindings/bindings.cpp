#include "effects.h"
#include <color.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <vector>

namespace py = pybind11;

PYBIND11_MODULE(FXLIB, m) {
    m.def("Zamning", [](int a, int b) { return a + b; });

    pybind11::class_<NEOFX::RGB>(m, "RGB")
    .def(py::init<double, double, double>())
    .def("__add__", [](const NEOFX::RGB& self, const NEOFX::RGB& other) { return self.operator+(other); })
    .def("__add__", [](const NEOFX::RGB& self, double& other) { return self.operator+(other); })

    .def("__sub__", [](const NEOFX::RGB& self, const NEOFX::RGB& other) { return self.operator-(other); })
    .def("__sub__", [](const NEOFX::RGB& self, double other) { return self.operator-(other); })

    .def("__mul__", [](const NEOFX::RGB& self, const NEOFX::RGB& other) { return self.operator*(other); })
    .def("__mul__", [](const NEOFX::RGB& self, double other) { return self.operator*(other); })

    .def("__truediv__", [](const NEOFX::RGB& self, const NEOFX::RGB& other) { return self.operator/(other); })
    .def("__truediv__", [](const NEOFX::RGB& self, double other) { return self.operator/(other); })

    .def("__str__", &NEOFX::RGB::str)
    .def("__repr__", &NEOFX::RGB::str)

    .def("from_HSV", &NEOFX::RGB::from_HSV)
    .def_readwrite("R", &NEOFX::RGB::R)
    .def_readwrite("G", &NEOFX::RGB::G)
    .def_readwrite("B", &NEOFX::RGB::B);

    pybind11::class_<NEOFX::ColorRamp>(m, "ColorRamp")
    .def(py::init<std::vector<NEOFX::RGB>, std::vector<double>>())
    .def("__getitem__", &NEOFX::ColorRamp::operator[]);
    
}