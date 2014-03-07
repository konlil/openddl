#pragma once
#include <cstdint>
namespace openddl
{
	struct Token;
	struct Literal
	{
	public:
		Literal(const Token & t);
		~Literal();

		bool is_integer();
		bool is_float();

	private:
		int type;
		bool negate;
		uint64_t _int;
	};
}


