#ifndef STAR_SONG_HPP
#define STAR_SONG_HPP

#include <boost/function.hpp>
#include "song_info.hpp"

namespace star
{

    class song
    {
    public:
        typedef boost::function0<void> callback_type;

        song (song_info const&);

        void start (callback_type const&) const;

    private:
        // ...
    };

}

#endif

