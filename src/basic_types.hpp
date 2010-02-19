#ifndef STAR_BASIC_TYPES_HPP
#define STAR_BASIC_TYPES_HPP

#include <cstddef>
#include <boost/integer.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/xtime.hpp>

namespace star
{

    /// Struct to hold a note value (as a float for higher precision) and the octave.
    /// The value corresponds to the values declared in #notes.
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

    using boost::posix_time::time_period;
    using boost::posix_time::time_iterator;
    using boost::posix_time::milliseconds;
    typedef boost::posix_time::millisec time_duration;
    typedef boost::posix_time::ptime time_point;

}

#endif
