#ifndef STAR_SCREEN_HPP
#define STAR_SCREEN_HPP

#include "scene.hpp"
#include "math.hpp"

#include <map>
#include <utility>

namespace star
{

    /// \todo Pimpl?!
    struct widget
    {
        typedef std::pair<scalar, scalar> position_t;
        void draw_at (position_t);
        typedef widget* ptr_type;
        typedef const widget* const_ptr_type;
    };

    class screen : public scene_node_base
    {
    public:
        screen ();

        void fade_to (screen* other);

        void add_widget (widget::position_t p, widget::ptr_type w);

    protected:
        virtual void fade_in ();
        virtual void fade_out ();
        virtual void draw ();

    private:
        typedef std::multimap<int,
                               std::pair<widget::position_t, widget::ptr_type>
                              >
            widgets_type;

        widgets_type _widgets;
    };

}

#endif

