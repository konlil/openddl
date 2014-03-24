#include "stdafx.h"

#include "catch.hpp"
#include "..\openddl\detail\detail.h"
#include "..\openddl\detail\Error.h"
#include "..\openddl\detail\Token.h"
#include "..\openddl\detail\Command.h"

TEST_CASE("Literal overflows", "[semantic]"){
	GIVEN("Data list with members which will cause containing type to overflow"){
		std::string input = "int8 {2000,-2000}";
		std::vector<openddl::detail::Error> errors;
		std::vector<openddl::detail::Token> tokens;
		std::vector<openddl::detail::Command> commands;
		std::map<std::string, unsigned int> global_names;
		std::map<unsigned int, std::map<std::string, unsigned int> > local_names;
		WHEN("the string is parsed"){
			REQUIRE(openddl::detail::lex(input, tokens, errors));
			THEN("should have no errors"){
				REQUIRE(errors.empty());
				AND_WHEN("the token stream is parsed"){
					REQUIRE(openddl::detail::parse(tokens, commands, errors));
					AND_THEN("should have no errors"){
						REQUIRE(errors.empty());
						AND_WHEN("the command stream is validated"){
							REQUIRE_FALSE(openddl::detail::semantic_check(commands, errors, global_names, local_names));
							AND_THEN("should have errors"){
								REQUIRE(errors.size() == 2);
								CHECK(errors[0].message == "semantic.literal.overflow");
								CHECK(errors[1].message == "semantic.literal.underflow");
							}
						}
					}
				}
			}
		}
	}
	GIVEN("Data list with members which will cause containing type to overflow"){
		std::string input = "unsigned_int8 {2000,-22}";
		std::vector<openddl::detail::Error> errors;
		std::vector<openddl::detail::Token> tokens;
		std::vector<openddl::detail::Command> commands;
		std::map<std::string, unsigned int> global_names;
		std::map<unsigned int, std::map<std::string, unsigned int> > local_names;
		WHEN("the string is parsed"){
			REQUIRE(openddl::detail::lex(input, tokens, errors));
			THEN("should have no errors"){
				REQUIRE(errors.empty());
				AND_WHEN("the token stream is parsed"){
					REQUIRE(openddl::detail::parse(tokens, commands, errors));
					AND_THEN("should have no errors"){
						REQUIRE(errors.empty());
						AND_WHEN("the command stream is validated"){
							REQUIRE_FALSE(openddl::detail::semantic_check(commands, errors, global_names, local_names));
							AND_THEN("should have errors"){
								REQUIRE(errors.size() == 2);
								CHECK(errors[0].message == "semantic.literal.overflow");
								CHECK(errors[1].message == "semantic.literal.underflow");
							}
						}
					}
				}
			}
		}
	}
}

TEST_CASE("Array size mismatch", "[semantic]"){
	GIVEN("Data array with zero array size"){
		std::string input = "int8[0] { {1,1}, {2} }";
		std::vector<openddl::detail::Error> errors;
		std::vector<openddl::detail::Token> tokens;
		std::vector<openddl::detail::Command> commands;
		std::map<std::string, unsigned int> global_names;
		std::map<unsigned int, std::map<std::string, unsigned int> > local_names;
		WHEN("the string is parsed"){
			REQUIRE(openddl::detail::lex(input, tokens, errors));
			THEN("should have no errors"){
				REQUIRE(errors.empty());
				AND_WHEN("the token stream is parsed"){
					REQUIRE(openddl::detail::parse(tokens, commands, errors));
					AND_THEN("should have no errors"){
						REQUIRE(errors.empty());
						AND_WHEN("the command stream is validated"){
							REQUIRE_FALSE(openddl::detail::semantic_check(commands, errors, global_names, local_names));
							AND_THEN("should have errors"){
								REQUIRE(errors.size() == 1);
								CHECK(errors[0].message == "semantic.array.zero_dimension");
							}
						}
					}
				}
			}
		}
	}
	GIVEN("Data array element dimension mismatch"){
		std::string input = "int8[2] { {1,1}, {2} }";
		std::vector<openddl::detail::Error> errors;
		std::vector<openddl::detail::Token> tokens;
		std::vector<openddl::detail::Command> commands;
		std::map<std::string, unsigned int> global_names;
		std::map<unsigned int, std::map<std::string, unsigned int> > local_names;
		WHEN("the string is parsed"){
			REQUIRE(openddl::detail::lex(input, tokens, errors));
			THEN("should have no errors"){
				REQUIRE(errors.empty());
				AND_WHEN("the token stream is parsed"){
					REQUIRE(openddl::detail::parse(tokens, commands, errors));
					AND_THEN("should have no errors"){
						REQUIRE(errors.empty());
						AND_WHEN("the command stream is validated"){
							REQUIRE_FALSE(openddl::detail::semantic_check(commands, errors, global_names, local_names));
							AND_THEN("should have errors"){
								REQUIRE(errors.size() == 1);
								CHECK(errors[0].message == "semantic.array.dimension_mismatch");
							}
						}
					}
				}
			}
		}
	}
}
TEST_CASE("Structure Property Name Clash", "[semantic]"){
	
	GIVEN("Structures with two properties with same name"){
		std::string input = "Hello $name (hello = 1 , hello = 2 ){} Hello (hello = 1 , world = 1 ) {}";
		std::vector<openddl::detail::Error> errors;
		std::vector<openddl::detail::Token> tokens;
		std::vector<openddl::detail::Command> commands;
		std::map<std::string, unsigned int> global_names;
		std::map<unsigned int, std::map<std::string, unsigned int> > local_names;
		WHEN("the string is parsed"){
			REQUIRE(openddl::detail::lex(input, tokens, errors));
			THEN("should have no errors"){
				REQUIRE(errors.empty());
				AND_WHEN("the token stream is parsed"){
					REQUIRE(openddl::detail::parse(tokens, commands, errors));
					AND_THEN("should have no errors"){
						REQUIRE(errors.empty());
						AND_WHEN("the command stream is validated"){
							REQUIRE_FALSE(openddl::detail::semantic_check(commands, errors, global_names, local_names));
							AND_THEN("should have errors"){
								REQUIRE(errors.size() == 1);
								CHECK(errors[0].message == "semantic.structure.property.name_clash");
							}
						}
					}
				}
			}
		}
	}
	
}

