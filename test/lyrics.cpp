#include "lyrics_file.hpp"

#include <iostream>

int main (int argc, char** argv)
{
    if (argc < 2)
        throw 1;

    star::lyrics_file f (argv[1]);
    
    star::lyrics t = f.get_lyrics ();
    t.start (std::cout);
}

