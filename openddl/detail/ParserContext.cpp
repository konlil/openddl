#include "ParserContext.h"
#include "LiteralHelpers.h"
#include <iostream>

openddl::detail::ParserContext::ParserContext(const std::vector<Token> & tokens, std::vector<Command> & commands, std::vector<Error> & errors)
: tokens(tokens), commands(commands), errors(errors), reference_error(false)
{
}

void openddl::detail::ParserContext::push_literal(const Token * t, Command::LiteralPayload::encoding_t encoding)
{

	Command::LiteralPayload payload;
	payload.encoding = encoding;
	int error = 0;
	if(decode_literal(*t, payload) && (error = detect_limits(convert(*element_type),payload)) == 0)
		literals.push_back(payload);
	else
	{
		Error e;
		e.payload = t->payload;
		if (error > 0)
			e.message = "semantic.literal_limits(" + element_type->payload + ").overflow";
		else if (error < 0)
			e.message = "semantic.literal_limits(" + element_type->payload + ").underflow";
		else
			e.message = "parse.literal.out_of_range";
		errors.push_back(e);
	}
	
}

void openddl::detail::ParserContext::build_reference(const Token * t)
{
	if (!reference.empty() && t->payload[0] != '%')
		reference_error = true;
	reference.push_back(t->payload);
}

void openddl::detail::ParserContext::push_reference()
{
	if (reference_error)
	{
		Error e;
		std::string payload;
		for (auto & p : reference)
			payload += p + " ";
		payload.pop_back();
		e.payload = payload;
		e.message = "parse.literal.reference.illegal_global_name";
		errors.push_back(e);
	}
	else
	{
		Command::LiteralPayload payload;
		payload.encoding = Command::LiteralPayload::kReference;
		payload.value.reference_ = new std::vector<std::string>(reference);
		literals.push_back(payload);
	}
	reference.clear();
	reference_error = false;
}

void openddl::detail::ParserContext::push_data_list(Token const * type)
{
	element_type = type;
}
void openddl::detail::ParserContext::end_data_list()
{
	Command::DataListPayload payload;
	payload.type = convert(*element_type);
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