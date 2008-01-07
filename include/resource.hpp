#ifndef STAR_RESOURCE_HPP
#define STAR_RESOURCE_HPP

#include "game_window.hpp"

#include <boost/type_traits/aligned_storage.hpp>
#include <boost/type_traits/alignment_of.hpp>
#include <boost/preprocessor/repetition.hpp>
#include <boost/bind.hpp>

#ifndef STAR_MAX_RESOURCE_ARITY
#define STAR_MAX_RESOURCE_ARITY 5
#endif

namespace star
{

    /// \todo Document!
    /// \todo Proper naming. (delayed init?)
    template <class T>
    class resource
    {
        struct dont_initialize_t {};
    public:

#define STAR_RESOURCE_CONSTRUCTOR(Z, N, _)                                      \
        template <BOOST_PP_ENUM_PARAMS(N, typename A)>                          \
        resource (BOOST_PP_ENUM_BINARY_PARAMS(N, A, a))                         \
            : _initialized (false)                                              \
        {                                                                       \
            init (BOOST_PP_ENUM_PARAMS(N, a));                                  \
        }


        BOOST_PP_REPEAT_FROM_TO(1, STAR_MAX_RESOURCE_ARITY, 
                                STAR_RESOURCE_CONSTRUCTOR, _)

#undef STAR_RESOURCE_CONSTRUCTOR

        /// \todo Implement default constructor like the above and enable
        ///       "dont_initialize"
        resource () : _initialized (false) {}

        ~resource ()
        {
            if (_initialized)
                game_window::instance ().enqueue_init
                (
                    boost::bind (&resource::deinitialize, this)
                );
            /// \todo Conditional wait
        }

#define STAR_RESOURCE_INIT(Z, N, _)                                          \
        template <BOOST_PP_ENUM_PARAMS(N, typename A)>                       \
        void init (BOOST_PP_ENUM_BINARY_PARAMS(N, A, a))                     \
        {                                                                    \
            typedef void (resource::*init_type) (BOOST_PP_ENUM_PARAMS(N, A));\
            init_type fp = &resource::template do_init;                      \
            game_window::instance ().enqueue_init                        \
            (                                                                \
                boost::bind (fp, this BOOST_PP_ENUM_TRAILING_PARAMS(N, a))   \
            );                                                               \
        }

        BOOST_PP_REPEAT_FROM_TO(1, STAR_MAX_RESOURCE_ARITY, STAR_RESOURCE_INIT, _)

        /// \todo Use boost::shared_ptr's unspecified_bool_type
        operator bool () const { return _initialized; }

        T* const operator-> () const { return get_ptr (); }
        T* operator-> () { return get_ptr (); }

    private:

#define STAR_RESOURCE_DO_INIT(Z, N, _)                               \
        template <BOOST_PP_ENUM_PARAMS(N, typename A)>               \
        void do_init (BOOST_PP_ENUM_BINARY_PARAMS(N, A, a))          \
        {                                                            \
            new (get_ptr ()) T (BOOST_PP_ENUM_PARAMS(N, a));         \
            _initialized = true;                                     \
        }

        BOOST_PP_REPEAT_FROM_TO(1, STAR_MAX_RESOURCE_ARITY, 
                                STAR_RESOURCE_DO_INIT, _)

#undef STAR_RESOURCE_DO_INIT

        void deinitialize ()
        {
            delete get_ptr ();
            _initialized = false;
        }

        T* const get_ptr () const
        {
            return reinterpret_cast<T* const> (_storage.address ());
        }

        T* get_ptr ()
        {
            return reinterpret_cast<T*> (_storage.address ());
        }

        typedef 
            boost::aligned_storage<sizeof(T), boost::alignment_of<T>::value>
            storage_type;

        storage_type _storage;
        bool _initialized;
    };

}

#endif

