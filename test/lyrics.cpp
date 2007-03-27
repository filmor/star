#include "../src/lyrics.hpp"

#include <iostream>

int main ()
{
    star::lyrics::text v;
    v.push_back (boost::make_tuple (2000, 0, "Aah"));
    v.push_back (boost::make_tuple (1000, 0, " "));
    v.push_back (boost::make_tuple (1000, 0, "Bee"));
    
    star::lyrics l (v);
    l.start (std::cout);
}

