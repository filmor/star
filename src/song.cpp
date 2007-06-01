#include "song.hpp"

#include "pitch_detector.hpp"

#include <algorithm>

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
        static const duration_t resolution = 200;

        template <typename FunctionT>
        inline void call (FunctionT f)
        {
            f ();
        }
    }
            
    void song::start (song_info const& _info) const
    {
        typedef pitch_detector<fmod_detector> detector;
        detector detect;

        song_info::notes n = _info.get_notes ();
        audio_stream as = _info.get_audio_stream ();

        boost::thread_group tg;
        
        boost::xtime xs;
        boost::xtime_get (&xs, boost::TIME_UTC);

        as.play ();

        for (song_info::notes::const_iterator i = n.begin (); i != n.end (); ++i)
        {
            if (!_syllable_callbacks.empty ())
                std::for_each (_syllable_callbacks.begin (),
                               _syllable_callbacks.end (),
                               call<syllable_callback_type>
                        );

            duration_t const& duration = i->get<0> ();

            if (_notes_callback)
            {
                note_t const& note = i->get<1> ();

                duration_t const start = to_milliseconds (xs);
                duration_t const end = start + duration;

                syllable_t syl = { start, start, end };
                
                /// \todo Handle unfitting note lengthes properly
                for (; syl.pos < syl.end; syl.pos += resolution)
                {
                    add_milliseconds (xs, resolution);
                    boost::thread::sleep (xs);
                    _notes_callback (note, detect (resolution), syl);
                }
            }
        }

        as.wait ();
        tg.join_all ();
    }

}
