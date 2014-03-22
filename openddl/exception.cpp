#include "exception.h"
#include <sstream>

openddl::ParseError::ParseError(std::vector<openddl::detail::Error> & e)
: _errors(std::move(e)) {}
openddl::LexerError::LexerError(std::vector<openddl::detail::Error> & e)
: _errors(std::move(e)) {}
openddl::SemanticError::SemanticError(std::vector<openddl::detail::Error> & e)
: _errors(std::move(e)) {}

const char * openddl::ParseError::what()
{
	return "An error occurred during parsing";
}
const char * openddl::LexerError::what()
{
	return "An error occurred during lexing";
}
const char * openddl::SemanticError::what()
{
	return "A semantic error occurred";
}

std::string openddl::LexerError::errors()
{
	std::stringstream out;
	for (auto & e : _errors)
		out << "-- " << e.message << ": " << e.payload << std::endl;
	return std::move(out.str());
}
std::string openddl::ParseError::errors()
{
	std::stringstream out;
	for (auto & e : _errors)
		out << "-- " << e.message << std::endl;
	return std::move(out.str());
}
std::string openddl::SemanticError::errors()
{
	std::stringstream out;
	for (auto & e : _errors)
		out << "-- " << e.message << std::endl;
	return std::move(out.str());
}
