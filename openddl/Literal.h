//================================================================================================================
// Copyright 2014 Denis Hilliard (armchaircommando@gmail.com)
// Licensed under MIT License
//================================================================================================================
#pragma once
#include <cstdint>
#include <type_traits>
#include <stdexcept>

namespace openddl
{
	struct Token;
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
			else throw type_error("Type Conversion Error");
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
			else throw type_error("Type Conversion Error");
		}
		template <typename T>
		const typename std::enable_if<std::is_floating_point<T>::value, T>::type get()
		{
			if (type == kFloat)
			{
				T value;
				if (lexical_encoding)
					value = (T)u_.d_value;
				else
					value = negate ? -*reinterpret_cast<T*>(&u_.i_value) : *reinterpret_cast<T*>(&u_.i_value);

				if (value <= std::numeric_limits<T>::max() || value == std::numeric_limits<T>::infinity())
					if (value >= -std::numeric_limits<T>::max() || value == -std::numeric_limits<T>::infinity())
						return value;
					else
						throw type_error("Underflow");
				else
					throw type_error("Overflow");
			}
			else throw type_error("Type Conversion Error");
		}
		
		Literal(Literal && l);

		~Literal();

	private:
		Literal();
		type_t type;
		union _storage 
		{ 
			std::string * s_value; 
			bool b_value; 
			uint64_t i_value; 
			double d_value;
		};
		_storage u_;
		bool negate;
		bool lexical_encoding;
	public:
		//Construct Numeric Literal from token, providing type hint to enforce on token
		static Literal construct(const Token & token, type_t type_hint);

	};
}


