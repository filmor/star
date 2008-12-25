#include "screen_manager.hpp"

#include "game_window.hpp"

#include <boost/bind.hpp>
#include <GL/glfw.h>

namespace star
{

    screen_manager::screen_manager ()
    {
        set_as_drawer ();
    }

    void screen_manager::set_as_drawer ()
    {
        game_window::instance ().set_drawer (
                boost::bind (&screen_manager::draw, this)
                );
    }

    screen_manager::~screen_manager ()
    {
        game_window::instance ().clear_drawer ();
    }

    void screen_manager::set_screen (screen_ptr screen)
    {
        _current = screen;
    }

    void screen_manager::draw ()
    {
        // glClear (GL_COLOR_BIT);
        glLoadIdentity ();
        // glOrtho (blblbla);

        _current->draw ();
    }

}

