from function_v2 import *

f = Functor()
call_func( f )

def pyfunc() : print "pyfunc"
call_func( pyfunc )

call_func( c_func )

i = identity( f )
i()

i = identity( pyfunc )
i()

cf = get_c_func()
cf()

# Expected output:
# functor
# object_functor0: pyfunc
# object_functor0: c_func
# functor
# pyfunc
# c_func
