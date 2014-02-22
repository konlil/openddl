//================================================================================================================
// Copyright 2014 Denis Hilliard (armchaircommando@gmail.com)
// Licensed under MIT License
//================================================================================================================
#include "stdafx.h"
#include "openddl.h"


//================================================================================================================
// Internal common functionality for decoding literals.
//================================================================================================================
//Internal function used to consume individual/aggregate characters out of a token
char consume_character(const std::string & token, unsigned int & index, const unsigned int length)
{
	char value = 0;
	if (token[index] == '\\'){
		if ((length - index) >= 2)
		{
			switch (token[index + 1])
			{
			case '"':
				value = '"'; index += 2; break;
			case '\'':
				value = '\''; index += 2; break;
			case '?':
				value = '?'; index += 2; break;
			case '\\':
				value = '\\'; index += 2; break;
			case 'a':
				value = '\a'; index += 2; break;
			case 'b':
				value = '\b'; index += 2; break;
			case 'f':
				value = '\f'; index += 2; break;
			case 'n':
				value = '\n'; index += 2; break;
			case 't':
				value = '\t'; index += 2; break;
			case 'v':
				value = '\v'; index += 2; break;
			case 'x':
				if ((length - index) >= 4)
				{
					size_t position = 0;
					value = std::stoi(token.substr(index + 2, 2), &position, 16);
					if (position != 2)
						throw openddl::exception("Invalid hex character literal");
					index += 4;
				}
				else
					throw openddl::exception("Insufficient characters to consume");
			}
		}
	}
	else if ((length - index) >= 1)
	{
		const char character = token[index];
		if ((character >= 0x20 && character < '\'') || (character > '\'' && character < 0x7F))
		{
			index += 1;
			return character;
		}
		else
			throw openddl::exception("Not a valid character literal");
	}
	return value;
}

struct literal_encoding
{
	bool negate;
	bool character;
	int number_base;
	int offset;
};
//Decode integer specific encoding details from token string
literal_encoding decode_literal(const std::string & token)
{
	literal_encoding lit;
	const int length = token.length();

	lit.number_base = 10;
	lit.offset = 0;
	lit.negate = false;
	lit.character = false;

	if (length > 1)
	{
		const char first_character = token[0];
		if (first_character == '-')
		{
			lit.negate = true;
			lit.offset += 1;
		}
		else if (first_character == '+')
			lit.offset += 1;

		char encoding_char = token[lit.offset];

		if (encoding_char == '\'')
			lit.character = true;
		else if (encoding_char == '0')
		{
			encoding_char = token[lit.offset + 1];
			lit.offset += 2;
			if (encoding_char == 'b' || encoding_char == 'B')
				lit.number_base = 2;
			else if (encoding_char == 'x' || encoding_char == 'X')
				lit.number_base = 16;
		}
	}
	return lit;
}

uint64_t decode_unsigned_integer(const std::string & token)
{
	const int length = token.length();
	auto lit = decode_literal(token);
	uint64_t value = 0;
	if (lit.negate)
		throw std::underflow_error("Unsigned literal may not be negative");
	if (lit.character)
		value = openddl::parse_character_literal(token, lit.offset);
	else
	{
		size_t position = 0;
		value = std::stoull(token.substr(lit.offset, length - lit.offset), &position, lit.number_base);
		if (position != (length - lit.offset))
			throw std::length_error("Invalid characters part of token");
	}
	return value;
}

int64_t decode_integer(const std::string & token)
{
	const int length = token.length();
	auto lit = decode_literal(token);
	int64_t value = 0;
	if (lit.character)
		value = openddl::parse_character_literal(token, lit.offset);
	else
	{
		size_t position = 0;
		value = std::stoll(token.substr(lit.offset, length - lit.offset), &position, lit.number_base);
		if (position != (length - lit.offset))
			throw std::length_error("Invalid characters part of token");
	}
	if (lit.negate)
		value *= -1;
	return value;
}

