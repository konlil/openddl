//================================================================================================================
// Copyright 2014 Denis Hilliard (armchaircommando@gmail.com)
// Licensed under MIT License
//================================================================================================================

#include "Literal.h"
#include <string>
#include "Lexer.h"

char consume_character(const std::string & in, int & position)
{
	char value = 0;
	if (in[position] == '\\')
	{
		switch (in[position + 1])
		{
		case '"':
			value = '"'; position += 2; break;
		case '\'':
			value = '\''; position += 2; break;
		case '?':
			value = '?'; position += 2; break;
		case '\\':
			value = '\\'; position += 2; break;
		case 'a':
			value = '\a'; position += 2; break;
		case 'b':
			value = '\b'; position += 2; break;
		case 'f':
			value = '\f'; position += 2; break;
		case 'n':
			value = '\n'; position += 2; break;
		case 't':
			value = '\t'; position += 2; break;
		case 'v':
			value = '\v'; position += 2; break;
		case 'x':
			value = std::stoi(in.substr(position + 2, 2), nullptr, 16);
			position += 4;
			break;
		}
	}
	else
	{
		value = in[position]; position += 1;
	}
	return value;
}
uint64_t decode_integer(openddl::Token::token_t type,const std::string & in, bool & negate)
{
	uint64_t value = 0;
	negate = false;
	int offset = 0;
	switch (in[0])
	{
	case '-':
		negate = true;
		offset++;
		break;
	case '+':
		offset++;
		break;
	}
	switch (type)
	{
	case openddl::Token::kCharacterLiteral:
	{
		int position = 0;
		std::string characters = in.substr(1, in.length() - 2);
		for (int i = 0; i < 7; i++)
		{
			value = (value << 8) + consume_character(characters, position);
			if (position == characters.length())
				break;
		}
		break;
	}
	case openddl::Token::kDecimalLiteral:
		value = std::stoull(in.substr(offset),nullptr,10);
		break;
	case openddl::Token::kBinaryLiteral:
		value = std::stoull(in.substr(offset+2), nullptr, 2);
		break;
	case openddl::Token::kHexLiteral:
		value = std::stoull(in.substr(offset + 2), nullptr, 16);
		break;
	}
	return value;
}

openddl::Literal::Literal()
: type(kNone), negate(false)
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

openddl::Literal::Literal(Literal && l) : type(l.type), negate(l.negate), lexical_encoding(l.lexical_encoding)
{
	switch (l.type)
	{
	case kString:
		u_.s_value = l.u_.s_value;  l.u_.s_value = nullptr; break;
	case kBoolean:
		u_.b_value = l.u_.b_value; break;
	case kInteger:
		u_.i_value = l.u_.i_value; break;
	case kFloat:
		u_.d_value = l.u_.d_value; break;
	}
}
openddl::Literal openddl::Literal::construct(const Token & token, type_t type_hint)
{
	Literal l;
	switch (type_hint)
	{
	case kBoolean:
		if (token.token_type == Token::kBooleanLiteral)
		{
			l.type = type_hint;
			if (token.payload == "true")
				l.u_.b_value = true;
			else
				l.u_.b_value = false;
		}
		else
			type_error("Encoding mismatch constructing boolean literal");
		break;
	case kString:
		if (token.token_type == Token::kStringLiteral)
		{
			l.type = type_hint;
			l.u_.s_value = new std::string(token.payload);
		}
		else
			type_error("Encoding mismatch constructing string literal");
		break;
	case kInteger:
		if (token.is_integer_encoded())
		{
			l.type = type_hint;
			l.u_.i_value = decode_integer(token.token_type,token.payload,l.negate);
		}
		else
			type_error("Encoding mismatch constructing integer literal");
		break;
	case kFloat:
		if (token.is_float_encoded())
		{
			l.type = type_hint;
			switch (token.token_type)
			{
			case Token::kBinaryLiteral:
			case Token::kHexLiteral:
				l.u_.i_value = decode_integer(token.token_type, token.payload, l.negate);
				l.lexical_encoding = false;
				break;
			case Token::kDecimalLiteral:
			case Token::kFloatLiteral:
				l.lexical_encoding = true;
				l.u_.d_value = std::stod(token.payload);
				break;

			}
		}
		else
			type_error("Encoding mismatch constructing float literal");
		break;
		
	}
	return std::move(l);
}


