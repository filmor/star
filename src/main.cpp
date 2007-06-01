#include <boost/python.hpp>
#include <boost/filesystem.hpp>

#include <iostream>

#include "fmod.hpp"

#define STAR_DETECTOR_POLICY fmod_detector

#include "python-base.hpp"

namespace bp = boost::python;
namespace bf = boost::filesystem;

using namespace star;

int main (int argc, char** argv)
{
    try
    {
        Py_Initialize ();
        PySys_SetArgv (argc, argv);

        bp::object global = bp::import ("__main__").attr ("__dict__");

        // Create the pseudo built-in module _star
        bp::object star (bp::handle<> (PyModule_New ("_star")));
        global["__builtins__"].attr ("__dict__")["_star"] = star;

        {
            bp::scope s (star);
            // python::module_audio ();
            python::module_base ();
        }

        bf::path main_py ("python/main.py");

    /// Hand the control to the main python script
        bp::exec_file (bp::str(main_py.native_file_string ()), global, global);
    }
    catch (boost::python::error_already_set const&)
    {
        PyErr_Print ();
    }

    Py_Finalize ();
}
