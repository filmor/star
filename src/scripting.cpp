#include "scripting.hpp"

#include "player.hpp"
#include "basic_types.hpp"
#include "game_window.hpp"

namespace star
{
    namespace
    {
        void* alloc(void* ud, void* ptr, size_t osize, size_t nsize)
        {
            (void)ud; (void)osize;

            if (nsize == 0)
            {
                std::free(ptr);
                return 0;
            }
            else
                return std::realloc(ptr, nsize);
        }
    }

    interpreter::interpreter()
    {
        state_ = lua_newstate(&alloc, 0);
        // lua_atpanic
    }

    interpreter::~interpreter()
    {
        lua_close(state_);
    }
    
    namespace
    {
        const char* istream_reader(lua_State* L, void* data, size_t* size)
        {
            std::istream& is = *reinterpret_cast<std::istream*>(data);
            if (is)
            {
                const size_t BLOCK_SIZE = 1024;
                void* ud;
                lua_Alloc alloc = lua_getallocf(L, &ud);

                char* ret = 0;
                ret = reinterpret_cast<char*>(alloc(ud, ret, 0, BLOCK_SIZE));

                is.read(ret, BLOCK_SIZE);
                *size = is.gcount();
                
                return ret;
            }
            else
            {
                *size = 0;
                return 0;
            }
        }

        /// Stub
        std::string generate_name() { return ""; }
    }

    program interpreter::load_program(std::istream& is, std::string name)
    {
        if (name == "")
            name = generate_name();

        int err = lua_load(state_, &istream_reader, &is, name.c_str());
        switch(err)
        {
        case LUA_ERRSYNTAX:
            throw std::runtime_error("Syntax Error");
            lua_pop(state_, 1);
            break;
        case LUA_ERRMEM:
            throw std::runtime_error("Memory Error");
            lua_pop(state_, 1);
            break;
        }

        lua_setglobal(state_, name.c_str());
        return program(name);
    }

    void interpreter::run_program(program const& scr)
    {
        lua_getglobal(state_, scr.c_str());
        lua_pcall(state_, 0, LUA_MULTRET, 0);
        /// \todo Error handling
    }


/*namespace python
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

        void set_key_callback (game_window::key_callback_type const& cb)
        { game_window::instance ().set_key_callback (cb, game_window::KEY_MODE); }

        void set_char_callback (game_window::key_callback_type const& cb)
        { game_window::instance ().set_key_callback (cb, game_window::CHAR_MODE); }

        void clear_key_callback ()
        { game_window::instance ().clear_key_callback (); }

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
        ::function::export_function<game_window::key_callback_type>
            ("_key_callback_type");

        class_<note_t> ("note_t")
            .def_readonly ("value", &note_t::value)
            .def_readonly ("octave", &note_t::octave)
            ;

        typedef player::syllable_t syllable_t;

        class_<syllable_t> ("syllable_t")
           // .def_readonly ("period", &syllable_t::period)
           // .def_readonly ("pos", &syllable_t::pos)
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
        def ("set_key_callback", &set_key_callback);
        def ("set_char_callback", &set_char_callback);
        def ("clear_key_callback", &clear_key_callback);
        def ("enqueue_init", &enqueue_init);
        def ("get_dimensions", &get_dimensions);

        ::function::register_pyobject_to_function<player::notes_callback_type> ();
        ::function::register_pyobject_to_function<player::syllable_callback_type> ();
        ::function::register_pyobject_to_function<game_window::key_callback_type> ();
    }
}*/
}
