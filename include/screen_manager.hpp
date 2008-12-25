#ifndef SCREEN_MANAGER_HPP
#define SCREEN_MANAGER_HPP

#include <boost/utility.hpp>

#include "game_window.hpp"
#include "scripting.hpp"

#include <boost/filesystem/path.hpp>

namespace star
{

    class screen_manager : boost::noncopyable
    {
    public:
        screen_manager(game_window& window) : window_(window)
        {}

        ~screen_manager() {}

        void load_screen(std::string const& name, script const& scr);

        void show_screen(std::string const& name);

    private:
        game_window& window_;
        interpreter intp_;
        std::map<std::string, script> screens_;
    };

}

#endif
