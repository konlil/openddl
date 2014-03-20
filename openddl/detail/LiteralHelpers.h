#pragma once
#include "detail.h"
#include "Token.h"
#include "Command.h"
#include <string>

namespace openddl
{
	namespace detail
	{
		Type convert(const Token & t);
		void encode_utf8(std::string & out, const char32_t token);
		int read_escape_character(std::string & out, const std::string & token, const int index);
		std::string * escape_string(const std::string & in);
		char consume_character(const std::string & in, int & position);
		uint64_t decode_integer(Token::token_t type, const std::string & in, bool & negate);
		//Return 1 if decoded literal would cause out of range return -1 if type mismatch
		int decode_literal(const Token & t, Command::LiteralPayload & payload);	
		//Return -1 if underflow, return 1 if overflow else return 0
		int detect_limits(Type type, const Command::LiteralPayload & payload);


	}
}
