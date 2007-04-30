#include "song_info.hpp"

#include <boost/spirit.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/function.hpp>

#include <boost/tuple/tuple_io.hpp>

#include <sstream>

namespace fs = boost::filesystem;
namespace sp = boost::spirit;

namespace star
{
    /// \todo Regel für Zeile statt für die ganze Datei

    namespace
    {
        using namespace sp;

        struct description_grammar : public grammar<description_grammar>
        {
            template <typename ScannerT>
            struct definition
            {
                rule<ScannerT> r;
                definition (description_grammar const& self)
                {}

                rule<ScannerT> const& start () const { return r; }
            };
        };

    }

    song_info::song_info (fs::path const& path)
        : _path (path)
    {
        fs::ifstream lyrics (_path / "lyrics");

        while (lyrics)
        {
            std::string line;
            std::getline (lyrics, line);
            data_type::value_type tuple;

            std::istringstream si (line);
            si >> tuple.get<0> () >> tuple.get<1> () >> tuple.get<2> ();

            _data.push_back (tuple);
        }

        // sp::file_iterator<char> desc ((_path / "description").string ());
    }

    audio_stream song_info::get_audio_stream () const
    {
        return audio_stream ("x-application/ogg", _path / "audio");
    }

}    
