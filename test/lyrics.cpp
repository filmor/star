#include "song.hpp"

#include <iostream>

int main (int argc, char** argv)
{
    Py_Initialize ();
    /// Currently not working, needs Python
    if (argc < 2)
        throw 1;

    std::cout << argv[1] << std::endl;
    star::song f (argv[1]);
    
    star::song::lines l = f.get_lines ();
    
    for (star::song::lines::const_iterator i = l.begin (); i != l.end ();
            ++i)
        std::cout << i->get<0> () <<  ' ' << i->get<1> () << std::endl;
}

