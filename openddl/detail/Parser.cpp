
#line 1 "C:/Users/Denis/Development/openddl/openddl/detail/Ragel/Parser.rl"
#include "ParserContext.h"

using namespace openddl::detail;



#line 7 "detail/Parser.cpp"
static const char _Parser_actions[] = {
	0, 1, 0, 1, 1, 1, 2, 1, 
	3, 1, 4, 1, 5, 1, 6, 1, 
	7, 1, 8, 2, 6, 8
};

static const char _Parser_key_offsets[] = {
	0, 0, 2, 4, 6, 7, 9, 12, 
	14, 15, 17, 19, 22, 24, 25, 27, 
	28, 30, 31, 33, 34, 36, 37, 39, 
	41, 43, 44
};

static const char _Parser_trans_keys[] = {
	4, 8, 11, 14, 3, 5, 4, 4, 
	8, 16, 12, 14, 3, 5, 4, 4, 
	8, 8, 9, 3, 5, 8, 3, 5, 
	4, 4, 8, 10, 3, 5, 4, 4, 
	8, 15, 3, 5, 4, 4, 8, 17, 
	30, 3, 5, 4, 27, 28, 29, 30, 
	17, 18, 19, 26, 0
};

static const char _Parser_single_lengths[] = {
	0, 2, 0, 2, 1, 2, 1, 2, 
	1, 2, 2, 3, 2, 1, 2, 1, 
	2, 1, 2, 1, 2, 1, 2, 0, 
	2, 1, 4
};

static const char _Parser_range_lengths[] = {
	0, 0, 1, 0, 0, 0, 1, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 1, 
	0, 0, 2
};

static const char _Parser_index_offsets[] = {
	0, 0, 3, 5, 8, 10, 13, 16, 
	19, 21, 24, 27, 31, 34, 36, 39, 
	41, 44, 46, 49, 51, 54, 56, 59, 
	61, 64, 66
};

static const char _Parser_indicies[] = {
	0, 2, 1, 3, 1, 0, 4, 1, 
	0, 1, 5, 6, 1, 7, 7, 1, 
	5, 4, 1, 5, 1, 8, 9, 1, 
	10, 11, 1, 12, 13, 10, 1, 12, 
	13, 1, 8, 1, 14, 15, 1, 16, 
	1, 14, 4, 1, 14, 1, 17, 18, 
	1, 19, 1, 17, 4, 1, 17, 1, 
	20, 21, 1, 22, 1, 20, 4, 1, 
	20, 1, 25, 26, 27, 28, 23, 24, 
	1, 0
};

static const char _Parser_trans_targs[] = {
	2, 0, 4, 3, 26, 6, 8, 7, 
	10, 13, 11, 12, 10, 26, 15, 17, 
	16, 19, 21, 20, 23, 25, 24, 1, 
	5, 9, 14, 18, 22
};

static const char _Parser_trans_actions[] = {
	0, 0, 0, 3, 17, 0, 0, 1, 
	0, 0, 11, 11, 13, 19, 0, 0, 
	5, 0, 0, 7, 0, 0, 9, 15, 
	15, 15, 15, 15, 15
};

static const int Parser_start = 26;
static const int Parser_first_final = 26;
static const int Parser_error = 0;

static const int Parser_en_main = 26;


#line 97 "C:/Users/Denis/Development/openddl/openddl/detail/Ragel/Parser.rl"


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

	
	
#line 102 "detail/Parser.cpp"
	{
	cs = Parser_start;
	}

#line 116 "C:/Users/Denis/Development/openddl/openddl/detail/Ragel/Parser.rl"
	
#line 105 "detail/Parser.cpp"
	{
	int _klen;
	unsigned int _trans;
	const char *_acts;
	unsigned int _nacts;
	const char *_keys;

	if ( p == pe )
		goto _test_eof;
	if ( cs == 0 )
		goto _out;
_resume:
	_keys = _Parser_trans_keys + _Parser_key_offsets[cs];
	_trans = _Parser_index_offsets[cs];

	_klen = _Parser_single_lengths[cs];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + _klen - 1;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + ((_upper-_lower) >> 1);
			if ( ( p->token_type) < *_mid )
				_upper = _mid - 1;
			else if ( ( p->token_type) > *_mid )
				_lower = _mid + 1;
			else {
				_trans += (unsigned int)(_mid - _keys);
				goto _match;
			}
		}
		_keys += _klen;
		_trans += _klen;
	}

	_klen = _Parser_range_lengths[cs];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + (_klen<<1) - 2;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + (((_upper-_lower) >> 1) & ~1);
			if ( ( p->token_type) < _mid[0] )
				_upper = _mid - 2;
			else if ( ( p->token_type) > _mid[1] )
				_lower = _mid + 2;
			else {
				_trans += (unsigned int)((_mid - _keys)>>1);
				goto _match;
			}
		}
		_trans += _klen;
	}

_match:
	_trans = _Parser_indicies[_trans];
	cs = _Parser_trans_targs[_trans];

	if ( _Parser_trans_actions[_trans] == 0 )
		goto _again;

	_acts = _Parser_actions + _Parser_trans_actions[_trans];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 )
	{
		switch ( *_acts++ )
		{
	case 0:
#line 12 "C:/Users/Denis/Development/openddl/openddl/detail/Ragel/Parser.rl"
	{
		context.push_literal(p,Command::LiteralPayload::encoding_t::kInteger);
	}
	break;
	case 1:
#line 15 "C:/Users/Denis/Development/openddl/openddl/detail/Ragel/Parser.rl"
	{
		context.push_literal(p,Command::LiteralPayload::encoding_t::kFloat);
	}
	break;
	case 2:
#line 18 "C:/Users/Denis/Development/openddl/openddl/detail/Ragel/Parser.rl"
	{
		context.push_literal(p,Command::LiteralPayload::encoding_t::kBoolean);
	}
	break;
	case 3:
#line 21 "C:/Users/Denis/Development/openddl/openddl/detail/Ragel/Parser.rl"
	{
		context.push_literal(p,Command::LiteralPayload::encoding_t::kString);
	}
	break;
	case 4:
#line 24 "C:/Users/Denis/Development/openddl/openddl/detail/Ragel/Parser.rl"
	{
		context.push_literal(p,Command::LiteralPayload::encoding_t::kType);
	}
	break;
	case 5:
#line 27 "C:/Users/Denis/Development/openddl/openddl/detail/Ragel/Parser.rl"
	{
		context.build_reference(p);
	}
	break;
	case 6:
#line 30 "C:/Users/Denis/Development/openddl/openddl/detail/Ragel/Parser.rl"
	{
		context.push_reference();
	}
	break;
	case 7:
#line 34 "C:/Users/Denis/Development/openddl/openddl/detail/Ragel/Parser.rl"
	{
		context.push_data_list(p);
	}
	break;
	case 8:
#line 37 "C:/Users/Denis/Development/openddl/openddl/detail/Ragel/Parser.rl"
	{
		context.end_data_list();
	}
	break;
#line 223 "detail/Parser.cpp"
		}
	}

_again:
	if ( cs == 0 )
		goto _out;
	if ( ++p != pe )
		goto _resume;
	_test_eof: {}
	_out: {}
	}

#line 117 "C:/Users/Denis/Development/openddl/openddl/detail/Ragel/Parser.rl"
	return p==pe && errors.empty();
}