//================================================================================================================
// Copyright 2014 Denis Hilliard (armchaircommando@gmail.com)
// Licensed under MIT License
//================================================================================================================
#pragma once
#include <vector>
#include <string>
#include <cstdint>
#include <map>
namespace openddl
{

	namespace detail
	{

		struct Token;
		struct Error;
		struct Command;

		//Will return false upon error. If errors is also empty, an undefined error has occurred and should be reported
		bool lex(const std::string & input, std::vector<Token> &tokens, std::vector<Error> & errors);
		//Will return false upon error. If errors is also empty, an undefined error has occurred and should be reported
		bool parse(const std::vector<Token> & tokens, std::vector<Command> & commands, std::vector<Error> & errors);
		//Will return false upon error
		//Will construct reference indices (to speed up reference lookups) in global_names and local_names respectively 
		bool semantic_check(std::vector<Command> & commands, std::vector<Error> & errors, std::map<std::string,int> & global_names, std::map<int,std::map<std::string,int> > & local_names);

	}


};



