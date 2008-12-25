#ifndef STAR_SCREEN_MANAGER_HPP
#define STAR_SCREEN_MANAGER_HPP

#include "screen.hpp"

#include <boost/shared_ptr.hpp>

namespace star
{

    class screen_manager
    {
    public:
        typedef boost::shared_ptr<screen> screen_ptr;
        typedef int fader_type;

        // Takes control over game_window
        screen_manager ();
        ~screen_manager ();

        void set_as_drawer ();
        
        void set_screen (screen_ptr screen, fader_type fader = 0);

    private:
        void draw ();
        screen_ptr _current;
    };
}

#endif
