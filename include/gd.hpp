#ifndef STAR_GD_HPP
#define STAR_GD_HPP

#include "texture_drawer.hpp"

#include <boost/filesystem/path.hpp>
#include <string>
#include <cstdlib>
#include <gd.h>

namespace star
{

    struct string_drawer : texture_drawer 
    {
        string_drawer (std::string const&, double, std::string const&);
    };

    struct png_drawer : texture_drawer
    {
        png_drawer (boost::filesystem::path const&);
    };

    /// \todo
    /// struct svg_drawer
}

#endif

