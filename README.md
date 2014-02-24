openddl
=======

OpenDDL Parser written in C++. Current status is pre-alpha. 

All low level (integer/float/double/string) token parsing functions have 
been written and a number of tests for each.
Internal functions have been moved to the detail namespace but need a 
comprehensive set of tests written.

Some clean up/reorganisation is needed to make certain functions much 
easier to understand.

Phase 2 is now complete, as tokenising functions have been written and tested.

Phase 3 is now under way which is specifying the structure & implementing 
token stream to structure conversion functions.
