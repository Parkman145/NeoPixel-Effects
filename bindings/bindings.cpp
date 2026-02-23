#include "effects.h"
#include <color.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>
#include <vector>

namespace py = pybind11;

PYBIND11_MODULE(FXLIB, m) {
    m.def("Zamning", [](int a, int b) { return a + b; });

    pybind11::class_<NEOFX::RGB>(m, "RGB")
    .def(py::init<double, double, double>())
    .def("to_array", &NEOFX::RGB::to_array)
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

    pybind11::class_<NEOFX::solid>(m, "solid")
    .def(py::init<NEOFX::RGB>())
    .def("__call__", &NEOFX::solid::operator())
    .def_readwrite("color", &NEOFX::solid::color);

    pybind11::class_<NEOFX::cycle>(m, "cycle")
    .def(py::init<NEOFX::ColorRamp, double>())
    .def("__call__", &NEOFX::cycle::operator())
    .def_readwrite("ramp", &NEOFX::cycle::ramp)
    .def_readwrite("speed", &NEOFX::cycle::speed);

    pybind11::class_<NEOFX::radial>(m, "radial")
    .def(py::init<NEOFX::ColorRamp, double, double, double, double>())
    .def("__call__", &NEOFX::radial::operator())
    .def_readwrite("ramp", &NEOFX::radial::ramp)
    .def_readwrite("speed", &NEOFX::radial::speed)
    .def_readwrite("scale", &NEOFX::radial::scale)
    .def_readwrite("center_x", &NEOFX::radial::center_x)
    .def_readwrite("center_y", &NEOFX::radial::center_y);


    m.def("batch_process", &NEOFX::batch_process);
    m.def("batch_process_array", &NEOFX::batch_process_array);

    m.attr("rainbow") = NEOFX::rainbow;

    m.attr("red") = NEOFX::red;
    m.attr("orange") = NEOFX::orange;
    m.attr("yellow") = NEOFX::yellow;
    m.attr("green") = NEOFX::green;
    m.attr("blue") = NEOFX::blue;
    m.attr("purple") = NEOFX::purple;
    m.attr("white") = NEOFX::white;
    m.attr("black") = NEOFX::black;
    
}