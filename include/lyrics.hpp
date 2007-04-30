#ifndef STAR_LYRICS_HPP
#define STAR_LYRICS_HPP

#include <boost/tuple/tuple.hpp>
#include <string>
#include <vector>
#include <iosfwd>

namespace star
{

    class lyrics
    {
    public:
        // (Länge, Tonhöhe, Text)
        typedef boost::tuple<short, double, std::string> syllable;
        typedef std::vector<syllable> text;

        lyrics (text const& t) : _lyrics (t) {}
        lyrics (lyrics const& other) : _lyrics (other._lyrics) {}

        std::vector<short, std::string> lines () const;

    private:
        text _lyrics;
    };

}

#endif

