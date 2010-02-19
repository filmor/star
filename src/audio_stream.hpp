#ifndef STAR_AUDIO_STREAM_HPP
#define STAR_AUDIO_STREAM_HPP

#include "basic_types.hpp"

#include <boost/filesystem/path.hpp>
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>
#include <string>
#include <map>
#include <utility>


namespace star
{

    class audio_stream
    {
    public:
        audio_stream (std::string const& /* type */
                     ,boost::filesystem::path const& /* location */);
        
        audio_stream (audio_stream const& other)
            : _impl (other._impl)
        {}

        ~audio_stream ();

        void play ();
        void stop ();
        void wait ();

//        void synchronize (boost::system_time const& /* should be */,
//                          boost::system_time const& /* is */);

    public:
        struct stream_impl
        {
            virtual void play () = 0;
            virtual void stop () = 0;
            virtual void wait () = 0;
            virtual time_duration get_pos () const = 0;
            virtual ~stream_impl () {}
        };

    private:
        typedef std::map<std::string,
                        boost::function<stream_impl* (std::string const&)>
                       > registry_type; 
    public:
        template <typename T>
        struct register_
        {
            template <typename IteratorT>
            register_ (IteratorT begin, IteratorT end,
                       registry_type::mapped_type const& f
                          = &register_<T>::creator)
            {
                do
                {
                    register_ (*begin);
                }
                while (++begin != end);
            }

            register_ (registry_type::key_type const& n,
                       registry_type::mapped_type const& f 
                          = &register_<T>::creator)
            {
                _get_registered ()->insert (std::make_pair (n, f));
            }
        private:
            static stream_impl* creator (std::string const& s) { return new T (s); }
        };

        template <typename T>
        friend struct register_;

    private:
        static registry_type* _get_registered ()
        {
            static registry_type map;
            return &map;
        }

        boost::shared_ptr<stream_impl> _impl;
    };

    template <class DerivedT>
    class audio_stream_impl : public audio_stream::stream_impl
    {
        static audio_stream::register_<DerivedT> _impl_register;
    };

    template <class DerivedT>
    audio_stream::register_<DerivedT> audio_stream_impl<DerivedT>::_impl_register
        (DerivedT::mime_type ())
        ;

}

#endif
