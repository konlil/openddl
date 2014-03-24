#include "detail.h"
#include "Error.h"
#include "Command.h"
#include "../Type.h"
#include "LiteralHelpers.h"
#include <iostream>
using namespace openddl::detail;
struct Context
{
	Command * start;
	std::vector<Error> & errors; 
	std::map<std::string, unsigned int> & global_names;
	std::map<unsigned int, std::map<std::string, unsigned int> > & local_names;
	std::map<std::string, unsigned int> structure_properties;
	Context(Command * s, std::vector<Error> & e, std::map<std::string, unsigned int> & g, std::map<unsigned int, std::map<std::string, unsigned int> > & l)
		: start(s), errors(e), global_names(g), local_names(l) {}
	
	void push_name(const std::string & name, unsigned int index, unsigned int parent)
	{
		if (name[0] == '$') //Global name
		{
			if (global_names.find(name) == global_names.end())
				global_names.emplace(name, index);
			else
				push_error("semantic.global_name_clash");
		}
		else if (name[0] == '%') //Local name
		{
			auto parent_map = local_names.find(parent);
			//Create parent index mapping if it does not exist
			if (parent_map == local_names.end())
				parent_map = local_names.emplace(parent, std::map < std::string, unsigned int>()).first;
			auto & name_map = parent_map->second;
			if (name_map.find(name) == name_map.end())
				name_map.emplace(name, index);
			else
				push_error("semantic.local_name_clash");
		}
	}
	void push_error(const std::string & msg)
	{
		Error e;
		e.message = msg;
		errors.push_back(e);
	}

	void validate_literal(openddl::Type type,Command * object)
	{
		if (object->type == Command::kLiteral)
		{
			if (encoding_mismatch(type, object->payload.literal_.encoding))
				push_error("semantic.literal.type_mismatch");
			else
			{
				int code = detect_limits(type, object->payload.literal_);
				if (code == -1)
					push_error("semantic.literal.underflow");
				else if (code == 1)
					push_error("semantic.literal.overflow");
			}
		}
		else
			push_error("semantic.internal_error.validate_literal");
	}
	void validate_literal_list(openddl::Type type, Command * object, unsigned int length)
	{
		for (unsigned int i = 0; i < length; i++)
		{
			validate_literal(type, object + i);
		}
	}
	unsigned int validate_data_list(Command * object)
	{
		openddl::Type type = object->payload.list_.type;
		unsigned int length = object->payload.list_.length;
		if (object->payload.list_.name)
			push_name(*object->payload.list_.name, object - start,object->parent);
		validate_literal_list(type, object + 1, length);
		return length;
	}
	unsigned int validate_data_array(Command * object)
	{
		openddl::Type type = object->payload.array_.type;
		unsigned int length = object->payload.array_.length;
		unsigned int dimension = object->payload.array_.dimension;
		if (object->payload.array_.name)
			push_name(*object->payload.array_.name, object - start,object->parent);
		if (dimension == 0)
			push_error("semantic.array.zero_dimension");

		Command * header = object + 1;
		for (unsigned int i = 0; i < length; i++)
		{
			unsigned int sub_index = header->payload.element_.subindex;
			unsigned int sub_length = header->payload.element_.length;
			if (dimension != 0 && sub_length != dimension)
				push_error("semantic.array.dimension_mismatch");
			validate_literal_list(type,header+1, sub_length);
			header += sub_length+1;
		}
		return header - object-1;

	}
	bool validate_property(Command * object, unsigned int index)
	{
		const std::string & identifier = *object->payload.property_.identifier;
		if (structure_properties.find(identifier) != structure_properties.end())
			return false;
		structure_properties.emplace(identifier, index);
		return true;
		
	}
	unsigned int validate_structure(Command * object)
	{
		unsigned int properties = object->payload.structure_.properties;
		if (object->payload.structure_.name)
			push_name(*object->payload.structure_.name, object - start,object->parent);
		Command * prop = object + 1;
		for (unsigned int i = 0; i < properties; i++)
		{
			if (!validate_property(prop + i, i))
				push_error("semantic.structure.property.name_clash");
		}
		structure_properties.clear();
		return properties;
	}

};

bool openddl::detail::semantic_check(std::vector<Command> & commands, std::vector<Error> & errors, std::map<std::string, unsigned int> & global_names, std::map<unsigned int, std::map<std::string, unsigned int> > & local_names)
{
	Context context(commands.data(),errors, global_names, local_names);
	Command * te = commands.data() + commands.size();
	for (Command * ts = commands.data(); ts < te; ts++)
	{
		switch (ts->type)
		{
		case Command::kStructure:
			ts += context.validate_structure(ts);
			break;
		case Command::kDataArray:
			ts += context.validate_data_array(ts);
			break;
		case Command::kDataList:
			ts += context.validate_data_list(ts);
			break;
		}
	}
	return errors.size() == 0;
}