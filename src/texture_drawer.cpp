#include "texture_drawer.hpp"

#include <GL/glfw.h>

namespace star
{

    texture::texture (data_type const& data, std::size_t width, std::size_t height)
    {
        glGenTextures (1, &_handle);
        glBindTexture (GL_TEXTURE_2D, _handle);
        glTexImage2D (GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGBA,
                      GL_UNSIGNED_INT_8_8_8_8, &data[0]);
    }

    texture::~texture ()
    {
        glDeleteTextures (1, &_handle);
    }

    void texture_drawer::do_draw ()
    {
        if (!_texture)
            return;
        _texture->bind ();
        glBegin (GL_QUADS);
        glTexCoord2f (0., 0.);
        glVertex2f (0., 0.);
        glTexCoord2f (0., 1.);
        glVertex2f (0., _height);
        glTexCoord2f (1., 1.);
        glVertex2f (_width, _height);
        glTexCoord2f (1., 0.);
        glVertex2f (_width, _height);
        glEnd ();
    }

}
