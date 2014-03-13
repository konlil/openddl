#include "..\openddl\detail.h"
#include <iostream>
int main(int argc, char * argv[])
{

	using namespace openddl::detail;
	std::vector<Token> tokens;
	std::vector<Error> errors;
	lex("float {1.0, 2.0, 3.0}", tokens, errors);
	if (parse(tokens, errors))
		std::cout << "Success" << std::endl;
}
