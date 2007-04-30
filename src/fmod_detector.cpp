#include "fmod.hpp"
#include <cstring> // memset

#include <boost/preprocessor.hpp>

#define EC(expr) \
    error_check (BOOST_PP_STRINGIZE(expr), (expr))

namespace star
{

    fmod_detector::fmod_detector ()
    {
        FMOD_CREATESOUNDEXINFO exinfo;

        std::memset ((void*) &exinfo, 0, sizeof (FMOD_CREATESOUNDEXINFO));
        exinfo.cbsize = sizeof (FMOD_CREATESOUNDEXINFO);
        exinfo.numchannels = 2;
        exinfo.defaultfrequency = 44100;
        exinfo.format = FMOD_SOUND_FORMAT_PCM16;
        exinfo.length = 44100 * 0.2; 

        FMOD::System& system = get_system ();

        // system_lock_type lock (system_mutex);

        EC(system.createSound (0, FMOD_2D | FMOD_SOFTWARE | FMOD_LOOP_NORMAL
                                     | FMOD_OPENUSER, &exinfo, &_sound));

        EC(system.recordStart (_sound, true));

        EC(system.playSound (FMOD_CHANNEL_REUSE, _sound, false, &_channel));

        EC(_channel->setVolume (0));
    }

    fmod_detector::frequency_type fmod_detector::get_frequency
        (std::size_t channel, long d)
    {
        static const std::size_t ssize = 2048;
        float spectrum[ssize];

        EC(_channel->getSpectrum (spectrum, ssize, channel,
                                  FMOD_DSP_FFT_WINDOW_TRIANGLE));

        /// \todo Echte Peaksuchfunktion (Ableitung = 0?)
        float peak_height = spectrum[0];
        std::size_t peak_index = 0;

        for (std::size_t i = 1; i < ssize; ++i)
            if (spectrum[i] > peak_height)
            {
                peak_height = spectrum[i];
                peak_index = i;
            }

        // Richtig böser Hack
        return peak_height > 0.005f ? peak_index * (22050.0 / ssize) : 0;
    }

}

