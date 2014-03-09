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
		"\"Hello\" true -1000 0x22 0b11 'ABCD' 0x3f800000 0x7ff0000000000000";

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
	
		std::cout << openddl::Literal::construct(tokens[0],openddl::Literal::kString).get<std::string>() << std::endl;
		std::cout << openddl::Literal::construct(tokens[1], openddl::Literal::kBoolean).get<bool>() << std::endl;
		std::cout << openddl::Literal::construct(tokens[2], openddl::Literal::kInteger).get<short>() << std::endl;
		std::cout << openddl::Literal::construct(tokens[3], openddl::Literal::kInteger).get<short>() << std::endl;
		std::cout << openddl::Literal::construct(tokens[4], openddl::Literal::kInteger).get<unsigned short>() << std::endl;
		std::cout << openddl::Literal::construct(tokens[5], openddl::Literal::kInteger).get<int>() << std::endl;
		std::cout << openddl::Literal::construct(tokens[6], openddl::Literal::kFloat).get<float>() << std::endl;
		std::cout << openddl::Literal::construct(tokens[7], openddl::Literal::kFloat).get<double>() << std::endl;

	}
	catch (std::runtime_error & e)
	{
		std::cout << e.what() << std::endl;
	}
	
	return 0;
}