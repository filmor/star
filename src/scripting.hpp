#ifndef STAR_SCRIPTING_HPP
#define STAR_SCRIPTING_HPP

#include <string>
#include <iosfwd>

#include <lua.hpp>

#include <boost/utility.hpp>
#include <boost/operators.hpp>

namespace star
{

    // \todo Proper script type (iterator value to set)
    typedef std::string program;

    class interpreter : boost::noncopyable
    {
    public:
        typedef lua_State* state_type;

        /// Takes control over the state (which is deleted in the destructor!)
        explicit interpreter(state_type& state) : state_(state) {}
        interpreter();
        ~interpreter();

        // typedef luabind::object module
        // void add_module(std::string&, module)

        program load_program(std::istream& is, std::string name = "");

        void run_program(program const&);

        state_type get_state() { return state_; }

    private:
        state_type state_;
    };

    // void module_star ();
}

#endif
