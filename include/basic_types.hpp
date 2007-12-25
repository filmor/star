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

    /// Holds a time duration im milliseconds.
    /// 24 Bit are enough for about 4 hours.
    typedef boost::uint_t<24>::fast duration_t;

    /**
     * Time class.
     *
     * Simplifies the use of the boost::xtime struct and functions.
     */
    class time
    {
    public:
        /// Initializes with "now".
        time () { boost::xtime_get (&_xt, boost::TIME_UTC); }

        time (time const& other) : _xt (other._xt) {}

        /// \return Time in milliseconds.
        operator duration_t () { return _xt.sec * 1000 + _xt.nsec / 1000000; }

        /// Adds a duration to the time.
        time& operator+= (duration_t milliseconds)
        {
            _xt.sec += milliseconds / 1000;
            _xt.nsec += (milliseconds % 1000) * 1000000;
            return *this;
        }

        /// Let's the calling thread fall asleep until the point of time is over.
        void wait () const { boost::thread::sleep (_xt); }

    protected:
        boost::xtime& get_xtime () { return _xt; }
        boost::xtime const& get_xtime () const { return _xt; }

    private:
        /// Storage for the point of time
        boost::xtime _xt;
    };

}

#endif
