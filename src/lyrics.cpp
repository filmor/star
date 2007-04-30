#include "song_info.hpp"

#include <boost/thread/thread.hpp>
#include <boost/thread/xtime.hpp>
#include <boost/algorithm/string/predicate.hpp>

#include <iostream>

namespace star
{

    // Aye, so stimmt das nicht. tuple_iterator scheint hier nicht angebracht, nur für
    // notes ist das  semantisch korrekt.
    song_info::lines song_info::get_lines () const
    {
        return boost::make_iterator_range (lines_iterator (_data.begin ()),
                                           lines_iterator (_data.end ())
                                          );
    }

/*        lines_vector res (1);

        for (data_type::const_iterator i = _data.begin (); i != _data.end (); ++i)
        {
            res[0].get<0> () += i->get<0> ();
            std::string s = i->get<2> ();
            if (s != "~")
            {
                if (boost::ends_with (s, "-"))
                {
                    s.resize (s.length () - 1);
                    res[0].get<1> () += s;
                }
                else
                    (res[0].get<1> () += s) += ' ';
            }
        }
        return res;
    }*/

    song_info::notes song_info::get_notes () const
    {
        return boost::make_iterator_range (notes_iterator (_data.begin ()),
                                           notes_iterator (_data.end ())
                                          );
    } 

}

