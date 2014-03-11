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
			kIdentifier,
			kName,
			kEquals,
			kNull,
			kBooleanLiteral,
			kFloatLiteral,
			kHexLiteral,
			kDecimalLiteral,
			kBinaryLiteral,
			kStringLiteral,
			kCharacterLiteral,
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
			kType
		};

		bool is_float_encoded() const;
		bool is_integer_encoded() const;
		bool is_data_type() const;

		token_t		token_type;			

		std::string payload;

		unsigned int range_start;
		unsigned int range_length;

	};
	inline bool has_intervening_whitespace(const Token & a, const Token & b) { return (a.range_start + a.range_length) != b.range_start; }
	struct TokenError
	{
		
		std::string payload;				//The literal (as string) which caused the error
		std::string message;				//Plain text key describing error		

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



