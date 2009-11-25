#include "config.hpp"

#include <boost/filesystem/path.hpp>

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
