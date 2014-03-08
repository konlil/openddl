
#line 1 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
//================================================================================================================
// Copyright 2014 Denis Hilliard (armchaircommando@gmail.com)
// Licensed under MIT License
//================================================================================================================

#include "stdafx.h"
#include "Lexer.h"
#include <sstream>

void lex_error(const std::string & name, std::vector<openddl::TokenError> & errors, const char* p, const char * ts, const char* te, int line,int position)
{
	std::stringstream formatter;
	formatter <<"("<< line << ":" << position << ")";
	openddl::TokenError error;
	error.payload = std::string(ts,te);
	error.message = name; 
	error.position = formatter.str();
	error.range_start = unsigned int(ts-p);
	error.range_length = te - ts;
	errors.push_back(error);
}

void lex_emit(openddl::Token::type_t code, std::vector<openddl::Token>& tokens, const char* p, const char* ts, const char* te)
{

	if(code == openddl::Token::kString && tokens.size() && tokens.back().code == openddl::Token::kString)
	{
		//Concatenate two string literals if they are adjacent without intervening comma
		openddl::Token & t = tokens.back();
		t.payload = t.payload.substr(0,t.payload.length()-1) + std::string(ts+1,te);
		t.range_length = (te-p)-t.range_start;
	}
	else
	{

		//Create token on token stack
		openddl::Token t;
		t.code = code;

		t.payload = std::string(ts,te);

		t.range_start = unsigned int(ts-p);
		t.range_length = te - ts;

		tokens.push_back(t);
	}

}

#define e(t) lex_emit(t, tokens,input.c_str(), ts, te)
#define error(m) lex_error(m, errors,input.c_str(),ts,te,curline,ts-line_start)


#line 54 ".\\Lexer.cpp"
static const char _Lexer_actions[] = {
	0, 1, 0, 1, 1, 1, 2, 1, 
	3, 1, 4, 1, 5, 1, 6, 1, 
	7, 1, 8, 1, 9, 1, 10, 1, 
	17, 1, 18, 1, 20, 1, 21, 1, 
	22, 1, 23, 1, 24, 1, 25, 1, 
	26, 1, 27, 1, 28, 1, 29, 1, 
	30, 1, 31, 1, 32, 1, 33, 1, 
	34, 1, 35, 1, 37, 1, 38, 1, 
	39, 1, 40, 1, 41, 1, 42, 1, 
	43, 2, 3, 36, 2, 5, 19, 2, 
	6, 19, 2, 10, 11, 2, 10, 12, 
	2, 10, 13, 2, 10, 14, 2, 10, 
	15, 2, 10, 16
};

static const short _Lexer_key_offsets[] = {
	0, 0, 2, 16, 18, 20, 22, 24, 
	27, 29, 31, 45, 51, 57, 63, 69, 
	75, 81, 88, 92, 104, 108, 114, 120, 
	122, 125, 128, 131, 134, 140, 145, 149, 
	150, 162, 166, 172, 178, 181, 188, 191, 
	193, 196, 202, 209, 210, 211, 212, 213, 
	244, 244, 258, 271, 278, 286, 294, 302, 
	310, 318, 326, 334, 342, 350, 358, 366, 
	374, 382, 390, 401, 409, 417, 425, 433, 
	441, 449, 457, 465, 473, 481, 489, 497, 
	505, 513, 521, 529, 537, 545, 553, 560, 
	568, 573, 574, 578, 587, 592, 601, 608, 
	622, 629, 639, 646, 657, 659, 661, 662, 
	669, 677, 685, 693, 701, 709, 717, 725, 
	733, 741, 750, 758, 766, 774, 782, 790, 
	798, 806, 814, 825, 833, 841, 849, 857, 
	865, 873, 881, 889, 897, 905, 914, 922, 
	930, 938, 946, 954, 962, 970, 978, 986, 
	993, 1001, 1001
};

