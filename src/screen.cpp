#include "screen.hpp"

#include "math.hpp"
#include "game_window.hpp"

#include <boost/foreach.hpp>

namespace star
{

    screen::screen ()
    {}

    void screen::draw ()
    {
        BOOST_FOREACH(widgets_type::value_type& m, _widgets)
        {
            widgets_type::mapped_type& w = m.second;
            w.second->draw_at(w.first);
        }
    }

}


