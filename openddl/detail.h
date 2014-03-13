//================================================================================================================
// Copyright 2014 Denis Hilliard (armchaircommando@gmail.com)
// Licensed under MIT License
//================================================================================================================
#pragma once
#include <vector>
#include <iostream>
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

			bool is_float_encoded() const;
			bool is_integer_encoded() const;
			bool is_data_type() const;

			token_t		token_type;

			std::string payload;

			unsigned int range_start;
			unsigned int range_length;

			unsigned int line;

		};
		inline bool has_intervening_whitespace(const Token & a, const Token & b) { return (a.range_start + a.range_length) != b.range_start; }
		struct Error
		{

			std::string payload;				//The literal (as string) which caused the error
			std::string message;				//Plain text key describing error		

			unsigned int range_start;			//Position of offset of offending literal in string
			unsigned int range_length;
		};

		//Will only return false if an internal error has occurred and not all input was consumed.
		bool lex(const std::string & input, std::vector<Token> &tokens, std::vector<Error> & errors);
		//Will only return false if an internal error has occurred and not all input was consumed.
		bool parse(const std::vector<Token> & tokens, std::vector<Error> & errors);


		struct LexerContext
		{
			std::vector<Error> & errors;
			std::vector<Token> & tokens;
			const std::string & input;
		private:
			int line;
			char const * line_start;
			int characters_consumed;

		public:
			LexerContext(const std::string & _i, std::vector<Token> & _t, std::vector<Error> & _e);

			void reset_count() { characters_consumed = 0; }
			void count_character() { characters_consumed++; }
			int get_character_count() { return characters_consumed; }

			void new_line(const char * p);

			void lex_error(const std::string & name, unsigned int ts, unsigned int te);
			void lex_error(const std::string & name, unsigned int ts, char const* te);
			void lex_error(const std::string & name, char const* ts, unsigned int te);
			void lex_error(const std::string & name, const char * ts, const char* te);

			void lex_emit(Token::token_t t_type, const char* ts, const char* te);
		};
	}


};



