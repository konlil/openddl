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
	if (!lex("float {3.0} int8 {99,22} ref {null}", tokens, errors))
	{
		std::cout << "Error during lexing" << std::endl;	
	}	
	else
	{
		for (auto & e : errors)
			std::cout << e.message << std::endl;
		if (!parse(tokens, commands, errors))
		{
			std::cout << "Error during parsing" << std::endl;
			for (auto & e : errors)
				std::cout << e.message << std::endl;
		}
		else
		{
			
			if (errors.size() == 0)
			{
				std::cout << "Success" << std::endl;
				std::string format("-- ");
				for (auto & c : commands)
				{
					switch (c.type)
					{
					case Command::kDataList:
						std::cout << "Got data list with "<< c.payload.list_.length << " elements."<< std::endl;
						break;
					case Command::kLiteral:
					{
						std::cout << format << "Got ";
						switch (c.payload.literal_.encoding)
						{
						case Command::LiteralPayload::kBoolean:
							std::cout << "boolean"; break;
						case Command::LiteralPayload::kFloat:
							std::cout << "float"; break;
						case Command::LiteralPayload::kInteger:
							std::cout << "integer"; break;
						case Command::LiteralPayload::kReference:
							std::cout << "reference"; break;
						case Command::LiteralPayload::kString:
							std::cout << "string"; break;
						case Command::LiteralPayload::kType:
							std::cout << "type"; break;
						}
						std::cout <<" Literal" << std::endl;
					}
						
						
					}
				}
			}
			else
				for (auto & e : errors)
					std::cout << e.message << std::endl;
		}
	
	}
	
}
