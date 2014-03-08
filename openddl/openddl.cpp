//================================================================================================================
// Copyright 2014 Denis Hilliard (armchaircommando@gmail.com)
// Licensed under MIT License
//================================================================================================================

#include "Lexer.h"
#include <string>
#include <iostream>

const char * token_name(openddl::Token & t)
{
	using openddl::Token;
	switch (t.token_type)
	{
	case Token::kArrayType:
		return "Array Data Type";
	case Token::kLiteral:
		return "Literal";
	case Token::kIdentifier:
		return "Identifier";
	case Token::kLeftBrace:
		return "Left Brace";
	case Token::kRightBrace:
		return "Right Brace";
	case Token::kComma:
		return "Comma";
	case Token::kName:
		return "Name";
	case Token::kDataType:
		return "Data Type";
	default:
		return "Undefined";
	}
}

int main(int argc, char * argv[])
{
	std::string out;
	std::string input = 
		"float[3]\n"
		"{\n"
		"	1,2,3,4,5\n"
		" }";
	std::vector<openddl::Token> tokens;
	std::vector<openddl::TokenError> errors;
	bool success = openddl::lex(input, tokens, errors);

	std::cout << "=================================================================" << std::endl;
	if (errors.size())
		for (auto & error : errors)
			std::cout << error.message << " (" << error.line << ":" << error.position << "): " << error.payload << std::endl;
	else
	{
		for (auto & token : tokens)
			std::cout << token_name(token) << " : " << token.payload << std::endl;
	}
	
	std::cout << "=================================================================" << std::endl;
	
	return 0;
}