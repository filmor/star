#ifndef STAR_PYTHON_BASE_HPP
#define STAR_PYTHON_BASE_HPP

#include "../song.hpp"

#include "function/function_v2.hpp"

#include <boost/python.hpp>

namespace star
{
namespace python
{

    void module_base ()
    {
        using namespace boost::python;

        ::function::export_function<song::callback_type> ("_callback_type");

        class_<song_info> ("song_info", init<std::string> ())
            ;

        class_<song> ("song", init<song_info> ())
            .def ("start", &song::start)
            ;

        ::function::register_pyobject_to_function<song::callback_type> ();
    }
}
}

#endif
