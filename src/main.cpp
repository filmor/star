#include <boost/python.hpp>
#include <boost/filesystem.hpp>

#include <iostream>

#include "fmod.hpp"

#define STAR_DETECTOR_POLICY fmod_detector
#include "python/pitch_detector.hpp"
#include "python/base.hpp"

namespace bp = boost::python;
namespace bf = boost::filesystem;

using namespace star;

int main (int argc, char** argv)
{
    Py_Initialize ();
    PySys_SetArgv (argc, argv);

    bp::object main_module = bp::import ("__main__");
    bp::object global = main_module.attr("__dict__");

    bp::exec (  "import __builtin__\n"
                "_star = type(__builtin__)('_star')\n"
                "del __builtin__"
             , global, global);

    bp::object star = global["_star"];
    {
        bp::scope s (star);
        // python::module_audio ();
        python::module_base ();
    }

    bf::path main_py ("python/main.py");

    bp::exec_file (bp::str(main_py.native_file_string ()), global, global);

    Py_Finalize ();
}