//================================================================================================================

std::string & openddl::format_utf8(std::string & out, char32_t token)
{
	if (token < 0x80)
	{
		out.push_back(token);
	}
	else if (token < 0x800)
	{
		out.push_back(0xC0 | (token >> 6) & 0x3F);
		out.push_back(0x80 | token & 0x3F);
	}
	else if (token < 0x10000)
	{
		out.push_back(0xE0 | (token >> 12) & 0x3F);
		out.push_back(0x80 | (token >> 6) & 0x3F);
		out.push_back(0x80 | token & 0x3F);
	}
	else if (token < 0x200000)
	{
		out.push_back(0xF0 | (token >> 18) & 0x3F);
		out.push_back(0x80 | (token >> 12) & 0x3F);
		out.push_back(0x80 | (token >> 6) & 0x3F);
		out.push_back(0x80 | token & 0x3F);
	}
	else throw openddl::exception("Unicode overflow");
	return out;

}
bool openddl::is_identifier(const std::string & token, const unsigned int index)
{
	const unsigned int length = token.length();
	if (index >= length)
		return false;
	char character = token[index];
	if ((character < 'A' || character > 'Z') && (character < 'a' || character > 'z') && character != '_')
		return false;
	for (unsigned int i = index + 1; i < length; i++)
	{
		character = token[i];
		if ((character < 'A' || character > 'Z') && (character < 'a' || character > 'z') && (character < '0' || character > '9') && character != '_')
			return false;
	}
	return true;
}

uint64_t openddl::parse_character_literal(const std::string & token, const unsigned int index)
{
	const unsigned int length = token.length();
	
	if (length > index + 2 && token[index] == '\'' && token[length - 1] == '\'')
	{
		uint64_t value = 0;
		unsigned int position = 1;
		//Iterate through string consuming (symbolic) characters up to a maximum of 8
		for (unsigned int i = 0; i < 8; i++)
		{
			value += consume_character(token, position, length - 1);
			if (position >= length - 1)
				break;
			value = value << 8;
		}
		//Ensure all characters have been consumed out of the input string
		if (position < length-1)
			throw exception("Not all characters have been consumed");
		return value;
	}
	throw exception("Not a valid character literal");
}

int openddl::read_escape_character(std::string & out, const std::string & token, const unsigned int index)
{
	switch (token[index])
	{
	case '"':
		out.append("\"");
		return 1;
	case '\'':
		out.append("\'");
		return 1;
	case '?':
		out.append("?");
		return 1;
	case '\\':
		out.append("\\");
		return 1;
	case 'a':
		out.append("\a");
		return 1;
	case 'b':
		out.append("\b");
		return 1;
	case 'f':
		out.append("\f");
		return 1;
	case 'n':
		out.append("\n");
		return 1;
	case 'r':
		out.append("\r");
		return 1;
	case 't':
		out.append("\t");
		return 1;
	case 'v':
		out.append("\v");
		return 1;
	case 'u':
	{
		if (index + 4 > token.length())
			throw openddl::exception(std::string("Encountered invalid unicode escape character token token '") + token + "' whilst parsing string structure");
		size_t position = 0;
		const char32_t code_point = std::stoi(token.substr(index + 1, 4), &position, 16);
		if (position != 4)
			throw openddl::exception(std::string("Encountered invalid unicode escape character token token '") + token + "' whilst parsing string structure");
		if (code_point < 0x0001 || code_point > 0x1FFFFF)
			throw openddl::exception(std::string("Encountered invalid unicode escape character token token '") + token + "' whilst parsing string structure");
		format_utf8(out, code_point);
		return 5;
	}
	case 'U':
	{
		if (index + 6 > token.length())
			throw openddl::exception(std::string("Encountered invalid unicode escape character token token '") + token + "' whilst parsing string structure");
		size_t position = 0;
		const char32_t code_point = std::stoi(token.substr(index + 1, 6), &position, 16);
		if (position != 6)
			throw openddl::exception(std::string("Encountered invalid unicode escape character token token '") + token + "' whilst parsing string structure");
		format_utf8(out, code_point);
		return 7;
	}
	default:
		throw openddl::exception(std::string("Encountered invalid unicode escape character token token '") + token + "' whilst parsing string structure");
	}
}
bool openddl::is_name(const std::string & token,const unsigned int index)
{
	const unsigned int length = token.length();
	if (index + 1 >= length) 
		return false;
	char first_character = token[index];
	if (first_character != '$' && first_character != '%') 
		return false;
	return is_identifier(token, index + 1);
}
bool openddl::is_local_name(const std::string & token, const unsigned int index)
{
	const unsigned int length = token.length();
	if (index + 1 >= length)
		return false;
	char first_character = token[index];
	if (first_character != '%')
		return false;
	return is_identifier(token, index + 1);
}

