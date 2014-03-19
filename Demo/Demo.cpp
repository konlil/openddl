#include "..\openddl\detail.h"
#include "..\openddl\detail\Error.h"
#include "..\openddl\detail\Token.h"
#include "..\openddl\detail\Command.h"
#include <fstream>
#include <streambuf>
#include <iostream>


bool parse_string(const std::string &input, std::vector<openddl::detail::Command> &commands)
{
	using namespace openddl::detail;
	std::vector<Token> tokens;
	std::vector<Error> errors;
	if (!lex(input, tokens, errors))
	{
		std::cout << "An error occurred during lexing" << std::endl;
		for (auto & e : errors)
			std::cout << "-- " << e.message << ": " << e.payload << std::endl;
		return false;
	}
	else if (!parse(tokens, commands, errors))
	{
		std::cout << "An error occurred during parsing" << std::endl;
		for (auto & e : errors)
			std::cout << "-- " << e.message << ": " << e.payload << std::endl;
		return false;
	}
	return true;
}
using namespace openddl::detail;
int print_data_list(std::string & format,Command * ts, Command * te)
{
	
	if (ts->type == Command::kDataList)
	{
		std::cout << format << " Data List" << std::endl;
		for (int i = 0; i < ts->payload.list_.length; i++)
		{
			std::cout << format << "- Literal" << std::endl;
		}
		return ts->payload.array_.length;
	}
	else if (ts->type == Command::kArrayElement)
	{
		std::cout << format << "- Array Element" << std::endl;
		for (int i = 0; i < ts->payload.element_.length; i++)
		{
			std::cout << format << "-- Literal" << std::endl;
		}
		return ts->payload.element_.length;
	}
	return 0;
}
int print_data_array_list(std::string & format, Command * ts, Command * te)
{
	if (ts->type == Command::kDataArray)
	{
		Command * start = ts;
		std::cout << format << "Data Array List" << std::endl;
		int length = ts->payload.array_.length;
		ts += 1;
		for (int i = 0; i < length ; i++)
		{
			ts+=print_data_list(format,ts, te);
		}
		return ts-start;
	}
	return 0;
}
int main(int argc, char * argv[])
{

	std::ifstream file("input.oddl");
	std::string input;
	
	if (file)
	{
		file.seekg(0, std::ios::end);
		input.reserve(file.tellg());
		file.seekg(0, std::ios::beg);
		input.assign((std::istreambuf_iterator<char>(file)),
			std::istreambuf_iterator<char>());
	}
	

	std::vector<openddl::detail::Command> commands;
	if (input.empty())
	{
		std::cout << "Error reading file" << std::endl;
	}
	else if (parse_string(input,commands))
	{
		std::cout << "Successfully parsed input string" << std::endl;
		
		Command * te = commands.data() + commands.size();
		std::string format;

		for (Command * ts = commands.data(); ts < te;)
		{
			format.clear();
			for (int i = 0; i < ts->depth; i++)
			{
				format.push_back('-');
			}
			switch (ts->type)
			{
			case Command::kStructure:
				std::cout << format << "Structure";
				if (ts->payload.structure_.name != nullptr)
					std::cout << " with name "<< *ts->payload.structure_.name;
				if (ts->payload.structure_.properties)
					std::cout << " with " << ts->payload.structure_.properties << " properties.";
				std::cout << std::endl;
				break;
			case Command::kProperty:
				std::cout << format << "Property" << std::endl;
				break;
				
			case Command::kDataList:
				ts += print_data_list(format,ts, te);
				break;
			case Command::kDataArray:
				ts += print_data_array_list(format,ts, te);
				break;

			}
			ts++;
		}
	}
		
	return 0;
	
}
