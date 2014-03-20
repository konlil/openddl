#pragma once
#include <string>
#include <vector>

#include "detail\Command.h"
#include "detail\Error.h"

namespace openddl
{	
	



	//Handles to openddl elements which are default constructible as null objects
	struct Literal
	{
		Literal();
	};
	struct Reference
	{
		Reference();
	};
	struct String
	{
		String();
		const std::string & get(bool decode = true);
	};
	struct DataArray
	{
		DataArray();
	};
	struct DataList
	{
		DataList();
	};
	struct Property
	{
		Property();
		const std::string & name();
		
	};
	struct Structure
	{
		Structure();

		const std::string & identifier();
		bool has_name();
		const std::string & name();
		const unsigned int children();
		const unsigned int properties();

		struct Visitor
		{
			virtual void visit(const Property & p) = 0;
			virtual void visit(const Structure & s) = 0;
			virtual void visit(const DataArray & a) = 0;
			virtual void visit(const DataList & l) = 0;
		};

		void visit_children(Visitor & v);
	};

	
	//High level wrapper around low level command stream
	struct Tree
	{
		Tree();
		Tree(Tree && t);
		void visit_children(Structure::Visitor & v);
		static Tree parse(const std::string & i);
	private:
		std::vector<detail::Command> commands;
		
	};

	class ParseError : public std::exception
	{
	public:
		const char * what();
		std::string errors();
		ParseError(std::vector<detail::Error> &e);
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

