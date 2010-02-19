#ifndef STAR_UTILITY_FILTER_TUPLE_HPP
#define STAR_UTILITY_FILTER_TUPLE_HPP

#include <boost/tuple/tuple.hpp>

namespace star
{
    template <class Tuple, unsigned Arg1, unsigned Arg2>
    struct filter_tuple
    {
        typedef boost::tuples::tuple<
                        typename boost::tuples::element<Arg1, Tuple>::type const&,
                        typename boost::tuples::element<Arg2, Tuple>::type const&
                                    >
                result_type;

        result_type operator () (Tuple const& t) const
        {
            return result_type (t.template get<Arg1> (), t.template get<Arg2> ());
        }
    };
}

#endif
