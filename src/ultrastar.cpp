#include "ultrastar.hpp"

#include <algorithm>
#include <boost/filesystem/fstream.hpp>
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/python/long.hpp>
#include <boost/python/str.hpp>
#include <boost/range.hpp>
#include <boost/spirit.hpp>

namespace bf = boost::filesystem;

namespace star
{

    void load_ultrastar_song (bf::path const& input, song::data_type& data,
                              song::desc_type& desc)
    {
        using namespace boost;
        using namespace spirit;

        desc["type"] = "ultrastar";
        desc["origin"] = input.native_file_string ();

        /// \todo Actions for the rules (to fill the lyrics vector
        /// \todo Full grammar that also parses the header

        rule<> syllable_rule =
            (ch_p(':') | ch_p('*')) >> uint_p >> uint_p >> lexeme_d[' ' >> *anychar_p]
            ;

        rule<> pause_rule =
            ch_p('-') >> uint_p >> !uint_p
            ;

        rule<> line_rule =
            (syllable_rule | pause_rule)
            ;


        bf::ifstream file (input);
        std::string line;
        
        while (file)
        {
            std::getline (file, line);

            if (line.length () < 1)
                continue;

            /// Header line
            if (line[0] == '#')
            {
                std::string::iterator delimiter
                    = std::find (line.begin (), line.end (), ':');
                
                std::string name (line.begin () + 1, delimiter);

                algorithm::to_lower (name);

                std::string value (delimiter + 1, line.end ());

                algorithm::trim (value);

                if (name == "mp3")
                {
                    desc["audio_type"] = "mpeg/mp3";
                    desc["audio_file"] = value;
                }
                else if (name == "language")
                    /// \todo Parse LANGUAGE properly (i.e. only the part in parens)
                    desc["language"] = "en";
                else if (name == "bpm" || name == "gap")
                {
                    algorithm::replace_first (value, ",", ".");
                    /// Aye, no float available :(
                    desc[name] = value;
                }
                else
                    desc[name] = value;
            }
            /// Lyric line
            else
            {
            }
        }

    }

}

