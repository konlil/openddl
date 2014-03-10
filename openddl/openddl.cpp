//================================================================================================================
// Copyright 2014 Denis Hilliard (armchaircommando@gmail.com)
// Licensed under MIT License
//================================================================================================================

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Lexer.h"
#include "Literal.h"

TEST_CASE("Comments", "[lexer]"){
	using openddl::Token;
	using openddl::TokenError;
	using openddl::lex;
	std::vector<Token> tokens;
	std::vector<TokenError> errors;
	SECTION("Block Comment")
	{
		REQUIRE(lex("/* */", tokens, errors));
		REQUIRE(errors.size() == 0);
		CHECK(tokens.size() == 0);
		tokens.clear(); errors.clear();
	}
	SECTION("Nested Block Comment")
	{
		REQUIRE(lex("/* /* */", tokens, errors));
		REQUIRE(errors.size() == 1);
		tokens.clear(); errors.clear();
	}
	SECTION("Trailing Close Block Comment")
	{
		REQUIRE(lex("*/", tokens, errors));
		REQUIRE(errors.size() == 1);
		tokens.clear(); errors.clear();
	}
	SECTION("Unterminated Block Comment")
	{
		REQUIRE(lex("/*", tokens, errors));
		REQUIRE(errors.size() == 1);
		tokens.clear(); errors.clear();
	}
	SECTION("Line Comment")
	{
		REQUIRE(lex("//   \n // ", tokens, errors));
		REQUIRE(errors.size() == 0);
		CHECK(tokens.size() == 0);
		tokens.clear(); errors.clear();
	}
}
/*
TEST_CASE("Structural Tokens", "[lexer]"){
	using openddl::Token;
	using openddl::TokenError;
	using openddl::lex;
	std::vector<Token> tokens;
	std::vector<TokenError> errors;
	REQUIRE(lex("[ ] { , }", tokens, errors));
	REQUIRE(errors.size() == 0);
	CHECK(tokens.size() == 5);
}
TEST_CASE("Textual Tokens", "[lexer]"){
	using openddl::Token;
	using openddl::TokenError;
	using openddl::lex;
	std::vector<Token> tokens;
	std::vector<TokenError> errors;
	SECTION("Types"){
		REQUIRE(lex("bool float double int8 int16 int32 int64 unsigned_int8 unsigned_int16 unsigned_int32 unsigned_int64 string ref type", tokens, errors));
		REQUIRE(errors.size() == 0);
		CHECK(tokens[0].data_type == Token::kBool);
		CHECK(tokens[1].data_type == Token::kFloat);
		CHECK(tokens[2].data_type == Token::kDouble);
		CHECK(tokens[3].data_type == Token::kInt8);
		CHECK(tokens[4].data_type == Token::kInt16);
		CHECK(tokens[5].data_type == Token::kInt32);
		CHECK(tokens[6].data_type == Token::kInt64);
		CHECK(tokens[7].data_type == Token::kUnsignedInt8);
		CHECK(tokens[8].data_type == Token::kUnsignedInt16);
		CHECK(tokens[9].data_type == Token::kUnsignedInt32);
		CHECK(tokens[10].data_type == Token::kUnsignedInt64);
		CHECK(tokens[11].data_type == Token::kString);
		CHECK(tokens[12].data_type == Token::kRef);
		CHECK(tokens[13].data_type == Token::kType);
		tokens.clear(); errors.clear();
	}
	SECTION("Array Types"){
		REQUIRE(lex("float[3]", tokens, errors));
		REQUIRE(errors.size() == 0);
		CHECK(tokens[0].token_type == Token::kDataType);
		CHECK(tokens[1].token_type == Token::kLeftSquareBracket);
		CHECK(tokens[2].token_type == Token::kLiteral);
		CHECK(tokens[3].token_type == Token::kRightSquareBracket);
		tokens.clear(); errors.clear();
	}
	SECTION("Names"){
		REQUIRE(lex("hello world null float", tokens, errors));
		REQUIRE(errors.size() == 0);
		CHECK(tokens[0].token_type == Token::kName);
		CHECK(tokens[1].token_type == Token::kName);
		CHECK(tokens[2].token_type != Token::kName);
		CHECK(tokens[3].token_type != Token::kName);
		tokens.clear(); errors.clear();
	}
	SECTION("Identifiers")
	{
		REQUIRE(lex("null $hello %hello", tokens, errors));
		REQUIRE(errors.size() == 0);
		CHECK(tokens[0].token_type == Token::kNull);
		CHECK(tokens[1].token_type == Token::kIdentifier);
		CHECK(tokens[2].token_type == Token::kIdentifier);
		tokens.clear(); errors.clear();
	}
}
*/
TEST_CASE("Literal Encodings","[lexer]"){
	using openddl::Token;
	using openddl::TokenError;
	using openddl::lex;
	std::vector<Token> tokens;
	std::vector<TokenError> errors;
	SECTION("Binary Literals"){
		tokens.clear(); errors.clear();
	}
	SECTION("Hex Literals"){
		tokens.clear(); errors.clear();
	}
	SECTION("Character Literals"){
		tokens.clear(); errors.clear();
	}
	SECTION("Decimal Literals"){
		tokens.clear(); errors.clear();
	}
	SECTION("Float Literals"){
		tokens.clear(); errors.clear();
	}
	SECTION("String Literals"){
		tokens.clear(); errors.clear();
	}
	SECTION("Boolean Literals"){
		REQUIRE(lex("true false TRUE FALSE null yes no", tokens, errors));
		REQUIRE(errors.size() == 0);
		CHECK(tokens[0].literal_type == Token::kBooleanLiteral);
		CHECK(tokens[1].literal_type == Token::kBooleanLiteral);
		CHECK(tokens[2].literal_type != Token::kBooleanLiteral);
		CHECK(tokens[3].literal_type != Token::kBooleanLiteral);
		CHECK(tokens[4].literal_type != Token::kBooleanLiteral);
		CHECK(tokens[5].literal_type != Token::kBooleanLiteral);
		CHECK(tokens[6].literal_type != Token::kBooleanLiteral);
		tokens.clear(); errors.clear();
	}
	SECTION("Handling Error Literals"){
		REQUIRE(lex("0b1222 0xAZX 99AT 30.0Y 'AYC\\c' \" \x5C \"", tokens, errors));
		CHECK(errors[0].payload == "0b1222");
		CHECK(errors[1].payload == "0xAZX");
		CHECK(errors[2].payload == "99AT");
		CHECK(errors[3].payload == "30.0Y");
		CHECK(errors[4].payload == "'AYC\\c'");
		CHECK(errors[5].payload == "\" \x5C \"");
		tokens.clear(); errors.clear();
	}
}
