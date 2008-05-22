#include <boost/python.hpp>
#include <boost/filesystem.hpp>
#include <iostream>
#include <stdexcept>

#include "fmod.hpp"
#include "game_window.hpp"

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
    catch (std::exception const& exc)
    {
        std::cerr << exc.what () << std::endl;
    }
    catch (...)
    {
        std::cerr << "Error in Python thread, bitch!" << std::endl;
    }

    game_window::instance ().close ();
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

        /// Create the pseudo built-in module _star
        bp::object star (bp::handle<> (PyModule_New ("_star")));
        builtin["_star"] = star;
        {
            bp::scope s (star);
            python::module_star ();
            python::module_star_graphics ();
        }

        bf::path main_py ("python/main.py");

        boost::thread py_thread (
                boost::bind (&python_thread,
                             bp::str (main_py.native_file_string ()),
                             global)
                );

        game_window::instance ().draw ();

        /// \todo Handle closing of the graphics window
        py_thread.join ();
    }
    catch (boost::python::error_already_set const&)
    {
        PyErr_Print ();
    }

//  boost-devel ml said this won't work. I'll believe them for now.
//    Py_Finalize ();
}
