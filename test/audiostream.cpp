#include "audio_stream.hpp"

#include <unistd.h>

#include <iostream>

int main (int argc, char** argv)
{
    if (argc < 2)
        throw 1;

    std::cout << argv[1] << std::endl;
    try
    {
        star::audio_stream p ("ogg/vorbis", argv[1]);
        p.play ();
        p.wait ();
        usleep (1000000);
    }
    catch (std::string const& s)
    {
        std::cerr << s << std::endl;
    }    
}

