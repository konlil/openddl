openddl (codeinoz.tumblr.com)
=======

OpenDDL Parser written in C++. Current status is pre-alpha. 

Parser and Lexer have been written with Ragel and have a set of compliance tests for each. 
All components in the detail namespace are completely functional and tested. Focus is now
on implementing a C++ API with all the bells and whistles developers are used to in a fluent
API.

Memory management (Destructor/Constructor) for openddl::detail::Command is yet to be implemented.

