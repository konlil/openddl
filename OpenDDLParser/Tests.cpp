//================================================================================================================
// Copyright 2014 Denis Hilliard (armchaircommando@gmail.com)
// Licensed under MIT License
//================================================================================================================

#include "stdafx.h"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "openddl.h"

TEST_CASE("OpenDDL Identifier Validation", "[validate]"){
	CHECK( openddl::is_identifier("hello",0));
	CHECK(openddl::is_identifier("_hello", 0));
	CHECK_FALSE(openddl::is_identifier("9hello", 0));
	CHECK(openddl::is_identifier("hello_9", 0));
}

TEST_CASE("Parse Character Literal", "[parse]") {
	CHECK(openddl::parse_character_literal("\'\\n\'", 0) == '\n');
	CHECK(openddl::parse_character_literal("\'\\n\\n\'", 0) == '\n\n');
	CHECK(openddl::parse_character_literal("\'\\t\'", 0) == '\t');
	CHECK(openddl::parse_character_literal("\'\\x01\'", 0) == 0x01);
	CHECK(openddl::parse_character_literal("\'a\'",0) == 'a');
	CHECK(openddl::parse_character_literal("\'ABCD\'", 0) == 'ABCD');
}

TEST_CASE("OpenDDL Name", "[name]") {
	CHECK(openddl::is_name("%name",0));
	CHECK(openddl::is_name("$name", 0));
	CHECK_FALSE(openddl::is_name("name", 0));
}

TEST_CASE("Local OpenDDL Name", "[name]"){
	CHECK(openddl::is_local_name("%name", 0));
	CHECK_FALSE(openddl::is_local_name("$name", 0));
}

TEST_CASE("Parse Type", "[parse]") {
	CHECK(openddl::parse_type("bool") == openddl::Type::kBool);
	CHECK(openddl::parse_type("int8") == openddl::Type::kInt8);
	CHECK(openddl::parse_type("int16") == openddl::Type::kInt16);
	CHECK(openddl::parse_type("int32") == openddl::Type::kInt32);
	CHECK(openddl::parse_type("int64") == openddl::Type::kInt64);
	CHECK(openddl::parse_type("unsigned_int8") == openddl::Type::kUnsignedInt8);
	CHECK(openddl::parse_type("unsigned_int16") == openddl::Type::kUnsignedInt16);
	CHECK(openddl::parse_type("unsigned_int32") == openddl::Type::kUnsignedInt32);
	CHECK(openddl::parse_type("unsigned_int64") == openddl::Type::kUnsignedInt64);
	CHECK(openddl::parse_type("float") == openddl::Type::kFloat);
	CHECK(openddl::parse_type("double") == openddl::Type::kDouble);
	CHECK(openddl::parse_type("string") == openddl::Type::kString);
	CHECK(openddl::parse_type("ref") == openddl::Type::kRef);
	CHECK(openddl::parse_type("type") == openddl::Type::kType);
	CHECK_THROWS(openddl::parse_type("undefined"));
}

TEST_CASE("Decode Boolean", "[decode]"){
	CHECK(openddl::decode_boolean("true"));
	CHECK_FALSE(openddl::decode_boolean("false"));
	CHECK_THROWS(openddl::decode_boolean("other"));
}

TEST_CASE("Decode unsigned_int8", "[decode]") {
	CHECK(openddl::decode_unsigned_int8("\'a\'") == 'a');
	CHECK(openddl::decode_unsigned_int8("+9") == 9);
	CHECK(openddl::decode_unsigned_int8("9") == 9);
	CHECK(openddl::decode_unsigned_int8("21") == 21);
	CHECK(openddl::decode_unsigned_int8("0xF0") == 0xF0);
	CHECK(openddl::decode_unsigned_int8("0XF0") == 0xF0);
	CHECK(openddl::decode_unsigned_int8("0b11110000") == 0xF0);
	CHECK(openddl::decode_unsigned_int8("0B11110000") == 0xF0);
	CHECK_THROWS(openddl::decode_unsigned_int8("\'ABCD\'"));
	CHECK_THROWS(openddl::decode_unsigned_int8("600"));
	CHECK_THROWS(openddl::decode_unsigned_int8("-20"));
	CHECK_THROWS(openddl::decode_unsigned_int8("hello"));
	CHECK_THROWS(openddl::decode_unsigned_int8("21b"));
	CHECK_THROWS(openddl::decode_unsigned_int8("-9"));
	CHECK_THROWS(openddl::decode_unsigned_int8("-"));

}

