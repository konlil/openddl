#include "ParserContext.h"
#include "LiteralHelpers.h"
#include <iostream>

openddl::detail::ParserContext::ParserContext(const std::vector<Token> & tokens, std::vector<Command> & commands, std::vector<Error> & errors)
: tokens(tokens), commands(commands), errors(errors)
{
}

void openddl::detail::ParserContext::push_literal(const Token * t, Command::LiteralPayload::encoding_t encoding)
{

	Command::LiteralPayload payload;
	payload.encoding = encoding;
	if(decode_literal(*t, payload))
		literals.push_back(payload);
	else
	{
		Error e;
		e.payload = t->payload;
		e.message = "Literal out of range";
		errors.push_back(e);
	}
	
}

void openddl::detail::ParserContext::build_reference(const Token * t)
{
	reference.push_back(t->payload);
}

void openddl::detail::ParserContext::push_reference()
{
	Command::LiteralPayload payload;

	payload.encoding = Command::LiteralPayload::kReference;
	payload.value.reference_ = new std::vector<std::string>(reference);
	literals.push_back(payload);
	reference.clear();
}

void openddl::detail::ParserContext::push_data_list(const Token & type)
{
	element_type = convert(type);
}
void openddl::detail::ParserContext::end_data_list()
{
	Command::DataListPayload payload;
	payload.type = element_type;
	payload.length = literals.size();
	payload.name = nullptr;
	Command command;
	command.type = Command::kDataList;
	command.payload.list_ = payload;
	commands.push_back(command);
	command.type = Command::kLiteral;
	for (auto & l : literals)
	{
		command.payload.literal_ = l;
		commands.push_back(command);
	}
	literals.clear();
}