//================================================================================================================
// Copyright 2014 Denis Hilliard (armchaircommando@gmail.com)
// Licensed under MIT License
//================================================================================================================

#include "Lexer.h"
#include "Literal.h"
#include <string>
#include <iostream>

const char * token_name(openddl::Token & t)
{
	using openddl::Token;
	switch (t.token_type)
	{
	case Token::kLeftSquareBracket:
		return "Left Square Bracket";
	case Token::kRightSquareBracket:
		return "Right Square Bracket";
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
	try{
	std::string out;
	std::string input =
		"\"Hello\" true";

	std::vector<openddl::Token> tokens;
	std::vector<openddl::TokenError> errors;
	bool success = openddl::lex(input, tokens, errors);

	std::cout << std::boolalpha;
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
	
		int position = 0;
		std::cout << openddl::Literal::construct(tokens, position, openddl::Literal::kString).get<std::string>() << std::endl;
		std::cout << openddl::Literal::construct(tokens, position, openddl::Literal::kBoolean).get<bool>() << std::endl;

	}
	catch (std::runtime_error & e)
	{
		std::cout << e.what() << std::endl;
	}
	
	return 0;
}