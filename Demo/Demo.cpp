#include "..\openddl\Tree.h"
#include "..\openddl\exception.h"

#include <fstream>
#include <streambuf>
#include <iostream>


std::string read_file(const char * name)
{
	std::string out;
	std::ifstream file("input.oddl");
	if (file)
	{
		file.seekg(0, std::ios::end);
		out.reserve((unsigned int)file.tellg());
		file.seekg(0, std::ios::beg);
		out.assign((std::istreambuf_iterator<char>(file)),
			std::istreambuf_iterator<char>());
	}
	return std::move(out);
}
int main(int argc, char * argv[])
{

	std::string input = read_file("input.oddl");
	if (input.empty())
		std::cout << "Error reading file" << std::endl;
	else
		try{
			openddl::Tree tree = openddl::Tree::parse(input);
		}
		catch (openddl::LexerError & e){
			std::cout << e.what() << std::endl;
			std::cout << e.errors() << std::endl;
		}
		catch (openddl::ParseError & e){
			std::cout << e.what() << std::endl;
			std::cout << e.errors() << std::endl;
		}
		
	return 0;
	
}
