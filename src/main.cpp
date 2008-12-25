#include <boost/python.hpp>
#include <boost/filesystem.hpp>
#include <iostream>
#include <stdexcept>

#include "fmod.hpp"
#include "game_window.hpp"
#include "screen_manager.hpp"

#define STAR_DETECTOR_POLICY fmod_detector

#include "python.hpp"

namespace bp = boost::python;
namespace bf = boost::filesystem;

using namespace star;

void thread_main ()
{
    bp::str path (bf::path ("python/main.py").file_string ());

    bp::object global = bp::import ("__main__").attr ("__dict__");
    bp::object builtin = bp::import ("__builtin__").attr ("__dict__");

    screen_manager manager;

    /// Create the pseudo built-in module _star
    bp::object star (bp::handle<> (PyModule_New ("_star")));
    builtin["_star"] = star;
    {
        bp::scope s (star);
        python::module_star ();
        python::module_star_graphics ();
    }

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
        std::cerr << "Error in Program thread, bitch!" << std::endl;
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

        // Setup configuration data
        config& cfg = config::instance ();

        cfg.add_source (new command_line_source (argc, argv));
        try
        {
            cfg.add_source (new python_source (cfg.get<bf::path> ("config_file")));
        }
        catch (file_not_found&) {}

        // Give the configuration data to program_thread
        boost::thread program_thread (&thread_main);

        game_window::instance ().draw ();

        /// \todo Handle closing of the graphics window
        program_thread.join ();
    }
    catch (boost::python::error_already_set const&)
    {
        PyErr_Print ();
    }

//  boost-devel ml said this won't work. I'll believe them for now.
//    Py_Finalize ();
}
