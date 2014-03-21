#include "Command.h"

openddl::detail::Command::Command(LiteralPayload & lit, int p, unsigned int d)
: Command(kLiteral,p,d)
{
	payload.literal_ = lit;
}
openddl::detail::Command::Command(StructurePayload & s, int p, unsigned int d)
: Command(kStructure, p, d)
{
	payload.structure_ = s;
}
openddl::detail::Command::Command(DataListPayload & list, int p, unsigned int d)
: Command(kDataList, p, d)
{
	payload.list_ = list;
}
openddl::detail::Command::Command(DataArrayPayload & a, int p, unsigned int d)
: Command(kDataArray, p, d)
{
	payload.array_ = a;
}
openddl::detail::Command::Command(ArrayElementPayload & e, int p, unsigned int d)
: Command(kArrayElement, p, d)
{
	payload.element_ = e;
}
openddl::detail::Command::Command(PropertyPayload & prop, int p, unsigned int d)
: Command(kProperty, p, d)
{
	payload.property_ = prop;
}
openddl::detail::Command::Command(Type t, int p, unsigned int d)
: type(t), parent(p), depth(d) 
{
}

openddl::detail::Command::Command(Command && rhs)
{
	std::swap(type, rhs.type);
	std::swap(depth, rhs.depth);
	std::swap(parent, rhs.parent);
	std::swap(payload, rhs.payload);
}

//Internal helper functions for freeing memory used by payloads
void destroy(openddl::detail::Command::LiteralPayload & literal)
{
	using openddl::detail::Command;
	switch (literal.encoding)
	{
	case Command::LiteralPayload::kReference:
		literal.value.reference_->~vector();
		break;
	case Command::LiteralPayload::kString:
		literal.value.string_->~basic_string();
		break;
	}
}
void destroy(openddl::detail::Command::DataListPayload & list){
	delete list.name;
	list.name = nullptr;
}
void destroy(openddl::detail::Command::DataArrayPayload & array){
	delete array.name;
	array.name = nullptr;
}
void destroy(openddl::detail::Command::PropertyPayload & property){
	using openddl::detail::Command;
	delete property.identifier;
	property.identifier = nullptr;
	switch (property.encoding)
	{
	case Command::PropertyPayload::kReference:
		property.value.reference_->~vector();
		break;
	case Command::PropertyPayload::kString:
		property.value.string_->~basic_string();
		break;
	case Command::PropertyPayload::kBinary:
	case Command::PropertyPayload::kCharacter:
	case Command::PropertyPayload::kHex:
	case Command::PropertyPayload::kFloat:
	case Command::PropertyPayload::kDecimal:
		property.value.numeric_->~basic_string();
		break;
	}
}
void destroy(openddl::detail::Command::StructurePayload & structure){
	delete structure.name;
	structure.name = nullptr;
	delete structure.identifier;
	structure.name = nullptr;
}


openddl::detail::Command::~Command()
{
	switch (type)
	{
	case Command::kLiteral:
		destroy(payload.literal_); 
		break;
	case Command::kDataArray:
		destroy(payload.array_); 
		break;
	case Command::kDataList:
		destroy(payload.list_); 
		break;
	case Command::kProperty:
		destroy(payload.property_); 
		break;
	case Command::kStructure:
		destroy(payload.structure_); 
		break;
	}
}


