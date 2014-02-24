#pragma once

#include <cstdint>
#include <string>

namespace detail {
	//Internal function used to consume individual/aggregate characters out of a token
	char consume_character(const std::string & token, unsigned int & index, const unsigned int length);
	//Internal function used to consume characters out of a string and decode them into their utf32 form
	//Returns decoded character and sets length to number of characters within literal.
	char32_t decode_utf8(const std::string & token, const unsigned int index, const unsigned int token_length, unsigned int & length);

	//Encodes utf32 encoded character as a sequence of utf8 encoded bytes (appending to string)
	//Handles characters in the range of 0x00 to 0x10FFFF
	void encode_utf8(std::string & out, const char32_t token);

	struct literal_encoding
	{
		bool negate;
		bool character;
		int number_base;
		int offset;
	};
	//Decode integer specific encoding details from token string
	literal_encoding decode_literal(const std::string & token);

	uint64_t decode_unsigned_integer(const std::string & token);

	int64_t decode_integer(const std::string & token);

	int read_escape_character(std::string & out, const std::string & token, const unsigned int index);

	bool is_valid_character(const char32_t character);

	bool is_whitespace(const char character);

	bool is_structural(const char character);
}