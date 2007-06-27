#include <boost/python.hpp>
#include <boost/filesystem.hpp>

#include "fmod.hpp"
#include "graphics_output.hpp"

#define STAR_DETECTOR_POLICY fmod_detector

#include "python.hpp"

namespace bp = boost::python;
namespace bf = boost::filesystem;

using namespace star;

void python_thread (bp::str path, bp::object global)
{
    try
    {
        bp::exec_file (path, global, global);
    }
    catch (boost::python::error_already_set const&)
    {
        PyErr_Print ();
    }

    graphics_output::instance ().close_window ();
}

int main (int argc, char** argv)
{
    try
    {
        PyEval_InitThreads ();
        Py_Initialize ();
        PySys_SetArgv (argc, argv);

        bp::object global = bp::import ("__main__").attr ("__dict__");
        bp::object builtin = bp::import ("__builtin__").attr ("__dict__");

        // Create the pseudo built-in module _star
        bp::object star (bp::handle<> (PyModule_New ("_star")));
        builtin["_star"] = star;
        {
            bp::scope s (star);
            python::module_star ();
        }

        bf::path main_py ("python/main.py");

        boost::thread py_thread (
                boost::bind (&python_thread,
                             bp::str (main_py.native_file_string ()),
                             global)
                );

        graphics_output::instance ().draw ();

        /// \todo Handle closing of the graphics window
        py_thread.join ();
    }
    catch (boost::python::error_already_set const&)
    {
        PyErr_Print ();
    }

    Py_Finalize ();
}
