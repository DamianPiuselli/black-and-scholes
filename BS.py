"""
    To include C code in Python, you can use the ctypes library, which allows you to call C functions from Python.

Here's an example of how you can use ctypes to call the Black-Scholes function from the C code above:

Note that you will need to compile the C code into a shared library (.so file) first, using a tool like GCC. You can then pass the path to the shared library to the CDLL() function to load it.

For example, to compile the C code above into a shared library called black_scholes.so, you can use the following command:
"""

import ctypes

# Load the C library
lib = ctypes.CDLL("./BS.so")

# Set the argument types and return type
lib.call_price.argtypes = [
    ctypes.c_double,
    ctypes.c_double,
    ctypes.c_double,
    ctypes.c_double,
    ctypes.c_double,
]
lib.call_price.restype = ctypes.c_double

lib.put_price.argtypes = [
    ctypes.c_double,
    ctypes.c_double,
    ctypes.c_double,
    ctypes.c_double,
    ctypes.c_double,
]
lib.put_price.restype = ctypes.c_double

# Call the C functions
S = 50.0
K = 52.0
r = 0.05
v = 0.2
T = 0.5
call = lib.call_price(S, K, r, v, T)
put = lib.put_price(S, K, r, v, T)

print("Call price:", call)
print("Put price:", put)
