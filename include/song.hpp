#ifndef STAR_SONG_HPP
#define STAR_SONG_HPP

#include "lyrics_file.hpp"

namespace star
{

    class song
    {
    public:
        song (lyrics_file const&);

        void start () const;

    private:
        lyrics_stream _lyrics_stream;
        audio_stream _audio_stream;
    };

}

#endif