static const char _Lexer_trans_keys[] = {
	-96, -65, -62, -32, -19, -17, 34, 92, 
	-61, -33, -31, -18, -16, -12, 32, 126, 
	-128, -65, -96, -65, -128, -65, -128, -97, 
	-65, -128, -66, -128, -67, -112, -65, 34, 
	39, 63, 85, 92, 102, 110, 114, 117, 
	120, 97, 98, 116, 118, 48, 57, 65, 
	70, 97, 102, 48, 57, 65, 70, 97, 
	102, 48, 57, 65, 70, 97, 102, 48, 
	57, 65, 70, 97, 102, 48, 57, 65, 
	70, 97, 102, 48, 57, 65, 70, 97, 
	102, 95, 48, 57, 65, 90, 97, 122, 
	39, 92, 32, 126, 34, 39, 63, 92, 
	102, 110, 114, 116, 118, 120, 97, 98, 
	39, 92, 32, 126, 48, 57, 65, 70, 
	97, 102, 48, 57, 65, 70, 97, 102, 
	48, 57, 10, 42, 47, 10, 42, 47, 
	10, 42, 47, 10, 42, 47, 39, 43, 
	45, 48, 49, 57, 92, 32, 38, 40, 
	126, 39, 92, 32, 126, 93, 34, 39, 
	63, 92, 102, 110, 114, 116, 118, 120, 
	97, 98, 39, 92, 32, 126, 48, 57, 
	65, 70, 97, 102, 48, 57, 65, 70, 
	97, 102, 48, 49, 57, 66, 88, 93, 
	98, 120, 48, 57, 93, 48, 57, 48, 
	49, 93, 48, 49, 48, 57, 65, 70, 
	97, 102, 93, 48, 57, 65, 70, 97, 
	102, 39, 39, 34, 34, 10, 34, 39, 
	42, 44, 46, 47, 48, 95, 98, 100, 
	102, 105, 114, 115, 116, 117, 123, 125, 
	1, 32, 36, 37, 43, 45, 49, 57, 
	65, 90, 97, 122, -62, -32, -19, -17, 
	34, 92, -61, -33, -31, -18, -16, -12, 
	32, 126, 95, 98, 100, 102, 105, 114, 
	115, 116, 117, 65, 90, 97, 122, 95, 
	48, 57, 65, 90, 97, 122, 95, 111, 
	48, 57, 65, 90, 97, 122, 95, 111, 
	48, 57, 65, 90, 97, 122, 95, 108, 
	48, 57, 65, 90, 97, 122, 95, 111, 
	48, 57, 65, 90, 97, 122, 95, 117, 
	48, 57, 65, 90, 97, 122, 95, 98, 
	48, 57, 65, 90, 97, 122, 95, 108, 
	48, 57, 65, 90, 97, 122, 95, 101, 
	48, 57, 65, 90, 97, 122, 95, 108, 
	48, 57, 65, 90, 97, 122, 95, 111, 
	48, 57, 65, 90, 97, 122, 95, 97, 
	48, 57, 65, 90, 98, 122, 95, 116, 
	48, 57, 65, 90, 97, 122, 95, 110, 
	48, 57, 65, 90, 97, 122, 95, 116, 
	48, 57, 65, 90, 97, 122, 49, 51, 
	54, 56, 95, 48, 57, 65, 90, 97, 
	122, 54, 95, 48, 57, 65, 90, 97, 
	122, 50, 95, 48, 57, 65, 90, 97, 
	122, 52, 95, 48, 57, 65, 90, 97, 
	122, 95, 101, 48, 57, 65, 90, 97, 
	122, 95, 102, 48, 57, 65, 90, 97, 
	122, 95, 116, 48, 57, 65, 90, 97, 
	122, 95, 114, 48, 57, 65, 90, 97, 
	122, 95, 105, 48, 57, 65, 90, 97, 
	122, 95, 110, 48, 57, 65, 90, 97, 
	122, 95, 103, 48, 57, 65, 90, 97, 
	122, 95, 121, 48, 57, 65, 90, 97, 
	122, 95, 112, 48, 57, 65, 90, 97, 
	122, 95, 110, 48, 57, 65, 90, 97, 
	122, 95, 115, 48, 57, 65, 90, 97, 
	122, 95, 105, 48, 57, 65, 90, 97, 
	122, 95, 103, 48, 57, 65, 90, 97, 
	122, 95, 110, 48, 57, 65, 90, 97, 
	122, 95, 101, 48, 57, 65, 90, 97, 
	122, 95, 100, 48, 57, 65, 90, 97, 
	122, 95, 48, 57, 65, 90, 97, 122, 
	95, 105, 48, 57, 65, 90, 97, 122, 
	92, 32, 38, 40, 126, 47, 46, 48, 
	49, 57, 44, 69, 101, 123, 125, 1, 
	32, 48, 57, 44, 123, 125, 1, 32, 
	44, 123, 125, 1, 32, 43, 45, 48, 
	57, 44, 123, 125, 1, 32, 48, 57, 
	44, 46, 66, 69, 88, 98, 101, 120, 
	123, 125, 1, 32, 48, 57, 44, 123, 
	125, 1, 32, 48, 57, 44, 46, 69, 
	101, 123, 125, 1, 32, 48, 57, 44, 
	123, 125, 1, 32, 48, 49, 44, 123, 
	125, 1, 32, 48, 57, 65, 70, 97, 
	102, 48, 57, 42, 47, 10, 95, 48, 
	57, 65, 90, 97, 122, 95, 111, 48, 
	57, 65, 90, 97, 122, 95, 111, 48, 
	57, 65, 90, 97, 122, 95, 108, 48, 
	57, 65, 90, 97, 122, 91, 95, 48, 
	57, 65, 90, 97, 122, 95, 111, 48, 
	57, 65, 90, 97, 122, 95, 117, 48, 
	57, 65, 90, 97, 122, 95, 98, 48, 
	57, 65, 90, 97, 122, 95, 108, 48, 
	57, 65, 90, 97, 122, 95, 101, 48, 
	57, 65, 90, 97, 122, 95, 97, 108, 
	48, 57, 65, 90, 98, 122, 95, 108, 
	48, 57, 65, 90, 97, 122, 95, 115, 
	48, 57, 65, 90, 97, 122, 95, 101, 
	48, 57, 65, 90, 97, 122, 95, 111, 
	48, 57, 65, 90, 97, 122, 95, 97, 
	48, 57, 65, 90, 98, 122, 95, 116, 
	48, 57, 65, 90, 97, 122, 95, 110, 
	48, 57, 65, 90, 97, 122, 95, 116, 
	48, 57, 65, 90, 97, 122, 49, 51, 
	54, 56, 95, 48, 57, 65, 90, 97, 
	122, 54, 95, 48, 57, 65, 90, 97, 
	122, 50, 95, 48, 57, 65, 90, 97, 
	122, 52, 95, 48, 57, 65, 90, 97, 
	122, 95, 101, 48, 57, 65, 90, 97, 
	122, 95, 102, 48, 57, 65, 90, 97, 
	122, 95, 116, 48, 57, 65, 90, 97, 
	122, 95, 114, 48, 57, 65, 90, 97, 
	122, 95, 105, 48, 57, 65, 90, 97, 
	122, 95, 110, 48, 57, 65, 90, 97, 
	122, 95, 103, 48, 57, 65, 90, 97, 
	122, 95, 114, 121, 48, 57, 65, 90, 
	97, 122, 95, 117, 48, 57, 65, 90, 
	97, 122, 95, 112, 48, 57, 65, 90, 
	97, 122, 95, 110, 48, 57, 65, 90, 
	97, 122, 95, 115, 48, 57, 65, 90, 
	97, 122, 95, 105, 48, 57, 65, 90, 
	97, 122, 95, 103, 48, 57, 65, 90, 
	97, 122, 95, 110, 48, 57, 65, 90, 
	97, 122, 95, 101, 48, 57, 65, 90, 
	97, 122, 95, 100, 48, 57, 65, 90, 
	97, 122, 95, 48, 57, 65, 90, 97, 
	122, 95, 105, 48, 57, 65, 90, 97, 
	122, 0
};

