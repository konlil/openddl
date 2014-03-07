//================================================================================================================
// Copyright 2014 Denis Hilliard (armchaircommando@gmail.com)
// Licensed under MIT License
//================================================================================================================

#include "Lexer.h"
#include <string>
#include <iostream>

static const char* token_names[] = 
			{ "Array Data Type","Data Type","Identifier","Name","Boolean","Float",
				"Hex", "Decimal", "Binary", "String", 
				"Character", "Comma", "Left Brace", "Right Brace", 
				"Character Error","Unterminated Error","Literal Error","None","Length Error" };

int main(int argc, char * argv[])
{
	std::string out;
	std::string input = 
		"ref\n"
		"{\n"
		"	$hello%cookie, 0b112, \"Hello \" \" World\"\n"
		"*/ }";
	std::vector<openddl::Token> tokens;
	std::vector<openddl::TokenError> errors;
	bool success = openddl::lex(input, tokens, errors);

	std::cout << "=================================================================" << std::endl;
	if (errors.size())
		for (auto & error : errors)
			std::cout << error.message << ": " << error.payload << std::endl;
	else
		for (auto & token : tokens)
			std::cout << token_names[token.code] << " : " << token.payload << std::endl;
	std::cout << "=================================================================" << std::endl;
	
	return 0;
}