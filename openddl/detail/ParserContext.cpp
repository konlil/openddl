#include "ParserContext.h"
#include "LiteralHelpers.h"
#include "../Type.h"
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

void openddl::detail::ParserContext::push_error(const std::string & message)
{
	Error e;
	e.message = std::move(message);
	errors.push_back(e);
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
		int code;
		if ((code=decode_literal(*ts, payload))!=0)
		{		
			if(code == 1)
				push_error("parse.literal.out_of_range");
			else if (code == -1)
				push_error("parse.literal.type_mismatch"); 
		}
		return 1;
	}
}
void openddl::detail::ParserContext::push_list_type(Token const * type, Token const * name)
{

	unsigned int depth = parents.size();
	int parent;
	Command::DataListPayload list;
	list.type = convert(*type);

	if (parents.empty())
		parent = -1;
	else
	{
		parent = parents.back();
		if (commands[parents.back()].type == Command::kStructure)
			commands[parents.back()].payload.structure_.children++;
	}
	if (name)
		list.name = new std::string(name->payload);
	else
		list.name = nullptr;

	commands.emplace_back(list,parent,depth);

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

	int parent = commands.size() - 1;
	unsigned int depth = parents.size();
	Command::LiteralPayload payload;

	Token const * i = ts + 1;
	while (i < te - 1)
	{
		i += build_literal(encoding, i, te - 1, payload) + 1;
		commands.emplace_back(payload,parent,depth);
		
	}

	{
		//Set parent lengths
		Command * parent = &commands[parents.back()];
		if (parent->type == Command::kDataList)
			parent->payload.list_.length = &commands.back() - parent;
		else if (parent->type == Command::kArrayElement)
			parent->payload.element_.length = &commands.back() - parent;
	}
	
	parents.pop_back();

}

void openddl::detail::ParserContext::push_array_type(Token const * type, Token const * dimensions, Token const * name)
{

	unsigned int depth = parents.size();
	int parent;
	Command::DataArrayPayload payload;
	payload.type = convert(*type);
	payload.length = 0;
	if (parents.empty())
		parent = -1;
	else
	{
		parent = &commands[parents.back()] - commands.data();
		if (commands[parents.back()].type == Command::kStructure)
			commands[parents.back()].payload.structure_.children++;
	}
		
	if (name != nullptr)
		payload.name = new std::string(name->payload);
	else
		payload.name = nullptr;
	Command::LiteralPayload dimension_size;
	dimension_size.encoding = Command::LiteralPayload::kInteger;

	if (decode_literal(*dimensions, dimension_size) != 0 )
	{

		push_error("parse.array.index.decode_error");

		payload.dimension = 0;
	}
	else
	{
			
		payload.dimension = (uint32_t)dimension_size.value.integer_.value;
	}
	commands.emplace_back(payload, parent, depth);
	parents.push_back(commands.size() - 1);
	
	
}

void openddl::detail::ParserContext::push_array_element()
{
	Command & array = commands[parents.back()];
	unsigned int depth = parents.size();
	int parent = parents.back();

	Command::ArrayElementPayload payload;
	payload.subindex = array.payload.array_.length;
	array.payload.array_.length++;
	payload.length = 0;
	commands.emplace_back(payload, parent, depth);
	parents.push_back(commands.size() - 1);
}

void openddl::detail::ParserContext::end_array()
{
	parents.pop_back();
}

void openddl::detail::ParserContext::push_structure(Token const * identifier, Token const * name)
{
	unsigned int depth = parents.size();
	int parent;
	if (parents.empty())
		parent = -1;
	else
	{
		parent = parents.back();
		if (commands[parents.back()].type == Command::kStructure)
			commands[parents.back()].payload.structure_.children++;
	}
		
	Command::StructurePayload payload;
	payload.identifier = new std::string(identifier->payload);
	if (name != nullptr)
		payload.name = new std::string(name->payload);
	else
		payload.name = nullptr;
	payload.properties = 0;
	payload.children = 0;
	commands.emplace_back(payload, parent, depth);
	parents.push_back(commands.size() - 1);
	
}
void openddl::detail::ParserContext::push_property(Token const *ts, Token const * te)
{
	int parent = parents.back();
	int depth = parents.size();
	Command::PropertyPayload payload;
	payload.identifier = new std::string(ts->payload);
	Token const *value = ts + 1;
	switch (value->token_type)
	{
	case Token::kBinaryLiteral:
		payload.encoding = Command::PropertyPayload::kBinary; 
		payload.value.numeric_ = new std::string(value->payload);
		break;
	case Token::kHexLiteral:
		payload.encoding = Command::PropertyPayload::kHex; 
		payload.value.numeric_ = new std::string(value->payload);
		break;
	case Token::kCharacterLiteral:
		payload.encoding = Command::PropertyPayload::kCharacter; 
		payload.value.numeric_ = new std::string(value->payload);
		break;
	case Token::kDecimalLiteral:
		payload.encoding = Command::PropertyPayload::kDecimal; 
		payload.value.numeric_ = new std::string(value->payload);
		break;
	case Token::kFloatLiteral:
		payload.encoding = Command::PropertyPayload::kFloat; 
		payload.value.numeric_ = new std::string(value->payload);
		break;
	case Token::kStringLiteral:
		payload.encoding = Command::PropertyPayload::kString;
		payload.value.string_ = new std::string(value->payload);
		break;
	case Token::kBooleanLiteral:
		payload.encoding = Command::PropertyPayload::kBool;
		payload.value.boolean_ = "true" ? true : false;
		break;
	case Token::kType:
		payload.encoding = Command::PropertyPayload::kDataType;
		payload.value.type_ = convert(*value);
		break;
	
	case Token::kNull:
	case Token::kGlobalName:
	case Token::kLocalName:
		payload.encoding = Command::PropertyPayload::kReference;
		std::vector<std::string> * reference = new std::vector<std::string>();
		for (Token const * i = value; i <= te; i++)
			reference->emplace_back(i->payload);
		payload.value.reference_ = reference;
		break;
	}
	commands[parents.back()].payload.structure_.properties++;
	commands.emplace_back(payload, parent, depth);
}
void openddl::detail::ParserContext::end_structure()
{
	parents.pop_back();
}