static const char _Lexer_single_lengths[] = {
	0, 0, 6, 0, 0, 0, 0, 1, 
	0, 0, 10, 0, 0, 0, 0, 0, 
	0, 1, 2, 10, 2, 0, 0, 0, 
	3, 3, 3, 3, 4, 1, 2, 1, 
	10, 2, 0, 0, 1, 5, 1, 0, 
	1, 0, 1, 1, 1, 1, 1, 19, 
	0, 6, 9, 1, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 5, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 1, 2, 
	1, 1, 2, 5, 3, 3, 3, 10, 
	3, 6, 3, 3, 0, 2, 1, 1, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 3, 2, 2, 2, 2, 2, 2, 
	2, 2, 5, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 3, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 1, 
	2, 0, 0
};

static const char _Lexer_range_lengths[] = {
	0, 1, 4, 1, 1, 1, 1, 1, 
	1, 1, 2, 3, 3, 3, 3, 3, 
	3, 3, 1, 1, 1, 3, 3, 1, 
	0, 0, 0, 0, 1, 2, 1, 0, 
	1, 1, 3, 3, 1, 1, 1, 1, 
	1, 3, 3, 0, 0, 0, 0, 6, 
	0, 4, 2, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	2, 0, 1, 2, 1, 3, 2, 2, 
	2, 2, 2, 4, 1, 0, 0, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 0, 0
};

