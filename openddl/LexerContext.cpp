#include "LexerContext.h"


Lexer::Context::Context(const std::string & _i, std::vector<openddl::Token> & _t, std::vector<openddl::TokenError> & _e)
: errors(_e), tokens(_t), input(_i), line(1), line_start(_i.c_str()), characters_consumed(0) {}

void Lexer::Context::new_line(const char * p)
{
	line++;
	line_start = p;
}
void Lexer::Context::lex_error(const std::string & name, unsigned int ts, unsigned int te)
{
	lex_error(name, input.c_str() + ts, input.c_str() + te);
}
void Lexer::Context::lex_error(const std::string & name, unsigned int ts, char const* te)
{
	lex_error(name, input.c_str() + ts, te);
}
void Lexer::Context::lex_error(const std::string & name, char const* ts, unsigned int te)
{
	lex_error(name, ts, input.c_str() + te);
}

void Lexer::Context::lex_error(const std::string & name, const char * ts, const char* te)
{
	openddl::TokenError error;
	error.payload = std::string(ts, te);
	error.message = name;
	error.range_start = ts - input.c_str();
	error.range_length = te - ts;
	errors.push_back(error);
}
void Lexer::Context::lex_emit(openddl::Token::token_t t_type, const char* ts, const char* te)
{

	if (t_type == openddl::Token::kStringLiteral && tokens.size() && tokens.back().token_type == openddl::Token::kStringLiteral)
	{
		//Concatenate two string literals if they are adjacent without intervening comma
		openddl::Token & t = tokens.back();
		t.payload = t.payload.substr(0, t.payload.length() - 1) + std::string(ts + 1, te);
		t.range_length = (te - input.c_str()) - t.range_start;
	}
	else
	{

		//Create token on token stack
		openddl::Token t;
		t.token_type = t_type;
		t.payload = std::string(ts, te);
		t.range_start = unsigned int(ts - input.c_str());
		t.range_length = te - ts;

		tokens.push_back(t);
	}

}
