#ifndef STAR_LYRICS_FILE_HPP
#define STAR_LYRICS_FILE_HPP

#include "lyrics.hpp"

#include <boost/filesystem/path.hpp>

namespace star
{
    
    class lyrics_file
    {
    public:
        lyrics_file (boost::filesystem::path const&);

//        audio_stream get_audio () const;

        /// \todo size_t Parameter für "Spur" (bei mehrstimmigen Liedern)
        lyrics get_lyrics () const;

    private:
        boost::filesystem::path const& _path;
    };

}

#endif

