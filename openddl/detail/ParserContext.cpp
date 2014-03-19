#include "ParserContext.h"
#include "LiteralHelpers.h"
#include <cstdint>



bool encoding_mismatch(openddl::Type type, openddl::detail::Command::LiteralPayload::encoding_t encoding)
{
	using openddl::detail::Command;
	using openddl::Type;
	switch (type)
	{
	case Type::kInt8:
	case Type::kInt16:
	case Type::kInt32:
	case Type::kInt64:
	case Type::kUnsignedInt8:
	case Type::kUnsignedInt16:
	case Type::kUnsignedInt32:
	case Type::kUnsignedInt64:
		if (encoding == Command::LiteralPayload::kInteger) return false; else return true;
	case Type::kBool:
		if (encoding == Command::LiteralPayload::kBoolean) return false; else return true;
	case Type::kDouble:
	case Type::kFloat:
		if (encoding == Command::LiteralPayload::kFloat) return false; else return true;
	case Type::kRef:
		if (encoding == Command::LiteralPayload::kReference) return false; else return true;
	case Type::kString:
		if (encoding == Command::LiteralPayload::kString) return false; else return true;
	case Type::kType:
		if (encoding == Command::LiteralPayload::kType) return false; else return true;
	default:
		return true;
	}
}
openddl::detail::Command::LiteralPayload::encoding_t get_encoding(openddl::Type type)
{
	using namespace openddl;
	using openddl::detail::Command;
	switch (type)
	{
	case Type::kInt8:
	case Type::kInt16:
	case Type::kInt32:
	case Type::kInt64:
	case Type::kUnsignedInt8:
	case Type::kUnsignedInt16:
	case Type::kUnsignedInt32:
	case Type::kUnsignedInt64:
		return Command::LiteralPayload::kInteger;
	case Type::kDouble:
	case Type::kFloat:
		return Command::LiteralPayload::kFloat;
	case Type::kBool:
		return Command::LiteralPayload::kBoolean;
	case Type::kRef:
		return Command::LiteralPayload::kReference;
	case Type::kString:
		return Command::LiteralPayload::kString;
	case Type::kType:
		return Command::LiteralPayload::kType;
	}
}

openddl::detail::ParserContext::ParserContext(const std::vector<Token> & tokens, std::vector<Command> & commands, std::vector<Error> & errors)
: tokens(tokens), commands(commands), errors(errors)
{
}

int openddl::detail::ParserContext::build_literal(Command::LiteralPayload::encoding_t encoding, Token const * ts, Token const * te, Command::LiteralPayload & payload)
{
	payload.encoding = encoding;
	
	if (encoding == Command::LiteralPayload::kReference)
	{
		Token const * i = ts;
		std::vector<std::string> * reference = new std::vector<std::string>();
		while (i <= te && (i->token_type == Token::kNull || i->token_type == Token::kGlobalName || i->token_type == Token::kLocalName))
		{
			reference->emplace_back(i->payload);
			i++;
		}
		payload.value.reference_ = reference;
		return i - ts;
	}
	else
	{
		Type type;
		Command * parent = &commands[parents.back()];
		if (parent->type == Command::kDataList)
			type = parent->payload.list_.type;
		else if (parent->type == Command::kArrayElement)
		{
			type = commands[parent->parent].payload.array_.type;
		}
		int code = 0;
		if ((code=decode_literal(*ts, payload))!=0)
		{
			Error e;
			
			switch (code)
			{
			case 1:
				e.message = "parse.literal.out_of_range";
				break;
			case -1:
				e.message = "semantic.literal.type_mismatch";
				break;
			}
			
			e.payload = ts->payload;
			errors.push_back(e);
		}
		else if ((code = detect_limits(type, payload)) != 0)
		{
			Error e;

			switch (code)
			{
			case 1:
				e.message = "semantic.literal.overflow";
				break;
			case -1:
				e.message = "semantic.literal.underflow";
				break;
			}

			e.payload = ts->payload;
			errors.push_back(e);
		}
		return 1;
	}
}
void openddl::detail::ParserContext::push_list_type(Token const * type, Token const * name)
{
	Command c;
	c.type = Command::kDataList;
	c.payload.list_.type = convert(*type);
	if (parents.empty())
		c.parent = -1;
	else
	{
		c.parent = parents.back();
		if (commands[parents.back()].type == Command::kStructure)
			commands[parents.back()].payload.structure_.children++;
	}
	if (name)
		c.payload.list_.name = new std::string(name->payload);
	commands.push_back(c);
	parents.push_back(commands.size()-1);
}

