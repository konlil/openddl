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
TEST_CASE("Literal Encodings","[lexer]"){
	using openddl::Token;
	using openddl::TokenError;
	using openddl::lex;
	std::vector<Token> tokens;
	std::vector<TokenError> errors;
	SECTION("Binary Literals"){
		REQUIRE(lex("0b11 +0B11 -0B00", tokens, errors));
		REQUIRE(errors.size() == 0);
		CHECK(tokens[0].literal_type == Token::kBinaryLiteral);
		CHECK(tokens[1].literal_type == Token::kBinaryLiteral);
		CHECK(tokens[2].literal_type == Token::kBinaryLiteral);
		tokens.clear(); errors.clear();
	}
	SECTION("Hex Literals"){
		REQUIRE(lex("0x00 +0x99 -0xFF", tokens, errors));
		REQUIRE(errors.size() == 0);
		CHECK(tokens[0].literal_type == Token::kHexLiteral);
		CHECK(tokens[1].literal_type == Token::kHexLiteral);
		CHECK(tokens[2].literal_type == Token::kHexLiteral);
		tokens.clear(); errors.clear();
	}
	SECTION("Character Literals"){
		REQUIRE(lex("'a' '\\x99' '\\t'", tokens, errors));
		REQUIRE(errors.size() == 0);
		CHECK(tokens[0].literal_type == Token::kCharacterLiteral);
		CHECK(tokens[1].literal_type == Token::kCharacterLiteral);
		CHECK(tokens[2].literal_type == Token::kCharacterLiteral);
		tokens.clear(); errors.clear();
	}
	SECTION("Decimal Literals"){
		REQUIRE(lex("99 -1000 +1337", tokens, errors));
		REQUIRE(errors.size() == 0);
		CHECK(tokens[0].literal_type == Token::kDecimalLiteral);
		CHECK(tokens[1].literal_type == Token::kDecimalLiteral);
		CHECK(tokens[2].literal_type == Token::kDecimalLiteral);
		tokens.clear(); errors.clear();
	}
	SECTION("Float Literals"){
		REQUIRE(lex("99.0 -99e-10 +.99E+22", tokens, errors));
		REQUIRE(errors.size() == 0);
		CHECK(tokens[0].literal_type == Token::kFloatLiteral);
		CHECK(tokens[1].literal_type == Token::kFloatLiteral);
		CHECK(tokens[2].literal_type == Token::kFloatLiteral);
		tokens.clear(); errors.clear();
	}
	SECTION("String Literals"){
		REQUIRE(lex("\" abcd \" \"\\U123456 \\u9999 \"", tokens, errors));
		REQUIRE(errors.size() == 0);
		CHECK(tokens[0].literal_type == Token::kStringLiteral);
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
	SECTION("Handling Unterminated strings/characters"){
		REQUIRE(lex("\" partial string", tokens, errors));
		REQUIRE(errors.size() == 1);
		tokens.clear(); errors.clear();
		REQUIRE(lex("' part", tokens, errors));
		REQUIRE(errors.size() == 1);
		tokens.clear(); errors.clear();

	}
}

TEST_CASE("Literal", "[literal]"){
	using openddl::Literal;
	std::vector<openddl::Token> tokens;
	std::vector<openddl::TokenError> errors;
	SECTION("Integer Conversion"){
		
		REQUIRE(lex("-1094861636 0x41424344 +0b01000001010000100100001101000100 'ABCD'", tokens, errors));
		REQUIRE(errors.size() == 0);

		//Overflow errors
		CHECK_THROWS(Literal::construct(tokens[0], Literal::kInteger).get<unsigned int>());
		CHECK_THROWS(Literal::construct(tokens[0], Literal::kInteger).get<short>());
		CHECK_THROWS(Literal::construct(tokens[0], Literal::kInteger).get<char>());

		CHECK(Literal::construct(tokens[0], Literal::kInteger).get<int>() == -'ABCD');
		CHECK(Literal::construct(tokens[1], Literal::kInteger).get<unsigned int>() == 'ABCD');
		CHECK(Literal::construct(tokens[2], Literal::kInteger).get<uint64_t>() == 'ABCD');
		CHECK(Literal::construct(tokens[3], Literal::kInteger).get<int>() == 'ABCD');
		tokens.clear(); errors.clear();
	}
	SECTION("Float Literal"){
		
		REQUIRE(lex("99 0x3f800000 -30.0 'ABCD'", tokens, errors));
		REQUIRE(errors.size() == 0);
		CHECK(Literal::construct(tokens[0], Literal::kFloat).get<float>() == 99.0f);
		CHECK(Literal::construct(tokens[0], Literal::kFloat).get<double>() == 99.0);
		CHECK(Literal::construct(tokens[1], Literal::kFloat).get<float>() == 1.0f);
		CHECK(Literal::construct(tokens[1], Literal::kFloat).get<double>() == 5.26354424712e-315);
		CHECK(Literal::construct(tokens[2], Literal::kFloat).get<float>() == -30.0f);
		CHECK(Literal::construct(tokens[2], Literal::kFloat).get<double>() == -30.0);
		CHECK_THROWS(Literal::construct(tokens[3], Literal::kFloat).get<double>());
		tokens.clear(); errors.clear();
	}
	SECTION("Boolean Literal"){
		REQUIRE(lex("true false null", tokens, errors));
		REQUIRE(errors.size() == 0);
		CHECK(Literal::construct(tokens[0], Literal::kBoolean).get<bool>() == true);
		CHECK(Literal::construct(tokens[1], Literal::kBoolean).get<bool>() == false);
		CHECK_THROWS(Literal::construct(tokens[2], Literal::kBoolean).get<bool>());
		tokens.clear(); errors.clear();
	}
	SECTION("String Literal"){
		REQUIRE(lex("\"Hello \" \"World\" null", tokens, errors));
		REQUIRE(errors.size() == 0);
		CHECK(Literal::construct(tokens[0], Literal::kString).get<std::string>() == "\"Hello World\"");
		CHECK_THROWS(Literal::construct(tokens[1], Literal::kString).get<std::string>());
		tokens.clear(); errors.clear();
	}
	
	
}