static const short _Lexer_index_offsets[] = {
	0, 0, 2, 13, 15, 17, 19, 21, 
	24, 26, 28, 41, 45, 49, 53, 57, 
	61, 65, 70, 74, 86, 90, 94, 98, 
	100, 104, 108, 112, 116, 122, 126, 130, 
	132, 144, 148, 152, 156, 159, 166, 169, 
	171, 174, 178, 183, 185, 187, 189, 191, 
	217, 218, 229, 241, 246, 252, 258, 264, 
	270, 276, 282, 288, 294, 300, 306, 312, 
	318, 324, 330, 339, 345, 351, 357, 363, 
	369, 375, 381, 387, 393, 399, 405, 411, 
	417, 423, 429, 435, 441, 447, 453, 458, 
	464, 468, 470, 474, 482, 487, 494, 500, 
	513, 519, 528, 534, 542, 544, 547, 549, 
	554, 560, 566, 572, 578, 584, 590, 596, 
	602, 608, 615, 621, 627, 633, 639, 645, 
	651, 657, 663, 672, 678, 684, 690, 696, 
	702, 708, 714, 720, 726, 732, 739, 745, 
	751, 757, 763, 769, 775, 781, 787, 793, 
	798, 804, 805
};

static const unsigned char _Lexer_indicies[] = {
	1, 0, 2, 4, 6, 7, 9, 10, 
	3, 5, 8, 1, 0, 1, 0, 3, 
	0, 3, 0, 3, 0, 11, 3, 0, 
	1, 0, 5, 0, 1, 1, 1, 12, 
	1, 1, 1, 1, 13, 14, 1, 1, 
	0, 15, 15, 15, 0, 13, 13, 13, 
	0, 16, 16, 16, 0, 14, 14, 14, 
	0, 17, 17, 17, 0, 1, 1, 1, 
	0, 19, 19, 19, 19, 18, 22, 23, 
	21, 20, 24, 24, 24, 24, 24, 24, 
	24, 24, 24, 25, 24, 20, 27, 28, 
	26, 20, 29, 29, 29, 20, 24, 24, 
	24, 20, 31, 30, 33, 34, 35, 32, 
	37, 38, 39, 36, 33, 34, 40, 32, 
	33, 41, 35, 32, 43, 44, 44, 45, 
	46, 42, 48, 47, 47, 42, 50, 51, 
	49, 42, 52, 42, 53, 53, 53, 53, 
	53, 53, 53, 53, 53, 54, 53, 42, 
	56, 57, 55, 42, 58, 58, 58, 42, 
	53, 53, 53, 42, 45, 46, 42, 59, 
	60, 52, 59, 60, 46, 42, 52, 46, 
	42, 61, 42, 52, 61, 42, 62, 62, 
	62, 42, 52, 62, 62, 62, 42, 64, 
	63, 65, 63, 64, 66, 67, 66, 70, 
	71, 73, 74, 76, 77, 78, 79, 81, 
	82, 83, 84, 85, 86, 87, 88, 89, 
	90, 91, 69, 72, 75, 80, 81, 81, 
	68, 92, 2, 4, 6, 7, 9, 10, 
	3, 5, 8, 1, 93, 19, 95, 96, 
	97, 98, 99, 100, 101, 102, 19, 19, 
	94, 19, 19, 19, 19, 103, 19, 104, 
	19, 19, 19, 103, 19, 105, 19, 19, 
	19, 103, 19, 106, 19, 19, 19, 103, 
	19, 107, 19, 19, 19, 103, 19, 108, 
	19, 19, 19, 103, 19, 109, 19, 19, 
	19, 103, 19, 110, 19, 19, 19, 103, 
	19, 106, 19, 19, 19, 103, 19, 111, 
	19, 19, 19, 103, 19, 112, 19, 19, 
	19, 103, 19, 113, 19, 19, 19, 103, 
	19, 106, 19, 19, 19, 103, 19, 114, 
	19, 19, 19, 103, 19, 115, 19, 19, 
	19, 103, 116, 117, 118, 106, 19, 19, 
	19, 19, 103, 106, 19, 19, 19, 19, 
	103, 106, 19, 19, 19, 19, 103, 106, 
	19, 19, 19, 19, 103, 19, 119, 19, 
	19, 19, 103, 19, 106, 19, 19, 19, 
	103, 19, 120, 19, 19, 19, 103, 19, 
	121, 19, 19, 19, 103, 19, 122, 19, 
	19, 19, 103, 19, 123, 19, 19, 19, 
	103, 19, 106, 19, 19, 19, 103, 19, 
	124, 19, 19, 19, 103, 19, 110, 19, 
	19, 19, 103, 19, 125, 19, 19, 19, 
	103, 19, 126, 19, 19, 19, 103, 19, 
	127, 19, 19, 19, 103, 19, 128, 19, 
	19, 19, 103, 19, 129, 19, 19, 19, 
	103, 19, 130, 19, 19, 19, 103, 19, 
	131, 19, 19, 19, 103, 132, 19, 19, 
	19, 103, 19, 98, 19, 19, 19, 103, 
	135, 134, 134, 133, 136, 94, 137, 79, 
	80, 94, 138, 140, 140, 138, 138, 138, 
	31, 139, 141, 141, 141, 141, 139, 141, 
	141, 141, 141, 142, 143, 139, 144, 144, 
	144, 144, 143, 139, 145, 146, 147, 140, 
	148, 147, 140, 148, 145, 145, 145, 80, 
	139, 141, 141, 141, 141, 31, 139, 145, 
	146, 140, 140, 145, 145, 145, 80, 139, 
	144, 144, 144, 144, 149, 139, 144, 144, 
	144, 144, 150, 150, 150, 139, 31, 94, 
	32, 151, 94, 152, 151, 81, 81, 81, 
	81, 144, 81, 154, 81, 81, 81, 153, 
	81, 155, 81, 81, 81, 153, 81, 156, 
	81, 81, 81, 153, 158, 81, 81, 81, 
	81, 157, 81, 159, 81, 81, 81, 153, 
	81, 160, 81, 81, 81, 153, 81, 161, 
	81, 81, 81, 153, 81, 162, 81, 81, 
	81, 153, 81, 156, 81, 81, 81, 153, 
	81, 163, 164, 81, 81, 81, 153, 81, 
	165, 81, 81, 81, 153, 81, 166, 81, 
	81, 81, 153, 81, 167, 81, 81, 81, 
	153, 81, 168, 81, 81, 81, 153, 81, 
	169, 81, 81, 81, 153, 81, 156, 81, 
	81, 81, 153, 81, 170, 81, 81, 81, 
	153, 81, 171, 81, 81, 81, 153, 172, 
	173, 174, 156, 81, 81, 81, 81, 153, 
	156, 81, 81, 81, 81, 153, 156, 81, 
	81, 81, 81, 153, 156, 81, 81, 81, 
	81, 153, 81, 175, 81, 81, 81, 153, 
	81, 156, 81, 81, 81, 153, 81, 176, 
	81, 81, 81, 153, 81, 177, 81, 81, 
	81, 153, 81, 178, 81, 81, 81, 153, 
	81, 179, 81, 81, 81, 153, 81, 156, 
	81, 81, 81, 153, 81, 180, 181, 81, 
	81, 81, 153, 81, 166, 81, 81, 81, 
	153, 81, 162, 81, 81, 81, 153, 81, 
	182, 81, 81, 81, 153, 81, 183, 81, 
	81, 81, 153, 81, 184, 81, 81, 81, 
	153, 81, 185, 81, 81, 81, 153, 81, 
	186, 81, 81, 81, 153, 81, 187, 81, 
	81, 81, 153, 81, 188, 81, 81, 81, 
	153, 189, 81, 81, 81, 153, 81, 85, 
	81, 81, 81, 153, 64, 64, 0
};

