#include "ParserContext.h"

using namespace openddl::detail;


%%{
	
	machine Parser;
	getkey fpc->token_type;
	write data;

	action on_integer_literal{
		context.push_literal(p,Command::LiteralPayload::encoding_t::kInteger);
	}
	action on_float_literal{
		context.push_literal(p,Command::LiteralPayload::encoding_t::kFloat);
	}
	action on_bool_literal{
		context.push_literal(p,Command::LiteralPayload::encoding_t::kBoolean);
	}
	action on_string_literal{
		context.push_literal(p,Command::LiteralPayload::encoding_t::kString);
	}
	action on_type_literal{
		context.push_literal(p,Command::LiteralPayload::encoding_t::kType);
	}
	action build_reference{
		context.build_reference(p);
	}
	action on_reference_literal{
		context.push_reference();
	}

	action on_data_list_start{
		context.push_data_list(p);
	}
	action on_data_list_end{
		context.end_data_list();
	}
	
	s_lsquare = 1;
	s_rsquare = 2;
	s_comma = 3;
	s_lbrace = 4;
	s_rbrace = 5;
	s_equals = 6;
	w_identifier = 7;
	w_name = 8;
	w_null = 9;
	
	l_bool = 10;
	l_float = 11;
	l_hex = 12;
	l_decimal = 13;
	l_binary = 14;
	l_string = 15;
	l_character = 16;

	t_float = 17..18;
	t_integer = 19..26;

	t_ref = 27;
	t_bool = 28;
	t_string = 29;
	t_type = 30;
	

	#Literal rules
	boolean_literal = l_bool;
	integer_literal = l_character | l_hex | l_decimal | l_binary;
	float_literal = l_float | l_decimal | l_hex | l_binary;
	string_literal = l_string;
	reference = (w_null | w_name+) $build_reference %on_reference_literal;
	data_type = t_integer | t_float | t_ref | t_string | t_bool | t_type;
	
	boolean_list = (boolean_literal (s_comma boolean_literal)*) @on_bool_literal;
	integer_list = (integer_literal (s_comma integer_literal)*) @on_integer_literal;
	float_list = (float_literal (s_comma float_literal)*) @on_float_literal;
	string_list = (string_literal (s_comma string_literal)*) @on_string_literal;
	reference_list = (reference (s_comma reference)*);
	data_type_list = (data_type (s_comma data_type)*) @on_type_literal;

	float_literal_list = t_float w_name? s_lbrace float_list s_rbrace;
	integer_literal_list = t_integer w_name? s_lbrace integer_list s_rbrace;
	boolean_literal_list = t_bool w_name? s_lbrace boolean_list s_rbrace;
	string_literal_list = t_string w_name? s_lbrace string_list s_rbrace;
	reference_literal_list = t_ref w_name? s_lbrace reference_list s_rbrace;
	data_type_literal_list = t_type w_name? s_lbrace data_type_list s_rbrace;

	data_list = (float_literal_list | integer_literal_list | boolean_literal_list | string_literal_list | reference_literal_list | data_type_literal_list) >on_data_list_start @on_data_list_end;

	array_data_type = data_type s_lsquare integer_literal s_rsquare;

	#data_array_list = array_data_type (w_name? $!on_expected_name) s_lbrace element_list (s_comma element_list)* s_rbrace @on_data_array_list;
	main := data_list*;
	
}%%

bool openddl::detail::parse(const std::vector<Token> & tokens, std::vector<Command> & commands, std::vector<Error> & errors)
{
	ParserContext context(tokens,commands,errors);
	Token const *p = tokens.data();

	//End
	Token const *pe = p + tokens.size();
	Token const *eof = pe;

	//State
	int cs = 0, act, have = 0;
	Token const *ts = 0; 
	Token const *te = 0;
	int done = 0;

	
	%% write init;
	%% write exec;
	return p==pe && errors.empty();
}