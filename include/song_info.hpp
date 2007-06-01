#ifndef STAR_SONG_INFO_HPP
#define STAR_SONG_INFO_HPP

#include "basic_types.hpp"
#include "audio_stream.hpp"

#include "utility/tuple_iterator.hpp"

#include <boost/filesystem/path.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/range/sub_range.hpp>
#include <boost/python/dict.hpp>
#include <string>
#include <vector>

namespace star
{
    
    /**
     * \todo Rename to song.
     */
    class song_info
    {
    public:
        /// time, note, text
        typedef boost::tuple<duration_t, note_t, std::string>   syllable_type;
        typedef std::vector<syllable_type>                      data_type;

        typedef data_type::const_iterator                       syllable_iterator;
        typedef tuple_iterator<data_type::const_iterator, 0, 1> notes_iterator;

        typedef boost::iterator_range<notes_iterator>           notes;

        song_info (boost::filesystem::path const&);

        audio_stream get_audio_stream (unsigned char s = 0) const;

        notes get_notes (unsigned char s = 0) const;

    private:
        boost::filesystem::path _path;
        /// \todo Make the dict either usable to python or un-intrusive (prefer last)
        boost::python::dict _desc;
        data_type _lyrics_data;
    };

}

#endif