static const unsigned char _Lexer_trans_targs[] = {
	47, 2, 1, 3, 4, 5, 6, 7, 
	9, 47, 10, 8, 11, 13, 15, 12, 
	14, 16, 47, 51, 47, 18, 47, 19, 
	20, 21, 18, 47, 19, 22, 47, 91, 
	24, 25, 26, 27, 24, 25, 26, 27, 
	47, 26, 47, 29, 36, 37, 38, 30, 
	32, 30, 31, 32, 47, 33, 34, 30, 
	31, 32, 35, 39, 41, 40, 42, 44, 
	0, 145, 46, 146, 47, 47, 48, 49, 
	50, 88, 89, 90, 47, 100, 101, 95, 
	97, 103, 104, 108, 113, 120, 126, 128, 
	133, 136, 47, 47, 47, 47, 47, 52, 
	55, 60, 64, 70, 72, 77, 79, 47, 
	53, 54, 17, 56, 57, 58, 59, 61, 
	62, 63, 65, 66, 67, 68, 69, 71, 
	73, 74, 75, 76, 78, 80, 81, 82, 
	83, 84, 85, 86, 87, 47, 18, 19, 
	47, 23, 47, 92, 93, 47, 94, 94, 
	47, 47, 96, 98, 99, 98, 99, 102, 
	47, 47, 105, 106, 107, 47, 28, 109, 
	110, 111, 112, 114, 117, 115, 116, 103, 
	118, 119, 121, 122, 123, 124, 125, 127, 
	129, 130, 131, 132, 134, 135, 137, 138, 
	139, 140, 141, 142, 143, 144
};

