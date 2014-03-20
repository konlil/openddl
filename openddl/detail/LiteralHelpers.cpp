#include "LiteralHelpers.h"
#include "../Type.h"
//Helper function
openddl::Type openddl::detail::convert(const openddl::detail::Token & t)
{
	using openddl::detail::Token;
	using namespace openddl;
	switch (t.token_type)
	{
	case Token::kBool: return Type::kBool;
	case Token::kDouble: return Type::kDouble;
	case Token::kFloat: return Type::kFloat;
	case Token::kInt8: return Type::kInt8;
	case Token::kInt16: return Type::kInt16;
	case Token::kInt32: return Type::kInt32;
	case Token::kInt64: return Type::kInt64;
	case Token::kUnsignedInt8: return Type::kUnsignedInt8;
	case Token::kUnsignedInt16: return Type::kUnsignedInt16;
	case Token::kUnsignedInt32: return Type::kUnsignedInt32;
	case Token::kUnsignedInt64: return Type::kUnsignedInt64;
	case Token::kRef: return Type::kRef;
	case Token::kString: return Type::kString;
	case Token::kType: return Type::kType;
	}
	throw std::out_of_range("Token enum was not type value");
}
void openddl::detail::encode_utf8(std::string & out, const char32_t token)
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
	else if (token < 0x4000000)
	{
		out.push_back((0xF8 | token >> 24));
		out.push_back((0x80 | token >> 18 & 0x3F));
		out.push_back((0x80 | token >> 12 & 0x3F));
		out.push_back((0x80 | token >> 6 & 0x3F));
		out.push_back((0x80 | token & 0x3F));
	}
	// 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
	else if (token < 0x8000000)
	{
		out.push_back((0xFC | token >> 30));
		out.push_back((0x80 | token >> 18 & 0x3F));
		out.push_back((0x80 | token >> 12 & 0x3F));
		out.push_back((0x80 | token >> 6 & 0x3F));
		out.push_back((0x80 | token & 0x3F));
	}

}
int openddl::detail::read_escape_character(std::string & out, const std::string & token, const int index)
{
	switch (token[index])
	{
	case '"':
		out.push_back('"'); return 1;
	case '\'':
		out.push_back('\''); return 1;
	case '?':
		out.push_back('?'); return 1;
	case '\\':
		out.push_back('\\'); return 1;
	case 'a':
		out.push_back('\a'); return 1;
	case 'b':
		out.push_back('\b'); return 1;
	case 'f':
		out.push_back('\f'); return 1;
	case 'n':
		out.push_back('\n'); return 1;
	case 'r':
		out.push_back('\r'); return 1;
	case 't':
		out.push_back('\t'); return 1;
	case 'v':
		out.push_back('\v'); return 1;
	case 'u':
	{
		const char32_t code_point = std::stoi(token.substr(index + 1, 4), nullptr, 16);
		encode_utf8(out, code_point);
		return 5;
	}
	case 'U':
	{
		const char32_t code_point = std::stoi(token.substr(index + 1, 6), nullptr, 16);
		encode_utf8(out, code_point);
		return 7;
	}
	default:
		return 0;
	}
}
std::string * openddl::detail::escape_string(const std::string & in)
{
	std::string * out = new std::string();
	const int length = in.length() - 2;
	for (int i = 1; i < length; i++)
	{
		const char character = in[i];
		if (character == '\\')
			i += read_escape_character(*out, in, i + 1);
		else
			out->push_back(character);
	}
	return out;
}
char openddl::detail::consume_character(const std::string & in, int & position)
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
uint64_t openddl::detail::decode_integer(openddl::detail::Token::token_t type, const std::string & in, bool & negate)
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
	case Token::kCharacterLiteral:
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
	case Token::kDecimalLiteral:
		value = std::stoull(in.substr(offset), nullptr, 10);
		break;
	case Token::kBinaryLiteral:
		value = std::stoull(in.substr(offset + 2), nullptr, 2);
		break;
	case Token::kHexLiteral:
		value = std::stoull(in.substr(offset + 2), nullptr, 16);
		break;
	}
	return value;
}
int openddl::detail::decode_literal(const openddl::detail::Token & t, openddl::detail::Command::LiteralPayload & payload)
{

	//Command::LiteralPayload::kReference is handled elsewhere
	switch (payload.encoding)
	{
	case Command::LiteralPayload::kType:
		try { payload.value.type_ = convert(t); }
		catch (std::out_of_range &) { return 1; }
		break;
	case Command::LiteralPayload::kBoolean:
		if (t.payload == "true") payload.value.boolean_ = true;
		else if (t.payload == "false") payload.value.boolean_ = false;
		else return -1;
		break;
	case Command::LiteralPayload::kFloat:
		switch (t.token_type)
		{
		case Token::kHexLiteral:
		case Token::kBinaryLiteral:
		{
			payload.value.double_.lexical = false;
			bool negate = false;
			try{ payload.value.integer_.value = decode_integer(t.token_type, t.payload, negate); }
			catch (std::out_of_range &) { return 1; }
			payload.value.double_.value *= negate ? -1.0 : 1.0;
		}
			break;
		case Token::kDecimalLiteral:
		case Token::kFloatLiteral:
			payload.value.double_.lexical = true;
			try{ payload.value.double_.value = std::stod(t.payload); }
			catch (std::out_of_range &) { return 1; }
			break;
		default:
			return -1;
		}
		break;
	case Command::LiteralPayload::kInteger:
		switch (t.token_type)
		{
		case Token::kHexLiteral:
		case Token::kBinaryLiteral:
		case Token::kCharacterLiteral:
		case Token::kDecimalLiteral:
			try{ payload.value.integer_.value = decode_integer(t.token_type, t.payload, payload.value.integer_.negate); }
			catch (std::out_of_range &) { return 1; }
			break;
		default:
			return -1;
		}
		break;
	case Command::LiteralPayload::kString:
		if (t.token_type == Token::kStringLiteral)
			payload.value.string_ = escape_string(t.payload);
		else
			return -1;
		break;
	}
	return 0;
}



