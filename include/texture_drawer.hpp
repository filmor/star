#ifndef STAR_TEXTURE_DRAWER_HPP
#define STAR_TEXTURE_DRAWER_HPP

#include "resource.hpp"

#include <vector>
#include <boost/utility.hpp>
#include <GL/glfw.h>

namespace star
{

    namespace detail
    {
        /// \todo Reference counting and copy semantics
        class texture : boost::noncopyable
        {
        public:
            /// Only GL_UNSIGNED_INT_8_8_8_8 data for now.
            typedef std::vector<GLuint> data_type;
            texture (data_type const& data, std::size_t width, std::size_t height);
            ~texture ();

            void bind () { glBindTexture (GL_TEXTURE_2D, _handle); }

        private:
            GLuint _handle;
        };
    }


    /// Drawing policy to draw textures on a rectangle (for now).
    class texture_drawer_policy
    {
    public:
        void load_texture (detail::texture::data_type const& data, std::size_t height,
                           std::size_t width);

    protected:
        void draw ();

    private:
        /// Texture dimensions.
        std::size_t _height, _width;
        resource<detail::texture> _texture;
    };

}

#endif

