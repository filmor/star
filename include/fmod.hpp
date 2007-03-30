#ifndef STAR_FMOD_HPP
#define STAR_FMOD_HPP

#include <cstddef>
#include <string>
#include <fmod/fmod.hpp>

namespace star
{
    namespace detail
    {
        class fmod_base
        {
        protected:
            FMOD::System& get_system ();
            void error_check (std::string const&, FMOD_RESULT);

        private:
            static FMOD::System* _system;
        };
    }

    class fmod_detector : private detail::fmod_base
    {
    protected:
        typedef float frequency_type;

        fmod_detector ();
        
        frequency_type get_frequency (std::size_t channel, long d);

    private:
        FMOD::Sound* _sound;
        FMOD::Channel* _channel;
    };

    class fmod_audio : private detail::fmod_base
    {
    public:
    };

}

#endif

