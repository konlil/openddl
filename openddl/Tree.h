#pragma once
#include <string>
#include <vector>
#include <map>

#include "detail\Command.h"
#include "detail\Error.h"

namespace openddl
{	
	

	//Helper templates
	template <typename T>
	struct is_openddl_object
	{
		static const bool value = std::is_same<DataArray, T>::value || std::is_same<DataList, T>::value || std::is_same<Structure, T>::value;
	};

	/*
	* OpenDDL Object Handles
	*/
	struct Literal
	{
		Literal();
	private:
	};
	//Will eventually allow references to be constructed/validated via code
	struct Reference
	{
		Reference();
	private:
	};
	struct String
	{
		String();
		const std::string & get();
	private:
	};
	struct DataArray
	{
		DataArray();
	private:
	};
	struct DataList
	{
		DataList();
	private:
	};
	struct Property
	{
		Property();
		const std::string & name();
	private:
		
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
		//Visit the direct descendants of this structure node
		void visit_children(Visitor & v);
	private:
	};

	
	/*
	*	Entry point into high level API over detail namespace
	*/
	struct Tree
	{
		Tree();
		Tree(Tree && t);

		//Visit the direct descendants of the root node
		void visit_children(Structure::Visitor & v);
		
		//Parse an input string and construct the tree structure.
		static Tree parse(const std::string & i);

		
	private:
		std::vector<detail::Command> commands;

		/*
		* Members related to performing reference look ups within the OpenDDL tree
		*/
		
		typedef std::map<std::string,unsigned int> reference_table;
		reference_table global_names;
		std::map<unsigned int,reference_table> local_names;

		//Implementation used internally by structure/tree to find referenced node
		//friend struct Structure;
		//static int find(Tree & tree, const int parent, const Reference & ref);
		
		
	};
	
}

