#include "config.hpp"

namespace star
{

    config::config ()
    {}

    config::~config ()
    {}

    void config::enqueue_source (source_ptr ptr)
    {
        _sources.push_back (ptr);
    }

}
