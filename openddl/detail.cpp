#include "detail.h"

bool openddl::detail::Token::is_float_encoded() const {
	return (token_type == kFloatLiteral || token_type == kDecimalLiteral || token_type == kBinaryLiteral || token_type == kHexLiteral);
}
bool openddl::detail::Token::is_integer_encoded() const {
	return (token_type == kCharacterLiteral || token_type == kDecimalLiteral || token_type == kBinaryLiteral || token_type == kHexLiteral);
}
bool openddl::detail::Token::is_data_type() const {
	switch (token_type)
	{
	case kFloat:
	case kDouble:
	case kRef:
	case kUnsignedInt8:
	case kUnsignedInt16:
	case kUnsignedInt32:
	case kUnsignedInt64:
	case kInt8:
	case kInt16:
	case kInt32:
	case kInt64:
	case kBool:
	case kString:
	case kType:
		return true;
	default:
		return false;
	}
}
