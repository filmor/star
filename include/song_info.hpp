#ifndef STAR_SONG_INFO_HPP
#define STAR_SONG_INFO_HPP

#include "lyrics.hpp"

#include <boost/filesystem/path.hpp>

namespace star
{
    
    class song_info
    {
    public:
        song_info (boost::filesystem::path const&);
        // Sucht im Standardpfad nach möglichen Dateien
        song_info (std::string const&);

        //  audio_stream get_audio () const;

        /// \todo size_t Parameter für "Spur" (bei mehrstimmigen Liedern)
        lyrics get_lyrics () const;

    private:
        boost::filesystem::path const& _path;
    };

}

#endif

