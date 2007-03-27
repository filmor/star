#ifndef STAR_MEDIA_HPP
#define STAR_MEDIA_HPP

#include <boost/utility.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

namespace star
{
    namespace
    {
        template <class PlayerType>
        class output : boost::noncopyable
        {
        public:
            typedef typename PlayerType::stream_type stream_type;
            typedef PlayerType player_type;

            virtual ~output () {};

            void start (stream_type const& vs)
            {
                _player = player_type::factory::create (vs);
                this->do_start (_player);
                _player.reset ();
            }

        protected:
            virtual void do_start (boost::weak_ptr<player_type> player) = 0;
            boost::shared_ptr<player_type> _player;
        };
    }

    typedef output<video_player> video_output;
    typedef output<audio_player> audio_output;
    typedef output<lyrics_player> lyrics_output;

}

#endif

