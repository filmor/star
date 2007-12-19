#ifndef STAR_TEXTURE_DRAWER_HPP
#define STAR_TEXTURE_DRAWER_HPP

// #include "scene.hpp"
#include "resource.hpp"

#include <vector>
#include <boost/utility.hpp>
#include <GL/glfw.h>

namespace star
{

    /// \todo Reference counting and copy semantics
    class texture : boost::noncopyable
    {
    public:
        /// Only GL_UNSIGNED_INT_8_8_8_8 for now.
        typedef std::vector<GLuint> data_type;
        texture (data_type const& data, std::size_t width, std::size_t height);
        ~texture ();

        void bind () { glBindTexture (GL_TEXTURE_2D, _handle); }

    private:
        GLuint _handle;
    };

    class texture_drawer
    {
    public:
        texture_drawer (texture::data_type const& data, std::size_t height,
                        std::size_t width)
        {
            load_texture (data, height, width);
        }

        texture_drawer () {}

        void load_texture (texture::data_type const& data, std::size_t height,
                           std::size_t width)
        {
            if (bool (_texture) || data.size () < width * height)
                return;
            _texture.init (data, height, width);
            _width = width;
            _height = height;
        }
        
        void do_draw ();

    private:
        std::size_t _height, _width;
        resource<texture> _texture;
    };

}

#endif

