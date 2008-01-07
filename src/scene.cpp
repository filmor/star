#include "scene.hpp"

#include <GL/glfw.h>
#include <boost/foreach.hpp>

namespace star
{

    /// \todo Add possibility to optimize by generating a display list
    void scene_node_base::draw ()
    {
        glPushMatrix ();

        glMultMatrixd (_matrix.data ().begin ());

        this->do_draw ();

        if (!_children.empty ())
            BOOST_FOREACH(ptr_type& n, _children)
                n->draw ();

        glPopMatrix ();
    }

}

