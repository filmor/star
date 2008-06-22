#include "player.hpp"

#include "utility/midi/midi_dispatcher.hpp"
#include "pitch_detector.hpp"

#include <algorithm>

#include <boost/thread/thread.hpp>
#include <boost/ref.hpp>
#include <boost/bind.hpp>
#include <boost/foreach.hpp>

#ifndef STAR_DETECTOR_POLICY
#define STAR_DETECTOR_POLICY ::star::fmod_detector
#include "fmod.hpp"
#endif

namespace star
{
    namespace
    {
        /// \todo Get from config
        static const duration_t resolution = 200;
    }
    
    /// \todo Rewrite using midi_dispatcher, but not now ;)
    void player::start (song const& _info) const
    {
        _playing = true;

        typedef pitch_detector<STAR_DETECTOR_POLICY> detector;
        detector detect;

        song::notes n = _info.get_notes ();
        audio_stream as = _info.get_audio_stream ();

        boost::thread_group tg;
        
        time t;

        as.play ();

        for (song::notes::const_iterator i = n.begin (); i != n.end (); ++i)
        {
            if (!_syllable_callbacks.empty ())
                BOOST_FOREACH(syllable_callback_type const& cb, _syllable_callbacks)
                    cb ();

            duration_t const& duration = i->get<0> ();

            if (_notes_callback)
            {
                note_t const& note = i->get<1> ();

                duration_t const start = t;
                duration_t const end = start + duration;

                syllable_t syl = { start, start, end };
                
                /// \todo Handle unfitting note lengthes properly
                for (; syl.pos < syl.end; syl.pos += resolution)
                {
                    t += resolution;
                    t.wait ();
                    _notes_callback (note, detect (resolution), syl);
                }
            }
        }

        as.wait ();
        tg.join_all ();

        _playing = false;
    }

}
