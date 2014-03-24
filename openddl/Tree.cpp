#include "Tree.h"
#include "detail/Error.h"
#include "detail/Command.h"
#include "detail/Token.h"
#include "detail/detail.h"
#include "Visitor.h"
#include "Object.h"

#include "exception.h"
#include <iostream>

struct openddl::Tree::Impl
{
	typedef std::map<std::string, unsigned int> name_table;
	typedef std::map<unsigned int, name_table> local_name_table;
	std::vector<detail::Command> commands;
	name_table global_names;
	local_name_table local_names;
	std::map<unsigned int, std::vector<unsigned int>> child_table;
	void visit_children(Visitor & visitor,unsigned int parent,Tree * tree)
	{
		auto it = child_table.find(parent);
		if (it == child_table.end())
			return;
		std::vector<unsigned int> & children = it->second;
		unsigned int properties = 0;
		//Skip any properties if the structure has any
		//if (parent != 0 && commands[parent - 1].type == detail::Command::kStructure) properties = commands[parent - 1].payload.structure_.properties;
		for (unsigned int i = properties; i < children.size(); i++)
		{
			unsigned int index = children[i];
			detail::Command & child = commands[index];
			Object o(tree, index);
			switch (child.type)
			{

			case detail::Command::kDataArray:
				visitor.visit(DataArrayList(o));
				break;
			case detail::Command::kDataList:
				visitor.visit(DataList(o));
				break;
			case detail::Command::kStructure:
				visitor.visit(Structure(o));
				break;
			default:
				break;
			}
		}
	}
	void visit_properties(std::function<void(const Property&)> & visitor, unsigned int parent, Tree * tree)
	{
		detail::Command * structure = &commands[parent - 1];
		if (structure->type == detail::Command::kStructure)
		{
			unsigned int properties = structure->payload.structure_.properties;
			
			for (unsigned int i = 1; i <= properties; i++)
			{
				Object o(tree, parent+i-1);
				visitor(Property(o));
			}
		}
	}
};

openddl::Tree openddl::Tree::parse(const std::string & i)
{
	Tree::Impl * impl = new Tree::Impl();
	std::vector<detail::Token> tokens;
	std::vector<detail::Error> errors;
	if (!detail::lex(i, tokens, errors))
	{
		throw LexerError(errors);
	}
	else if (!detail::parse(tokens, impl->commands, errors))
	{
		throw ParseError(errors);
	}
	else if (!detail::semantic_check(impl->commands, errors, impl->global_names, impl->local_names))
	{
		throw SemanticError(errors);
	}

	//Build the child table to avoid walking the table whenever running visitors across the data
	for (unsigned int i = 0; i < impl->commands.size(); i++)
	{
		auto it = impl->child_table.find(impl->commands[i].parent);
		if (it == impl->child_table.end())
			it = impl->child_table.emplace(impl->commands[i].parent,std::vector<unsigned int>()).first;
		it->second.push_back(i);
	}
	Tree t; t.implementation.reset(impl);
	return std::move(t);
}

openddl::Tree::Tree() {}

openddl::Tree::Tree(Tree&&t)
{
	implementation = std::move(t.implementation);
}

void openddl::Tree::visit_children(Visitor & visitor)
{
	implementation->visit_children(visitor, 0, this);
}

void openddl::Structure::visit_children(Visitor & visitor)
{
	this->tree->implementation->visit_children(visitor, this->index+1, this->tree);
}
void openddl::Structure::visit_properties(std::function<void(const Property&)> visitor)
{
	tree->implementation->visit_properties(visitor, index + 1, tree);
}
bool openddl::Structure::has_name()
{
	return this->tree->implementation->commands[this->index].payload.structure_.name != nullptr;
}
const std::string & openddl::Structure::name()
{
	if(tree->implementation->commands[this->index].payload.structure_.name != nullptr)
		return *this->tree->implementation->commands[this->index].payload.structure_.name;
	else throw std::invalid_argument("Structure does not have a name");
}
const std::string & openddl::Structure::identifier()
{
	return *this->tree->implementation->commands[this->index].payload.structure_.identifier;

}


