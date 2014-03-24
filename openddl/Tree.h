#pragma once
#include <string>
#include <memory>


namespace openddl
{	
	struct Visitor;
	/*
	*	Entry point into high level API over detail namespace
	*/
	struct Tree
	{
		Tree();
		Tree(Tree && t);
		
		//Visit the direct descendants of the root node
		void visit_children(Visitor & v);
		
		//Parse an input string and construct the tree structure.
		static Tree parse(const std::string & i);

		
		
	private:
		friend struct Structure;
		struct Impl;
		std::shared_ptr<Impl> implementation;
		
		
	};
	
}

