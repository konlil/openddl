#pragma once
#include <vector>
namespace openddl
{	
	struct Structure;
	struct Token;
	struct Error;
	void parse(const std::vector<Token> & tokens, std::vector<Error> & errors, Structure & s);
}

