#ifndef STAR_SCENE_HPP
#define STAR_SCENE_HPP

#include "math.hpp"

#include <vector>
#include <boost/shared_ptr.hpp>

namespace star
{

    /**
     * Base class for scene nodes.
     *
     * The scenes are organized as trees of scene nodes which are derived from this
     * class. Every node has an orientation and location relative to its ancestors.
     */
    class scene_node_base
    {
    public:
        typedef boost::shared_ptr<scene_node_base> ptr_type;

        /**
         * Creates a scene node with translation trans and rotation rot.
         *
         * The translation vector and the rotation (as a quaternion) are combined
         * into a matrix (first translate, than rotate).
         *
         * \param trans Translation vector.
         * \param rot Rotation quaternion.
         */
        scene_node_base (vector const& trans = zero_vector (),
                         quaternion const& rot = 1)
        {
            _matrix =
                    prod (rotation_from_quaternion (rot)
                         ,translation_from_vector (trans)
                         )
                    ;
        }

        /// Virtual destructor, as this class is intended to be used runtime
        /// polymorphic.
        virtual ~scene_node_base () {}

        /// Draw the scene.
        void draw ();

        /// Add a child node to the scene. Children are drawn after their parents.
        void add_child (ptr_type child) { _children.push_back (child); }

    protected:
        /**
         * Virtual draw method to be overridden in derived classes.
         *
         * The actual frame drawing happens here. The method is not abstract, because
         * if it was there would have to be an extra class for scenes, that don't
         * draw for themselves but let their children do the work.
         */
        virtual void do_draw () {}
        
    private:
        /// Combined rotation and translation matrix.
        matrix _matrix;
        /// Child nodes.
        std::vector<ptr_type> _children;
    };

    /**
     * Policy scene node base.
     *
     * To simplify the definition of own scene nodes, this class provides a policy
     * based interface. DrawPolicies does only have to have a draw method and are
     * used by public (!) derivation. draw should thus be protected.
     *
     * \param DrawPolicy Drawing policy for this scene node. Must have a draw method.
     */
    template <class DrawPolicy>
    class scene_node : public scene_node_base
                     , public DrawPolicy
    {
    public:
        /// Forwarding constructor (obsolete with C++09).
        scene_node (vector const& trans = zero_vector (3), quaternion const& rot = 1)
            : scene_node_base (trans, rot)
        {}

    protected:
        /// Calls the policies draw function.
        virtual void do_draw () { DrawPolicy::draw (); }
    };

}

#endif