TEST_CASE("Structure name clash", "[semantic]"){
	GIVEN("Structures with different names"){
		std::string input = "Hello $world {} Hello $name {}";
		std::vector<openddl::detail::Error> errors;
		std::vector<openddl::detail::Token> tokens;
		std::vector<openddl::detail::Command> commands;
		std::map<std::string, unsigned int> global_names;
		std::map<unsigned int, std::map<std::string, unsigned int> > local_names;
		WHEN("the string is parsed"){
			REQUIRE(openddl::detail::lex(input, tokens, errors));
			THEN("should have no errors"){
				REQUIRE(errors.empty());
				AND_WHEN("the token stream is parsed"){
					REQUIRE(openddl::detail::parse(tokens, commands, errors));
					AND_THEN("should have no errors"){
						REQUIRE(errors.empty());
						AND_WHEN("the command stream is validated"){
							REQUIRE(openddl::detail::semantic_check(commands, errors, global_names, local_names));
							AND_THEN("should have no errors"){
								REQUIRE(errors.empty());
							}
						}
					}
				}
			}
		}
	}
	GIVEN("Structures with same global name"){
		std::string input = "Hello $name {} Hello $name {}";
		std::vector<openddl::detail::Error> errors;
		std::vector<openddl::detail::Token> tokens;
		std::vector<openddl::detail::Command> commands;
		std::map<std::string, unsigned int> global_names;
		std::map<unsigned int,std::map<std::string, unsigned int> > local_names;
		WHEN("the string is parsed"){
			REQUIRE(openddl::detail::lex(input, tokens, errors));
			THEN("should have no errors"){
				REQUIRE(errors.empty());
				AND_WHEN("the token stream is parsed"){
					REQUIRE(openddl::detail::parse(tokens, commands, errors));
					AND_THEN("should have no errors"){
						REQUIRE(errors.empty());
						AND_WHEN("the command stream is validated"){
							REQUIRE_FALSE(openddl::detail::semantic_check(commands, errors, global_names, local_names));
							AND_THEN("should have errors"){
								REQUIRE(errors.size() == 1);
								CHECK(errors[0].message == "semantic.global_name_clash");
							}
						}
					}
				}
			}
		}
	}
	GIVEN("Structures with same local name"){
		std::string input = "Hello %name {} Hello %name {}";
		std::vector<openddl::detail::Error> errors;
		std::vector<openddl::detail::Token> tokens;
		std::vector<openddl::detail::Command> commands;
		std::map<std::string, unsigned int> global_names;
		std::map<unsigned int, std::map<std::string, unsigned int> > local_names;
		WHEN("the string is parsed"){
			REQUIRE(openddl::detail::lex(input, tokens, errors));
			THEN("should have no errors"){
				REQUIRE(errors.empty());
				AND_WHEN("the token stream is parsed"){
					REQUIRE(openddl::detail::parse(tokens, commands, errors));
					AND_THEN("should have no errors"){
						REQUIRE(errors.empty());
						AND_WHEN("the command stream is validated"){
							REQUIRE_FALSE(openddl::detail::semantic_check(commands, errors, global_names, local_names));
							AND_THEN("should have errors"){
								REQUIRE(errors.size() == 1);
								CHECK(errors[0].message == "semantic.local_name_clash");
							}
						}
					}
				}
			}
		}
	}
}