static const char _Lexer_trans_actions[] = {
	65, 0, 0, 0, 0, 0, 0, 0, 
	0, 25, 0, 0, 0, 0, 0, 0, 
	0, 0, 61, 0, 67, 11, 76, 11, 
	0, 0, 13, 79, 13, 0, 69, 0, 
	0, 0, 0, 0, 7, 7, 7, 7, 
	27, 9, 63, 0, 0, 0, 0, 15, 
	15, 11, 11, 11, 23, 0, 0, 13, 
	13, 13, 0, 0, 0, 0, 0, 0, 
	0, 1, 0, 1, 39, 37, 0, 21, 
	0, 21, 0, 21, 29, 0, 21, 0, 
	0, 97, 0, 0, 0, 0, 0, 0, 
	0, 0, 31, 33, 73, 53, 59, 0, 
	0, 0, 0, 0, 0, 0, 0, 49, 
	0, 21, 0, 0, 0, 0, 21, 0, 
	0, 21, 0, 21, 21, 21, 21, 21, 
	0, 0, 0, 21, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 55, 15, 15, 
	35, 0, 43, 0, 0, 45, 91, 88, 
	71, 41, 0, 91, 91, 85, 82, 0, 
	57, 47, 0, 0, 21, 51, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 94, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0
};

static const char _Lexer_to_state_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 17, 0, 17, 0, 17, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0
};

static const char _Lexer_from_state_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 19, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0
};

static const char _Lexer_eof_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 3, 0, 5, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0
};

static const short _Lexer_eof_trans[] = {
	0, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 19, 21, 21, 21, 21, 21, 31, 
	31, 31, 31, 31, 43, 43, 43, 43, 
	43, 43, 43, 43, 43, 43, 43, 43, 
	43, 43, 43, 0, 0, 0, 0, 0, 
	93, 94, 95, 104, 104, 104, 104, 104, 
	104, 104, 104, 104, 104, 104, 104, 104, 
	104, 104, 104, 104, 104, 104, 104, 104, 
	104, 104, 104, 104, 104, 104, 104, 104, 
	104, 104, 104, 104, 104, 104, 104, 104, 
	134, 95, 95, 139, 142, 142, 145, 146, 
	142, 146, 145, 145, 95, 95, 153, 145, 
	154, 154, 154, 158, 154, 154, 154, 154, 
	154, 154, 154, 154, 154, 154, 154, 154, 
	154, 154, 154, 154, 154, 154, 154, 154, 
	154, 154, 154, 154, 154, 154, 154, 154, 
	154, 154, 154, 154, 154, 154, 154, 154, 
	154, 0, 0
};

