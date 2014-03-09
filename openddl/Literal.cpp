//================================================================================================================
// Copyright 2014 Denis Hilliard (armchaircommando@gmail.com)
// Licensed under MIT License
//================================================================================================================

#include "Literal.h"

openddl::Literal::Literal()
: type(kNone)
{

}
openddl::Literal::~Literal()
{

	switch (type)
	{
	case kString:
		delete u_.s_value; u_.s_value = nullptr; break;
	}
	
}

openddl::Literal::Literal(Literal && l) : type(l.type)
{
	switch (l.type)
	{
	case kString:
		u_.s_value = l.u_.s_value;  l.u_.s_value = nullptr; break;
	case kBoolean:
		u_.b_value = l.u_.b_value; break;
	}
}
openddl::Literal openddl::Literal::construct(std::vector<Token> & tokens, int & position, type_t type_hint)
{
	Literal l;
	switch (type_hint)
	{
	case kBoolean:
		if (tokens[position].literal_type == Token::kBooleanLiteral)
		{
			l.type = type_hint;
			if (tokens[position].payload == "true")
				l.u_.b_value = true;
			else
				l.u_.b_value = false;
			position++;
		}
		else
			type_error("Type mismatch constructing literal");
		break;
	case kString:
		if (tokens[position].literal_type == Token::kStringLiteral)
		{
			l.type = type_hint;
			l.u_.s_value = new std::string(tokens[position].payload);
			position++;
		}
		else
			type_error("Type mismatch constructing literal");
		break;
	}
	return l;
}


