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
            throw fmod_exception (result);
    }

    FMOD::System* fmod_base::_system = 0;

    FMOD::System& fmod_base::get_system ()
    {
        if (_system == 0)
        {
            
            STAR_FMOD_EC(FMOD::System_Create (&_system));

/*            STAR_FMOD_EC(_system->setOutput (
                          config::instance ().get<fmod_facility::output> ()
                        ));
                        */

            STAR_FMOD_EC(_system->setSoftwareFormat (44100, FMOD_SOUND_FORMAT_PCM16
                                                , 2, 0, FMOD_DSP_RESAMPLER_LINEAR)
                    );

            STAR_FMOD_EC(_system->init(32, FMOD_INIT_NORMAL, 0));
        }

        return *_system;
    }

}

    fmod_exception::fmod_exception (FMOD_RESULT result) throw ()
        : std::runtime_error (FMOD_ErrorString (result))
    {}

}

