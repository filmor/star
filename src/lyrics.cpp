#include "lyrics.hpp"

#include <boost/thread/thread.hpp>
#include <boost/thread/xtime.hpp>
#include <boost/iterator/zip_iterator.hpp>

namespace star
{

    namespace
    {
        inline void add_milliseconds (boost::xtime& xt, short milliseconds)
        {
            xt.sec += milliseconds / 1000;
            xt.nsec += (milliseconds % 1000) * 1000;
        }
    } 

    void lyrics::start (std::ostream& os, note_callback cb) const
    {
        std::vector<boost::xtime> times;


        std::ostream::sentry guard (os);

        boost::thread_group tg;

        for (text::const_iterator i = _lyrics.begin (); i != _lyrics.end (); ++i)
        {
            syllable const& s = *i;
            boost::xtime xt;
            boost::xtime_get (&xt, boost::TIME_UTC);
            os << s.get<2> () << std::flush;
            if (s.get<2> () != "")
                tg.create_thread (cb (s.get<0> (), s.get<1> ()));
            tg.join_all ();
            add_milliseconds (xt, s.get<0> ());
            boost::thread::sleep (xt);
        }
    }
}


