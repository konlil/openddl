#include "stdafx.h"
#include "catch.hpp"
#include "../openddl/detail/detail.h"
#include "../openddl/detail/Command.h"
#include "../openddl/detail/Token.h"
#include "../openddl/detail/Error.h"
TEST_CASE("String Literal Lists", "[parse]")
{
	GIVEN("Valid string list"){
		std::string input = "string { \" \" }";
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
	GIVEN("Strings with illegal characters"){
		std::string input = "string { \" \x5C  \x15 \" }";
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
						REQUIRE(errors.size() == 2);
						CHECK(errors[0].message == "parse.string.invalid_character");
						CHECK(errors[1].message == "parse.string.invalid_character");
					}
				}
			}
		}
	}
	
}

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
		std::string input = "int8 { 30,3.0 } ";
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
						CHECK(errors[0].message == "parse.literal.type_mismatch");
					}
				}
			}
		}
	}
	GIVEN("Literal List missing comma"){
		std::string input = "bool { false true false } ";
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
	
	GIVEN("Invalid reference literal"){
		std::string input = "ref { null $hello, %hello $hello  } ";
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
						CHECK(errors[0].message == "parse.list.illegal_reference");
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


}

TEST_CASE("Parsing data structures", "[parse]"){

	GIVEN("Empty OpenDDL structures"){
		std::string input = "Hello {} Hello $name {} Hello (){}";
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
	GIVEN("Nested OpenDDL structures"){
		std::string input = "Hello { Hello { int8{1} } } ";
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
						REQUIRE(commands.size() == 4);
					}
				}
			}
		}
	}

	GIVEN("OpenDDL Structures with properties"){
		std::string input = "Hello (hello = true){} Hello (hello = true,goodbye = 'abcd'){}  Hello $name (){}";
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
	GIVEN("Illegal token following property list"){
		std::string input = "Hello(hello = 1, world = 1) $name {}";
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
						REQUIRE(errors.size() == 1);
						CHECK(errors[0].message == "parse.illegal_token");
					}
				}
			}
		}
	}
	
	GIVEN("Valid OpenDDL structures"){
		std::string input = "Hello {string {\"Hello\"}} Hello $name {int8{1} float{99}}";
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

	GIVEN("Unterminated OpenDDL structure"){
		std::string input = "Hello () {";
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
						CHECK(errors[0].message == "parse.unexpected_end_of_file");
					}
				}
			}
		}
	}
	GIVEN("Unterminated Property Array"){
		std::string input = "Hello (";
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
						CHECK(errors[0].message == "parse.unexpected_end_of_file");
					}
				}
			}
		}
	}
}
