#include "screen.hpp"

#include "math.hpp"
#include "game_window.hpp"

#include <boost/foreach.hpp>

namespace star
{
    namespace
    {
        matrix create_orthogonal_projection ()
        {
            return orthogonal_projection (0, 0, 0, 0, 0, 0);
        }
    }

    screen::screen () : scene_node_base (create_orthogonal_projection (), true)
    {}

    void screen::draw ()
    {
        BOOST_FOREACH(widgets_type::mapped_type& w, _widgets)
            w.second->draw_at(w.first);
    }

}


