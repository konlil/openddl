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
		template <typename T> const T & get();
		template <> const std::string & get<std::string>() 
		{ 
			if (type == kString) return *(u_.s_value); 
			else throw type_error("Type Conversion Error"); 
		}
		template <> const bool & get<bool>() 
		{ 
			if (type == kBoolean) return u_.b_value; 
			else throw type_error("Type Conversion Error"); 
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
		typename std::enable_if<is_signed_integer<T>::value, T>::type get()
		{
			if (type == kInteger)
			{
				if (negate && u_.i_value > abs(std::numeric_limits<T>::min())) throw type_error("Underflow");
				if (!negate && u_.i_value > std::numeric_limits<T>::max()) throw type_error("Overflow");
				return negate ? -u_.i_value : u_.i_value;
			}
			else throw type_error("Type Conversion Error");
		}
		template <typename T>
		typename std::enable_if<is_unsigned_integer<T>::value, T>::type get()
		{
			if (type == kInteger)
			{
				if (negate) throw type_error("Underflow");
				if (u_.i_value > std::numeric_limits<T>::max()) throw type_error("Overflow");
				return u_.i_value;
			}
			else throw type_error("Type Conversion Error");
		}
		
		Literal();
		Literal(Literal && l);
		~Literal();

		bool is_type(type_t t) { return t == type; }
	private:
		type_t type;
		union _storage { std::string * s_value; bool b_value; uint64_t i_value; };
		_storage u_;
		bool negate;
	public:
		//Construct Literal from token stream, providing type hint to enforce on tokens
		//Will advance position past consumed tokens.
		static Literal construct(std::vector<Token> & tokens, int & position, type_t type_hint);
	};
}


