#include "Tree.h"
#include "detail/Error.h"
#include "detail/Command.h"
#include "detail/Token.h"
#include "detail/detail.h"

#include "exception.h"


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