int openddl::detail::detect_limits(Type type, const Command::LiteralPayload & payload)
{
	
	static const double float_limits[2][2] = 
	{ 
		{std::numeric_limits<float>::infinity(),std::numeric_limits<float>::max()} ,
		{std::numeric_limits<double>::infinity(), std::numeric_limits<double>::max()}
	};
	static const uint64_t integer_limits[8][2] =
	{
		{ 0, UINT8_MAX },
		{ 0, UINT16_MAX },
		{ 0, UINT32_MAX },
		{ 0, UINT64_MAX },
		{ -INT8_MIN, INT8_MAX },
		{ -INT16_MIN, INT16_MAX },
		{ -INT32_MIN, INT32_MAX },
		{ -INT64_MIN, INT64_MAX },
	};
	switch (type)
	{
	case Type::kFloat:
	{
		if (payload.encoding != Command::LiteralPayload::kFloat) return 0;
		float value;
		//Must perform (lexical/binary) conversion between double storage type and temp float variable
		if (payload.value.double_.lexical)
			value = (float)payload.value.double_.value;
		else
			value = *(float*)&payload.value.double_.value;
		if (value <= float_limits[type][1] || value == float_limits[type][0])
			if (value >= -float_limits[type][1] || value == -float_limits[type][0])
				return 0;
			else
				return -1;
		else
			return 1;
	}
	case Type::kDouble:
	{
		if (payload.encoding != Command::LiteralPayload::kFloat) return 0;
		double value = payload.value.double_.value;
		if (value <= float_limits[type][1] || value == float_limits[type][0])
			if (value >= -float_limits[type][1] || value == -float_limits[type][0])
				return 0;
			else
				return -1;
		else
			return 1;
	}
	case Type::kUnsignedInt8:
	case Type::kUnsignedInt16:
	case Type::kUnsignedInt32:
	case Type::kUnsignedInt64:
	case Type::kInt8:
	case Type::kInt16:
	case Type::kInt32:
	case Type::kInt64:
		if (payload.encoding != Command::LiteralPayload::kInteger)
			return 0;
		else if (integer_limits[type - Type::kUnsignedInt8][0] == 0 && payload.value.integer_.negate) //Unsigned integer literals may not be negated
			return -1;
		else if (payload.value.integer_.value > integer_limits[type - Type::kUnsignedInt8][0] && payload.value.integer_.negate)
			return -1;
		else if (payload.value.integer_.value > integer_limits[type - Type::kUnsignedInt8][1] && !payload.value.integer_.negate)
			return 1;
		else
			return 0;
	}
	//Does not apply to this literal
	return 0;
}