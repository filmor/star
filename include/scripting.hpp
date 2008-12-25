#ifndef STAR_SCRIPTING_HPP
#define STAR_SCRIPTING_HPP

#include <lua.hpp>
#include <luabind/luabind.hpp>

namespace star
{
    typedef lua_State* interpreter;
    typedef std::string script;

    void module_star ();
}

#endif