void openddl::detail::ParserContext::push_literal_list(Command::LiteralPayload::encoding_t encoding, Token const * ts, Token const * te)
{
	Command::LiteralPayload::encoding_t type_encoding;
	if (commands.back().type == Command::kDataList)
		type_encoding = get_encoding(commands.back().payload.list_.type);
	else
		type_encoding = get_encoding(commands[commands[parents.back()].parent].payload.array_.type);
	if (type_encoding == Command::LiteralPayload::kInteger && encoding == Command::LiteralPayload::kFloat)
	{
		encoding = type_encoding;
	}
	else if (type_encoding == Command::LiteralPayload::kFloat && encoding == Command::LiteralPayload::kInteger)
	{
		encoding = type_encoding;
	}
	Command c;
	c.type = Command::kLiteral;
	c.parent = commands.size() - 1;
	Command::LiteralPayload payload;

	Token const * i = ts + 1;
	while (i < te - 1)
	{
		i += build_literal(encoding, i, te - 1, payload) + 1;
		c.payload.literal_ = payload;
		commands.push_back(c);
	}

	{
		//Set parent lengths
		Command * parent = &commands[parents.back()];
		if (parent->type == Command::kDataList)
			parent->payload.list_.length = &commands.back() - parent;
		else if (parent->type == Command::kArrayElement)
			parent->payload.element_.length = &commands.back() - parent;
	}
	

	if (type_encoding != encoding)
	{
		Error e;
		e.message = "semantic.literal.type_mismatch";
		errors.push_back(e);
	}
	
	parents.pop_back();

}

void openddl::detail::ParserContext::push_array_type(Token const * type, Token const * dimensions, Token const * name)
{
	Command c;
	c.type = Command::kDataArray;
	c.payload.array_.type = convert(*type);
	c.payload.array_.length = 0;
	if (parents.empty())
		c.parent = -1;
	else
	{
		c.parent = &commands[parents.back()] - commands.data();
		if (commands[parents.back()].type == Command::kStructure)
			commands[parents.back()].payload.structure_.children++;
	}
		
	if (name != nullptr)
		c.payload.array_.name = new std::string(name->payload);
	else
		name = nullptr;
	Command::LiteralPayload dimension_size;
	dimension_size.encoding = Command::LiteralPayload::kInteger;
	int a = 0, b=0;
	if ((a=decode_literal(*dimensions, dimension_size))!=0 && (b = detect_limits(Type::kUnsignedInt32, dimension_size)) != 0)
	{
		Error e;
		
		if (b == -1)
			e.message = "semantic.array.size_negative";
		else
			e.message = "semantic.array.size_invalid";
		e.payload = dimensions->payload;
		errors.push_back(e);
		c.payload.array_.dimension = 0;
	}
	else
	{
		if (dimension_size.value.integer_.value == 0)
		{
			Error e;
			e.message = "semantic.array.size_zero";
			errors.push_back(e);
		}
			
		c.payload.array_.dimension = (uint32_t)dimension_size.value.integer_.value;
	}
	commands.push_back(c);
	parents.push_back(commands.size() - 1);
	
}

void openddl::detail::ParserContext::push_array_element()
{
	Command & parent = commands[parents.back()];
	Command c;
	c.type = Command::kArrayElement;
	c.parent = parents.back();
	c.payload.element_.subindex = parent.payload.array_.length;
	parent.payload.array_.length++;
	c.payload.element_.length = 0;
	commands.push_back(c);
	parents.push_back(commands.size() - 1);
}

