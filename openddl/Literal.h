//================================================================================================================
// Copyright 2014 Denis Hilliard (armchaircommando@gmail.com)
// Licensed under MIT License
//================================================================================================================
#pragma once
#include "Lexer.h"
#include <cstdint>
#include <type_traits>

namespace openddl
{

	struct Literal
	{
		using type_error = std::runtime_error;
		enum type_t
		{
			kInteger,		
			kFloat,			
			kString,		
			kBoolean,
			kRef,
			kNone
		};

		template <typename T> const typename std::enable_if<std::is_same<std::string,T>::value,T>::type & get() 
		{ 
			if (type == kString) return *(u_.s_value); 
			else throw type_error("Type Conversion Error (String)"); 
		}
		template <typename T> const typename std::enable_if<std::is_same<bool, T>::value, T>::type get()
		{ 
			if (type == kBoolean) return u_.b_value; 
			else throw type_error("Type Conversion Error (Boolean)"); 
		}
		
		template <typename T>
		struct is_signed_integer
		{
			static const bool value = std::is_signed<T>::value && !std::is_floating_point<T>::value && !std::is_same<bool, T>::value;
		};
		template <typename T>
		struct is_unsigned_integer
		{
			static const bool value = std::is_unsigned<T>::value && !std::is_floating_point<T>::value && !std::is_same<bool, T>::value;
		};
		template <typename T>
		const typename std::enable_if<is_signed_integer<T>::value, T>::type get()
		{
			if (type == kInteger)
			{
				if (negate && u_.i_value > std::abs(std::numeric_limits<T>::min()))
					throw type_error("Underflow");
				else if (u_.i_value > std::numeric_limits<T>::max()) 
					throw type_error("Overflow");
				return negate ? -(T)u_.i_value : (T)u_.i_value;
			}
			else throw type_error("Type Conversion Error (Integer)");
		}
		template <typename T>
		const typename std::enable_if<is_unsigned_integer<T>::value, T>::type get()
		{
			if (type == kInteger)
			{
				if (negate) throw type_error("Underflow");
				if (u_.i_value > std::numeric_limits<T>::max()) throw type_error("Overflow");
				return (T)u_.i_value;
			}
			else throw type_error("Type Conversion Error (Unsigned Integer)");
		}
		
		
		Literal(Literal && l);

		~Literal();

	private:
		Literal();
		type_t type;
		union _storage { std::string * s_value; bool b_value; uint64_t i_value; };
		_storage u_;
		bool negate;
	public:
		//Construct Literal from token, providing type hint to enforce on token
		static Literal construct(const Token & token, type_t type_hint);
	};
}


