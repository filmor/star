#include "fmod.hpp"
#include "pitch_detector.hpp"

#include <iostream>
#include <boost/thread.hpp>

using namespace star;

int main ()
{
    typedef pitch_detector<fmod_detector> pd_t;
    pd_t pd;

    for (;;)
    {
        std::cout << '\r';
        boost::xtime xt;
        boost::xtime_get (&xt, boost::TIME_UTC);
        xt.nsec += 2e8;
        boost::thread::sleep (xt);
        note n = pd (200);
        std::cout << n.value << ' ' << n.octave << "        " << std::flush;
    }
}
