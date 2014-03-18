#include "stdafx.h"
#include "catch.hpp"
#include "../openddl/detail.h"
#include "../openddl/detail/Command.h"
#include "../openddl/detail/Token.h"
#include "../openddl/detail/Error.h"

TEST_CASE("Parsing Data Lists", "[parse]"){
	GIVEN("A OpenDDL integer list"){
		std::string input = "int8 { 99, 22 } ";
		std::vector<openddl::detail::Error> errors;
		std::vector<openddl::detail::Token> tokens;
		std::vector<openddl::detail::Command> commands;
		WHEN("the string is parsed"){
			REQUIRE(openddl::detail::lex(input, tokens, errors));
			THEN("should have no errors"){
				REQUIRE(errors.empty());
				AND_WHEN("the token stream is parsed"){
					REQUIRE(openddl::detail::parse(tokens, commands, errors));
					THEN("should have no errors"){
						using openddl::detail::Command;
						REQUIRE(errors.empty());
						REQUIRE(commands.size() == 3);
						CHECK(commands[0].type == Command::kDataList);
						CHECK(commands[0].parent == -1);
						CHECK(commands[0].payload.list_.length == 2);
						CHECK(commands[0].payload.list_.type == openddl::Type::kInt8);
						CHECK(commands[1].type == Command::kLiteral);
						CHECK(commands[1].parent == 0);
						CHECK(commands[2].type == Command::kLiteral);
						CHECK(commands[2].parent == 0);
					}
				}
			}
		}
	}
	GIVEN("An OpenDDL float list"){
		std::string input = "float { 99, +99e99 } ";
		std::vector<openddl::detail::Error> errors;
		std::vector<openddl::detail::Token> tokens;
		std::vector<openddl::detail::Command> commands;
		WHEN("the string is parsed"){
			REQUIRE(openddl::detail::lex(input, tokens, errors));
			THEN("should have no errors"){
				REQUIRE(errors.empty());
				AND_WHEN("the token stream is parsed"){
					REQUIRE(openddl::detail::parse(tokens, commands, errors));
					THEN("should have no errors"){
						using openddl::detail::Command;
						REQUIRE(errors.empty());
						REQUIRE(commands.size() == 3);
						CHECK(commands[0].type == Command::kDataList);
						CHECK(commands[0].parent == -1);
						CHECK(commands[0].payload.list_.length == 2);
						CHECK(commands[0].payload.list_.type == openddl::Type::kFloat);
						CHECK(commands[1].type == Command::kLiteral);
						CHECK(commands[1].parent == 0);
						CHECK(commands[2].type == Command::kLiteral);
						CHECK(commands[2].parent == 0);
					}
				}
			}
		}
	}
	GIVEN("An OpenDDL string list"){
		std::string input = "string { \"hello\", \"world\" } ";
		std::vector<openddl::detail::Error> errors;
		std::vector<openddl::detail::Token> tokens;
		std::vector<openddl::detail::Command> commands;
		WHEN("the string is parsed"){
			REQUIRE(openddl::detail::lex(input, tokens, errors));
			THEN("should have no errors"){
				REQUIRE(errors.empty());
				AND_WHEN("the token stream is parsed"){
					REQUIRE(openddl::detail::parse(tokens, commands, errors));
					THEN("should have no errors"){
						using openddl::detail::Command;
						REQUIRE(errors.empty());
						REQUIRE(commands.size() == 3);
						CHECK(commands[0].type == Command::kDataList);
						CHECK(commands[0].parent == -1);
						CHECK(commands[0].payload.list_.length == 2);
						CHECK(commands[0].payload.list_.type == openddl::Type::kString);
						CHECK(commands[1].type == Command::kLiteral);
						CHECK(commands[1].parent == 0);
						CHECK(commands[2].type == Command::kLiteral);
						CHECK(commands[2].parent == 0);
					}
				}
			}
		}
	}
}
TEST_CASE("Parsing Data List Array", "[parse]"){

}
TEST_CASE("Parsing nested data structures", "[parse]"){

}