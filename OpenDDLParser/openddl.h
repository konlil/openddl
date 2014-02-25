//================================================================================================================
// Copyright 2014 Denis Hilliard (armchaircommando@gmail.com)
// Licensed under MIT License
//================================================================================================================
#pragma once
#include <string>
#include <cstdint>
#include <vector>

namespace openddl
{
	using exception = std::runtime_error;
	struct Reference
	{

	};
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

		//Helper templates for converting between c++ types and type enum
		template <typename T> enum_t get()		{ return kCount; }
		template <> enum_t get<bool>()			{ return kBool; }
		template <> enum_t get<int8_t>()		{ return kInt8; }
		template <> enum_t get<int16_t>()		{ return kInt16; }
		template <> enum_t get<int32_t>()		{ return kInt32; }
		template <> enum_t get<int64_t>()		{ return kInt64; }
		template <> enum_t get<uint8_t>()		{ return kUnsignedInt8; }
		template <> enum_t get<uint16_t>()		{ return kUnsignedInt16; }
		template <> enum_t get<uint32_t>()		{ return kUnsignedInt32; }
		template <> enum_t get<uint64_t>()		{ return kUnsignedInt64; }
		template <> enum_t get<float>()			{ return kFloat; }
		template <> enum_t get<double>()		{ return kDouble; }
		template <> enum_t get<std::string>()	{ return kString; }
		template <> enum_t get<Reference>()		{ return kRef; }

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

	//Used to turn string into sequence of tokens
	struct Tokenizer
	{
		struct Token
		{
			unsigned int line_number;
			std::string value;
			Token(unsigned int line, const std::string & value);
		};
		unsigned int consume_whitespace(const std::string & token, const unsigned int index);
		unsigned int consume_token(const std::string & token, const unsigned int index);
		unsigned int line_number;
		std::vector<Token> tokens;
		void operator()(const std::string & token);
		Tokenizer() : line_number(1) {}
	};

	struct Parser
	{
		
		struct Adapter
		{
			virtual void push_list(Type::enum_t type) = 0;
			virtual void add_value(const int8_t value) = 0;
			virtual void add_value(const int16_t value) = 0;
			virtual void add_value(const int32_t value) = 0;
			virtual void add_value(const int64_t value) = 0;
			virtual void add_value(const uint8_t value) = 0;
			virtual void add_value(const uint16_t value) = 0;
			virtual void add_value(const uint32_t value) = 0;
			virtual void add_value(const uint64_t value) = 0;
			virtual void add_value(const float value) = 0;
			virtual void add_value(const double value) = 0;
			virtual void add_value(const std::string & value) = 0;
			virtual void pop() = 0;
		};

		void operator()(const Tokenizer & tokens, Adapter & adapter);
	};
	

	
};

