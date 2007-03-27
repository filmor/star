#include "lyrics_file.hpp"

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
                    rule<ScannerT> line = (int_p >> real_p >> *alpha_p)
                            /*[push_back (var (self._text),
                                construct_<lyrics::syllable> (arg1, arg2,
                                    construct_<std::string> (arg3)
                                    )
                                )
                            ]*/;
                    r = *line;
                }

                rule<ScannerT> const& start () const { return r; }
            };

            lyrics::text& _text;
        };

    }

    lyrics_file::lyrics_file (fs::path const& path)
        : _path (path)
    {
        sp::file_iterator<char> desc ((_path / "description").string ());
    }

    lyrics lyrics_file::get_lyrics () const
    {
        sp::file_iterator<char> f ((_path / "lyrics").string ());
        lyrics::text res;
       /* sp::parse_info info = */sp::parse (f, f.make_end (), lyrics_grammar (res));
        return res;
    }

}    
