//================================================================================================================
// Copyright 2014 Denis Hilliard (armchaircommando@gmail.com)
// Licensed under MIT License
//================================================================================================================
#include "stdafx.h"
#include "openddl.h"

#include "detail.h"



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
			value += detail::consume_character(token, position, length - 1);
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
		uint64_t value = detail::decode_unsigned_integer(token);
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
		uint64_t value = detail::decode_unsigned_integer(token);
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
		uint64_t value = detail::decode_unsigned_integer(token);
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
		uint64_t value = detail::decode_unsigned_integer(token);
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
		int64_t value = detail::decode_integer(token);
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
		int64_t value = detail::decode_integer(token);
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
		int64_t value = detail::decode_integer(token);
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
		int64_t value = detail::decode_integer(token);
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
			unsigned int characters_consumed = 0;
			char32_t character = detail::decode_utf8(token, position, length - 1, characters_consumed);
			if (character == '\\')
			{
				if ((length - position) < 1)
					throw exception("Encountered invalid escape character in token " + token + " whilst parsing string structure");
				position += detail::read_escape_character(out, token, position + 1) + 1;
			}
			else if (detail::is_valid_character(character) )
			{
				for (unsigned int i = 0; i < characters_consumed; i++)
					out.push_back(token[position + i]);
				position += characters_consumed;		
			}
			else
			{ 		
				throw exception("Encountered illegal character in token " + token + " whilst parsing string structure");
			}
		}
		return out;
	}
	throw exception("'" + token + "' is not a valid string");
}

//Consumes whitespace characters and/or comments out of input string token
unsigned int openddl::consume_whitespace(const std::string & token, const unsigned int index)
{
	const unsigned int length = token.length();
	unsigned int characters_consumed = 0;
	bool block_comment = false;
	bool line_comment = false;
	for (unsigned int position = index; position < length; position++)
	{
		if (line_comment)
		{
			if (token[position] == '\n')
			{
				line_comment = false;
			}
			characters_consumed += 1;
		}
		else if (block_comment)
		{
			if (token[position] == '/')
				if (token[position + 1] == '*' && block_comment)
					throw std::runtime_error("Block Comments may not be nested");
			if (token[position] == '*')
				if (token[position + 1] == '/')
				{
					characters_consumed += 2;
					position++;
					block_comment = false;
				}
			characters_consumed++;
		}
		else
		{
			if (token[position] == '/')
			{
				if (token[position + 1] == '*')
				{
					block_comment = true;
					position++;
					characters_consumed += 2;
				}
				else if (token[position + 1] == '/')
				{
					line_comment = true;
					position++;
					characters_consumed += 2;
				}
			}
			else if (detail::is_whitespace(token[position]))
				characters_consumed++;
			else
				break;
		}
	}
	if (block_comment)
		throw std::runtime_error("Unexpected end of file");
	return characters_consumed;
}

unsigned int openddl::consume_token(const std::string & token, const unsigned int index)
{
	const unsigned int length = token.length();	
	bool string_literal = (token[index] == '"');
	unsigned int characters_consumed = string_literal ? 1 : 0;
	for (unsigned int position = index + (string_literal ? 1 : 0); position < length; position++)
	{
		if (string_literal)
		{
			if (token[position] == '"' && token[position - 1] != '/')
				string_literal = false;
			characters_consumed++;
		}
		else if (!detail::is_whitespace(token[position]))
			characters_consumed++;	
		else
			break;
	}
	if (string_literal)
		throw std::runtime_error("Unexpected end of file");
	return characters_consumed;
}