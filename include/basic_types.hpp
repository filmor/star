#ifndef STAR_BASIC_TYPES_HPP
#define STAR_BASIC_TYPES_HPP

#include <cstddef>
#include <boost/integer.hpp>
#include <boost/thread/xtime.hpp>

namespace star
{

    struct note_t
    {
        float value;
        boost::uint_t<4>::fast octave;
    };

    struct notes
    {
        enum { C = 0, Cis = 1, D = 2, Dis = 3, E = 4, F = 5
             , Fis = 6, G = 7, Gis = 8, A = 9, Ais = 10, B = 11 };
    };

    struct coord_t
    {
        float x;
        float y;
        float z;
    };

    /// Holds a time duration im milliseconds.
    /// 24 Bit are enough for about 4 hours.
    typedef boost::uint_t<24>::fast duration_t;

    inline void add_milliseconds (boost::xtime& xt, duration_t milliseconds)
    {
        xt.sec += milliseconds / 1000;
        xt.nsec += (milliseconds % 1000) * 1000000;
    }

    inline duration_t to_milliseconds (boost::xtime const& xt)
    {
        return xt.sec * 1000 + xt.nsec / 1000000;
    }

}

#endif
