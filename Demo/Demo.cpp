#include "..\openddl\detail.h"
#include "..\openddl\detail\Error.h"
#include "..\openddl\detail\Token.h"
#include "..\openddl\detail\Command.h"

#include <iostream>
int main(int argc, char * argv[])
{

	using namespace openddl::detail;
	std::vector<Token> tokens;
	std::vector<Error> errors;
	std::vector<Command> commands;
	if (!lex("int64 { -99, 2000, -2000 } int8{ 1,2,3}", tokens, errors))
	{
		std::cout << "An error occurred during lexing" << std::endl;
		for (auto & e : errors)
			std::cout << "-- " << e.message << ": " << e.payload << std::endl;
	}	
	else if (!parse(tokens, commands, errors))
	{
		std::cout << "An error occurred during parsing" << std::endl;
		for (auto & e : errors)
			std::cout << "-- " <<  e.message << ": "<< e.payload << std::endl;
	}
	else
	{
		std::cout << "Successfully parsed input string" << std::endl;
		std::cout << "-- Got " << tokens.size() << " tokens." << std::endl;
		std::cout << "-- Got " << commands.size() << " commands." << std::endl;
	}
		
	return 0;
	
}