static const int Lexer_start = 47;
static const int Lexer_first_final = 47;
static const int Lexer_error = 0;

static const int Lexer_en_recover_character_literal = 43;
static const int Lexer_en_recover_string_literal = 45;
static const int Lexer_en_main = 47;


#line 153 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"



bool openddl::lex(const std::string & input,std::vector<Token> &tokens,std::vector<TokenError> & errors)
{
	int characters_consumed = 0;
	
	char const *p = input.c_str();
	char const *char_error = 0;

	//End
	char const *pe = p + input.length();
	char const *eof = pe;

	//State
	int cs = 0, act, have = 0, curline = 1;
	char const *ts = 0; 
	char const *te = 0;
	int done = 0;

	char const *line_start = p;
	
#line 562 ".\\Lexer.cpp"
	{
	cs = Lexer_start;
	ts = 0;
	te = 0;
	act = 0;
	}

#line 175 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	
#line 568 ".\\Lexer.cpp"
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
	_acts = _Lexer_actions + _Lexer_from_state_actions[cs];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 ) {
		switch ( *_acts++ ) {
	case 9:
#line 1 "NONE"
	{ts = p;}
	break;
#line 587 ".\\Lexer.cpp"
		}
	}

	_keys = _Lexer_trans_keys + _Lexer_key_offsets[cs];
	_trans = _Lexer_index_offsets[cs];

	_klen = _Lexer_single_lengths[cs];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + _klen - 1;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + ((_upper-_lower) >> 1);
			if ( (*p) < *_mid )
				_upper = _mid - 1;
			else if ( (*p) > *_mid )
				_lower = _mid + 1;
			else {
				_trans += (unsigned int)(_mid - _keys);
				goto _match;
			}
		}
		_keys += _klen;
		_trans += _klen;
	}

	_klen = _Lexer_range_lengths[cs];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + (_klen<<1) - 2;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + (((_upper-_lower) >> 1) & ~1);
			if ( (*p) < _mid[0] )
				_upper = _mid - 2;
			else if ( (*p) > _mid[1] )
				_lower = _mid + 2;
			else {
				_trans += (unsigned int)((_mid - _keys)>>1);
				goto _match;
			}
		}
		_trans += _klen;
	}

_match:
	_trans = _Lexer_indicies[_trans];
