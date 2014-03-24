#include "LiteralHelpers.h"
#include "../Type.h"
#include "Error.h"
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
char32_t openddl::detail::decode_utf8(const std::string & token, const unsigned int index, unsigned int & length)
{
	unsigned int token_length = token.length()-1;
	char32_t value = 0;
	// 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
	if ((token[index] & 0xFC) == 0xFC)
	{
		if ((token_length - index) < 6) return 0;
		value = ((token[index] & 0x01) << 30) | ((token[index + 1] & 0x3F) << 24)
			| ((token[index + 2] & 0x3F) << 18) | ((token[index + 3]
			& 0x3F) << 12)
			| ((token[index + 4] & 0x3F) << 6) | (token[index + 5] & 0x3F);
		length = 6;
	}
	// 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
	else if ((token[index] & 0xF8) == 0xF8)
	{
		if ((token_length - index) < 5) return 0;
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
		if ((token_length - index) <4) return 0;
		value = ((token[index] & 0x07) << 18) | ((token[index + 1]
			& 0x3F) << 12)
			| ((token[index + 2] & 0x3F) << 6) | (token[index + 3] & 0x3F);
		length = 4;
	}
	// 1110xxxx 10xxxxxx 10xxxxxx
	else if ((token[index] & 0xE0) == 0xE0)
	{
		if ((token_length - index) < 3) return 0;
		value = ((token[index] & 0x0F) << 12) | ((token[index + 1] & 0x3F) << 6)
			| (token[index + 2] & 0x3F);
		length = 3;
	}
	// 110xxxxx 10xxxxxx
	else if ((token[index] & 0xC0) == 0xC0)
	{
		if ((token_length - index) < 2) return 0;
		value = ((token[index] & 0x1F) << 6) | (token[index + 1] & 0x3F);
		length = 2;
	}
	// 0xxxxxxx
	else if (token[index] < 0x80)
	{
		if ((token_length - index) < 1) return 0;
		value = token[index];
		length = 1;
	}
	return value;
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


bool accept_character(char32_t character)
{
	if (character == 0x20)
		return true;
	else if (character == 0x21)
		return true;
	else if (character <= 0x5B && character >= 0x23)
		return true;
	else if (character <= 0x7E && character >= 0x5D)
		return true;
	else if (character <= 0xD7FF && character >= 0xA0)
		return true;
	else if (character <= 0xFFFD && character >= 0xE000)
		return true;
	else if (character <= 0x10FFFF && character >= 0x10000)
		return true;
	return false;
}
//Don't worry about validating presence of enclosing double quotes
void openddl::detail::validate_string(std::vector<Error> & errors, std::string & out, const std::string & in)
{
	auto push_error = [&](const std::string & msg){Error e; e.message = msg; errors.push_back(e); };
	unsigned int token_length = 0;
	unsigned int length = in.length() -1;
	for (unsigned int i = 1; i < length; i++)
	{
		char32_t character;
		if (in[i] == '\\')
		{
			switch (in[i + 1])
			{
			case '"':
				out.push_back('"'); i++;
				break;
			case '\'':
				out.push_back('\''); i++;
				break;
			case '?':
				out.push_back('?'); i++;
				break;
			case '\\':
				out.push_back('\\'); i++;
				break;
			case 'a':
				out.push_back('\a'); i++;
				break;
			case 'b':
				out.push_back('\b'); i++;
				break;
			case 'f':
				out.push_back('\f'); i++;
				break;
			case 'n':
				out.push_back('\n'); i++;
				break;
			case 'r':
				out.push_back('\r'); i++;
				break;
			case 't':
				out.push_back('\t'); i++;
				break;
			case 'v':
				out.push_back('\v'); i++;
				break;
			case 'x':
				if (length - i < 4)
					push_error("parse.string.invalid_character");
				else
				{
					size_t position = 0;
					character = std::stoi(in.substr(i + 2, 2), &position, 16);
					if (position == 2)
						encode_utf8(out, character);
					else
						push_error("parse.string.invalid_character");
					i += position+1;
				}
				break;
			case 'u':
				if (length- i < 6)
					push_error("parse.string.invalid_character");
				else
				{
					size_t position = 0;
					character = std::stoi(in.substr(i + 2, 4), &position, 16);
					if (position == 4)
						encode_utf8(out, character);
					else
						push_error("parse.string.invalid_character");
					i += position+1;
				}
				break;
			case 'U':
				if (length - i < 8)
					push_error("parse.string.invalid_character");
				else
				{
					size_t position = 0;
					character = std::stoi(in.substr(i + 2, 6), &position, 16);
					if (position == 6)
						encode_utf8(out, character);
					else
						push_error("parse.string.invalid_character");
					i += position+1;
				}
				break;
			}
		}
		else if (character = decode_utf8(in,i,token_length))
		{
			if (accept_character(character))
				encode_utf8(out, character);
			else
				push_error("parse.string.invalid_character");
			i += token_length-1;
		}
		else
			push_error("parse.string.invalid_character");
	}
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
	}
	return 0;
}



int openddl::detail::detect_limits(Type type, const Command::LiteralPayload & payload)
{

	static const double float_limits[2][2] =
	{
		{ std::numeric_limits<float>::infinity(), std::numeric_limits<float>::max() },
		{ std::numeric_limits<double>::infinity(), std::numeric_limits<double>::max() }
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
bool openddl::detail::encoding_mismatch(openddl::Type type, Command::LiteralPayload::encoding_t encoding)
{
	using openddl::detail::Command;
	using openddl::Type;
	switch (type)
	{
	case Type::kInt8:
	case Type::kInt16:
	case Type::kInt32:
	case Type::kInt64:
	case Type::kUnsignedInt8:
	case Type::kUnsignedInt16:
	case Type::kUnsignedInt32:
	case Type::kUnsignedInt64:
		if (encoding == Command::LiteralPayload::kInteger) return false; else return true;
	case Type::kBool:
		if (encoding == Command::LiteralPayload::kBoolean) return false; else return true;
	case Type::kDouble:
	case Type::kFloat:
		if (encoding == Command::LiteralPayload::kFloat) return false; else return true;
	case Type::kRef:
		if (encoding == Command::LiteralPayload::kReference) return false; else return true;
	case Type::kString:
		if (encoding == Command::LiteralPayload::kString) return false; else return true;
	case Type::kType:
		if (encoding == Command::LiteralPayload::kType) return false; else return true;
	default:
		return true;
	}
}
openddl::detail::Command::LiteralPayload::encoding_t openddl::detail::get_encoding(openddl::Type type)
{
	using namespace openddl;
	using openddl::detail::Command;
	switch (type)
	{
	case Type::kInt8:
	case Type::kInt16:
	case Type::kInt32:
	case Type::kInt64:
	case Type::kUnsignedInt8:
	case Type::kUnsignedInt16:
	case Type::kUnsignedInt32:
	case Type::kUnsignedInt64:
		return Command::LiteralPayload::kInteger;
	case Type::kDouble:
	case Type::kFloat:
		return Command::LiteralPayload::kFloat;
	case Type::kBool:
		return Command::LiteralPayload::kBoolean;
	case Type::kRef:
		return Command::LiteralPayload::kReference;
	case Type::kString:
		return Command::LiteralPayload::kString;
	case Type::kType:
		return Command::LiteralPayload::kType;
	default:
		throw std::out_of_range("Type is out of range");
	}
}