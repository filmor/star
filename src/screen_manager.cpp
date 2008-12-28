#include "screen_manager.hpp"

namespace bf = boost::filesystem;

namespace star
{

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

