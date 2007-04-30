#include "song_info.hpp"

#include <boost/spirit.hpp>
#include <boost/spirit/phoenix.hpp>
#include <boost/filesystem.hpp>
#include <boost/function.hpp>

namespace fs = boost::filesystem;
namespace sp = boost::spirit;

namespace star
{

    namespace
    {
        using namespace sp;
        using namespace phoenix;

        struct push_back_impl
        {
            template <typename Container, typename Item>
            struct result
            {
                typedef void type;
            };

            template <typename Container, typename Item>
            void operator()(Container& c, Item const& item) const
            {
                c.push_back(item);
            }
        };

        function<push_back_impl> const push_back = push_back_impl ();

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

        struct string_closure : public ::sp::closure<string_closure, std::string>
        {
            member1 val;
        };

        class lyrics_grammar : public grammar<lyrics_grammar>
        {
        public:
            lyrics_grammar (lyrics::text& t) : _text (t) {}

            template <typename ScannerT>
            struct definition
            {
                rule<ScannerT> r;
                definition (lyrics_grammar const& self)
                {
                    rule<ScannerT, string_closure::context_t> string
                        = ((alpha_p) >> *(alpha_p))
                            [string.val = construct_<std::string> (arg1, arg2)];

                    rule<ScannerT> line = (int_p >> real_p >> !string)
                            [push_back (var (self._text),
                                construct_<lyrics::syllable> (200, 2.5, string.val)
                                )
                            ];

                    r = *line;
                }

                rule<ScannerT> const& start () const { return r; }
            };

            lyrics::text& _text;
        };

    }

    song_info::song_info (fs::path const& path)
        : _path (path)
    {
        std::cout << path << std::endl;
        // sp::file_iterator<char> desc ((_path / "description").string ());
    }

    song_info::song_info (std::string const& p)
        : _path (p + ".star")
    {
    }

    lyrics song_info::get_lyrics () const
    {
        sp::file_iterator<char> f ((_path/* / "lyrics"*/).string ());
        if (!f)
            throw 1;
        lyrics::text res;
        /* sp::parse_info info = */sp::parse (f, f.make_end (), lyrics_grammar (res));
        std::cout << "blubb" << std::endl;
        
        return lyrics (res);
    }

}    
