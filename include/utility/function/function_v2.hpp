#ifndef FUNCTION_V2_HPP
#define FUNCTION_V2_HPP

#include <boost/python.hpp>
#include <boost/function.hpp>
#include <iostream>
#include <map>

namespace function {

    using namespace ::boost::python;

// We need a wrapper functor for Python objects to store in a boost::functionN
// object, mostly because we need to extract the return type.

#if 0 // NDEBUG
#define FUNCTION_OBJECT_FUNCTOR_DEBUG( n ) \
    ::std::cout << "object_functor" << n << ": "
#else
#define FUNCTION_OBJECT_FUNCTOR_DEBUG( n )
#endif

namespace detail
{
#ifndef FUNCTION_NO_THREADS
    class global_interpreter_lock : boost::noncopyable
    {
    public:
        global_interpreter_lock () : _state (PyGILState_Ensure ()) {}
        ~global_interpreter_lock () { PyGILState_Release (_state); }
    private:
        PyGILState_STATE _state;
    };
#else
    struct global_interpreter_lock : boost::noncopyable {};
#endif
}

template < typename Function ,
           unsigned int Arity = Function::arity >
struct object_functor ;

#define FUNCTION_OBJECT_FUNCTOR_DECL \
    handle<> obj ; \
    typedef typename Function::result_type result_type ; \
    object_functor( PyObject* obj ) : obj( borrowed( obj ) ) {}

template < typename Function >
struct object_functor< Function , 0 >
{
    FUNCTION_OBJECT_FUNCTOR_DECL

    result_type operator () () const
    {
        FUNCTION_OBJECT_FUNCTOR_DEBUG( 0 ) ;

        detail::global_interpreter_lock lock;

        return call< result_type >( obj.get() ) ;
    }

} ;

template < typename Function >
struct object_functor< Function , 1 >
{
    FUNCTION_OBJECT_FUNCTOR_DECL

    result_type operator () ( typename Function::arg1_type a1 ) const
    {
        FUNCTION_OBJECT_FUNCTOR_DEBUG( 1 ) ;

        detail::global_interpreter_lock lock;

        return call< result_type >( obj.get(), a1 ) ;
    }

} ;

template < typename Function >
struct object_functor< Function , 2 >
{
    FUNCTION_OBJECT_FUNCTOR_DECL

    result_type operator () ( typename Function::arg1_type a1 ,
                              typename Function::arg2_type a2 ) const
    {
        FUNCTION_OBJECT_FUNCTOR_DEBUG( 2 ) ;

        detail::global_interpreter_lock lock;

        return call< result_type >( obj.get(), a1, a2 ) ;
    }

} ;

template < typename Function >
struct object_functor< Function , 3 >
{
    FUNCTION_OBJECT_FUNCTOR_DECL

    result_type operator () ( typename Function::arg1_type a1 ,
                              typename Function::arg2_type a2 ,
                              typename Function::arg3_type a3 ) const
    {
        FUNCTION_OBJECT_FUNCTOR_DEBUG( 3 ) ;

        detail::global_interpreter_lock lock;

        return call< result_type >( obj.get(), a1, a2, a3 ) ;
    }

} ;

// Etc. up to the minimum between the max arity of boost::function and
// boost::python::call<>
// It could be helped with BOOST_PP.


// Solution v2:
//
// Export boost::function with class_, that is, make it an real class type to
// Python, but keep the pyobject_to_function as before, striped out of the
// implicit stuff, and then just push_back this converter for the
// boost::function. If we do this push_back at the end, we can also profit from
// implicit convertions.
//
// However, maybe we could still scan the chain of converters to avoid the
// push_back order problem.
//
// With this solution, the code gets a lot simpler, we can always get a callable
// object when a function returns a boost::function, whatever is
// inside. However, if, in Python, we want to extract the content of a
// boost::function, we will probably have to do something as in the first
// version, but called manually instead of implicitly.

template < typename Function >
struct pyobject_to_function
{
    static void* convertible( PyObject* obj )
    {
        // Is there anyway to test for the callable object's arity? Otherwise, I
        // don't see what else we can check here.
        return PyCallable_Check( obj ) ? obj : 0 ;
    }

    static void construct( PyObject* obj ,
                           converter::rvalue_from_python_stage1_data* data )
    {
        using namespace boost::python::converter ;
        void* storage
            = ((rvalue_from_python_storage< Function >*)data)->storage.bytes ;

        new (storage) Function( object_functor< Function >( obj ) ) ;
        
        // record successful construction
        data->convertible = storage ;
    }
} ;

template < typename Function >
void export_function( const char* name )
{
    class_< Function >( name )
        .def( "__call__" , & Function::operator() )
        ;
}

template < typename Function >
void register_pyobject_to_function()
{
    boost::python::converter::registry::push_back(
        & pyobject_to_function< Function >::convertible ,
        & pyobject_to_function< Function >::construct ,
        type_id< Function >()
    ) ;
}

template < typename Functor ,
           typename Function >
void export_functor( const char* name )
{
    class_< Functor >( name )
        .def( "__call__" , & Functor::operator() )
        ;
    implicitly_convertible< Functor , Function >() ;
}

} // end namespace function

#endif
