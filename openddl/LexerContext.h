#pragma once

#include "Lexer.h"
namespace Lexer
{
	struct Context
	{
		
		
		std::vector<openddl::TokenError> & errors;
		std::vector<openddl::Token> & tokens;
		const std::string & input;
	private:
		int line;
		char const * line_start;
		int characters_consumed;

	public:
		Context(const std::string & _i, std::vector<openddl::Token> & _t, std::vector<openddl::TokenError> & _e);

		void reset_count() {characters_consumed = 0;}
		void count_character() { characters_consumed++; }
		int get_character_count() { return characters_consumed;  }

		void new_line(const char * p);

		void lex_error(const std::string & name, unsigned int ts, unsigned int te);
		void lex_error(const std::string & name, unsigned int ts, char const* te);
		void lex_error(const std::string & name, char const* ts, unsigned int te);
		void lex_error(const std::string & name, const char * ts, const char* te);

		void lex_emit(openddl::Token::token_t t_type, const char* ts, const char* te);
	};

}