TEST_CASE("Decode unsigned_int16", "[decode]") {
	CHECK(openddl::decode_unsigned_int16("\'a\'") == 'a');
	CHECK(openddl::decode_unsigned_int16("+9") == 9);
	CHECK(openddl::decode_unsigned_int16("9") == 9);
	CHECK(openddl::decode_unsigned_int16("21") == 21);
	CHECK(openddl::decode_unsigned_int16("0xF0") == 0xF0);
	CHECK(openddl::decode_unsigned_int16("0XF0") == 0xF0);
	CHECK(openddl::decode_unsigned_int16("0b11110000") == 0xF0);
	CHECK(openddl::decode_unsigned_int16("0B11110000") == 0xF0);
	CHECK_THROWS(openddl::decode_unsigned_int16("\'ABCD\'"));
	CHECK_THROWS(openddl::decode_unsigned_int16("70000"));
	CHECK_THROWS(openddl::decode_unsigned_int16("-20"));
	CHECK_THROWS(openddl::decode_unsigned_int16("hello"));
	CHECK_THROWS(openddl::decode_unsigned_int16("21b"));
	CHECK_THROWS(openddl::decode_unsigned_int16("-9"));
	CHECK_THROWS(openddl::decode_unsigned_int16("-"));
}

TEST_CASE("Decode unsigned_int32", "[decode]") {
	CHECK(openddl::decode_unsigned_int32("\'a\'") == 'a');
	CHECK(openddl::decode_unsigned_int32("+9") == 9);
	CHECK(openddl::decode_unsigned_int32("9") == 9);
	CHECK(openddl::decode_unsigned_int32("21") == 21);
	CHECK(openddl::decode_unsigned_int32("0xF0") == 0xF0);
	CHECK(openddl::decode_unsigned_int32("0XF0") == 0xF0);
	CHECK(openddl::decode_unsigned_int32("0b11110000") == 0xF0);
	CHECK(openddl::decode_unsigned_int32("0B11110000") == 0xF0);
	CHECK(openddl::decode_unsigned_int32("\'ABCD\'") == 'ABCD');
	CHECK_THROWS(openddl::decode_unsigned_int32("4294968000"));
	CHECK_THROWS(openddl::decode_unsigned_int32("-20"));
	CHECK_THROWS(openddl::decode_unsigned_int32("hello"));
	CHECK_THROWS(openddl::decode_unsigned_int32("21b"));
	CHECK_THROWS(openddl::decode_unsigned_int32("-9"));
	CHECK_THROWS(openddl::decode_unsigned_int32("-"));
}

TEST_CASE("Decode unsigned_int64", "[decode]") {
	CHECK(openddl::decode_unsigned_int64("\'a\'") == 'a');
	CHECK(openddl::decode_unsigned_int64("+9") == 9);
	CHECK(openddl::decode_unsigned_int64("9") == 9);
	CHECK(openddl::decode_unsigned_int64("21") == 21);
	CHECK(openddl::decode_unsigned_int64("0xF0") == 0xF0);
	CHECK(openddl::decode_unsigned_int64("0XF0") == 0xF0);
	CHECK(openddl::decode_unsigned_int64("0b11110000") == 0xF0);
	CHECK(openddl::decode_unsigned_int64("0B11110000") == 0xF0);
	CHECK_THROWS(openddl::decode_unsigned_int64("18446744073709551616"));
	CHECK_THROWS(openddl::decode_unsigned_int64("-20"));
	CHECK_THROWS(openddl::decode_unsigned_int64("hello"));
	CHECK_THROWS(openddl::decode_unsigned_int64("21b"));
	CHECK_THROWS(openddl::decode_unsigned_int64("-9"));
	CHECK_THROWS(openddl::decode_unsigned_int64("-"));
}

