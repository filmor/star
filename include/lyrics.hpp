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
        typedef boost::tuple<short, double, std::string> syllable;
        typedef std::vector<syllable> text;

        lyrics (text const& t) : _lyrics (t) {}

        void start (std::ostream& os) const;

    private:
        text _lyrics;
    };

}

#endif

