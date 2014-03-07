#include "stdafx.h"
#include "Lexer.h"
#include <sstream>

void lex_error(const std::string & name, std::vector<openddl::TokenError> & errors, const char* p, const char * ts, const char* te, int line,int position)
{
	std::stringstream formatter;
	formatter <<"("<< line << ":" << position << ")";
	openddl::TokenError error;
	error.payload = std::string(ts,te);
	error.message = name + " @ " + formatter.str();
	error.range_start = unsigned int(ts-p);
	error.range_length = te - ts;
	errors.push_back(error);
}

void lex_emit(openddl::Token::type_t code, std::vector<openddl::Token>& tokens, const char* p, const char* ts, const char* te)
{

	if(code == openddl::Token::kString && tokens.size() && tokens.back().code == openddl::Token::kString)
	{
		//Concatenate two string literals if they are adjacent without intervening comma
		openddl::Token & t = tokens.back();
		t.payload = t.payload.substr(0,t.payload.length()-1) + std::string(ts+1,te);
		t.range_length = (te-p)-t.range_start;
	}
	else
	{

		//Create token on token stack
		openddl::Token t;
		t.code = code;

		t.payload = std::string(ts,te);

		t.range_start = unsigned int(ts-p);
		t.range_length = te - ts;

		tokens.push_back(t);
	}

}

#define e(t) lex_emit(t, tokens,input.c_str(), ts, te)
#define error(m,s,e) lex_error(m, errors,input.c_str(),s,e,curline,te-line_start)

%%{
  	machine Lexer;
	write data;

	action invalid_character_error {
		error("lex.invalid_character",te-1,p+1); 
		fgoto main;
	}
	action unterminated_character_literal{
		error("lex.unterminated_character_literal",ts,te);
	}
	recover_character_literal := ^"'"+ "'" @invalid_character_error @/unterminated_character_literal;

	action unterminated_string_literal{
		error("lex.unterminated_string_literal",ts,te);
	}
	recover_string_literal := ^'"'+ '"' @invalid_character_error @/unterminated_string_literal;

	newline = '\n' 
		%{ curline++; line_start = p;};
	escape_char = '\\' (["'\?\\abfnrtv]|'x' xdigit{2}) ;
	utf8 = (0x20..0x21) | (0x23..0x5B) | (0x5D..0x7E) |
		0xC2 (0xA0..0xBF) | (0xC3..0xDF) (0x80..0xBF) |
		0xE0 (0xA0..0xBF) (0x80..0xBF) | (0xE1..0xEC) (0x80..0xBF) (0x80..0xBF) |
		0xED (0x80..0x9F) (0x80..0xBF) | 0xEE (0x80..0xBF) (0x80..0xBF) |
		0xEF (0x80..0xBE) (0x80..0xBF) | 0xEF 0xBF (0x80..0xBD) |
		(0xF0..0xF3) (0x90..0xBF) (0x80..0xBF) (0x80..0xBF) |
		0xF4 (0x90..0xBF) (0x80..0xBF) (0x80..0xBF);

	block_comment = '/*' ( any-'\n' | newline  | '/*' @{error("lex.nested_block_comment",ts,te);} )*  :>> '*/';
	
	decimal_literal = [+\-]? digit+;
	binary_literal = [+\-]? '0' [bB] [01]+;
	hex_literal = [+\-]? '0' [xX] xdigit+;
	float_literal = [+\-]? (digit* '.' digit+ ([eE] [+\-]? digit+)? | digit+ ([eE] [+\-]? digit+)?);
	character_literal = "'" 
							((0x20..0x26|0x28..0x5B|0x5D..0x7E) %{characters_consumed++;}|escape_char %{characters_consumed++;})+ >{characters_consumed = 0;}
						:>> "'";

	bool_literal = 'true' | 'false';

	integer_literal = (decimal_literal|hex_literal|binary_literal|character_literal);
	

	data_type = 'bool' | 'int8' | 'int16' | 'int32' | 'int64' |
				'unsigned_int8' | 'unsigned_int16' | 'unsigned_int32' | 'unsigned_int64' |
				'float' | 'double' | 'string' | 'ref' | 'type';

	name = (alpha | '_' ) (alnum | '_')* - data_type;
	identifier = [$%] name;
	main := 
	|*
		# Numeric Literals
		decimal_literal		=>	{ e(openddl::Token::kDecimal); };
		hex_literal			=>	{ e(openddl::Token::kHex);};
		binary_literal		=>	{ e(openddl::Token::kBinary);};
		float_literal		=>	{ e(openddl::Token::kFloat);};
		#Fallback rule to catch improperly formatted numeric literals
		(decimal_literal|hex_literal|binary_literal|float_literal) ^(0x01..0x20|[,{}])+ 
							=> { error("lex.invalid_literal",ts,te);};

		#Boolean Literal
		bool_literal		=>	{ e(openddl::Token::kBoolean);};

		# Name
		name				=>	{ e(openddl::Token::kName);};
		identifier			=>	{ e(openddl::Token::kIdentifier);};

		#Type Names
		data_type			=>	{ e(openddl::Token::kDataType);};
		data_type '[' integer_literal ']'
							=>	{ e(openddl::Token::kArrayDataType);};

		# String Literals
		'"' (utf8|escape_char|'\\u' xdigit{4}|'\\U' xdigit{6})* :>> '"' 
							=> { e(openddl::Token::kString);};
		# Fallback path for catching errors
		'"'					=> { fgoto recover_string_literal;};

		# Character Literal
		character_literal	=> { if(characters_consumed > 7) error("lex.character_length_error",ts,te); else e(openddl::Token::kCharacter);}; 
		# Fallback path for catching errors
		"'"					=> { fgoto recover_character_literal;};

		# Comments
		'//' [^\n]*;
		block_comment;

		# Structural characters
		',' =>						{ e(openddl::Token::kComma);};
		'{' =>						{ e(openddl::Token::kLeftBrace);};
		'}' =>						{ e(openddl::Token::kRightBrace);};
		'*/' =>						{error("lex.free_close_comment",ts,te);};
		# Whitespace
		(0x01..0x20)-'\n';
		newline;
		any => { error("lex.unrecognised_character",ts,te);};

	*|;
	  
}%%


bool openddl::lex(const std::string & input,std::vector<Token> &tokens,std::vector<TokenError> & errors)
{
	int characters_consumed = 0;
	
	char const *p = input.c_str();
	char const *char_error = 0;

	//End
	char const *pe = p + input.length();
	char const *eof = pe;

	//State
	int cs = 0, act, have = 0, curline = 1;
	char const *ts = 0; 
	char const *te = 0;
	int done = 0;

	char const *line_start = p;
	%% write init;
	%% write exec;
	
	return (p==pe);
}

