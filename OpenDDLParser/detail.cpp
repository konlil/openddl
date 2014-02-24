//================================================================================================================
// Copyright 2014 Denis Hilliard (armchaircommando@gmail.com)
// Licensed under MIT License
//================================================================================================================
#include "stdafx.h"
#include "detail.h"

//Forward declarations
namespace openddl
{
	uint64_t parse_character_literal(const std::string & token, const unsigned int index);
}


//================================================================================================================
// Internal common functionality for decoding literals.
//================================================================================================================
namespace detail
{
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
							throw std::runtime_error("Invalid hex character literal");
						index += 4;
					}
					else
						throw std::runtime_error("Insufficient characters to consume");
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
				throw std::runtime_error("Not a valid character literal");
		}
		return value;
	}
	//Internal function used to consume characters out of a string and decode them into their utf32 form
	//Returns decoded character and sets length to number of characters within literal.
	char32_t decode_utf8(const std::string & token, const unsigned int index, const unsigned int token_length, unsigned int & length)
	{
		char32_t value = 0;
		// 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
		if ((token[index] & 0xFC) == 0xFC)
		{
			if ((token_length - index) < 6)
				throw std::length_error("");
			value = ((token[index] & 0x01) << 30) | ((token[index + 1] & 0x3F) << 24)
				| ((token[index + 2] & 0x3F) << 18) | ((token[index + 3]
				& 0x3F) << 12)
				| ((token[index + 4] & 0x3F) << 6) | (token[index + 5] & 0x3F);
			length = 6;
		}
		// 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
		else if ((token[index] & 0xF8) == 0xF8)
		{
			if ((token_length - index) < 5)
				throw std::length_error("");
			value = ((token[index] & 0x03) << 24) | ((token[index + 1]
				& 0x3F) << 18)
				| ((token[index + 2] & 0x3F) << 12) | ((token[index + 3]
				& 0x3F) << 6)
				| (token[index + 4] & 0x3F);
			length = 5;
		}
		// 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
		else if ((token[index] & 0xF0) == 0xF0)
		{
			if ((token_length - index) < 4)
				throw std::length_error("");
			value = ((token[index] & 0x07) << 18) | ((token[index + 1]
				& 0x3F) << 12)
				| ((token[index + 2] & 0x3F) << 6) | (token[index + 3] & 0x3F);
			length = 4;
		}
		// 1110xxxx 10xxxxxx 10xxxxxx
		else if ((token[index] & 0xE0) == 0xE0)
		{
			if ((token_length - index) < 3)
				throw std::length_error("");
			value = ((token[index] & 0x0F) << 12) | ((token[index + 1] & 0x3F) << 6)
				| (token[index + 2] & 0x3F);
			length = 3;
		}
		// 110xxxxx 10xxxxxx
		else if ((token[index] & 0xC0) == 0xC0)
		{
			if ((token_length - index) < 2)
				throw std::length_error("");
			value = ((token[index] & 0x1F) << 6) | (token[index + 1] & 0x3F);
			length = 2;
		}
		// 0xxxxxxx
		else if (token[index] < 0x80)
		{
			if ((token_length - index) < 1)
				throw std::length_error("");
			value = token[index];
			length = 1;
		}
		return value;
	}
	//Encodes utf32 encoded character as a sequence of utf8 encoded bytes (appending to string)
	//Handles characters in the range of 0x00 to 0x10FFFF
	void encode_utf8(std::string & out, const char32_t token)
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
		else throw std::runtime_error("Unicode overflow");

	}
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

	int read_escape_character(std::string & out, const std::string & token, const unsigned int index)
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
				throw std::runtime_error(std::string("Encountered invalid unicode escape character token token '") + token + "' whilst parsing string structure");
			size_t position = 0;
			const char32_t code_point = std::stoi(token.substr(index + 1, 4), &position, 16);
			if (position != 4)
				throw std::runtime_error(std::string("Encountered invalid unicode escape character token token '") + token + "' whilst parsing string structure");
			if (code_point < 0x0001)
				throw std::runtime_error(std::string("Encountered invalid unicode escape character token token '") + token + "' whilst parsing string structure");
			encode_utf8(out, code_point);
			return 5;
		}
		case 'U':
		{
			if (index + 6 > token.length())
				throw std::runtime_error(std::string("Encountered invalid unicode escape character token token '") + token + "' whilst parsing string structure");
			size_t position = 0;
			const char32_t code_point = std::stoi(token.substr(index + 1, 6), &position, 16);
			if (position != 6)
				throw std::runtime_error(std::string("Encountered invalid unicode escape character token token '") + token + "' whilst parsing string structure");
			if (code_point < 0x0001 || code_point > 0x10FFFF)
				throw std::runtime_error(std::string("Encountered invalid unicode escape character token token '") + token + "' whilst parsing string structure");
			encode_utf8(out, code_point);
			return 7;
		}
		default:
			throw std::runtime_error(std::string("Encountered invalid unicode escape character token token '") + token + "' whilst parsing string structure");
		}
	}

	bool is_valid_character(const char32_t character)
	{
		if (character == 0x20 || character == 0x21)
			return true;
		if (character >= 0x23 && character <= 0x5B)
			return true;
		if (character >= 0x5D && character <= 0x7E)
			return true;
		if (character >= 0xA0 && character <= 0xD7FF)
			return true;
		if (character >= 0xE000 && character <= 0xFFFD)
			return true;
		if (character >= 0x010000 && character <= 0x10FFFF)
			return true;
		return false;
	}

	bool is_whitespace(const char character)
	{
		if (character >= 1 && character <= 32)
			return true;
		return false;
	}

	bool is_structural(const char character)
	{
		switch (character)
		{
		case ',':
		case '{':
		case '}':
		case '[':
		case ']':
			return true;
		}
		return false;
	}
}
//================================================================================================================