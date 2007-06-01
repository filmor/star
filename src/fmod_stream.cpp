#include "fmod.hpp"

#include <unistd.h>

#include <boost/thread/thread.hpp>

namespace star
{
    namespace
    {
        audio_stream::register_<fmod_stream_impl> vorbis ("ogg/vorbis");
        audio_stream::register_<fmod_stream_impl> mp3 ("mpeg/mp3");
    }
    
    fmod_stream_impl::fmod_stream_impl (std::string const& path)
    {
        STAR_FMOD_EC(get_system ().createSound (path.c_str (), 
                          FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM,
                          0, &_sound)
          );
    }

    void fmod_stream_impl::play ()
    {
        STAR_FMOD_EC(get_system ().playSound
                (FMOD_CHANNEL_FREE, _sound, false, &_channel)
                );
    }

    void fmod_stream_impl::stop ()
    {
        STAR_FMOD_EC(_channel->stop ());
    }

    duration_t fmod_stream_impl::get_pos () const
    {
        unsigned int result = 0;
        STAR_FMOD_EC(_channel->getPosition (&result, FMOD_TIMEUNIT_MS));
        return result;
    }

    void fmod_stream_impl::wait ()
    {
        unsigned int length = 0;
        STAR_FMOD_EC(_sound->getLength(&length, FMOD_TIMEUNIT_MS));
        length -= get_pos (); // should be safe
        boost::xtime xt;
        xtime_get (&xt, boost::TIME_UTC);
        add_milliseconds (xt, length);
        boost::thread::sleep (xt); // argh
    }
}