openddl::Type::enum_t openddl::parse_type(const std::string & token)
{
	static const char* type_identifiers[] = {
		"bool", "int8", "int16", "int32", "int64",
		"unsigned_int8", "unsigned_int16", "unsigned_int32", "unsigned_int64",
		"float", "double", "string", "ref", "type"
	};
	for (int i = 0; i < Type::enum_t::kCount; i++)
	{
		if (token == type_identifiers[i])
			return Type::enum_t(i);
	}
	throw openddl::exception("Invalid Type Identifier");
}

bool openddl::decode_boolean(const std::string & token)
{
	if (token == "true") return true;
	else if (token == "false") return false;
	else throw new exception("'" + token + "' is not a valid boolean literal");
}

uint8_t openddl::decode_unsigned_int8(const std::string & token)
{
	try
	{
		uint64_t value = decode_unsigned_integer(token);
		if (value > UINT8_MAX)
			throw std::overflow_error("Literal overflowed");
		return (uint8_t)value;
	}
	catch (...)
	{
		throw exception("'" + token + "' is not a valid 8-bit unsigned integer literal");
	}
}

uint16_t openddl::decode_unsigned_int16(const std::string & token)
{
	try
	{
		uint64_t value = decode_unsigned_integer(token);
		if (value > UINT16_MAX)
			throw std::overflow_error("Literal overflowed");
		return (uint16_t)value;
	}
	catch (...)
	{
		throw exception("'" + token + "' is not a valid 16-bit unsigned integer literal");
	}
}

uint32_t openddl::decode_unsigned_int32(const std::string & token)
{
	try
	{
		uint64_t value = decode_unsigned_integer(token);
		if (value > UINT32_MAX)
			throw std::overflow_error("Literal overflowed");
		return (uint32_t)value;
	}
	catch (...)
	{
		throw exception("'" + token + "' is not a valid 32-bit unsigned integer literal");
	}
}

uint64_t openddl::decode_unsigned_int64(const std::string & token)
{
	try
	{
		uint64_t value = decode_unsigned_integer(token);
		if (value > UINT64_MAX)
			throw std::overflow_error("Literal overflowed");
		return value;
	}
	catch (...)
	{
		throw exception("'" + token + "' is not a valid 64-bit unsigned integer literal");
	}
}

int8_t openddl::decode_int8(const std::string & token)
{
	try
	{
		int64_t value = decode_integer(token);
		if (value < INT8_MIN || value > INT8_MAX)
			throw std::overflow_error("Literal overflowed");
		return (int8_t)value;
	}
	catch (...)
	{
		throw exception("'" + token + "' is not a valid 8-bit integer literal");
	}
}

int16_t openddl::decode_int16(const std::string & token)
{
	try
	{
		int64_t value = decode_integer(token);
		if (value < INT16_MIN || value > INT16_MAX)
			throw std::overflow_error("Literal overflowed");
		return (int16_t)value;
	}
	catch (...)
	{
		throw exception("'" + token + "' is not a valid 16-bit integer literal");
	}
}

