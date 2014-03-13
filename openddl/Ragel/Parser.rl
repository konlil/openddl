#include "detail.h"
#include <iostream>

using namespace openddl::detail;

%%{
	
	machine Parser;
	getkey fpc->token_type;
	write data;

	action on_data_list{
		std::cout << "Got data list" << std::endl;
	}
	action on_string_list_error{}
	action on_float_list_error{
		std::cout << "Float list error" << std::endl;
		if((p-1)->token_type != Token::kComma) std::cout << "Syntax Error: missing comma" << std::endl;
		else if((p-1)->token_type == Token::kComma && (p-2)->is_float_encoded()) std::cout << "Syntax Error: type mismatch" << std::endl;
	}
	action on_integer_list_error{}
	action on_bool_list_error{}
	action on_reference_list_error{}
	action on_type_list_error{}
	action on_expected_name{
		std::cout << "Syntax Error: Expected Name" << std::endl;
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
	reference = w_null | w_identifier+;
	data_type = t_integer | t_float | t_ref | t_string | t_bool | t_type;
	
	boolean_list = boolean_literal (s_comma boolean_literal)* $!on_bool_list_error;
	integer_list = integer_literal (s_comma integer_literal)* $!on_integer_list_error;
	float_list = float_literal (s_comma float_literal)* $!on_float_list_error;
	string_list = string_literal (s_comma string_literal)* $!on_string_list_error;
	reference_list = reference (s_comma reference)* $!on_reference_list_error;
	data_type_list = data_type (s_comma data_type)* $!on_reference_list_error;

	data_list = (boolean_list | integer_list | float_list | string_list | reference_list | data_type_list);

	
	dlist = data_type (w_name? $!on_expected_name) s_lbrace data_list s_rbrace @on_data_list;
	main :=  dlist;
	
}%%

bool openddl::detail::parse(const std::vector<Token> & tokens, std::vector<Error> & errors)
{
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
	return p==pe;
}