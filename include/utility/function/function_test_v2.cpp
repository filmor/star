#include "function_v2.hpp"

////////////////////////////////////////////////////////////////////////////////
// Example usage

template < typename Func >
void call_func( Func f )
{
    f() ;
}

template < typename Func >
Func identity( Func f )
{
    return f ;
}

struct functor
{
    void operator () () const
    {
        ::std::cout << "functor" << ::std::endl ;
    }
} ;

struct functor2
{
    void operator () () const
    {
        ::std::cout << "functor2" << ::std::endl ;
    }
} ;

void c_func()
{
    ::std::cout << "c_func" << ::std::endl ;
}

typedef boost::function< void () > function_type ;

function_type get_c_func()
{
    return function_type( & c_func ) ;
}

BOOST_PYTHON_MODULE( function_v2 )
{
    // We first need to call this
    function::export_function< function_type >( "Function" ) ;

    def( "call_func" , & call_func< function_type > ) ;

    function::export_functor< functor , function_type >( "Functor" ) ;
    function::export_functor< functor2 , function_type >( "Functor2" ) ;

    def( "identity" , & identity< function_type > ) ;

    def( "c_func" , & c_func ) ;
    def( "get_c_func" , & get_c_func ) ;

    // Make this the last call to allow precedent of implicit functor convertion.
    // Problem: What about other modules using this one?
    function::register_pyobject_to_function< function_type >() ;
}
