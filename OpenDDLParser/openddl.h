//================================================================================================================
// Copyright 2014 Denis Hilliard (armchaircommando@gmail.com)
// Licensed under MIT License
//================================================================================================================
#pragma once
#include <string>
#include <cstdint>

namespace openddl
{
	using exception = std::runtime_error;
	struct Type
	{
		enum enum_t {
			kBool,
			kInt8,
			kInt16,
			kInt32,
			kInt64,
			kUnsignedInt8,
			kUnsignedInt16,
			kUnsignedInt32,
			kUnsignedInt64,
			kFloat,
			kDouble,
			kString,
			kRef,
			kType,
			kCount
		};
	};

	//Token Processing functions
	bool is_identifier(const std::string & token, const unsigned int index);
	uint64_t parse_character_literal(const std::string & token, const unsigned int index);
	bool is_name(const std::string & token, const unsigned int index);
	bool is_local_name(const std::string & token, const unsigned int index);
	Type::enum_t parse_type(const std::string & token);
	bool decode_boolean(const std::string & token);
	uint8_t decode_unsigned_int8(const std::string & token);
	uint16_t decode_unsigned_int16(const std::string & token);
	uint32_t decode_unsigned_int32(const std::string & token);
	uint64_t decode_unsigned_int64(const std::string & token);
	int8_t decode_int8(const std::string & token);
	int16_t decode_int16(const std::string & token);
	int32_t decode_int32(const std::string & token);
	int64_t decode_int64(const std::string & token);
	float decode_float(const std::string & token);
	double decode_double(const std::string & token);
	std::string parse_string(const std::string & token);

	unsigned int consume_whitespace(const std::string & token, const unsigned int index);
	unsigned int consume_comment(const std::string & token, const unsigned int index);
};

