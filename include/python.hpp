#ifndef STAR_PYTHON_HPP
#define STAR_PYTHON_HPP

#include <boost/python/exec.hpp>
#include <boost/python/extract.hpp>

namespace star
{
namespace python
{
    using namespace boost::python;

    struct restricted_env
    {
        restricted_env () {}
        ~restricted_env () {}
    };

    void module_star ();
    void module_star_graphics ();

}
}

#endif
