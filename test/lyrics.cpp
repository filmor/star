#include "song_info.hpp"

#include <iostream>

int main (int argc, char** argv)
{
    if (argc < 2)
        throw 1;

    std::cout << argv[1] << std::endl;
    star::song_info f (argv[1]);
    
    star::song_info::lines l = f.get_lines ();
    
    for (star::song_info::lines::const_iterator i = l.begin (); i != l.end ();
            ++i)
        std::cout << i->get<0> () <<  ' ' << i->get<1> () << std::endl;
}

