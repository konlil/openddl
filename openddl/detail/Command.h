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

			//Assume ownership of all members
			struct StructurePayload
			{
				std::string * identifier;
				std::string * name;
				unsigned int properties;
				unsigned int children;
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
			struct PropertyPayload
			{
				std::string * identifier;
				enum {kHex,kBinary,kCharacter,kDecimal,kFloat,kBool,kString,kReference,kDataType} encoding;
				union {
					std::string * string_;
					std::string * numeric_;
					Type type_;
					std::vector<std::string> * reference_;
					bool boolean_;
				} value;
					
			};

			union {
				StructurePayload structure_;
				DataListPayload list_;
				DataArrayPayload array_;
				ArrayElementPayload element_;
				LiteralPayload literal_;
				PropertyPayload property_;
			} payload;

			enum { kStructure, kDataList, kDataArray, kArrayElement, kLiteral, kProperty } type;
			int parent;
			int depth;

		};
	}
}