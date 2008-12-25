#ifndef STAR_FMOD_HPP
#define STAR_FMOD_HPP

#include "audio_stream.hpp"
#include "config.hpp"

#include <cstddef>
#include <string>
#include <stdexcept>
#include <fmodex/fmod.hpp>

#ifndef NDEBUG
#   include <boost/preprocessor/stringize.hpp>
#   define STAR_FMOD_EC(expr) \
        error_check (BOOST_PP_STRINGIZE(expr), (expr))
#else
#   define STAR_FMOD_EC(expr) expr
#endif

namespace star
{
    namespace detail
    {
        class fmod_config : public config::facility
        {
        public:
            struct device_t : public dynamic_choice<device_t, int>
            {
            public:
                choices_type get_choices () const
                {
                    static choices_type _choices;
                    if (!_choices)
                    {
                        _choices.add
                            (0, "Blubb")
                            (2, "Blabb")
                            ;
                    }
                    return _choices;
                }
            };
            
            device_t output_device;
            // Combine system and output ("alsa", "emu10k1"), ("oss", "emu10k1") etc.

            device_t input_device;
        };

        class fmod_base
        {
        protected:
            FMOD::System& get_system ();
            void error_check (std::string const&, FMOD_RESULT) const;

        private:
            static FMOD::System* _system;
        };

        struct fmod_facility : public config::facility<fmod_facility>
        {
            config_element<config::choice, config::needs_restart> output;
            config_list<
                 config_element<config::choice>
                > inputs;
        };
    }

    class fmod_exception : public std::runtime_error
    {
    public:
        explicit fmod_exception (FMOD_RESULT) throw ();
    };

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

