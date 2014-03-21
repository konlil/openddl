OpenDDL Parser (0.1.2)
=======
I've reached the first numbered release after about 2 weeks of on and off work. 

Parser and Lexer have been written with Ragel and have a set of compliance tests for each. 
All components in the detail namespace are completely functional in their current state.
Focus is now on improving these for ease of development and clarity, then speed/memory usage.

An experimental C++ Wrapper API is in development in Tree.h/.cpp in the openddl subdirectory
and the demo has been updated to make use of this. However it is non functional for anything 
other than validating a function. First implementation of the API (0.4) depends on the 0.2 milestone
in which the Parser and all semantic validation will be split into seperate stages.

Otherwise, it would be possible for someone so inclined to write a CLI or P/Invoke shim and use the 
Lexer and Parser as is to bring support for OpenDDL to C#.



