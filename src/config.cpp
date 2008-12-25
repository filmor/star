#include "config.hpp"

#include <boost/filesystem/path.hpp>
#include <luabind/luabind.hpp>

namespace star
{

    config::config ()
    {}

    config::~config ()
    {}

    void config::enqueue_source (source_ptr ptr)
    {
        sources_.push_back (ptr);
    }

}
