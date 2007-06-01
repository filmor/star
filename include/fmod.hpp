#ifndef STAR_FMOD_HPP
#define STAR_FMOD_HPP

#include "audio_stream.hpp"

#include <cstddef>
#include <string>
#include <fmodex/fmod.hpp>

#include <boost/preprocessor/stringize.hpp>

#define STAR_FMOD_EC(expr) \
    error_check (BOOST_PP_STRINGIZE(expr), (expr))

namespace star
{
    namespace detail
    {
        class fmod_base
        {
        protected:
            FMOD::System& get_system ();
            void error_check (std::string const&, FMOD_RESULT) const;

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

    class fmod_stream_impl : public audio_stream_impl<fmod_stream_impl>
                           , private detail::fmod_base
    {
    public:
        fmod_stream_impl (std::string const& path);
        virtual ~fmod_stream_impl () {}

        virtual void play ();
        virtual void stop ();
        virtual void wait ();
        virtual duration_t get_pos () const;

    private:
        FMOD::Sound* _sound;
        FMOD::Channel* _channel;
    };

}

#endif

