#include "python.hpp"

#include "player.hpp"
#include "basic_types.hpp"
#include "graphics_output.hpp"

#include "utility/function/function_v2.hpp"

#include <boost/python.hpp>

namespace star
{
namespace python
{

    namespace
    {
        using namespace boost::python;

        void null (song const&)
        {}
        
        void set_drawer (graphics_output::drawer_type const& func)
        { graphics_output::instance ().set_drawer (func); }

        void clear_drawer ()
        { graphics_output::instance ().clear_drawer (); }

        void enqueue_init (graphics_output::initializer_type const& func)
        { graphics_output::instance ().enqueue_init (func); }

        tuple get_dimensions ()
        {
            std::pair<std::size_t, std::size_t> const& dim =
                graphics_output::instance ().get_dimensions ();
            return make_tuple (dim.first, dim.second);
        }
    }

    void module_star ()
    {
        using namespace boost::python;

        ::function::export_function<player::notes_callback_type>
            ("_notes_callback_type");
        ::function::export_function<player::syllable_callback_type>
            ("_syllable_callback_type");
        /*::function::export_function<graphics_output::drawer_type>
           ("_drawer_type");*/

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

        def ("set_drawer", &set_drawer);
        def ("enqueue_init", &enqueue_init);
        def ("clear_drawer", &clear_drawer);
        def ("get_dimensions", &get_dimensions);

        ::function::register_pyobject_to_function<player::notes_callback_type> ();
        ::function::register_pyobject_to_function<player::syllable_callback_type> ();
        // ::function::register_pyobject_to_function<graphics_output::drawer_type> ();
    }
}
}
