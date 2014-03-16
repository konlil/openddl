#pragma once
#include <string>
namespace openddl
{
	namespace detail
	{
		struct Token
		{
			enum token_t
			{
				kLeftSquareBracket = 1,
				kRightSquareBracket,
				kComma,
				kLeftBrace,
				kRightBrace,
				kEquals,
				kIdentifier,
				kName,
				kNull,
				kBooleanLiteral,
				kFloatLiteral,
				kHexLiteral,
				kDecimalLiteral,
				kBinaryLiteral,
				kStringLiteral,
				kCharacterLiteral,
				kFloat,
				kDouble,
				kUnsignedInt8,
				kUnsignedInt16,
				kUnsignedInt32,
				kUnsignedInt64,
				kInt8,
				kInt16,
				kInt32,
				kInt64,
				kRef,
				kBool,
				kString,
				kType
			};

			token_t		token_type;

			std::string payload;

			unsigned int range_start;
			unsigned int range_length;

			unsigned int line;

		};
	}
}
