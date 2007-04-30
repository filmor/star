#include "song.hpp"

#include "pitch_detector.hpp"

#include <boost/thread/thread.hpp>
#include <boost/thread/xtime.hpp>
#include <boost/ref.hpp>
#include <boost/bind.hpp>

#include "fmod.hpp"
#define STAR_DETECTOR_POLICY fmod_detector

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

    song::song (song_info const& l)
        : _info (l)
    {}

    void song::start (callback_type const& cb) const
    {
        typedef pitch_detector<fmod_detector> detector;
        detector dt;

        song_info::notes n = _info.get_notes ();
        audio_stream as = _info.get_audio_stream();

        boost::thread_group tg;
        
        /// notes_plane callback
        /// lyrics_plane callback

        boost::xtime xs;
        boost::xtime_get (&xs, boost::TIME_UTC);
        as.play ();
        /// synchronize now and then
        for (song_info::notes::const_iterator i = n.begin (); i != n.end (); ++i)
        {
            add_milliseconds (xs, i->get<0> ());
            note n = { i->get<1> (), 0 };
            note sn = dt (100u);
            cb (n, sn, 0);
            boost::thread::sleep (xs);
        }
        tg.join_all ();
    }

}