TEST_CASE("Decode int8", "[decode]") {
	CHECK(openddl::decode_int8("\'a\'") == 'a');
	CHECK(openddl::decode_int8("9") == 9);
	CHECK(openddl::decode_int8("21") == 21);
	CHECK(openddl::decode_int8("+21") == 21);
	CHECK(openddl::decode_int8("-21") == -21);
	CHECK_THROWS(openddl::decode_int8("-200"));
	CHECK_THROWS(openddl::decode_int8("+200"));
	CHECK_THROWS(openddl::decode_int8("hello"));
	CHECK_THROWS(openddl::decode_int8("21b"));
}
TEST_CASE("Decode int16", "[decode]") {
	CHECK(openddl::decode_int16("\'a\'") == 'a');
	CHECK(openddl::decode_int16("9") == 9);
	CHECK(openddl::decode_int16("21") == 21);
	CHECK(openddl::decode_int16("+21") == 21);
	CHECK(openddl::decode_int16("-21") == -21);
	CHECK_THROWS(openddl::decode_int16("-40000"));
	CHECK_THROWS(openddl::decode_int16("+40000"));
	CHECK_THROWS(openddl::decode_int16("hello"));
	CHECK_THROWS(openddl::decode_int16("21b"));
}
TEST_CASE("Decode int32", "[decode]") {
	CHECK(openddl::decode_int32("\'a\'") == 'a');
	CHECK(openddl::decode_int32("9") == 9);
	CHECK(openddl::decode_int32("21") == 21);
	CHECK(openddl::decode_int32("+21") == 21);
	CHECK(openddl::decode_int32("-21") == -21);
	CHECK_THROWS(openddl::decode_int32("-2147483650"));
	CHECK_THROWS(openddl::decode_int32("+2147483650"));
	CHECK_THROWS(openddl::decode_int32("hello"));
	CHECK_THROWS(openddl::decode_int32("21b"));
}
TEST_CASE("Decode int64", "[decode]") {
	CHECK(openddl::decode_int64("\'a\'") == 'a');
	CHECK(openddl::decode_int64("9") == 9);
	CHECK(openddl::decode_int64("21") == 21);
	CHECK(openddl::decode_int64("+21") == 21);
	CHECK(openddl::decode_int64("-21") == -21);
	CHECK_THROWS(openddl::decode_int64("-9223372036854775820"));
	CHECK_THROWS(openddl::decode_int64("+9223372036854775820"));
	CHECK_THROWS(openddl::decode_int64("hello"));
	CHECK_THROWS(openddl::decode_int64("21b"));
}
TEST_CASE("Decode float", "[decode]") {
	CHECK(openddl::decode_float("0x0") == 0);
	CHECK(openddl::decode_float("0x3f800000") == 1.0f); 
	CHECK(openddl::decode_float("-0x3f800000") == -1.0f);
	CHECK(openddl::decode_float("1.0") == 1.0f);
	CHECK(openddl::decode_float("0.5") == 0.5f);
	CHECK(openddl::decode_float(".5") == 0.5f);
	CHECK(openddl::decode_float("1e2") == 100.0f);
	CHECK(openddl::decode_float("1E2") == 100.0f);
	CHECK(openddl::decode_float("1E+2") == 100.0f);
	CHECK(openddl::decode_float("1E-1") == 0.1f);
}
TEST_CASE("Decode double", "[decode]") {
	CHECK(openddl::decode_double ("0x0") == 0);
	CHECK(openddl::decode_double("0x3ff0000000000000") == 1.0);
	CHECK(openddl::decode_double("-0x3ff0000000000000") == -1.0);
	CHECK(openddl::decode_double("1.0") == 1.0);
	CHECK(openddl::decode_double("0.5") == 0.5);
	CHECK(openddl::decode_double(".5") == 0.5);
	CHECK(openddl::decode_double("1e2") == 100.0);
	CHECK(openddl::decode_double("1E2") == 100.0);
	CHECK(openddl::decode_double("1E+2") == 100.0);
	CHECK(openddl::decode_double("1E-1") == 0.1);

}
TEST_CASE("Parse String", "[parse]") {
	CHECK(openddl::parse_string("\"abcd\"") == "abcd");
	CHECK(openddl::parse_string("\"\\u0100\"") == "\xC4\x80");
	CHECK(openddl::parse_string("\"\xEA\x80\x90\"") == "\xEA\x80\x90");
	CHECK(openddl::parse_string("\"abcd\"") == "abcd");
}
TEST_CASE("Consume Whitespace", "[whitespace]") {
	CHECK(openddl::consume_whitespace(" ", 0) == 1);
	CHECK(openddl::consume_whitespace("\t\n ", 0) == 3);
	CHECK(openddl::consume_whitespace("\t\n abcd", 0) == 3);
	CHECK(openddl::consume_whitespace("// This is a comment \n", 0) == 22);
	CHECK(openddl::consume_whitespace("// This is a comment \n Literal", 0) == 23);
	CHECK_THROWS(openddl::consume_whitespace("/*/* */", 0));
	CHECK_THROWS(openddl::consume_whitespace("/*", 0));
	CHECK_NOTHROW(openddl::consume_whitespace("/* //This is a nested comment \n */", 0));
}

TEST_CASE("Consume Token", "[token]") {
	CHECK(openddl::consume_token("abcd ", 0) == 4);
	CHECK(openddl::consume_token("0x4444 ", 0) == 6);
	CHECK(openddl::consume_token("\'ABCD\' ", 0) == 6);
	CHECK(openddl::consume_token("\"ABCD EFGH\" ", 0) == 11);
}
