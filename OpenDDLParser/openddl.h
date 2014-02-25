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
		template <typename T> static enum_t get()		{ return kCount; }
		template <> static enum_t get<bool>()			{ return kBool; }
		template <> static enum_t get<int8_t>()			{ return kInt8; }
		template <> static enum_t get<int16_t>()		{ return kInt16; }
		template <> static enum_t get<int32_t>()		{ return kInt32; }
		template <> static enum_t get<int64_t>()		{ return kInt64; }
		template <> static enum_t get<uint8_t>()		{ return kUnsignedInt8; }
		template <> static enum_t get<uint16_t>()		{ return kUnsignedInt16; }
		template <> static enum_t get<uint32_t>()		{ return kUnsignedInt32; }
		template <> static enum_t get<uint64_t>()		{ return kUnsignedInt64; }
		template <> static enum_t get<float>()			{ return kFloat; }
		template <> static enum_t get<double>()			{ return kDouble; }
		template <> static enum_t get<std::string>()	{ return kString; }
		template <> static enum_t get<Reference>()		{ return kRef; }

	};

	struct Value
	{
		Value() : type(Type::kCount) {}
		explicit Value(bool value) : type(Type::kBool) { v._boolean = value; }
		explicit Value(int8_t value) : type(Type::kInt8) { v._integer = value; }
		explicit Value(int16_t value) : type(Type::kInt16) { v._integer = value; }
		explicit Value(int32_t value) : type(Type::kInt32) { v._integer = value; }
		explicit Value(int64_t value) : type(Type::kInt64) { v._integer = value; }
		explicit Value(uint8_t value) : type(Type::kUnsignedInt8) { v._u_integer = value; }
		explicit Value(uint16_t value) : type(Type::kUnsignedInt16) { v._u_integer = value; }
		explicit Value(uint32_t value) : type(Type::kUnsignedInt32) { v._u_integer = value; }
		explicit Value(uint64_t value) : type(Type::kUnsignedInt64) { v._u_integer = value; }
		explicit Value(float value) : type(Type::kFloat) { v._float = value; }
		explicit Value(double value) : type(Type::kDouble) { v._double = value; }
		template <typename T> T & get() {
			if (type == Type::kCount)
				throw exception("Null Value");
			if (Type::get<T>() == type)
			{
				switch (type)
				{
				case Type::kBool:
					return (T&)v._boolean;
				case Type::kFloat:
					return (T&)v._float;
				case Type::kDouble:
					return (T&)v._double;
				case Type::kInt8:
				case Type::kInt16:
				case Type::kInt32:
				case Type::kInt64:
					return (T&)v._integer;
				case Type::kUnsignedInt8:
				case Type::kUnsignedInt16:
				case Type::kUnsignedInt32:
				case Type::kUnsignedInt64:
					return (T&)v._u_integer;
				default:
					throw exception("Not implemented yet");
				}
			}
			else
				throw exception("Value type mismatch");
		}
	private:
		
		union storage_ { bool _boolean;  float _float; double _double; uint64_t _u_integer; int64_t _integer; };

		int type;
		storage_ v;
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

	Value decode_value(const std::string & token, Type::enum_t type);

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
			
			virtual void push_value(Value & value) {};

			virtual void push_list(Type::enum_t type) = 0;
			virtual void pop() = 0;
		};

		static unsigned int parse_data_list(const std::vector<openddl::Tokenizer::Token> & tokens, Adapter & adapter, const unsigned int index);
	};
	

	
};

