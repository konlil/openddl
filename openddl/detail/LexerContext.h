#pragma once
#include <string>
#include <vector>
#include "Error.h"
#include "Token.h"

namespace openddl
{
	namespace detail
	{

		struct LexerContext
		{
			std::vector<Error> & errors;
			std::vector<Token> & tokens;
			const std::string & input;
		private:
			int line;
			char const * line_start;
			int characters_consumed;

		public:
			LexerContext(const std::string & _i, std::vector<Token> & _t, std::vector<Error> & _e);

			void reset_count() { characters_consumed = 0; }
			void count_character() { characters_consumed++; }
			int get_character_count() { return characters_consumed; }

			void new_line(const char * p);

			void lex_error(const std::string & name, unsigned int ts, unsigned int te);
			void lex_error(const std::string & name, unsigned int ts, char const* te);
			void lex_error(const std::string & name, char const* ts, unsigned int te);
			void lex_error(const std::string & name, const char * ts, const char* te);

			void lex_emit(Token::token_t t_type, const char* ts, const char* te);
		};

	}
}
