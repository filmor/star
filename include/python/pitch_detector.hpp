#ifndef STAR_PYTHON_PITCH_DETECTOR_HPP
#define STAR_PYTHON_PITCH_DETECTOR_HPP

#include "../pitch_detector.hpp"
#include "../basic_types.hpp"

#include <boost/python.hpp>

namespace star
{
namespace python
{

    void module_audio ()
    {
        using namespace boost::python;

        typedef pitch_detector<STAR_DETECTOR_POLICY> detector;

        class_<note> ("note")
            .def_readonly ("value", &note::value)
            .def_readonly ("octave", &note::octave)
            ;

        class_<detector> ("pitch_detector")
            .def ("__call__", &detector::operator())
            ;

    }
}
}

#endif
