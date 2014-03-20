#include "..\openddl\Tree.h"
#include <fstream>
#include <streambuf>
#include <iostream>



using namespace openddl::detail;

int main(int argc, char * argv[])
{

	std::ifstream file("input.oddl");
	std::string input;
	
	if (file)
	{
		file.seekg(0, std::ios::end);
		input.reserve((unsigned int)file.tellg());
		file.seekg(0, std::ios::beg);
		input.assign((std::istreambuf_iterator<char>(file)),
			std::istreambuf_iterator<char>());
	}
	

	if (input.empty())
	{
		std::cout << "Error reading file" << std::endl;
	}

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
