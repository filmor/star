#ifndef STAR_UTILITY_ITERATORS_HPP
#define STAR_UTILITY_ITERATORS_HPP

#include <stdexcept>
#include <boost/iterator/iterator_adaptor.hpp>

namespace star
{

    template <typename IteratorT>
    class end_checking_iterator : public boost::iterator_adaptor<
                                            end_checking_iterator<IteratorT>,
                                            IteratorT
                                         >
    {
    public:
        end_checking_iterator (IteratorT iter, IteratorT end)
                : end_checking_iterator::iterator_adaptor_ (iter) , _end (end)  
        {}

    private:
        friend class boost::iterator_core_access;

        void check_end () const
        {
            if (this->base_reference () == _end) throw std::out_of_range ("end");
        }

        /// \bug Implementing advance is not possible
        /// \todo Implement dereference
        void advance (std::ptrdiff_t n);
        void increment ()
        {
            check_end ();
            ++(this->base_reference ());
        }

        IteratorT _end;
    };


    template <typename IteratorT>
    class length_checking_iterator : public boost::iterator_adaptor<
                                                length_checking_iterator<IteratorT>,
                                                IteratorT
                                            >
    {
    public:
        length_checking_iterator (IteratorT iter, std::size_t length)
                : length_checking_iterator::iterator_adaptor_ (iter)
                , _length (length)
        {}

    private:
        friend class boost::iterator_core_access;

        void check_end () { if (!_length) throw std::out_of_range ("length"); }
        
        void advance (std::ptrdiff_t n);
        void increment ()
        {
            SHOW(_length)
            check_end ();
            --_length;
            ++(this->base_reference ());
        }

        void decrement ()
        {
            ++_length;
            --(this->base_reference ());
        }

        std::size_t _length;
    };

}

#endif
