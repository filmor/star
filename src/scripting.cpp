#include "scripting.hpp"

#include "player.hpp"
#include "basic_types.hpp"
#include "game_window.hpp"

namespace star
{
    namespace
    {
        void* alloc(void* ud, void* ptr, size_t osize, size_t nsize)
        {
            (void)ud; (void)osize;

            if (nsize == 0)
            {
                std::free(ptr);
                return 0;
            }
            else
                return std::realloc(ptr, nsize);
        }
    }

    interpreter::interpreter()
    {
        state_ = lua_newstate(&alloc, 0);
        // Register lua_atpanic
    }

    interpreter::~interpreter()
    {
        lua_close(state_);
    }
    
    namespace
    {
        const char* istream_reader(lua_State* L, void* data, size_t* size)
        {
            std::istream& is = *reinterpret_cast<std::istream*>(data);
            if (is)
            {
                const size_t BLOCK_SIZE = 1024;
                void* ud;
                lua_Alloc alloc = lua_getallocf(L, &ud);

                char* ret = 0;
                ret = reinterpret_cast<char*>(alloc(ud, ret, 0, BLOCK_SIZE));

                is.read(ret, BLOCK_SIZE);
                *size = is.gcount();
                
                return ret;
            }
            else
            {
                *size = 0;
                return 0;
            }
        }

        /// Stub
        std::string generate_name() { return ""; }
    }

    program interpreter::load_program(std::istream& is, std::string name)
    {
        if (name == "")
            name = generate_name();

        int err = lua_load(state_, &istream_reader, &is, name.c_str());
        switch(err)
        {
        case LUA_ERRSYNTAX:
            throw std::runtime_error("Syntax Error");
            lua_pop(state_, 1);
            break;
        case LUA_ERRMEM:
            throw std::runtime_error("Memory Error");
            lua_pop(state_, 1);
            break;
        }

        lua_setglobal(state_, name.c_str());
        return program(name);
    }

    void interpreter::run_program(program const& scr)
    {
        lua_getglobal(state_, scr.c_str());
        lua_pcall(state_, 0, LUA_MULTRET, 0);
        /// \todo Error handling
    }

}
