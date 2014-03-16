//================================================================================================================
// Copyright 2014 Denis Hilliard (armchaircommando@gmail.com)
// Licensed under MIT License
//================================================================================================================
#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <cstdint>
namespace openddl
{

	enum Type {
		kFloat,
		kDouble,
		kRef,
		kUnsignedInt8,
		kUnsignedInt16,
		kUnsignedInt32,
		kUnsignedInt64,
		kInt8,
		kInt16,
		kInt32,
		kInt64,
		kBool,
		kString,
		kType
	};
	namespace detail
	{

		struct Token;
		struct Error;
		struct Command;

		//Will only return false if an internal error has occurred and not all input was consumed.
		bool lex(const std::string & input, std::vector<Token> &tokens, std::vector<Error> & errors);
		//Will only return false if an internal error has occurred and not all input was consumed.
		bool parse(const std::vector<Token> & tokens, std::vector<Command> & commands, std::vector<Error> & errors);

	}


};



