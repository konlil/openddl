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
		public:
			ParserContext(const std::vector<Token> & tokens, std::vector<Command> & commands, std::vector<Error> & errors);
			const std::vector<Token> & tokens; 
			std::vector<Command> & commands; 
			std::vector<Error> & errors;
		

			std::vector<int> parents;
			

		public:

			void push_list_type(Token const * type, Token const * name = nullptr);
			//Used with
			void push_literal_list(Command::LiteralPayload::encoding_t encoding,Token const * ts, Token const * te);

			
			void push_array_type(Token const * type, Token const * dimensions, Token const * name = nullptr);
			void push_array_element();
			void end_array();


			void push_structure(Token const * identifier, Token const * name = nullptr);
			void push_property(Token const * ts, Token const * te);
			void end_structure();

		private:
			int build_literal(Command::LiteralPayload::encoding_t encoding, Token const * ts, Token const * te, Command::LiteralPayload & payload);
		};
	}
}


