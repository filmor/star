#include "screen_manager.hpp"

namespace bf = boost::filesystem;

namespace star
{

    screen_manager::screen_manager(game_window& window) : window_(window)
    {
        interpreter::state_type L = intp_.get_state();

        lua_pushnewlightuserdata(L, reinterpret_cast<void*> (this));
        lua_setglobal(L, "_screen_object");

        lua_pushcfunction(L, register_keyboard_handler);
        lua_setglobal(L, "register_keyboard_handler");

        lua_pushcfunction(L, register_frame_handler);
        lua_setglobal(L, "register_frame_handler");
    }

    void screen_manager::load_screen(std::string const& name, std::istream& scr)
    {
        screens_[name] = intp_.load_program(scr, name);
    }

    void screen_manager::show_screen(std::string const& name)
    {
        // window_.set_drawer(boost::bind(draw_screen // etc.));
        // ));
    }

}

