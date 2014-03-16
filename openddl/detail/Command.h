#pragma once
#include <string>
#include <vector>
#include <cstdint>

namespace openddl
{
	namespace detail
	{
		struct Command
		{
			struct StructurePayload
			{
				//Do not assume ownership of identifier/name
				std::string * identifier;
				std::string * name;
			};
			struct DataListPayload
			{
				Type type;
				std::string * name;
				unsigned int length;
			};
			struct ArrayElementPayload
			{
				unsigned int subindex;
				unsigned int length;
			};
			struct DataArrayPayload
			{
				Type type;
				std::string * name;
				unsigned int length;
				unsigned int dimension;
			};
			struct LiteralPayload
			{
				//Assume ownership of string_/reference_ members
				union {
					std::string * string_;
					std::vector<std::string> * reference_;
					struct { bool negate; uint64_t value; } integer_;
					struct { bool lexical; double value; } double_;
					bool boolean_;
					Type type_;
				} value;
				enum encoding_t { kString, kReference, kInteger, kFloat, kBoolean, kType };
				encoding_t encoding;
			};

			union _payload {
				StructurePayload structure_;
				DataListPayload list_;
				DataArrayPayload array_;
				ArrayElementPayload element_;
				LiteralPayload literal_;
			};

			enum { kStructure, kDataList, kDataArray, kArrayElement, kLiteral } type;
			_payload payload;
			unsigned int next;
		};
	}
}