#pragma once
#include <string>
#include <vector>
#include "detail\Error.h"

namespace openddl
{
	//Exceptions used for OpenDDL Tree API
	class ParseError : public std::exception
	{
	public:
		const char * what();
		std::string errors();
		ParseError(std::vector<detail::Error> &e);
	private:
		std::vector<detail::Error> _errors;
	};
	class SemanticError : public std::exception
	{
	public:
		const char * what();
		std::string errors();
		SemanticError(std::vector<detail::Error> &e);
	private:
		std::vector<detail::Error> _errors;
	};
	class LexerError : public std::exception
	{
	public:
		const char * what();
		std::string errors();
		LexerError(std::vector<detail::Error> &e);
	private:
		std::vector<detail::Error> _errors;
	};
}

