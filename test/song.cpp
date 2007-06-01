#include "song.hpp"

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
            star::song_info info (argv[1]);
            star::song s (info);

            s.set_notes_callback (&callback);
            s.start ();
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
