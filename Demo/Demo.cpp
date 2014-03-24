#include "..\openddl\Tree.h"
#include "..\openddl\exception.h"

#include <fstream>
#include <streambuf>
#include <iostream>
#include "..\openddl\Object.h"
#include "..\openddl\Visitor.h"


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
struct RootVisitor : public openddl::Visitor
{
	std::string format;
	void visit(openddl::Structure & structure) {
		std::cout << format << "Structure( "<< structure.identifier() << " )";
		if (structure.has_name())
			std::cout << " with name " << structure.name();
		std::cout << std::endl;
		format.push_back(' ');
		format.push_back(' ');
		structure.visit_properties([&](const openddl::Property&){ std::cout << format << "-Property" << std::endl; });
		structure.visit_children(*this);
		format.pop_back();
		format.pop_back();
	}
	void visit(openddl::DataList & data_list) {
		std::cout << format << "Data List" << std::endl;
	}
	void visit(openddl::DataArrayList & data_array_list) {
		std::cout << format << "Data Array" << std::endl;
	}
};
int main(int argc, char * argv[])
{

	std::string input = read_file("input.oddl");
	if (input.empty())
		std::cout << "Error reading file" << std::endl;
	else
		try{
			openddl::Tree tree = openddl::Tree::parse(input);
			std::cout << "Success" << std::endl;
			auto v = RootVisitor();
			tree.visit_children(v);
		}
		catch (openddl::LexerError & e){
			std::cout << e.what() << std::endl;
			std::cout << e.errors() << std::endl;
		}
		catch (openddl::ParseError & e){
			std::cout << e.what() << std::endl;
			std::cout << e.errors() << std::endl;
		}
		catch (openddl::SemanticError & e){
			std::cout << e.what() << std::endl;
			std::cout << e.errors() << std::endl;
		}
		
	return 0;
	
}
