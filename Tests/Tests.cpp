//================================================================================================================
// Copyright 2014 Denis Hilliard (armchaircommando@gmail.com)
// Licensed under MIT License
//================================================================================================================

#include "stdafx.h"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../openddl/detail.h"
#include "../openddl/detail/Command.h"
#include "../openddl/detail/Error.h"
#include "../openddl/detail/Token.h"

bool token_has_float_encoding(const openddl::detail::Token & token)
{
	using namespace openddl::detail;
	switch (token.token_type)
	{
	case Token::kBinaryLiteral:
	case Token::kHexLiteral:
	case Token::kDecimalLiteral:
	case Token::kFloatLiteral:
		return true;
	default:
		return false;
	}
}
bool token_has_integer_encoding(const openddl::detail::Token & token)
{
	using namespace openddl::detail;
	switch (token.token_type)
	{
	case Token::kBinaryLiteral:
	case Token::kHexLiteral:
	case Token::kDecimalLiteral:
	case Token::kCharacterLiteral:
		return true;
	default:
		return false;
	}
}
bool token_is_data_type(const openddl::detail::Token & token)
{
	using namespace openddl::detail;
	return token.token_type >= Token::kUnsignedInt8 && token.token_type <= Token::kInt64 || token.token_type == Token::kFloat || token.token_type == Token::kDouble;
}

