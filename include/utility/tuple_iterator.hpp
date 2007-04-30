#ifndef STAR_UTILITY_TUPLE_ITERATOR_HPP
#define STAR_UTILITY_TUPLE_ITERATOR_HPP

#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/tuple/tuple.hpp>

namespace star
{
    namespace
    {
        template <class Tuple, unsigned Arg1, unsigned Arg2>
        struct filter_tuple
        {
            typedef boost::tuples::tuple<
                            typename boost::tuples::element<Arg1, Tuple>::type,
                            typename boost::tuples::element<Arg2, Tuple>::type
                                        >
                    type;
        };
    }

    template <class IteratorT, unsigned Arg1, unsigned Arg2>
    class tuple_iterator : public boost::iterator_adaptor<
                                    tuple_iterator<IteratorT, Arg1, Arg2>,
                                    IteratorT,
                                    const typename filter_tuple<
                                                    typename IteratorT::value_type,
                                                    Arg1, Arg2>::type
                                                        >
    {
    public:
        typedef typename filter_tuple<typename IteratorT::value_type,Arg1,Arg2>::type
            value_type;
        explicit tuple_iterator (IteratorT const& iter)
            : tuple_iterator::iterator_adaptor_ (iter)
        {}

    private:
        friend class boost::iterator_core_access;
        value_type const& dereference () const
        {
            if (!_value_set)
            {
                _value = value_type (
                                 boost::tuples::get<Arg1> (*this->base_reference()),
                                 boost::tuples::get<Arg2> (*this->base_reference())
                                );
                _value_set = true;
            }

            return _value;
        }

        void increment ()
        {
            ++this->base_reference ();
            _value_set = false;
        }

        mutable bool _value_set;
        mutable value_type _value;
    };

}

#endif
