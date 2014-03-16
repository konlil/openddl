#pragma once
#include "..\detail.h"
#include "Token.h"
#include "Error.h"
#include "Command.h"

namespace openddl
{
	namespace detail
	{
		struct ParserContext
		{

			ParserContext(const std::vector<Token> & tokens, std::vector<Command> & commands, std::vector<Error> & errors);
			const std::vector<Token> & tokens; 
			std::vector<Command> & commands; 
			std::vector<Error> & errors;
		private:
			std::vector<Command::LiteralPayload> literals;
			std::vector<std::string> reference;
			Type element_type;
			unsigned int element_count;

		public:

			void push_literal(const Token * t,Command::LiteralPayload::encoding_t encoding);
			
			void build_reference(const Token * t);	//Used to push each component of the reference into array.
			void push_reference();					//Used to push built reference into command stream

			void push_array_element();
			void push_data_list(const Token & type);
			void end_data_list();
			void push_data_array_list(const Token & type, const Token & dimensions);
			void end_data_array_list();

		};
	}
}


