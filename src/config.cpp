#include "config.hpp"

#include <boost/filesystem/path.hpp>
#include <luabind/luabind.hpp>

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
        /// Lua
    }

}
