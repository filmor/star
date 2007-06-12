#include "config.hpp"

#include <boost/filesystem/path.hpp>
#include <boost/python/exec.hpp>
#include <boost/python/str.hpp>

namespace star
{

    config::config ()
    {
        boost::filesystem::path p ("config");

        load_source (p.string ());
    }

    config::~config ()
    {}

    void config::load_source (std::string const& str)
    {
        boost::python::exec (boost::python::str (str),
                             _data, _data);
    }

}
