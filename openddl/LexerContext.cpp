#include "LexerContext.h"


Lexer::Context::Context(const std::string & _i, std::vector<openddl::Token> & _t, std::vector<openddl::TokenError> & _e)
: errors(_e), tokens(_t), input(_i), line(1), line_start(_i.c_str()), characters_consumed(0) {}

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
	error.line = line;
	error.position = ts - line_start;
	error.range_start = ts - input.c_str();
	error.range_length = te - ts;
	errors.push_back(error);
}
void Lexer::Context::lex_emit(openddl::Token::token_t t_type, openddl::Token::type_t d_type, openddl::Token::literal_t l_type, const char* ts, const char* te)
{

	if (t_type == openddl::Token::kArrayType)
	{
		if (tokens.size())
		{
			openddl::Token & prev = tokens.back();
			if (prev.token_type == openddl::Token::kDataType)
			{
				if (prev.range_start + prev.range_length == ts - input.c_str())
				{
					prev.token_type = openddl::Token::kArrayType;
					prev.range_length += te - ts;
					prev.payload += std::string(ts, te);
					//Flag error if array size value is negative.
					//prev.array_size = openddl::parse_unsigned_integer(std::string(ts+1,te-1));
				}
				else
					lex_error("lex.invalid_array_notation", prev.range_start, te);
			}			
			else
				lex_error("lex.invalid_characters",ts,te);
		}
		else
			lex_error("lex.invalid_characters",ts,te);


	}
	else if (l_type == openddl::Token::kStringLiteral && tokens.size() && tokens.back().literal_type == openddl::Token::kStringLiteral)
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
		t.data_type = d_type;
		t.literal_type = l_type;

		t.payload = std::string(ts, te);

		t.line = line;
		t.position = te - line_start;
		t.range_start = unsigned int(ts - input.c_str());
		t.range_length = te - ts;

		tokens.push_back(t);
	}

}
