openddl (codeinoz.tumblr.com)
=======

OpenDDL Parser written in C++. Current status is pre-alpha. 

Parser and Lexer have been written with Ragel and have a set of compliance tests for each. 
All components in the detail namespace are essentially functional and tested but are in need of
their completed API counterpart to handle coercion of numeric literals/properties to C++ types
amongst others.

Other operations such as unescaping openddl encoded strings are left as a user invoked operation 
and are not done automatically (unless a case for such can be made).

Memory management (Destructor/Constructor) for openddl::detail::Command is yet to be implemented.

