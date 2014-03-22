#pragma once
#include <string>
#include <vector>
#include <cstdint>

namespace openddl
{
	enum Type;

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

				std::string * name;
				Type type;
				unsigned int length;

			};
			struct ArrayElementPayload
			{

				unsigned int subindex;
				unsigned int length;
			};
			struct DataArrayPayload
			{


				std::string * name;
				Type type;
				unsigned int length;
				unsigned int dimension;
			};
			
			struct LiteralPayload
			{

				union Value {
					std::string * string_;
					std::vector<std::string> * reference_;
					struct { bool negate; uint64_t value; } integer_;
					struct { bool lexical; double value; } double_;
					bool boolean_;
					Type type_;
					
				} value;
				enum encoding_t { kString, kReference, kInteger, kFloat, kBoolean, kType } encoding;
			};
			struct PropertyPayload
			{
				std::string * identifier;

				enum {kHex,kBinary,kCharacter,kDecimal,kFloat,kBool,kString,kReference,kDataType} encoding;
				union Value {
					std::string * string_;
					std::string * numeric_;
					Type type_;
					std::vector<std::string> * reference_;
					bool boolean_;

				} value;	
			};

			enum Type { kStructure, kDataList, kDataArray, kArrayElement, kLiteral, kProperty } type;
			union Payload {
				StructurePayload structure_;
				DataListPayload list_;
				DataArrayPayload array_;
				ArrayElementPayload element_;
				LiteralPayload literal_;
				PropertyPayload property_;
			} payload;

			//0 if no parent, non-zero if parent
			unsigned int parent;
			unsigned int depth;
			Command(LiteralPayload & p,unsigned int parent = 0,unsigned int depth = 0);
			Command(StructurePayload & s, unsigned int parent = 0, unsigned int depth = 0);
			Command(DataListPayload & l, unsigned int parent = 0, unsigned int depth = 0);
			Command(DataArrayPayload & a, unsigned int parent = 0, unsigned int depth = 0);
			Command(ArrayElementPayload & e, unsigned int parent = 0, unsigned int depth = 0);
			Command(PropertyPayload & p, unsigned int parent = 0, unsigned int depth = 0);
			Command(Type t, unsigned int parent, unsigned int depth);
			Command(Command && rhs);
			~Command();

		};
	}
}