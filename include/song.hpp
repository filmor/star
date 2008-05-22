#ifndef STAR_SONG_HPP
#define STAR_SONG_HPP

#include "basic_types.hpp"
#include "audio_stream.hpp"

#include "utility/filter_tuple.hpp"

#include <boost/filesystem/path.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <boost/python/dict.hpp>
#include <string>
#include <vector>

namespace star
{
    
    class song
    {
    public:
        /// time, note, text
        typedef boost::tuple<duration_t, note_t, std::string>   syllable_type;
        typedef std::vector<syllable_type>                      data_type;
        
        typedef boost::python::dict                             desc_type;

        typedef data_type::const_iterator                       syllable_iterator;

        typedef boost::transform_iterator<filter_tuple<data_type::value_type, 0, 1>,
                                          data_type::const_iterator 
                                         >
            notes_iterator;

        typedef boost::iterator_range<syllable_iterator>        lyrics;
        typedef boost::iterator_range<notes_iterator>           notes;

        song (boost::filesystem::path const&);

        audio_stream get_audio_stream (unsigned char track = 0) const;

        notes get_notes (unsigned char track = 0) const;

        lyrics get_lyrics (unsigned char track = 0) const;

        desc_type get_description () const { return _desc; }

    private:
        boost::filesystem::path _path;
        desc_type _desc;
        data_type _lyrics_data;
    };

}

#endif

