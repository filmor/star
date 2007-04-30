#include "song.hpp"

#include <boost/thread/thread.hpp>
#include <boost/ref.hpp>
#include <boost/bind.hpp>

namespace star
{
    song::song (song_info const& l)
    {
//        _audio_stream = l.get_audio ();
//        _lyrics = l.get_lyrics ();
    }

    void song::start (callback_type const&) const
    {
/*        using namespace boost;

        thread_group tg;
        tg.create_thread (bind (&video_output::start, vo, _video));
        tg.create_thread (bind (&audio_output::start, ao, _audio));
        tg.create_thread (bind (&lyrics_output::start, lo, _lyrics));
        tg.join_all ();*/
    }

}
