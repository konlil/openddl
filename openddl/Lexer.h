//================================================================================================================
// Copyright 2014 Denis Hilliard (armchaircommando@gmail.com)
// Licensed under MIT License
//================================================================================================================
#pragma once
#include <vector>
#include <iostream>
#include <string>
namespace openddl
{
	struct Token
	{
		enum token_t
		{
			kLeftSquareBracket,
			kRightSquareBracket,
			kComma,
			kLeftBrace,
			kRightBrace,	
			kArrayType,
			kDataType,
			kIdentifier,
			kName,
			kLiteral,
			kEquals,
			kNull
			
		};
		enum type_t
		{
			kFloat,
			kDouble,
			kRef,
			kUnsignedInt8,
			kUnsignedInt16,
			kUnsignedInt32,
			kUnsignedInt64,
			kInt8,
			kInt16,
			kInt32,
			kInt64,
			kBool,
			kString,
			kType,
			kInvalidType
		};
		enum literal_t
		{
			kBooleanLiteral = 1 << 0,
			kFloatLiteral = 1 << 1,
			kHexLiteral = 1 << 2,
			kDecimalLiteral = 1 << 3,
			kBinaryLiteral = 1 << 4,
			kStringLiteral = 1 << 5,
			kCharacterLiteral = 1 << 6,
			kInvalidLiteral = 0
		};

		token_t		token_type;			
		type_t		data_type;			//Used only if token_type == kDataType || kArrayType
		literal_t	literal_type;		//Used only if token_type == kLiteral
		unsigned int array_size;		//Set to value within braces if type array notation is used.

		std::string payload;

		
		unsigned int line, position;
		unsigned int range_start;
		unsigned int range_length;

	};
	bool has_intervening_whitespace(const Token & a, const Token & b);
	struct TokenError
	{
		
		std::string payload;				//The literal (as string) which caused the error
		std::string message;				//Plain text key describing error		
		unsigned int line, position;		//Position of the error within the string/file
		unsigned int range_start;			//Position of offset of offending literal in string
		unsigned int range_length;
	};

	//Will only return false if an internal error has occurred and not all input was consumed.
	//Accepts an input string, emitting successfully parsed tokens and errors into seperate arrays
	//If any errors exist, the token stream should not be used as it will not be in a valid state.
	//Internally performs the following duties;
	//	(Lexical) Validation of literals
	//	Concatenating adjacent string literals
	//	Consuming whitespace/comments
	bool lex(const std::string & input, std::vector<Token> &tokens, std::vector<TokenError> & errors);
};



