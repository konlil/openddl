//================================================================================================================
// Copyright 2014 Denis Hilliard (armchaircommando@gmail.com)
// Licensed under MIT License
//================================================================================================================

#include "..\stdafx.h"
#include "detail.h"
#include "LexerContext.h"
#include <iostream>

#define error(m) context.lex_error(m,ts,te)


#define token(t)	context.lex_emit(t, ts, te)



%%{
  	machine Lexer;
	write data;

	action count_character { context.count_character();}
	action reset_count { context.reset_count(); }
	
	action invalid_character_error {
		context.lex_error("lex.invalid_character",te-1,p+1); 
		fgoto main;
	}
	action unterminated_character_literal{
		context.lex_error("lex.unterminated_character_literal",te-1,p+1);
	}
	recover_character_literal := ^"'"+ "'" >{ char_error = p;} @invalid_character_error @/unterminated_character_literal;

	action unterminated_string_literal{
		error("lex.unterminated_string_literal");
		fbreak;
	}
	action unterminated_block_comment{
		error("lex.unterminated_block_comment"); 
		//Skip forward to end of file
		fexec(pe); fbreak;
	}
	recover_string_literal := ^'"'+ '"' >{ char_error = p;} @invalid_character_error @/unterminated_string_literal;

	newline = '\n' 
		%{ context.new_line(p);};
	escape_char = '\\' (["'\?\\abfnrtv]|'x' xdigit{2}) ;
	utf8 = (0x20..0x21) | (0x23..0x5B) | (0x5D..0x7E) |
		0xC2 (0xA0..0xBF) | (0xC3..0xDF) (0x80..0xBF) |
		0xE0 (0xA0..0xBF) (0x80..0xBF) | (0xE1..0xEC) (0x80..0xBF) (0x80..0xBF) |
		0xED (0x80..0x9F) (0x80..0xBF) | 0xEE (0x80..0xBF) (0x80..0xBF) |
		0xEF (0x80..0xBE) (0x80..0xBF) | 0xEF 0xBF (0x80..0xBD) |
		(0xF0..0xF3) (0x90..0xBF) (0x80..0xBF) (0x80..0xBF) |
		0xF4 (0x90..0xBF) (0x80..0xBF) (0x80..0xBF);

	block_comment = '/*' ( any-'\n' | newline  | '/*' @{error("lex.nested_block_comment");} )*  :>> '*/' @!unterminated_block_comment;
	
	decimal_literal = [+\-]? digit+;
	binary_literal = [+\-]? '0' [bB] [01]+;
	hex_literal = [+\-]? '0' [xX] xdigit+;
	float_literal = [+\-]? (digit* '.' digit+ ([eE] [+\-]? digit+)? | digit+ ([eE] [+\-]? digit+)?);
	character_literal = "'" 
							((0x20..0x26|0x28..0x5B|0x5D..0x7E) %count_character|escape_char %count_character)+ >reset_count
						:>> "'";

	bool_literal = 'true' | 'false';

	integer_literal = (decimal_literal|hex_literal|binary_literal|character_literal);
	

	data_type = 'bool' | 'int8' | 'int16' | 'int32' | 'int64' |
				'unsigned_int8' | 'unsigned_int16' | 'unsigned_int32' | 'unsigned_int64' |
				'float' | 'double' | 'string' | 'ref' | 'type';


	identifier = (alpha | '_' ) (alnum | '_')* - data_type -'null';
	main := 
	|*
		# Numeric Literals
		decimal_literal		=>	{ token(Token::kDecimalLiteral); };
		hex_literal			=>	{ token(Token::kHexLiteral);};
		binary_literal		=>	{ token(Token::kBinaryLiteral);};
		float_literal		=>	{ token(Token::kFloatLiteral);};
		#Fallback rule to catch improperly formatted numeric literals
		(decimal_literal|hex_literal|binary_literal|float_literal) ^(0x01..0x20|[},\]])+ 
							=> { error("lex.invalid_literal");};

		#Boolean Literal
		bool_literal		=>	{ token(Token::kBooleanLiteral);};

		# Name
		'%' identifier		=>	{ token(Token::kLocalName);};
		'$' identifier		=>	{ token(Token::kGlobalName);};
		identifier			=>	{ token(Token::kIdentifier);};
		'null'				=>	{ token(Token::kNull);};

		#Type Names
		'bool'				=>	{ token(Token::kBool);};
		'int8'				=>	{ token(Token::kInt8);};
		'int16'				=>	{ token(Token::kInt16);};
		'int32'				=>	{ token(Token::kInt32);};
		'int64'				=>	{ token(Token::kInt64);};
		'unsigned_int8'		=>	{ token(Token::kUnsignedInt8);};
		'unsigned_int16'	=>	{ token(Token::kUnsignedInt16);};
		'unsigned_int32'	=>	{ token(Token::kUnsignedInt32);};
		'unsigned_int64'	=>	{ token(Token::kUnsignedInt64);};
		'float'				=>	{ token(Token::kFloat);};
		'double'			=>	{ token(Token::kDouble);};
		'ref'				=>	{ token(Token::kRef);};
		'string'			=>	{ token(Token::kString);};
		'type'				=>  { token(Token::kType);};
		
	

		# String Literals
		('"' ( any - [\n"] | newline )* :>> '"' @/unterminated_string_literal) => { token(Token::kStringLiteral);};


		# Character token
		character_literal	=> { if(context.get_character_count() > 7) error("lex.character_length_error"); else token(Token::kCharacterLiteral);}; 
		# Fallback path for catching errors
		"'"					=> { fgoto recover_character_literal;};

		# Comments
		'//' [^\n]*;
		block_comment;

		# Structural characters
		',' =>						{ token(Token::kComma);};
		'(' =>						{ token(Token::kLeftBracket);};
		')' =>						{ token(Token::kRightBracket);};
		'{' =>						{ token(Token::kLeftBrace);};
		'}' =>						{ token(Token::kRightBrace);};
		'['	=>						{ token(Token::kLeftSquareBracket);};
		']'	=>						{ token(Token::kRightSquareBracket);};
		'=' =>						{ token(Token::kEquals);};
		'*/' =>						{error("lex.trailing_close_comment");};
		# Whitespace
		(0x01..0x20)-'\n';
		newline;
		any => { error("lex.unrecognised_character");};

	*|;
	  
}%%


bool openddl::detail::lex(const std::string & input,std::vector<Token> & tokens, std::vector<Error> & errors)
{
	LexerContext context(input,tokens,errors);
	
	char const *p = input.c_str();
	//Tracks the character which caused the character error within string or character literal
	const char *char_error = 0;

	//End
	char const *pe = p + input.length();
	char const *eof = pe;

	//State
	int cs = 0, act, have = 0;
	char const *ts = 0; 
	char const *te = 0;
	int done = 0;

	%% write init;
	%% write exec;
	
	return p==pe && errors.empty();
} 


