# LED_multiplexer

Compatable with my 32bit shift register driven LED matrix.

Version 1.0 produces a scrolling rainbow effect by offsetting the order in which bits are read.

Version 2.0 produces an alternating rainbow pattern using hex values to encode entire "scanlines" in a single data structure. This allows the creation of arbitrary patterns.

Version 2.1 produces a 6 pixel chasing pattern using a basic python file to turn small picture files into animation data, which must then be copied into the arduino source file.
