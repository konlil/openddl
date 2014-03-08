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
		enum type_t
		{
			kArrayDataType,
			kDataType,
			kIdentifier,
			kName,
			kBoolean,
			kFloat,
			kHex,
			kDecimal,
			kBinary,
			kString,
			kCharacter,
			kComma,
			kLeftBrace,
			kRightBrace,
		};

		type_t code;
		std::string payload;
		unsigned int range_start;
		unsigned int range_length;

	};
	struct TokenError
	{
		
		std::string payload;				//The literal (as string) which caused the error
		std::string message;				//Plain text key describing error		
		std::string position;				//Position of the error within the string/file
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



