#ifndef STAR_SONG_HPP
#define STAR_SONG_HPP

#include <boost/function.hpp>
#include "basic_types.hpp"
#include "song_info.hpp"

namespace star
{

    class song
    {
    public:
        typedef int syllable;
        typedef boost::function3<void, note, note, syllable> callback_type;

        song (song_info const&);

        void start (callback_type const&) const;

    private:
        song_info const& _info;
        // ...
    };

}

#endif

