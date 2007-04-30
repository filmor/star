#include "audio_stream.hpp"

#include <unistd.h>

#include <iostream>

int main (int argc, char** argv)
{
    if (argc < 2)
        throw 1;

    std::cout << argv[1] << std::endl;
    star::audio_stream p ("x-application/ogg", argv[1]);
    p.play ();
    
}