_eof_trans:
	cs = _Lexer_trans_targs[_trans];

	if ( _Lexer_trans_actions[_trans] == 0 )
		goto _again;

	_acts = _Lexer_actions + _Lexer_trans_actions[_trans];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 )
	{
		switch ( *_acts++ )
		{
	case 0:
#line 57 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{
		error("lex.invalid_character"); 
		{cs = 47; goto _again;}
	}
	break;
	case 3:
#line 72 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{ curline++; line_start = p;}
	break;
	case 4:
#line 82 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{error("lex.nested_block_comment");}
	break;
	case 5:
#line 89 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{characters_consumed++;}
	break;
	case 6:
#line 89 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{characters_consumed++;}
	break;
	case 7:
#line 89 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{characters_consumed = 0;}
	break;
	case 10:
#line 1 "NONE"
	{te = p+1;}
	break;
	case 11:
#line 107 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{act = 2;}
	break;
	case 12:
#line 108 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{act = 3;}
	break;
	case 13:
#line 109 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{act = 4;}
	break;
	case 14:
#line 112 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{act = 5;}
	break;
	case 15:
#line 115 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{act = 6;}
	break;
	case 16:
#line 118 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{act = 7;}
	break;
	case 17:
#line 124 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p+1;{ e(openddl::Token::kArrayDataType);}}
	break;
	case 18:
#line 128 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p+1;{ e(openddl::Token::kString);}}
	break;
	case 19:
#line 133 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p+1;{ if(characters_consumed > 7) error("lex.character_length_error"); else e(openddl::Token::kCharacter);}}
	break;
	case 20:
#line 139 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p+1;}
	break;
	case 21:
#line 142 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p+1;{ e(openddl::Token::kComma);}}
	break;
	case 22:
#line 143 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p+1;{ e(openddl::Token::kLeftBrace);}}
	break;
	case 23:
#line 144 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p+1;{ e(openddl::Token::kRightBrace);}}
	break;
	case 24:
#line 145 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p+1;{error("lex.free_close_comment");}}
	break;
	case 25:
#line 147 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p+1;}
	break;
	case 26:
#line 149 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p+1;{ error("lex.unrecognised_character",ts,te);}}
	break;
	case 27:
#line 106 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p;p--;{ e(openddl::Token::kDecimal); }}
	break;
	case 28:
#line 109 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p;p--;{ e(openddl::Token::kFloat);}}
	break;
	case 29:
#line 112 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p;p--;{ error("lex.invalid_literal");}}
	break;
	case 30:
#line 118 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p;p--;{ e(openddl::Token::kName);}}
	break;
	case 31:
#line 119 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p;p--;{ e(openddl::Token::kIdentifier);}}
	break;
	case 32:
#line 122 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p;p--;{ e(openddl::Token::kDataType);}}
	break;
	case 33:
#line 130 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p;p--;{ {cs = 45; goto _again;}}}
	break;
	case 34:
#line 135 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p;p--;{ {cs = 43; goto _again;}}}
	break;
	case 35:
#line 138 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p;p--;}
	break;
	case 36:
#line 148 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p;p--;}
	break;
	case 37:
#line 149 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p;p--;{ error("lex.unrecognised_character",ts,te);}}
	break;
	case 38:
#line 119 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{{p = ((te))-1;}{ e(openddl::Token::kIdentifier);}}
	break;
	case 39:
#line 122 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{{p = ((te))-1;}{ e(openddl::Token::kDataType);}}
	break;
	case 40:
#line 130 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{{p = ((te))-1;}{ {cs = 45; goto _again;}}}
	break;
	case 41:
#line 135 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{{p = ((te))-1;}{ {cs = 43; goto _again;}}}
	break;
	case 42:
#line 149 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{{p = ((te))-1;}{ error("lex.unrecognised_character",ts,te);}}
	break;
	case 43:
#line 1 "NONE"
	{	switch( act ) {
	case 2:
	{{p = ((te))-1;} e(openddl::Token::kHex);}
	break;
	case 3:
	{{p = ((te))-1;} e(openddl::Token::kBinary);}
	break;
	case 4:
	{{p = ((te))-1;} e(openddl::Token::kFloat);}
	break;
	case 5:
	{{p = ((te))-1;} error("lex.invalid_literal");}
	break;
	case 6:
	{{p = ((te))-1;} e(openddl::Token::kBoolean);}
	break;
	case 7:
	{{p = ((te))-1;} e(openddl::Token::kName);}
	break;
	}
	}
	break;
#line 795 ".\\Lexer.cpp"
		}
	}

_again:
	_acts = _Lexer_actions + _Lexer_to_state_actions[cs];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 ) {
		switch ( *_acts++ ) {
	case 8:
#line 1 "NONE"
	{ts = 0;}
	break;
#line 806 ".\\Lexer.cpp"
		}
	}

	if ( cs == 0 )
		goto _out;
	if ( ++p != pe )
		goto _resume;
	_test_eof: {}
	if ( p == eof )
	{
	if ( _Lexer_eof_trans[cs] > 0 ) {
		_trans = _Lexer_eof_trans[cs] - 1;
		goto _eof_trans;
	}
	const char *__acts = _Lexer_actions + _Lexer_eof_actions[cs];
	unsigned int __nacts = (unsigned int) *__acts++;
	while ( __nacts-- > 0 ) {
		switch ( *__acts++ ) {
	case 1:
#line 61 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{
		error("lex.unterminated_character_literal");
	}
	break;
	case 2:
#line 66 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{
		error("lex.unterminated_string_literal");
	}
	break;
#line 834 ".\\Lexer.cpp"
		}
	}
	}

	_out: {}
	}

#line 176 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	
	return (p==pe);
}

