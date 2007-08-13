#include "fmod.hpp"

#include <fmodex/fmod_errors.h>
#include <iostream>

namespace star
{
namespace detail
{
    void fmod_base::error_check (std::string const& expr, FMOD_RESULT result) const
    {
        if (result != FMOD_OK)
        {
            std::cerr << '"' << expr << "\":\n\t" << FMOD_ErrorString(result)
                      << std::endl;
            throw fmod_exception (result);
        }
    }

    FMOD::System* fmod_base::_system = 0;

    FMOD::System& fmod_base::get_system ()
    {
        if (_system == 0)
        {
            FMOD_RESULT result = FMOD::System_Create (&_system);
            error_check ("", result);

//            error_check ("", _system->setOutput (FMOD_OUTPUTTYPE_SOUNDMANAGER));

            result = _system->setSoftwareFormat (44100, FMOD_SOUND_FORMAT_PCM16
                                                , 2, 0, FMOD_DSP_RESAMPLER_LINEAR);
            error_check ("", result);

            result = _system->init(32, FMOD_INIT_NORMAL, 0);
            error_check ("", result);
        }

        return *_system;
    }

}

    fmod_exception::fmod_exception (FMOD_RESULT result) throw ()
        : std::runtime_error (FMOD_ErrorString (result))
    {}

}

