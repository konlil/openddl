#include "ParserContext.h"

using namespace openddl::detail;


%%{
	
	machine Parser;
	getkey fpc->token_type;
	write data;
	
	action end_of_file {
		Error e;
		e.message = "parse.unexpected_end_of_file";
		errors.push_back(e);
	}
	action data_list_error{
		if(p!=pe)
		{

			Error e;
			if(p->token_type == (p-1)->token_type)
				e.message = "parse.data_list.missing_comma";
			else if((p-1)->token_type == Token::kComma && (p-2)->token_type != p->token_type)
				e.message = "semantic.literal.type_mismatch";
			else
				e.message = "parse.panic.unknown_error";
			errors.push_back(e);
		}
		
	}

	left_square = 1;
	right_square = 2;
	comma = 3;
	left_brace = 4;
	right_brace = 5;
	equals = 6;
	identifier = 7;
	local_name = 8;
	global_name = 9;
	null_name = 10;


	float_type = 18..19;
	integer_type = 20..27;

	ref_type = 28;
	bool_type = 29;
	string_type = 30;
	type_type = 31;
	

	#Literal rules
	boolean_literal = 11;
	integer_literal = 17 | 13 | 14 | 15;
	float_literal = 12 | 14 | 13 | 15;
	string_literal = 16;
	data_type = integer_type | float_type | ref_type | string_type | bool_type | type_type;
	
	
	name = global_name | local_name;
	reference = null_name | local_name+ | global_name (local_name)*;

	literal = boolean_literal | integer_literal | float_literal | string_literal | data_type | reference;

	property = identifier equals (boolean_literal|integer_literal|float_literal|string_literal|reference|data_type);

	array_notation = data_type left_square integer_literal right_square;

	literal_sequence := |*
		(left_brace boolean_literal (comma boolean_literal)* right_brace) => {context.push_literal_list(Command::LiteralPayload::kBoolean,ts,te); fret;};
		(left_brace float_literal (comma float_literal)* right_brace) => {context.push_literal_list(Command::LiteralPayload::kFloat,ts,te); fret;};
		(left_brace integer_literal (comma integer_literal)* right_brace) => {context.push_literal_list(Command::LiteralPayload::kInteger,ts,te); fret;};
		
		(left_brace string_literal (comma string_literal)* right_brace) => {context.push_literal_list(Command::LiteralPayload::kString,ts,te); fret;};
		(left_brace reference (comma reference)* right_brace) => {context.push_literal_list(Command::LiteralPayload::kReference,ts,te); fret;};
		(left_brace data_type (comma data_type)* right_brace) => {context.push_literal_list(Command::LiteralPayload::kType,ts,te); fret;};

		left_brace => {Error e; e.message = "parse.unexpected_end_of_file"; errors.push_back(e);};
		left_brace literal (comma literal)* literal => {Error e; e.message = "parse.data_list.missing_comma"; errors.push_back(e);};
		left_brace literal (comma literal)* right_brace => {Error e; e.message = "semantic.literal.type_mismatch"; errors.push_back(e);};
	*|;
	data_array := |*
		left_brace => { context.push_array_element(); fhold; fcall literal_sequence;};
		comma;	
		right_brace => { context.end_array(); fret;};
		
	*|;
	structure_property_list := |* 
		property (comma|right_brace) => { context.push_property(ts,te-1); fhold;};
		comma;
		right_brace => { fhold; fgoto structure;};
		right_brace left_brace => {fgoto structure;};
		(data_type | identifier) => {fhold; fgoto structure;};
		left_brace right_brace left_brace => { fgoto structure;};
		left_brace;
	*|;
	structure := |*	
		data_type name? left_brace => { 
			if((te-ts)==3)
				context.push_list_type(ts,ts+1);
			else if((te-ts)==2)
				context.push_list_type(ts);
			fhold; fcall literal_sequence; 
		};
		array_notation name? left_brace => {
			if((te-ts)==6)
				context.push_array_type(ts,ts+2,ts+4);
			else if((te-ts)==5)
				context.push_array_type(ts,ts+2);
			fcall data_array;
		};
		identifier name? left_brace=> { 
				if((te-ts) == 3)
					context.push_structure(ts,ts+1); 
				else if((te-ts)==2)
					context.push_structure(ts);
				fcall structure_property_list;
				};
		right_brace => {
			 context.end_structure(); if( top!=0) {fret;}
		};
	*|;
	
}%%

bool openddl::detail::parse(const std::vector<Token> & tokens, std::vector<Command> & commands, std::vector<Error> & errors)
{
	ParserContext context(tokens,commands,errors);
	Token const *p = tokens.data();

	//End
	Token const *pe = p + tokens.size();
	Token const *eof = pe;

	//State
	int cs = 0, act,have = 0;
	int top;
	int stack[32];

	int done = 0;

	Token const *ts;
	Token const *te;
	
	%% write init;
	%% write exec;
	if(top != 0)
	{
		Error e;
		e.message = "parse.unexpected_end_of_file";
		errors.push_back(e);
	}
	return p == pe && errors.size() == 0;
}