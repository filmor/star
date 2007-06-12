#include "python.hpp"

#include "player.hpp"
#include "basic_types.hpp"

#include "utility/function/function_v2.hpp"

#include <boost/python.hpp>

namespace star
{
namespace python
{

    namespace
    {
        void null (song const&)
        {}
    }

    void module_star ()
    {
        using namespace boost::python;

        ::function::export_function<player::notes_callback_type>
            ("_notes_callback_type");
        ::function::export_function<player::syllable_callback_type>
            ("_syllable_callback_type");

        class_<note_t> ("note_t")
            .def_readonly ("value", &note_t::value)
            .def_readonly ("octave", &note_t::octave)
            ;

        typedef player::syllable_t syllable_t;

        class_<syllable_t> ("syllable_t")
            .def_readonly ("start", &syllable_t::start)
            .def_readonly ("pos", &syllable_t::pos)
            .def_readonly ("end", &syllable_t::end)
            ;

        class_<song> ("song", init<std::string> ())
            ;

        class_<player> ("player")
            .def ("start", &player::start)
            .add_property ("notes_callback", &null, &player::set_notes_callback)
            ;

        ::function::register_pyobject_to_function<player::notes_callback_type> ();
        ::function::register_pyobject_to_function<player::syllable_callback_type> ();
    }
}
}
