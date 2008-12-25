#include "config_sources.hpp"

namespace star
{

#define STAR_GET_BLA(type)                                  \
    type python_source::get_##type (std::string const& s)   \
    {                                                       \
        boost::python::extract<type> extractor (_dict[s]);  \
        if (!extractor.check ())                            \
            throw s;                                        \
        else                                                \
            return type (extractor);                        \
    }

}
