#ifndef STAR_CONFIG_FACILITY_HPP
#define STAR_CONFIG_FACILITY_HPP

#include "config.hpp"

namespace star
{

    namespace
    {
        class choices
        {
        public:
            choices add () { return *this; }
            operator bool () { return false; }
        };
    }

    class config::facility
    {
    protected:
        template <typename Derived, typename Type>
        class dynamic_choice
        {
        public:
            operator Type () {}
            typedef choices choices_type;
        };
    };

}

#endif

