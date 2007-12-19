#ifndef STAR_SCENE_HPP
#define STAR_SCENE_HPP

#include "math.hpp"

#include <GL/glfw.h>
#include <vector>
#include <boost/shared_ptr.hpp>

namespace star
{

    class scene_node_base
    {
    public:
        typedef boost::shared_ptr<scene_node_base> ptr_type;

        scene_node_base (vector const& trans = zero_vector (),
                         quaternion const& rot = 1)
            : _matrix ()
        {
            _matrix =
                    prod (translation_from_vector (trans) 
                         ,rotation_from_quaternion (rot)
                         )
                    ;
        }

        virtual ~scene_node_base () {}

        void draw ();

        void add_child (ptr_type child) { _children.push_back (child); }

    protected:
        virtual void do_draw () {}
        
    private:
        matrix _matrix;
        std::vector<ptr_type> _children;
    };

    template <class DrawPolicy>
    class scene_node : public scene_node_base
                     , public DrawPolicy
    {
    public:
        scene_node (vector const& trans = zero_vector (3), quaternion const& rot = 1)
            : scene_node_base (trans, rot)
        {}

    protected:
        virtual void do_draw () { DrawPolicy::draw (); }
    };

}

#endif

