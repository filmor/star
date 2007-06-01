#include "song_info.hpp"

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/python/exec.hpp>
#include <boost/python/extract.hpp>

#include <sstream>

namespace bf = boost::filesystem;
namespace bp = boost::python;

namespace star
{
    
    /// \todo Either implement converters and smf as standard or multiple inputs
    ///       (prefer first)
    song_info::song_info (bf::path const& path)
        : _path (path)
    {
        bf::ifstream lyrics (_path / "lyrics");

        while (lyrics)
        {
            std::string line;
            std::getline (lyrics, line);
            data_type::value_type tuple;

            std::istringstream si (line);

            std::string note = "";
    
            /// \todo Spirit-rule for reading a lyrics-files line instead
            si >> tuple.get<0> () >> note >> tuple.get<2> ();

            std::istringstream si2 (note);
            char c;
            si2 >> (tuple.get<1> ().value) >> c >> (tuple.get<1> ().octave);

            _lyrics_data.push_back (tuple);
        }

        bp::exec_file (bp::str ((_path / "description").native_file_string ()),
                       _desc, _desc);
    }

    audio_stream song_info::get_audio_stream (unsigned char s) const
    {
        return audio_stream (bp::extract<std::string> (_desc["audio_type"]),
                             _path / "audio");
    }

    song_info::notes song_info::get_notes (unsigned char s) const
    {
        return boost::make_iterator_range (notes_iterator (_lyrics_data.begin ()),
                                           notes_iterator (_lyrics_data.end ())
                                          );
    }

}
