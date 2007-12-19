#include "gd.hpp"

namespace star
{
    namespace
    {
        texture::data_type convert_image_to_texture (gdImagePtr im)
        {
            texture::data_type res (im->sx * im->sy);
            texture::data_type::iterator iterator = res.begin ();
            for (int y = 0; y < im->sy; ++y)
                for (int x = 0; x < im->sx; ++x)
                    *(iterator++) =
                        gdImageGetTrueColorPixel (im, x, im->sy - y) << 8 | 0xff;
            return res;
        }
    }

    
    string_drawer::string_drawer (std::string const& string, double size,
                                  std::string const& font)
    {
        int brect[8];
        char* font_s = const_cast<char*> (font.c_str ());
        char* string_s = const_cast<char*> (string.c_str ());
        char* err = gdImageStringFT (0, &brect[0], 0, font_s, size, 0., 0, 0, 
                                     string_s);
        unsigned x = brect[2] - brect[6] + 6;
        unsigned y = brect[3] - brect[7] + 6;
        gdImagePtr im = gdImageCreate (x, y);
        int foreground_color = gdImageColorResolve (im, 0xff, 0xff, 0xff);
        if (foreground_color)
            ;
        int background_color = gdImageColorResolveAlpha (im, 0, 0, 0, 0x7f);
        err = gdImageStringFT (im, &brect[0], background_color, font_s, size,
                               0.0, 3 - brect[6], 3 - brect[7], string_s);
        load_texture (convert_image_to_texture (im), gdImageSX(im), gdImageSY(im));
        gdImageDestroy (im);
    }
    
}
