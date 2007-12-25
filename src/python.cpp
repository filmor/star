#include "python.hpp"

#include "player.hpp"
#include "basic_types.hpp"
#include "game_window.hpp"
#include "scene.hpp"

#include "utility/function/function_v2.hpp"

#include <boost/python.hpp>

namespace star
{
namespace python
{


    /// \todo This file is pretty messy. Tidy (Split!) up!

    namespace
    {
        using namespace boost::python;

        void null (song const&)
        {}

        template <typename Function>
        void safe_python_call (Function const& func)
        {
            try
            {
                func ();
            }
            catch (error_already_set const&)
            {
                handle_exception ();
            }
        }
        
        void set_scene (scene_node_base const& s)
        {
            game_window::instance ().set_drawer (
                    boost::bind (&scene_node_base::draw, s)
                    );
        }

        void clear_scene ()
        { game_window::instance ().clear_drawer (); }

        void enqueue_init (game_window::initializer_type const& func)
        { game_window::instance ().enqueue_init (func); }

        tuple get_dimensions ()
        {
            std::pair<std::size_t, std::size_t> const& dim =
                game_window::instance ().get_dimensions ();
            return make_tuple (dim.first, dim.second);
        }

        object tuple_to_python (boost::tuples::null_type const&)
        { return tuple(); }

        template <class H, class T>
        object tuple_to_python (boost::tuples::cons<H,T> const& x)
        { return tuple(make_tuple (x.get_head ())) + tuple_to_python (x.get_tail()); }

        template <class T>
        struct tupleconverter
        {
            static PyObject* convert(T const& x)
            { return python::incref(tuple_to_python(x).ptr()); }
        };
    }

    void module_star ()
    {
        using namespace boost::python;

        ::function::export_function<player::notes_callback_type>
            ("_notes_callback_type");
        ::function::export_function<player::syllable_callback_type>
            ("_syllable_callback_type");
        // ::function::export_function<window::key_callback_type>
        //    ("_key_callback_type");

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

        /// \todo Use get_description for __getattribute__ 
        class_<song::lyrics> ("_lyrics")
            .def ("__iter__", iterator<song::lyrics> ())
            ;

        to_python_converter<song::data_type::value_type,
                            tupleconverter<song::data_type::value_type> >();

        class_<song> ("song", init<std::string> ())
            .def ("lyrics", &song::get_lyrics)
            .add_property ("description", &song::get_description)
            ;

        class_<player> ("player")
            .def ("start", &player::start)
            .def ("is_playing", &player::is_playing)
            .add_property ("notes_callback", &null, &player::set_notes_callback)
            .def ("add_syllable_callback", &player::add_syllable_callback)
            .def ("reset_syllable_callbacks", &player::reset_syllable_callbacks)
            ;

        def ("set_scene", &set_scene);
        def ("clear_scene", &clear_scene);
        def ("enqueue_init", &enqueue_init);
        def ("get_dimensions", &get_dimensions);

        ::function::register_pyobject_to_function<player::notes_callback_type> ();
        ::function::register_pyobject_to_function<player::syllable_callback_type> ();
        // ::function::register_pyobject_to_function<game_window::drawer_type> ();
    }
}
}
