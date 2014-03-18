#include "..\openddl\detail.h"
#include "..\openddl\detail\Error.h"
#include "..\openddl\detail\Token.h"
#include "..\openddl\detail\Command.h"

#include <iostream>

const char *command_names[] = { "kStructure", "kDataList", "kDataArray", "kArrayElement", "kLiteral", "kProperty" };
int main(int argc, char * argv[])
{

	using namespace openddl::detail;
	std::vector<Token> tokens;
	std::vector<Error> errors;
	std::vector<Command> commands;
	//std::string input = "Hello {name = \"Hello\"}{ int8 {22} }";
	std::string input = "int8[2] $name {{2,2},{2,2}} Hello {}{}";
	if (!lex(input, tokens, errors))
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
		for (auto & command : commands)
		{
			std::cout << command_names[command.type];
			std::cout << std::endl;
		}
	}
		
	return 0;
	
}
