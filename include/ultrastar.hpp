#ifndef STAR_ULTRASTAR_HPP
#define STAR_ULTRASTAR_HPP

#include "song.hpp"
#include <boost/filesystem/path.hpp>

namespace star
{
    /// Load a song in UltraStar's format.
    void load_ultrastar_song (boost::filesystem::path const& input,
                              song::data_type& data, song::desc_type& desc);

    /// \todo Convert the UltraStar song at input to a .star-package (later .star.bz2)
    void convert_ultrastar_song (boost::filesystem::path const& input,
                                 boost::filesystem::path const& output);

}

#endif