int32_t openddl::decode_int32(const std::string & token)
{
	try
	{
		int64_t value = decode_integer(token);
		if (value < INT32_MIN || value > INT32_MAX)
			throw std::overflow_error("Literal overflowed");
		return (int32_t)value;
	}
	catch (...)
	{
		throw exception("'" + token + "' is not a valid 32-bit integer literal");
	}

}

int64_t openddl::decode_int64(const std::string & token)
{
	try
	{
		int64_t value = decode_integer(token);
		if (value < INT64_MIN || value > INT64_MAX)
			throw std::overflow_error("Literal overflowed");
		return value;
	}
	catch (...)
	{
		throw exception("'" + token + "' is not a valid 64-bit integer literal");
	}
}

float openddl::decode_float(const std::string & token)
{
	try
	{
		bool negate = false;
		int index = 0;
		switch (token[0]){
		case '+':
			index += 1; break;
		case '-':
			index += 1; negate = true; break;
		}
		if (token[index] == '0')
		{
			uint32_t value = 0;
			size_t position = 0;
			switch (token[index + 1])
			{
			case 'x':
			case 'X':
				//Treat as hex literal
				index += 2;
				value = std::stoul(token.substr(index), &position, 16);
				break;
			case 'b':
			case 'B':
				//Treat as binary literal
				index += 2;
				value = std::stoul(token.substr(index), &position, 2);
				break;
			}
			if (position)
			{
				if ((position + index) < token.length())
					throw exception("Not all characters were consumed");
				return negate ? -*reinterpret_cast<float*>(&value) : *reinterpret_cast<float*>(&value);
			}
		}
		//Treat as stringified float literal
		size_t position = 0;
		float value = std::stof(token.substr(index), &position);
		if (position < token.length())
			throw exception("Not all characters were consumed");
		return negate ? -value : value;
	}
	catch (...)
	{
		throw exception("'" + token + "' is not a valid float literal");
	}

}

double openddl::decode_double(const std::string & token)
{
	try
	{
		bool negate = false;
		int index = 0;
		switch (token[0]){
		case '+':
			index += 1; break;
		case '-':
			index += 1; negate = true; break;
		}
		if (token[index] == '0')
		{
			uint64_t value = 0;
			size_t position = 0;
			switch (token[index + 1])
			{
			case 'x':
			case 'X':
				//Treat as hex literal
				index += 2;
				value = std::stoull(token.substr(index), &position, 16);
				break;
			case 'b':
			case 'B':
				//Treat as binary literal
				index += 2;
				value = std::stoull(token.substr(index), &position, 2);
				break;
			}
			if (position)
			{
				if ((position + index) < token.length())
					throw exception("Not all characters were consumed");
				return negate ? -*reinterpret_cast<double*>(&value) : *reinterpret_cast<double*>(&value);
			}
		}
		//Treat as stringified double literal
		size_t position = 0;
		double value = std::stod(token.substr(index), &position);
		if (position < token.length())
			throw exception("Not all characters were consumed");
		return negate ? -value : value;
	}
	catch (...)
	{
		throw exception("'" + token + "' is not a valid double literal");
	}

}
//TODO: Implement this
std::string openddl::parse_string(const std::string & token)
{
	const int length = token.length();
	if (length > 1 && token[0] == '"' && token[length - 1] == '"')
	{
		std::string out;
		int position = 1;
		while (position != (length - 1))
		{
			const char character = token[position];
			if (character == '\\')
			{
				if ((length - position) < 1)
					throw exception("Encountered invalid escape character in token " + token + " whilst parsing string structure");
				position += read_escape_character(out, token, position + 1) + 1;
			}
			else if (character < 0x20 || (character > 0x7E && character < 0xA0))
			{
				throw exception(std::string("Encountered illegal character '") + character + "' in token " + token + " whilst parsing string structure");
			}
			else
			{
				out.push_back(character);
				position += 1;
			}
		}
		return out;
	}
	throw exception("'" + token + "' is not a valid string");
}