#include <boost/python.hpp>
#include <boost/filesystem.hpp>

#include "fmod.hpp"
#include "graphics_output.hpp"

#define STAR_DETECTOR_POLICY fmod_detector

#include "python.hpp"

namespace bp = boost::python;
namespace bf = boost::filesystem;

using namespace star;

int main (int argc, char** argv)
{
    graphics_output& out = graphics_output::instance ();
    try
    {
        PyEval_InitThreads ();
        Py_Initialize ();
        PySys_SetArgv (argc, argv);

        bp::object global = bp::import ("__main__").attr ("__dict__");

        /// Create the pseudo built-in module _star
        /// \todo __builtins__ is forbidden. Use __builtin__ instead.
        bp::object star (bp::handle<> (PyModule_New ("_star")));
        global["__builtins__"].attr ("__dict__")["_star"] = star;

        {
            bp::scope s (star);
            python::module_star ();
        }

        // out.open_window (640, 480, true);
        out.draw ();

        bf::path main_py ("python/main.py");

    /// Hand the control to the main python script
        bp::exec_file (bp::str(main_py.native_file_string ()), global, global);
    }
    catch (boost::python::error_already_set const&)
    {
        PyErr_Print ();
    }

    out.close_window ();

    Py_Finalize ();
}
