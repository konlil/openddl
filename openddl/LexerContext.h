#pragma once

#include "Lexer.h"
namespace Lexer
{
	struct Context
	{
		
		
		std::vector<openddl::TokenError> & errors;
		std::vector<openddl::Token> & tokens;
		const std::string & input;
		int line;
		char const * line_start;
		int characters_consumed;


		Context(const std::string & _i, std::vector<openddl::Token> & _t, std::vector<openddl::TokenError> & _e);

		void lex_error(const std::string & name, unsigned int ts, unsigned int te);
		void lex_error(const std::string & name, unsigned int ts, char const* te);
		void lex_error(const std::string & name, char const* ts, unsigned int te);
		void lex_error(const std::string & name, const char * ts, const char* te);

		void lex_emit(openddl::Token::token_t t_type, openddl::Token::type_t d_type, openddl::Token::literal_t l_type, const char* ts, const char* te);
	};

}


