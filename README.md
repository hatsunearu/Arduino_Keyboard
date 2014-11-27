Arduino_Keyboard
================

Arduino sketch and circuit for a simple, no-parts keyboard matrix.

You can either opt to use diodes (sometimes built-in to switches) and double the amount of keys supported. 

For a diodeless switch matrix, you need an n by m switch matrix where n * m = number of keys.

For a diode switch matrix, you need an n by m switch matrix where 2 * n * m = number of keys, and d diodes where d is the lesser of n and m.
