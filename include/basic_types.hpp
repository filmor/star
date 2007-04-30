#ifndef STAR_BASIC_TYPES_HPP
#define STAR_BASIC_TYPES_HPP

#include <cstddef>

namespace star
{

    struct note
    {
        float value;
        unsigned char octave;
    };

    struct notes
    {
        enum { C = 0, Cis = 1, D = 2, Dis = 3, E = 4, F = 5
             , Fis = 6, G = 7, Gis = 8, A = 9, Ais = 10, B = 11 };
    };

    struct coords
    {
        float x;
        float y;
        float z;
    };

    typedef std::size_t duration_t;

}

#endif
