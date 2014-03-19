#include "stdafx.h"
#include "catch.hpp"
#include "../openddl/detail.h"
#include "../openddl/detail/Command.h"
#include "../openddl/detail/Token.h"
#include "../openddl/detail/Error.h"
/*
TEST_CASE("Parsing Data Lists", "[parse]"){
	
	GIVEN("Valid OpenDDL literal lists"){
		std::string input = "int8 { 99, 22 } bool $name {true,false} string %name { \"Hello\" } float { 99e10 } ref {null}";
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
						REQUIRE(errors.empty());
					}
				}
			}
		}
	}
	
	
	GIVEN("Missing literal from list"){
		std::string input = "int8 { 88 , ";
		std::vector<openddl::detail::Error> errors;
		std::vector<openddl::detail::Token> tokens;
		std::vector<openddl::detail::Command> commands;
		WHEN("the string is lexed"){
			REQUIRE(openddl::detail::lex(input, tokens, errors));
			THEN("should have no errors"){
				REQUIRE(errors.empty());
				AND_WHEN("the token stream is parsed"){
					REQUIRE_FALSE(openddl::detail::parse(tokens, commands, errors));
					THEN("should have errors"){
						REQUIRE_FALSE(errors.empty());
						CHECK(errors[0].message == "parse.unexpected_end_of_file");
					}
				}
			}
		}
	}
	
	GIVEN("Missing closing brace from list"){
		std::string input = "int8 { 88 , 80 ";
		std::vector<openddl::detail::Error> errors;
		std::vector<openddl::detail::Token> tokens;
		std::vector<openddl::detail::Command> commands;
		WHEN("the string is lexed"){
			REQUIRE(openddl::detail::lex(input, tokens, errors));
			THEN("should have no errors"){
				REQUIRE(errors.empty());
				AND_WHEN("the token stream is parsed"){
					REQUIRE_FALSE(openddl::detail::parse(tokens, commands, errors));
					THEN("should have errors"){
						REQUIRE_FALSE(errors.empty());
						CHECK(errors[0].message == "parse.unexpected_end_of_file");
					}
				}
			}
		}
	}

	GIVEN("Literal List encoding mismatch"){
		std::string input = "int8 { 3.0,30 } ";
		std::vector<openddl::detail::Error> errors;
		std::vector<openddl::detail::Token> tokens;
		std::vector<openddl::detail::Command> commands;
		WHEN("the string is lexed"){
			REQUIRE(openddl::detail::lex(input, tokens, errors));
			THEN("should have no errors"){
				REQUIRE(errors.empty());
				AND_WHEN("the token stream is parsed"){
					REQUIRE_FALSE(openddl::detail::parse(tokens, commands, errors));
					THEN("should have errors"){
						REQUIRE_FALSE(errors.empty());
						CHECK(errors[0].message == "semantic.literal.type_mismatch");
					}
				}
			}
		}
	}
	GIVEN("Literal List missing comma"){
		std::string input = "bool { false true } ";
		std::vector<openddl::detail::Error> errors;
		std::vector<openddl::detail::Token> tokens;
		std::vector<openddl::detail::Command> commands;
		WHEN("the string is lexed"){
			REQUIRE(openddl::detail::lex(input, tokens, errors));
			THEN("should have no errors"){
				REQUIRE(errors.empty());
				AND_WHEN("the token stream is parsed"){
					REQUIRE_FALSE(openddl::detail::parse(tokens, commands, errors));
					THEN("should have errors"){
						REQUIRE_FALSE(errors.empty());
						CHECK(errors[0].message == "parse.data_list.missing_comma");
					}
				}
			}
		}
	}
	GIVEN("Non homogenous data list"){
		std::string input = "bool { false , 99 } ";
		std::vector<openddl::detail::Error> errors;
		std::vector<openddl::detail::Token> tokens;
		std::vector<openddl::detail::Command> commands;
		WHEN("the string is lexed"){
			REQUIRE(openddl::detail::lex(input, tokens, errors));
			THEN("should have no errors"){
				REQUIRE(errors.empty());
				AND_WHEN("the token stream is parsed"){
					REQUIRE_FALSE(openddl::detail::parse(tokens, commands, errors));
					THEN("should have errors"){
						REQUIRE_FALSE(errors.empty());
						CHECK(errors[0].message == "semantic.literal.type_mismatch");
					}
				}
			}
		}
	}
	
	GIVEN("Literals which will cause containing type to overflow"){
		std::string input = "int8 { 200 , -200 } ";
		std::vector<openddl::detail::Error> errors;
		std::vector<openddl::detail::Token> tokens;
		std::vector<openddl::detail::Command> commands;
		WHEN("the string is lexed"){
			REQUIRE(openddl::detail::lex(input, tokens, errors));
			THEN("should have no errors"){
				REQUIRE(errors.empty());
				AND_WHEN("the token stream is parsed"){
					REQUIRE_FALSE(openddl::detail::parse(tokens, commands, errors));
					THEN("should have errors"){
						REQUIRE_FALSE(errors.empty());
						CHECK(errors[0].message == "semantic.literal.overflow");
						CHECK(errors[1].message == "semantic.literal.underflow");
					}
				}
			}
		}
	}
	
}

TEST_CASE("Parsing Data List Array", "[parse]"){
	GIVEN("Valid OpenDDL data array lists"){
		std::string input = "float[2] $name {{1.0,2},{3.0,4}} int8[2] %name {{'a',2},{'b',4}} ";
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
						REQUIRE(errors.empty());
					}
				}
			}
		}
	}
	GIVEN("Variable length data array lists"){
		std::string input = "float[2] $name {{1.0,2,3},{3.0,4}} ";
		std::vector<openddl::detail::Error> errors;
		std::vector<openddl::detail::Token> tokens;
		std::vector<openddl::detail::Command> commands;
		WHEN("the string is parsed"){
			REQUIRE(openddl::detail::lex(input, tokens, errors));
			THEN("should have no errors"){
				REQUIRE(errors.empty());
				AND_WHEN("the token stream is parsed"){
					REQUIRE_FALSE(openddl::detail::parse(tokens, commands, errors));
					THEN("should have errors"){
						REQUIRE_FALSE(errors.empty());
						CHECK(errors[0].message == "semantic.array.size_mismatch");
					}
				}
			}
		}
	}

}
*/
TEST_CASE("Parsing nested data structures", "[parse]"){
	GIVEN("Empty OpenDDL structures"){
		std::string input = "Hello {} Hello $name {} Hello {}{}";
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
						REQUIRE(errors.empty());
						REQUIRE(commands.size() == 3);
					}
				}
			}
		}
	}
	GIVEN("OpenDDL Structures with properties"){
		std::string input = "Hello {hello = true}{} Hello {hello = true,goodbye = 'abcd'}{}  Hello $name {}{}";
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
						REQUIRE(errors.empty());
						REQUIRE(commands.size() == 6);
					}
				}
			}
		}
	}
}