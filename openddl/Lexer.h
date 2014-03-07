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
		std::string payload;
		std::string message;
		unsigned int range_start;
		unsigned int range_length;
	};
	bool lex(const std::string & input, std::vector<Token> &tokens, std::vector<TokenError> & errors);
};



