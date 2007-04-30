#include "fmod.hpp"

#include <boost/preprocessor.hpp>

#define EC(expr) \
    error_check (BOOST_PP_STRINGIZE(expr), (expr))

namespace star
{
    audio_stream::register_<fmod_stream_impl> _reg ("x-application/ogg");
    
    fmod_stream_impl::fmod_stream_impl (std::string const& path)
    {
        EC(get_system ().createSound (path.c_str (), 
                            FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM,
                            0, &_sound)
          );
    }

    void fmod_stream_impl::play ()
    {
        EC(get_system ().playSound (FMOD_CHANNEL_FREE, _sound, false, &_channel));
    }

    void fmod_stream_impl::stop ()
    {
        EC(_channel->stop ());
    }

    duration_t fmod_stream_impl::get_pos () const
    {
        unsigned int result = 0;
        EC(_channel->getPosition (&result, FMOD_TIMEUNIT_MS));
        return result;
    }

}

