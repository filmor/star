#ifndef STAR_SONG_INFO_HPP
#define STAR_SONG_INFO_HPP

#include "basic_types.hpp"
#include "audio_stream.hpp"

#include "utility/tuple_iterator.hpp"

#include <boost/filesystem/path.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/range/iterator_range.hpp>
#include <string>
#include <vector>

namespace star
{
    
    class song_info
    {
    public:
        // \todo Iteratoren statt lines_vector/notes_vector
        typedef std::vector<boost::tuple<duration_t, double, std::string> >
            data_type;


        // \todo lines_iterator implementieren
        typedef tuple_iterator<data_type::const_iterator, 0, 2> lines_iterator;
        typedef tuple_iterator<data_type::const_iterator, 0, 1> notes_iterator;
        typedef boost::iterator_range<lines_iterator> lines;
        typedef boost::iterator_range<notes_iterator> notes;

        song_info (boost::filesystem::path const&);
        // Sucht im Standardpfad nach möglichen Dateien
        //song_info (std::string const&);

        audio_stream get_audio_stream () const;

        /// \todo size_t Parameter für "Spur" (bei mehrstimmigen Liedern)
        notes get_notes () const;

        lines get_lines () const;

    private:
        boost::filesystem::path _path;
        data_type _data;
    };

}

#endif

