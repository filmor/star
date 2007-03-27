#ifndef STAR_FMOD_AUDIO_HPP
#define STAR_FMOD_AUDIO_HPP

namespace star
{

    class fmod_audio
    {
        FMOD::System& get_system ()
        {
            if (_system == 0)
                int result = FMOD::System_Create (_system);
            return _system;
        }
        static FMOD::System* _system;
    };

}

#endif

