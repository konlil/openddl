//================================================================================================================
// Copyright 2014 Denis Hilliard (armchaircommando@gmail.com)
// Licensed under MIT License
//================================================================================================================

#include "stdafx.h"
#include "Lexer.h"
#include "LexerContext.h"

#define error(m) context.lex_error(m,ts,te)


#define token(t)	context.lex_emit(t,openddl::Token::kInvalidType,openddl::Token::kInvalidLiteral, ts, te)
#define literal(t)	context.lex_emit(openddl::Token::kLiteral,openddl::Token::kInvalidType,t, ts, te)
#define datatype(t) context.lex_emit(openddl::Token::kDataType,t,openddl::Token::kInvalidLiteral, ts, te)
#define arraytype() context.lex_emit(openddl::Token::kArrayType,openddl::Token::kInvalidType,openddl::Token::kInvalidLiteral, ts, te)


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
		error("lex.unterminated_character_literal");
	}
	recover_character_literal := ^"'"+ "'" >{ char_error = p;} @invalid_character_error @/unterminated_character_literal;

	action unterminated_string_literal{
		error("lex.unterminated_string_literal");
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


	name = (alpha | '_' ) (alnum | '_')* - data_type -'null';
	identifier = [$%] name;
	main := 
	|*
		# Numeric Literals
		decimal_literal		=>	{ literal(openddl::Token::kDecimalLiteral); };
		hex_literal			=>	{ literal(openddl::Token::kHexLiteral);};
		binary_literal		=>	{ literal(openddl::Token::kBinaryLiteral);};
		float_literal		=>	{ literal(openddl::Token::kFloatLiteral);};
		#Fallback rule to catch improperly formatted numeric literals
		(decimal_literal|hex_literal|binary_literal|float_literal) ^(0x01..0x20|[},\]])+ 
							=> { error("lex.invalid_literal");};

		#Boolean Literal
		bool_literal		=>	{ literal(openddl::Token::kBooleanLiteral);};

		# Name
		name				=>	{ token(openddl::Token::kName);};
		identifier			=>	{ token(openddl::Token::kIdentifier);};
		'null'				=>	{ token(openddl::Token::kNull);};

		#Type Names
		'bool'				=>	{ datatype(openddl::Token::kBool);};
		'int8'				=>	{ datatype(openddl::Token::kInt8);};
		'int16'				=>	{ datatype(openddl::Token::kInt16);};
		'int32'				=>	{ datatype(openddl::Token::kInt32);};
		'int64'				=>	{ datatype(openddl::Token::kInt64);};
		'unsigned_int8'		=>	{ datatype(openddl::Token::kUnsignedInt8);};
		'unsigned_int16'	=>	{ datatype(openddl::Token::kUnsignedInt16);};
		'unsigned_int32'	=>	{ datatype(openddl::Token::kUnsignedInt32);};
		'unsigned_int64'	=>	{ datatype(openddl::Token::kUnsignedInt64);};
		'float'				=>	{ datatype(openddl::Token::kFloat);};
		'double'			=>	{ datatype(openddl::Token::kDouble);};
		'ref'				=>	{ datatype(openddl::Token::kRef);};
		'string'			=>	{ datatype(openddl::Token::kString);};
		'type'				=>  { datatype(openddl::Token::kType);};
		
	

		# String Literals
		'"' (utf8|escape_char|'\\u' xdigit{4}|'\\U' xdigit{6})* :>> '"' 
							=> { literal(openddl::Token::kStringLiteral);};
		# Fallback path for catching errors
		'"'					=> { fgoto recover_string_literal;};

		# Character Literal
		character_literal	=> { if(context.get_character_count() > 7) error("lex.character_length_error"); else literal(openddl::Token::kCharacterLiteral);}; 
		# Fallback path for catching errors
		"'"					=> { fgoto recover_character_literal;};

		# Comments
		'//' [^\n]*;
		block_comment;

		# Structural characters
		',' =>						{ token(openddl::Token::kComma);};
		'{' =>						{ token(openddl::Token::kLeftBrace);};
		'}' =>						{ token(openddl::Token::kRightBrace);};
		'['	=>						{ token(openddl::Token::kLeftSquareBracket);};
		']'	=>						{ token(openddl::Token::kRightSquareBracket);};
		'=' =>						{ token(openddl::Token::kEquals);};
		'*/' =>						{error("lex.trailing_close_comment");};
		# Whitespace
		(0x01..0x20)-'\n';
		newline;
		any => { error("lex.unrecognised_character");};

	*|;
	  
}%%


bool openddl::lex(const std::string & input,std::vector<Token> &tokens,std::vector<TokenError> & errors)
{
	Lexer::Context context(input,tokens,errors);
	
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
	
	return (p==pe);
} 

