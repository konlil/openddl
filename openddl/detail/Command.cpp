#include "Command.h"

openddl::detail::Command::Command(LiteralPayload & lit, unsigned int p, unsigned int d)
: Command(kLiteral,p,d)
{
	payload.literal_ = lit;
}
openddl::detail::Command::Command(StructurePayload & s, unsigned int p, unsigned int d)
: Command(kStructure, p, d)
{
	payload.structure_ = s;
}
openddl::detail::Command::Command(DataListPayload & list, unsigned int p, unsigned int d)
: Command(kDataList, p, d)
{
	payload.list_ = list;
}
openddl::detail::Command::Command(DataArrayPayload & a, unsigned int p, unsigned int d)
: Command(kDataArray, p, d)
{
	payload.array_ = a;
}
openddl::detail::Command::Command(ArrayElementPayload & e, unsigned int p, unsigned int d)
: Command(kArrayElement, p, d)
{
	payload.element_ = e;
}
openddl::detail::Command::Command(PropertyPayload & prop, unsigned int p, unsigned int d)
: Command(kProperty, p, d)
{
	payload.property_ = prop;
}
openddl::detail::Command::Command(Type t, unsigned int p, unsigned int d)
: type(t), parent(p), depth(d) 
{
}

openddl::detail::Command::Command(Command && rhs)
{
	//Used to fix union deletion bug in Release.
	memset(&payload, 0, sizeof(payload));
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
		delete literal.value.reference_;
		literal.value.reference_ = nullptr;
		break;
	case Command::LiteralPayload::kString:
		delete literal.value.string_;
		literal.value.string_ = nullptr;
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
		delete property.value.reference_;
		property.value.reference_ = nullptr;
		break;
	case Command::PropertyPayload::kString:
		delete property.value.string_;
		property.value.string_ = nullptr;
		break;
	case Command::PropertyPayload::kBinary:
	case Command::PropertyPayload::kCharacter:
	case Command::PropertyPayload::kHex:
	case Command::PropertyPayload::kFloat:
	case Command::PropertyPayload::kDecimal:
		delete property.value.numeric_;
		property.value.numeric_ = nullptr;
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
	if(type == Command::kLiteral)
		destroy(payload.literal_); 
	else if(type == Command::kDataArray)
		destroy(payload.array_); 
	else if(type == Command::kDataList)
		destroy(payload.list_); 
	else if (type == Command::kProperty)
		destroy(payload.property_); 
	else if (type == Command::kStructure)
		destroy(payload.structure_); 

}


