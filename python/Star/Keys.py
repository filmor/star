
from _star.keys import *

def RegisterKeyCallback(func):
    _star.register_key_callback(func)

def UnregisterKeyCallback():
    _star.unregister_key_callback()

