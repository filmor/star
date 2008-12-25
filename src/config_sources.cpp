#include "config_sources.hpp"

#include <boost/python/exec.hpp>
#include <boost/python/object.hpp>
#include <boost/python/extract.hpp>

namespace star
{

    python_source::python_source (boost::filesystem::path const& path)
    {
        using namespace boost::python;

        exec_file (str (path.native_file_string ()), _dict, _dict);
    }

    python_source::python_source (boost::python::dict dict)
        : _dict (dict)
    {}

#define STAR_GET_BLA(type)                                  \
    type python_source::get_##type (std::string const& s)   \
    {                                                       \
        boost::python::extract<type> extractor (_dict[s]);  \
        if (!extractor.check ())                            \
            throw s;                                        \
        else                                                \
            return type (extractor);                        \
    }

    STAR_GET_BLA(int)

    STAR_GET_BLA(double)

    using std::string;

    STAR_GET_BLA(string)

}
