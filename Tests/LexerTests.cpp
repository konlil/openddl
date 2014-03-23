#include "stdafx.h"
#include "catch.hpp"
#include "../openddl/detail/detail.h"
#include "../openddl/detail/Token.h"
#include "../openddl/detail/Error.h"


TEST_CASE("lexer will catch common comment formatting errors", "[lex]"){
	GIVEN("An unterminated block comment"){
		std::string input = "/* ";
		std::vector<openddl::detail::Error> errors;
		std::vector<openddl::detail::Token> tokens;
		WHEN("the string is parsed"){
			REQUIRE_FALSE(openddl::detail::lex(input, tokens, errors));
			THEN("the error string should match"){
				REQUIRE_FALSE(errors.empty());
				REQUIRE(errors[0].message == "lex.unterminated_block_comment");
			}
		}
	}
	GIVEN("A trailing close block comment sequence"){
		std::string input = "*/ ";
		std::vector<openddl::detail::Error> errors;
		std::vector<openddl::detail::Token> tokens;
		WHEN("the string is parsed"){
			REQUIRE_FALSE(openddl::detail::lex(input, tokens, errors));
			THEN("the error string should match"){
				REQUIRE_FALSE(errors.empty());
				REQUIRE(errors[0].message == "lex.trailing_close_comment");
			}
		}
	}
	GIVEN("A nested block comment glyph"){
		std::string input = "/* /* */";
		std::vector<openddl::detail::Error> errors;
		std::vector<openddl::detail::Token> tokens;
		WHEN("the string is parsed"){
			REQUIRE_FALSE(openddl::detail::lex(input, tokens, errors));
			THEN("the error string should match"){
				REQUIRE_FALSE(errors.empty());
				REQUIRE(errors[0].message == "lex.nested_block_comment");
			}
		}
	}
}
TEST_CASE("Lexer will handle properly formatted comments", "[lex]"){
	GIVEN("A properly formatted block comment"){
		std::string input = "/* This is a block comment */";
		std::vector<openddl::detail::Error> errors;
		std::vector<openddl::detail::Token> tokens;
		WHEN("the string is parsed"){
			REQUIRE(openddl::detail::lex(input, tokens, errors));
			THEN("the comment should be filtered out"){
				REQUIRE(errors.empty());
				REQUIRE(tokens.empty());
			}
		}
	}
	GIVEN("A properly formatted line comment"){
		std::string input = "// This is a line comment \n";
		std::vector<openddl::detail::Error> errors;
		std::vector<openddl::detail::Token> tokens;
		WHEN("the string is parsed"){
			REQUIRE(openddl::detail::lex(input, tokens, errors));
			THEN("the comment should be filtered out"){
				REQUIRE(errors.empty());
				REQUIRE(tokens.empty());
			}
		}
	}
}
TEST_CASE("Lexer will handle type declarations", "[lex]"){
	GIVEN("A sequence of valid type names"){
		std::string input = "bool float double int8 int16 int32 int64\n" 
			"unsigned_int8 unsigned_int16 unsigned_int32\n"
			"unsigned_int64 string ref type";
		std::vector<openddl::detail::Error> errors;
		std::vector<openddl::detail::Token> tokens;
		WHEN("the string is parsed"){
			REQUIRE(openddl::detail::lex(input, tokens, errors));
			THEN("All types should be emitted as tokens"){
				using namespace openddl::detail;
				REQUIRE_FALSE(tokens.empty());
				REQUIRE(tokens.size() == 14);
			}
		}
	}
	GIVEN("A sequence of array type names"){
		std::string input = "int8[2] int16['a']\n"
							"int32[0x11] int64[0b11]";
		std::vector<openddl::detail::Error> errors;
		std::vector<openddl::detail::Token> tokens;
		WHEN("the string is parsed"){
			REQUIRE(openddl::detail::lex(input, tokens, errors));
			THEN("All types should be emitted as tokens"){
				using namespace openddl::detail;
				REQUIRE_FALSE(tokens.empty());
				REQUIRE(tokens.size() == 16);
			}
		}
	}
	GIVEN("A sequence of textual tokens"){
		std::string input = "hello world $hello %world null int8";
		std::vector<openddl::detail::Error> errors;
		std::vector<openddl::detail::Token> tokens;
		WHEN("the string is parsed"){
			REQUIRE(openddl::detail::lex(input, tokens, errors));
			THEN("All types should be emitted as appropriate tokens"){
				using namespace openddl::detail;
				REQUIRE_FALSE(tokens.empty());
				REQUIRE(tokens.size() == 6);
				CHECK(tokens[0].token_type == Token::kIdentifier);
				CHECK(tokens[1].token_type == Token::kIdentifier);
				CHECK(tokens[2].token_type == Token::kGlobalName);
				CHECK(tokens[3].token_type == Token::kLocalName);
				CHECK(tokens[4].token_type == Token::kNull);
				CHECK(tokens[5].token_type != Token::kIdentifier);
			}
		}
	}	
}
TEST_CASE("Lexer can identify the encoding of literals","[lex]"){
	GIVEN("A sequence of binary literals"){
		std::string input = "0b11 +0B11 -0B00";
		std::vector<openddl::detail::Error> errors;
		std::vector<openddl::detail::Token> tokens;
		WHEN("the string is parsed"){
			REQUIRE(openddl::detail::lex(input, tokens, errors));
			THEN("Tokens should be emitted as binary literals"){
				using namespace openddl::detail;
				REQUIRE_FALSE(tokens.empty());
				REQUIRE(tokens.size() == 3);
				for (auto & t : tokens)
				{
					CHECK(t.token_type == Token::kBinaryLiteral);
				}
			}
		}
	}
	GIVEN("A sequence of hex literals"){
		std::string input = "0x00 +0x99 -0xFF";
		std::vector<openddl::detail::Error> errors;
		std::vector<openddl::detail::Token> tokens;
		WHEN("the string is parsed"){
			REQUIRE(openddl::detail::lex(input, tokens, errors));
			THEN("Tokens should be emitted as hex literals"){
				using namespace openddl::detail;
				REQUIRE_FALSE(tokens.empty());
				REQUIRE(tokens.size() == 3);
				for (auto & t : tokens)
				{
					CHECK(t.token_type == Token::kHexLiteral);
				}
			}
		}
	}
	GIVEN("A sequence of character literals"){
		std::string input = "'a' '\\x99' '\\t'";
		std::vector<openddl::detail::Error> errors;
		std::vector<openddl::detail::Token> tokens;
		WHEN("the string is parsed"){
			REQUIRE(openddl::detail::lex(input, tokens, errors));
			THEN("Tokens should be emitted as character literals"){
				using namespace openddl::detail;
				REQUIRE_FALSE(tokens.empty());
				REQUIRE(tokens.size() == 3);
				for (auto & t : tokens)
				{
					CHECK(t.token_type == Token::kCharacterLiteral);
				}
			}
		}
	}
	GIVEN("A sequence of decimal literals"){
		std::string input = "99 -1000 +1337";
		std::vector<openddl::detail::Error> errors;
		std::vector<openddl::detail::Token> tokens;
		WHEN("the string is parsed"){
			REQUIRE(openddl::detail::lex(input, tokens, errors));
			THEN("Tokens should be emitted as decimal literals"){
				using namespace openddl::detail;
				REQUIRE_FALSE(tokens.empty());
				REQUIRE(tokens.size() == 3);
				for (auto & t : tokens)
				{
					CHECK(t.token_type == Token::kDecimalLiteral);
				}
			}
		}
	}
	GIVEN("A sequence of float literals"){
		std::string input = "99.0 -99e-10 +.99E+22";
		std::vector<openddl::detail::Error> errors;
		std::vector<openddl::detail::Token> tokens;
		WHEN("the string is parsed"){
			REQUIRE(openddl::detail::lex(input, tokens, errors));
			THEN("Tokens should be emitted as float literals"){
				using namespace openddl::detail;
				REQUIRE_FALSE(tokens.empty());
				REQUIRE(tokens.size() == 3);
				for (auto & t : tokens)
				{
					CHECK(t.token_type == Token::kFloatLiteral);
				}
			}
		}
	}
	GIVEN("A sequence of string literals"){
		std::string input = "\" abcd \" \"\\U123456 \\u9999 \"";
		std::vector<openddl::detail::Error> errors;
		std::vector<openddl::detail::Token> tokens;
		WHEN("the string is parsed"){
			REQUIRE(openddl::detail::lex(input, tokens, errors));
			THEN("Strings should be emitted as a seperate string literals"){
				using namespace openddl::detail;
				REQUIRE_FALSE(tokens.empty());
				REQUIRE(tokens.size() == 2);
				for (auto & t : tokens)
				{
					CHECK(t.token_type == Token::kStringLiteral);
				}
			}
		}
	}
	GIVEN("A sequence of boolean literals"){
		std::string input = "true false TRUE FALSE null yes no";
		std::vector<openddl::detail::Error> errors;
		std::vector<openddl::detail::Token> tokens;
		WHEN("the string is parsed"){
			REQUIRE(openddl::detail::lex(input, tokens, errors));
			THEN("Only valid tokens should be emitted as boolean literals"){
				using namespace openddl::detail;
				REQUIRE_FALSE(tokens.empty());
				REQUIRE(tokens.size() == 7);
				CHECK(tokens[0].token_type == Token::kBooleanLiteral);
				CHECK(tokens[1].token_type == Token::kBooleanLiteral);
				CHECK(tokens[2].token_type != Token::kBooleanLiteral);
				CHECK(tokens[3].token_type != Token::kBooleanLiteral);
				CHECK(tokens[4].token_type != Token::kBooleanLiteral);
				CHECK(tokens[5].token_type != Token::kBooleanLiteral);
				CHECK(tokens[6].token_type != Token::kBooleanLiteral);
			}
		}
	}
}
TEST_CASE("Lexer can handle improperly formatted literals", "[lex]"){
	GIVEN("An unterminated string"){
		std::string input = "\" abcd";
		std::vector<openddl::detail::Error> errors;
		std::vector<openddl::detail::Token> tokens;
		WHEN("the string is parsed"){
			REQUIRE_FALSE(openddl::detail::lex(input, tokens, errors));
			THEN("Errors should be emitted"){
				using namespace openddl::detail;
				REQUIRE(tokens.empty());
				REQUIRE_FALSE(errors.empty());
				CHECK(errors[0].message == "lex.unterminated_string_literal");

			}
		}
	}
	GIVEN("An unterminated character literal"){
		std::string input = "' abcd";
		std::vector<openddl::detail::Error> errors;
		std::vector<openddl::detail::Token> tokens;
		WHEN("the string is parsed"){
			REQUIRE_FALSE(openddl::detail::lex(input, tokens, errors));
			THEN("Errors should be emitted"){
				using namespace openddl::detail;
				REQUIRE(tokens.empty());
				REQUIRE_FALSE(errors.empty());
				CHECK(errors[0].message == "lex.unterminated_character_literal");

			}
		}
	}
	GIVEN("A too long character literal"){
		std::string input = "' abcd            '";
		std::vector<openddl::detail::Error> errors;
		std::vector<openddl::detail::Token> tokens;
		WHEN("the string is parsed"){
			REQUIRE_FALSE(openddl::detail::lex(input, tokens, errors));
			THEN("Errors should be emitted"){
				using namespace openddl::detail;
				REQUIRE(tokens.empty());
				REQUIRE_FALSE(errors.empty());
				CHECK(errors[0].message == "lex.character_length_error");

			}
		}
	}
	GIVEN("A character literal with invalid characters"){
		std::string input = "' abcd\\c'";
		std::vector<openddl::detail::Error> errors;
		std::vector<openddl::detail::Token> tokens;
		WHEN("the string is parsed"){
			REQUIRE_FALSE(openddl::detail::lex(input, tokens, errors));
			THEN("Errors should be emitted"){
				using namespace openddl::detail;
				REQUIRE(tokens.empty());
				REQUIRE_FALSE(errors.empty());
				CHECK(errors[0].message == "lex.invalid_character");

			}
		}
	}
	GIVEN("A string literal with invalid characters"){
		std::string input = "\" abcd\\c\"";
		std::vector<openddl::detail::Error> errors;
		std::vector<openddl::detail::Token> tokens;
		WHEN("the string is parsed"){
			REQUIRE_FALSE(openddl::detail::lex(input, tokens, errors));
			THEN("Errors should be emitted"){
				using namespace openddl::detail;
				REQUIRE(tokens.empty());
				REQUIRE_FALSE(errors.empty());
				CHECK(errors[0].message == "lex.invalid_character");

			}
		}
	}
	GIVEN("A sequence of error literals"){
		std::string input = "0b1222 0xAZX 99AT 30.0Y";
		std::vector<openddl::detail::Error> errors;
		std::vector<openddl::detail::Token> tokens;
		WHEN("the string is parsed"){
			REQUIRE_FALSE(openddl::detail::lex(input, tokens, errors));
			THEN("Errors should be emitted"){
				using namespace openddl::detail;
				REQUIRE(tokens.empty());
				REQUIRE_FALSE(errors.empty());
				for (auto & e : errors){
					CHECK(errors[0].message == "lex.invalid_literal");
				}
			}
		}
	}

}