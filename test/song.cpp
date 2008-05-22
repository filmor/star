#include "song.hpp"
#include "player.hpp"

void callback (star::note n, star::note sn, int)
{
    std::cout << n.value << ' ' << sn.value << "\n=======" << std::endl;
}

int main (int argc, char** argv)
{
    try
    {
        Py_Initialize ();
        if (argc < 2)
            throw 1;

        try
        {
            star::song s (argv[1]);
            star::player p (s);

            p.set_notes_callback (&callback);
            p.start ();
        }
        catch (std::string const& s)
        {
            std::cerr << s << std::endl;
        }
    }
    catch (boost::python::error_already_set const&)
    {
        PyErr_Print ();
    }
    Py_Finalize ();
}
