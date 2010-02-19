#ifndef STAR_UTILITY_BUFFER_HPP
#define STAR_UTILITY_BUFFER_HPP

#include <vector>

namespace star
{

    /// \todo Lightweight(!) buffer type. Does not need resizing.
    template <typename T>
    class buffer : public vector<T>
    {
        typedef vector<T> base_type;
    public:

        template <typename T1> buffer (T1 a1) : base_type (a1) {}
        template <typename T1, typename T2> buffer (T1 a1, T2 a2) : base_type (a1, a2)
        {}
    };

}

#endif