TEST_CASE("Comments", "[lexer]"){
	using namespace openddl::detail;
	std::vector<Token> tokens;
	std::vector<Error> errors;
	SECTION("Block Comment")
	{
		REQUIRE(lex("/* */", tokens, errors));
		tokens.clear(); errors.clear();
	}
	SECTION("Nested Block Comment")
	{
		REQUIRE_FALSE(lex("/* /* */", tokens, errors));
		REQUIRE_FALSE(errors.empty());
		tokens.clear(); errors.clear();
	}
	SECTION("Trailing Close Block Comment")
	{
		REQUIRE_FALSE(lex("*/", tokens, errors));
		REQUIRE_FALSE(errors.empty());
		tokens.clear(); errors.clear();
	}
	SECTION("Unterminated Block Comment")
	{
		REQUIRE_FALSE(lex("/*", tokens, errors));
		REQUIRE_FALSE(errors.empty());
		tokens.clear(); errors.clear();
	}
	SECTION("Line Comment")
	{
		REQUIRE(lex("//   \n // ", tokens, errors));
		REQUIRE(errors.empty());
		CHECK(tokens.size() == 0);
		tokens.clear(); errors.clear();
	}
}
TEST_CASE("Structural Tokens", "[lexer]"){
	using namespace openddl::detail;
	std::vector<Token> tokens;
	std::vector<Error> errors;
	REQUIRE(lex("[ ] { , }", tokens, errors));
	REQUIRE(errors.empty());
	CHECK(tokens.size() == 5);
}
TEST_CASE("Textual Tokens", "[lexer]"){

	using namespace openddl::detail;
	std::vector<Token> tokens;
	std::vector<Error> errors;
	SECTION("Types"){
		REQUIRE(openddl::detail::lex("bool float double int8 int16 int32 int64 unsigned_int8 unsigned_int16 unsigned_int32 unsigned_int64 string ref type", tokens, errors));
		REQUIRE(errors.empty());
		CHECK(tokens[0].token_type == Token::kBool);
		CHECK(tokens[1].token_type == Token::kFloat);
		CHECK(tokens[2].token_type == Token::kDouble);
		CHECK(tokens[3].token_type == Token::kInt8);
		CHECK(tokens[4].token_type == Token::kInt16);
		CHECK(tokens[5].token_type == Token::kInt32);
		CHECK(tokens[6].token_type == Token::kInt64);
		CHECK(tokens[7].token_type == Token::kUnsignedInt8);
		CHECK(tokens[8].token_type == Token::kUnsignedInt16);
		CHECK(tokens[9].token_type == Token::kUnsignedInt32);
		CHECK(tokens[10].token_type == Token::kUnsignedInt64);
		CHECK(tokens[11].token_type == Token::kString);
		CHECK(tokens[12].token_type == Token::kRef);
		CHECK(tokens[13].token_type == Token::kType);
		tokens.clear(); errors.clear();
	}
	SECTION("Array Types"){
		REQUIRE(lex("float[3]", tokens, errors));
		REQUIRE(errors.empty());
		CHECK(token_is_data_type(tokens[0]));
		CHECK(tokens[1].token_type == Token::kLeftSquareBracket);
		CHECK(token_has_integer_encoding(tokens[2]));
		CHECK(tokens[3].token_type == Token::kRightSquareBracket);
		tokens.clear(); errors.clear();
	}
	SECTION("Identifiers"){
		REQUIRE(lex("hello world null float", tokens, errors));
		REQUIRE(errors.empty());
		CHECK(tokens[0].token_type == Token::kIdentifier);
		CHECK(tokens[1].token_type == Token::kIdentifier);
		CHECK(tokens[2].token_type != Token::kIdentifier);
		CHECK(tokens[3].token_type != Token::kIdentifier);
		tokens.clear(); errors.clear();
	}
	SECTION("Names")
	{
		REQUIRE(lex("null $hello %hello", tokens, errors));
		REQUIRE(errors.empty());
		CHECK(tokens[0].token_type == Token::kNull);
		CHECK(tokens[1].token_type == Token::kName);
		CHECK(tokens[2].token_type == Token::kName);
		tokens.clear(); errors.clear();
	}
}
TEST_CASE("Literal Encodings", "[lexer]"){

	using namespace openddl::detail;
	std::vector<Token> tokens;
	std::vector<Error> errors;
	SECTION("Binary Literals"){
		REQUIRE(lex("0b11 +0B11 -0B00", tokens, errors));
		REQUIRE(errors.empty());
		CHECK(tokens[0].token_type == Token::kBinaryLiteral);
		CHECK(tokens[1].token_type == Token::kBinaryLiteral);
		CHECK(tokens[2].token_type == Token::kBinaryLiteral);
		tokens.clear(); errors.clear();
	}
	SECTION("Hex Literals"){
		REQUIRE(lex("0x00 +0x99 -0xFF", tokens, errors));
		REQUIRE(errors.empty());
		CHECK(tokens[0].token_type == Token::kHexLiteral);
		CHECK(tokens[1].token_type == Token::kHexLiteral);
		CHECK(tokens[2].token_type == Token::kHexLiteral);
		tokens.clear(); errors.clear();
	}
	SECTION("Character Literals"){
		REQUIRE(lex("'a' '\\x99' '\\t'", tokens, errors));
		REQUIRE(errors.empty());
		CHECK(tokens[0].token_type == Token::kCharacterLiteral);
		CHECK(tokens[1].token_type == Token::kCharacterLiteral);
		CHECK(tokens[2].token_type == Token::kCharacterLiteral);
		tokens.clear(); errors.clear();
	}
	SECTION("Decimal Literals"){
		REQUIRE(lex("99 -1000 +1337", tokens, errors));
		REQUIRE(errors.empty());
		CHECK(tokens[0].token_type == Token::kDecimalLiteral);
		CHECK(tokens[1].token_type == Token::kDecimalLiteral);
		CHECK(tokens[2].token_type == Token::kDecimalLiteral);
		tokens.clear(); errors.clear();
	}
	SECTION("Float Literals"){
		REQUIRE(lex("99.0 -99e-10 +.99E+22", tokens, errors));
		REQUIRE(errors.empty());
		CHECK(tokens[0].token_type == Token::kFloatLiteral);
		CHECK(tokens[1].token_type == Token::kFloatLiteral);
		CHECK(tokens[2].token_type == Token::kFloatLiteral);
		tokens.clear(); errors.clear();
	}
	SECTION("String Literals"){
		REQUIRE(lex("\" abcd \" \"\\U123456 \\u9999 \"", tokens, errors));
		REQUIRE(errors.empty());
		CHECK(tokens[0].token_type == Token::kStringLiteral);
		tokens.clear(); errors.clear();
	}
	SECTION("Boolean Literals"){
		REQUIRE(lex("true false TRUE FALSE null yes no", tokens, errors));
		REQUIRE(errors.empty());
		CHECK(tokens[0].token_type == Token::kBooleanLiteral);
		CHECK(tokens[1].token_type == Token::kBooleanLiteral);
		CHECK(tokens[2].token_type != Token::kBooleanLiteral);
		CHECK(tokens[3].token_type != Token::kBooleanLiteral);
		CHECK(tokens[4].token_type != Token::kBooleanLiteral);
		CHECK(tokens[5].token_type != Token::kBooleanLiteral);
		CHECK(tokens[6].token_type != Token::kBooleanLiteral);
		tokens.clear(); errors.clear();
	}
	SECTION("Handling Error Literals"){
		REQUIRE_FALSE(lex("0b1222 0xAZX 99AT 30.0Y 'AYC\\c' \" \x5C \"", tokens, errors));
		REQUIRE_FALSE(errors.empty());
		CHECK(errors.size() == 6);
		tokens.clear(); errors.clear();

	}
	SECTION("Handling Unterminated strings/characters"){
		REQUIRE_FALSE(openddl::detail::lex("\" partial string", tokens, errors));
		REQUIRE_FALSE(errors.empty());
		tokens.clear(); errors.clear();
		REQUIRE_FALSE(lex("' part", tokens, errors));
		REQUIRE_FALSE(errors.empty());
		tokens.clear(); errors.clear();

	}
}

TEST_CASE("Parser", "[parser]"){
	
}