void openddl::detail::ParserContext::end_array()
{
	Command * c = &commands[parents.back()];
	int count = c->payload.array_.length;
	int size = c->payload.array_.dimension;
	
	//Check to ensure all sub arrays in list are of specified size;
	//Don't bother if size == 0 as this case has already been handled
	if (size != 0)
	{
		c += 1;
		for (int i = 0; i < count; i++)
		{
			if (c->payload.element_.length != size)
			{
				Error e;
				e.message = "semantic.array.size_mismatch";
				errors.push_back(e);
				break;
			}
			c += c->payload.element_.length+1;
		}		
	}
	parents.pop_back();
}

void openddl::detail::ParserContext::push_structure(Token const * identifier, Token const * name)
{
	Command c;
	c.type = Command::kStructure;
	if (parents.empty())
		c.parent = -1;
	else
	{
		c.parent = parents.back();
		if (commands[parents.back()].type == Command::kStructure)
			commands[parents.back()].payload.structure_.children++;
	}
		
	c.payload.structure_.identifier = new std::string(identifier->payload);
	if (name != nullptr)
		c.payload.structure_.name = new std::string(name->payload);
	else
		c.payload.structure_.name = nullptr;
	c.payload.structure_.properties = 0;
	c.payload.structure_.children = 0;
	commands.push_back(c);
	parents.push_back(commands.size() - 1);
}
void openddl::detail::ParserContext::push_property(Token const *ts, Token const * te)
{
	Command c;
	c.type = Command::kProperty;
	c.parent = parents.back();
	c.payload.property_.identifier = new std::string(ts->payload);
	Token const *value = ts + 1;
	switch (value->token_type)
	{
	case Token::kBinaryLiteral:
		c.payload.property_.encoding = Command::PropertyPayload::kBinary; 
		c.payload.property_.value.numeric_ = new std::string(value->payload);
		break;
	case Token::kHexLiteral:
		c.payload.property_.encoding = Command::PropertyPayload::kHex; 
		c.payload.property_.value.numeric_ = new std::string(value->payload);
		break;
	case Token::kCharacterLiteral:
		c.payload.property_.encoding = Command::PropertyPayload::kCharacter; 
		c.payload.property_.value.numeric_ = new std::string(value->payload);
		break;
	case Token::kDecimalLiteral:
		c.payload.property_.encoding = Command::PropertyPayload::kDecimal; 
		c.payload.property_.value.numeric_ = new std::string(value->payload);
		break;
	case Token::kFloatLiteral:
		c.payload.property_.encoding = Command::PropertyPayload::kFloat; 
		c.payload.property_.value.numeric_ = new std::string(value->payload);
		break;
	case Token::kStringLiteral:
		c.payload.property_.encoding = Command::PropertyPayload::kString;
		c.payload.property_.value.string_ = new std::string(value->payload);
		break;
	case Token::kBooleanLiteral:
		c.payload.property_.encoding = Command::PropertyPayload::kBool;
		c.payload.property_.value.boolean_ = "true" ? true : false;
		break;
	case Token::kType:
		c.payload.property_.encoding = Command::PropertyPayload::kDataType;
		c.payload.property_.value.type_ = convert(*value);
		break;
	
	case Token::kNull:
	case Token::kGlobalName:
	case Token::kLocalName:
		c.payload.property_.encoding = Command::PropertyPayload::kReference;
		std::vector<std::string> * reference = new std::vector<std::string>();
		for (Token const * i = value; i <= te; i++)
			reference->emplace_back(i->payload);
		c.payload.property_.value.reference_ = reference;
		break;
	}
	commands[parents.back()].payload.structure_.properties++;
	commands.push_back(c);
}
void openddl::detail::ParserContext::end_structure()
{
	parents.pop_back();
}
