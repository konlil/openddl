//================================================================================================================
// Copyright 2014 Denis Hilliard (armchaircommando@gmail.com)
// Licensed under MIT License
//================================================================================================================

#include "stdafx.h"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Tokenizer.h"


TEST_CASE("Tokenizer", "[tokenizer]")
{
	std::string input = "{0b11, 0b11}";
	openddl::Lexer t(input.data(), input.data() + input.length());
	CHECK(t() == openddl::Token::kOpenBrace);
	CHECK(t() == openddl::Token::kLiteral);
	CHECK(t() == openddl::Token::kComma);
	CHECK(t() == openddl::Token::kLiteral);
	CHECK(t() == openddl::Token::kCloseBrace);
	CHECK(t() == openddl::Token::kEnd);

}

