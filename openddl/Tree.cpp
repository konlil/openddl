#include "Tree.h"
#include "detail\Error.h"
#include "detail\Command.h"
#include "detail\Token.h"
#include "detail.h"
#include <sstream>

openddl::ParseError::ParseError(std::vector<openddl::detail::Error> & e)
: _errors(std::move(e)) {}
openddl::LexerError::LexerError(std::vector<openddl::detail::Error> & e)
: _errors(std::move(e)) {}

const char * openddl::ParseError::what()
{
	return "An error occurred during parsing";
}
const char * openddl::LexerError::what()
{
	return "An error occurred during lexing";
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

openddl::Tree openddl::Tree::parse(const std::string & i)
{
	Tree t;
	std::vector<detail::Command> commands;
	std::vector<detail::Token> tokens;
	std::vector<detail::Error> errors;
	if (!detail::lex(i, tokens, errors))
	{
		throw LexerError(errors);
	}
	else if (!detail::parse(tokens, commands, errors))
	{
		throw ParseError(errors);
	}
	t.commands = std::move(commands);
	return std::move(t);
}

openddl::Tree::Tree()
{

}

openddl::Tree::Tree(Tree&&t)
{
	commands = std::move(t.commands);
}

