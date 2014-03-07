#include "Literal.h"
#include "Lexer.h"

char consume_character(const std::string & token, int & index)
{
	char value = 0;
	if (token[index] == '\\')
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
			value = std::stoi(token.substr(index + 2, 2), nullptr, 16);
			index += 4;
			break;
		}
	}
	else
	{
		const char character = token[index];
		if ((character >= 0x20 && character < '\'') || (character > '\'' && character < 0x7F))
		{
			index += 1;
			value = character;
		}
	}
	return value;
}
openddl::Literal::Literal(const Token & t)
: negate(false), type(t.code)
{
	int offset = 0;
	switch (t.payload[0])
	{
	case '-':
		negate = true;
	case '+':
		offset += 1;
	}
	switch (t.code)
	{
	case Token::kHex:
		_int = std::stoll(t.payload.substr(offset + 2), nullptr, 16);
		break;
	case Token::kBinary:
		_int = std::stoll(t.payload.substr(offset + 2), nullptr, 2);
		break;
	case Token::kDecimal:
		_int = std::stoll(t.payload.substr(offset), nullptr, 10);
		break;
	case Token::kCharacter:
		for (int i = 0; i < 8; i++)
		{
			_int += consume_character(t.payload, offset);
			if (offset == t.range_length)
				break;
			_int = _int << 8;
		}
		break;
	default:
		break;
	}
}

bool openddl::Literal::is_integer()
{
	switch (type)
	{
	case Token::kBinary:
	case Token::kHex:
	case Token::kDecimal:
	case Token::kCharacter:
		return true;
	default:
		return false;
	}
}
bool openddl::Literal::is_float()
{
	switch (type)
	{
	case Token::kBinary:
	case Token::kHex:
	case Token::kDecimal:
	case Token::kFloat:
		return true;
	default:
		return false;
	}
}