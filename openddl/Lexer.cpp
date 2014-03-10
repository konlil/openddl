
#line 1 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
//================================================================================================================
// Copyright 2014 Denis Hilliard (armchaircommando@gmail.com)
// Licensed under MIT License
//================================================================================================================

#include "stdafx.h"
#include "Lexer.h"
#include "LexerContext.h"

#define error(m) context.lex_error(m,ts,te)


#define token(t)	context.lex_emit(t,openddl::Token::kInvalidType,openddl::Token::kInvalidLiteral, ts, te)
#define literal(t)	context.lex_emit(openddl::Token::kLiteral,openddl::Token::kInvalidType,t, ts, te)
#define datatype(t) context.lex_emit(openddl::Token::kDataType,t,openddl::Token::kInvalidLiteral, ts, te)
#define arraytype() context.lex_emit(openddl::Token::kArrayType,openddl::Token::kInvalidType,openddl::Token::kInvalidLiteral, ts, te)



#line 20 ".\\Lexer.cpp"
static const char _Lexer_actions[] = {
	0, 1, 0, 1, 1, 1, 2, 1, 
	3, 1, 4, 1, 6, 1, 7, 1, 
	8, 1, 9, 1, 10, 1, 32, 1, 
	34, 1, 35, 1, 36, 1, 37, 1, 
	38, 1, 39, 1, 40, 1, 41, 1, 
	42, 1, 43, 1, 44, 1, 45, 1, 
	46, 1, 47, 1, 48, 1, 49, 1, 
	50, 1, 51, 1, 53, 1, 54, 1, 
	55, 1, 56, 1, 57, 1, 58, 2, 
	0, 33, 2, 5, 57, 2, 6, 52, 
	2, 10, 11, 2, 10, 12, 2, 10, 
	13, 2, 10, 14, 2, 10, 15, 2, 
	10, 16, 2, 10, 17, 2, 10, 18, 
	2, 10, 19, 2, 10, 20, 2, 10, 
	21, 2, 10, 22, 2, 10, 23, 2, 
	10, 24, 2, 10, 25, 2, 10, 26, 
	2, 10, 27, 2, 10, 28, 2, 10, 
	29, 2, 10, 30, 2, 10, 31
};

static const short _Lexer_key_offsets[] = {
	0, 0, 2, 16, 18, 20, 22, 24, 
	27, 29, 31, 45, 51, 57, 63, 69, 
	75, 81, 88, 92, 104, 110, 116, 118, 
	121, 124, 127, 130, 131, 132, 133, 134, 
	169, 169, 183, 197, 204, 212, 220, 228, 
	236, 244, 252, 260, 268, 276, 284, 292, 
	300, 308, 316, 327, 335, 343, 351, 359, 
	367, 375, 383, 391, 399, 407, 415, 423, 
	431, 439, 447, 455, 463, 471, 479, 487, 
	495, 502, 510, 515, 516, 520, 529, 534, 
	543, 550, 564, 571, 581, 588, 599, 601, 
	603, 604, 611, 619, 627, 635, 643, 651, 
	659, 667, 675, 684, 692, 700, 708, 716, 
	724, 732, 740, 748, 759, 767, 775, 783, 
	791, 799, 807, 815, 823, 831, 839, 847, 
	855, 863, 872, 880, 888, 896, 904, 912, 
	920, 928, 936, 944, 952, 959, 967, 975, 
	983, 994, 1002, 1010, 1018, 1018
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
	48, 57, 65, 70, 97, 102, 48, 57, 
	65, 70, 97, 102, 48, 57, 10, 42, 
	47, 10, 42, 47, 10, 42, 47, 10, 
	42, 47, 39, 39, 34, 34, 10, 34, 
	39, 42, 44, 46, 47, 48, 61, 91, 
	93, 95, 98, 100, 102, 105, 110, 114, 
	115, 116, 117, 123, 125, 1, 32, 36, 
	37, 43, 45, 49, 57, 65, 90, 97, 
	122, -62, -32, -19, -17, 34, 92, -61, 
	-33, -31, -18, -16, -12, 32, 126, 95, 
	98, 100, 102, 105, 110, 114, 115, 116, 
	117, 65, 90, 97, 122, 95, 48, 57, 
	65, 90, 97, 122, 95, 111, 48, 57, 
	65, 90, 97, 122, 95, 111, 48, 57, 
	65, 90, 97, 122, 95, 108, 48, 57, 
	65, 90, 97, 122, 95, 111, 48, 57, 
	65, 90, 97, 122, 95, 117, 48, 57, 
	65, 90, 97, 122, 95, 98, 48, 57, 
	65, 90, 97, 122, 95, 108, 48, 57, 
	65, 90, 97, 122, 95, 101, 48, 57, 
	65, 90, 97, 122, 95, 108, 48, 57, 
	65, 90, 97, 122, 95, 111, 48, 57, 
	65, 90, 97, 122, 95, 97, 48, 57, 
	65, 90, 98, 122, 95, 116, 48, 57, 
	65, 90, 97, 122, 95, 110, 48, 57, 
	65, 90, 97, 122, 95, 116, 48, 57, 
	65, 90, 97, 122, 49, 51, 54, 56, 
	95, 48, 57, 65, 90, 97, 122, 54, 
	95, 48, 57, 65, 90, 97, 122, 50, 
	95, 48, 57, 65, 90, 97, 122, 52, 
	95, 48, 57, 65, 90, 97, 122, 95, 
	117, 48, 57, 65, 90, 97, 122, 95, 
	108, 48, 57, 65, 90, 97, 122, 95, 
	101, 48, 57, 65, 90, 97, 122, 95, 
	102, 48, 57, 65, 90, 97, 122, 95, 
	116, 48, 57, 65, 90, 97, 122, 95, 
	114, 48, 57, 65, 90, 97, 122, 95, 
	105, 48, 57, 65, 90, 97, 122, 95, 
	110, 48, 57, 65, 90, 97, 122, 95, 
	103, 48, 57, 65, 90, 97, 122, 95, 
	121, 48, 57, 65, 90, 97, 122, 95, 
	112, 48, 57, 65, 90, 97, 122, 95, 
	110, 48, 57, 65, 90, 97, 122, 95, 
	115, 48, 57, 65, 90, 97, 122, 95, 
	105, 48, 57, 65, 90, 97, 122, 95, 
	103, 48, 57, 65, 90, 97, 122, 95, 
	110, 48, 57, 65, 90, 97, 122, 95, 
	101, 48, 57, 65, 90, 97, 122, 95, 
	100, 48, 57, 65, 90, 97, 122, 95, 
	48, 57, 65, 90, 97, 122, 95, 105, 
	48, 57, 65, 90, 97, 122, 92, 32, 
	38, 40, 126, 47, 46, 48, 49, 57, 
	44, 69, 93, 101, 125, 1, 32, 48, 
	57, 44, 93, 125, 1, 32, 44, 93, 
	125, 1, 32, 43, 45, 48, 57, 44, 
	93, 125, 1, 32, 48, 57, 44, 46, 
	66, 69, 88, 93, 98, 101, 120, 125, 
	1, 32, 48, 57, 44, 93, 125, 1, 
	32, 48, 57, 44, 46, 69, 93, 101, 
	125, 1, 32, 48, 57, 44, 93, 125, 
	1, 32, 48, 49, 44, 93, 125, 1, 
	32, 48, 57, 65, 70, 97, 102, 48, 
	57, 42, 47, 10, 95, 48, 57, 65, 
	90, 97, 122, 95, 111, 48, 57, 65, 
	90, 97, 122, 95, 111, 48, 57, 65, 
	90, 97, 122, 95, 108, 48, 57, 65, 
	90, 97, 122, 95, 111, 48, 57, 65, 
	90, 97, 122, 95, 117, 48, 57, 65, 
	90, 97, 122, 95, 98, 48, 57, 65, 
	90, 97, 122, 95, 108, 48, 57, 65, 
	90, 97, 122, 95, 101, 48, 57, 65, 
	90, 97, 122, 95, 97, 108, 48, 57, 
	65, 90, 98, 122, 95, 108, 48, 57, 
	65, 90, 97, 122, 95, 115, 48, 57, 
	65, 90, 97, 122, 95, 101, 48, 57, 
	65, 90, 97, 122, 95, 111, 48, 57, 
	65, 90, 97, 122, 95, 97, 48, 57, 
	65, 90, 98, 122, 95, 116, 48, 57, 
	65, 90, 97, 122, 95, 110, 48, 57, 
	65, 90, 97, 122, 95, 116, 48, 57, 
	65, 90, 97, 122, 49, 51, 54, 56, 
	95, 48, 57, 65, 90, 97, 122, 54, 
	95, 48, 57, 65, 90, 97, 122, 50, 
	95, 48, 57, 65, 90, 97, 122, 52, 
	95, 48, 57, 65, 90, 97, 122, 95, 
	117, 48, 57, 65, 90, 97, 122, 95, 
	108, 48, 57, 65, 90, 97, 122, 95, 
	108, 48, 57, 65, 90, 97, 122, 95, 
	101, 48, 57, 65, 90, 97, 122, 95, 
	102, 48, 57, 65, 90, 97, 122, 95, 
	116, 48, 57, 65, 90, 97, 122, 95, 
	114, 48, 57, 65, 90, 97, 122, 95, 
	105, 48, 57, 65, 90, 97, 122, 95, 
	110, 48, 57, 65, 90, 97, 122, 95, 
	103, 48, 57, 65, 90, 97, 122, 95, 
	114, 121, 48, 57, 65, 90, 97, 122, 
	95, 117, 48, 57, 65, 90, 97, 122, 
	95, 112, 48, 57, 65, 90, 97, 122, 
	95, 101, 48, 57, 65, 90, 97, 122, 
	95, 110, 48, 57, 65, 90, 97, 122, 
	95, 115, 48, 57, 65, 90, 97, 122, 
	95, 105, 48, 57, 65, 90, 97, 122, 
	95, 103, 48, 57, 65, 90, 97, 122, 
	95, 110, 48, 57, 65, 90, 97, 122, 
	95, 101, 48, 57, 65, 90, 97, 122, 
	95, 100, 48, 57, 65, 90, 97, 122, 
	95, 48, 57, 65, 90, 97, 122, 95, 
	105, 48, 57, 65, 90, 97, 122, 95, 
	110, 48, 57, 65, 90, 97, 122, 95, 
	116, 48, 57, 65, 90, 97, 122, 49, 
	51, 54, 56, 95, 48, 57, 65, 90, 
	97, 122, 54, 95, 48, 57, 65, 90, 
	97, 122, 50, 95, 48, 57, 65, 90, 
	97, 122, 52, 95, 48, 57, 65, 90, 
	97, 122, 0
};

static const char _Lexer_single_lengths[] = {
	0, 0, 6, 0, 0, 0, 0, 1, 
	0, 0, 10, 0, 0, 0, 0, 0, 
	0, 1, 2, 10, 0, 0, 0, 3, 
	3, 3, 3, 1, 1, 1, 1, 23, 
	0, 6, 10, 1, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 5, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	1, 2, 1, 1, 2, 5, 3, 3, 
	3, 10, 3, 6, 3, 3, 0, 2, 
	1, 1, 2, 2, 2, 2, 2, 2, 
	2, 2, 3, 2, 2, 2, 2, 2, 
	2, 2, 2, 5, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 3, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 1, 2, 2, 2, 
	5, 2, 2, 2, 0, 0
};

static const char _Lexer_range_lengths[] = {
	0, 1, 4, 1, 1, 1, 1, 1, 
	1, 1, 2, 3, 3, 3, 3, 3, 
	3, 3, 1, 1, 3, 3, 1, 0, 
	0, 0, 0, 0, 0, 0, 0, 6, 
	0, 4, 2, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 2, 0, 1, 2, 1, 3, 
	2, 2, 2, 2, 2, 4, 1, 0, 
	0, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 0, 0
};

static const short _Lexer_index_offsets[] = {
	0, 0, 2, 13, 15, 17, 19, 21, 
	24, 26, 28, 41, 45, 49, 53, 57, 
	61, 65, 70, 74, 86, 90, 94, 96, 
	100, 104, 108, 112, 114, 116, 118, 120, 
	150, 151, 162, 175, 180, 186, 192, 198, 
	204, 210, 216, 222, 228, 234, 240, 246, 
	252, 258, 264, 273, 279, 285, 291, 297, 
	303, 309, 315, 321, 327, 333, 339, 345, 
	351, 357, 363, 369, 375, 381, 387, 393, 
	399, 404, 410, 414, 416, 420, 428, 433, 
	440, 446, 459, 465, 474, 480, 488, 490, 
	493, 495, 500, 506, 512, 518, 524, 530, 
	536, 542, 548, 555, 561, 567, 573, 579, 
	585, 591, 597, 603, 612, 618, 624, 630, 
	636, 642, 648, 654, 660, 666, 672, 678, 
	684, 690, 697, 703, 709, 715, 721, 727, 
	733, 739, 745, 751, 757, 762, 768, 774, 
	780, 789, 795, 801, 807, 808
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
	24, 24, 24, 25, 24, 20, 26, 26, 
	26, 20, 24, 24, 24, 20, 28, 27, 
	31, 32, 33, 30, 35, 36, 37, 34, 
	31, 32, 38, 30, 31, 39, 33, 30, 
	41, 40, 42, 40, 41, 43, 44, 43, 
	47, 48, 50, 51, 53, 54, 55, 56, 
	58, 60, 61, 59, 62, 63, 64, 65, 
	66, 67, 68, 69, 70, 71, 72, 46, 
	49, 52, 57, 59, 59, 45, 73, 2, 
	4, 6, 7, 9, 10, 3, 5, 8, 
	1, 74, 19, 76, 77, 78, 79, 80, 
	81, 82, 83, 84, 19, 19, 75, 19, 
	19, 19, 19, 85, 19, 86, 19, 19, 
	19, 85, 19, 87, 19, 19, 19, 85, 
	19, 88, 19, 19, 19, 85, 19, 89, 
	19, 19, 19, 85, 19, 90, 19, 19, 
	19, 85, 19, 91, 19, 19, 19, 85, 
	19, 92, 19, 19, 19, 85, 19, 88, 
	19, 19, 19, 85, 19, 93, 19, 19, 
	19, 85, 19, 94, 19, 19, 19, 85, 
	19, 95, 19, 19, 19, 85, 19, 88, 
	19, 19, 19, 85, 19, 96, 19, 19, 
	19, 85, 19, 97, 19, 19, 19, 85, 
	98, 99, 100, 88, 19, 19, 19, 19, 
	85, 88, 19, 19, 19, 19, 85, 88, 
	19, 19, 19, 19, 85, 88, 19, 19, 
	19, 19, 85, 19, 101, 19, 19, 19, 
	85, 19, 87, 19, 19, 19, 85, 19, 
	102, 19, 19, 19, 85, 19, 88, 19, 
	19, 19, 85, 19, 103, 19, 19, 19, 
	85, 19, 104, 19, 19, 19, 85, 19, 
	105, 19, 19, 19, 85, 19, 106, 19, 
	19, 19, 85, 19, 88, 19, 19, 19, 
	85, 19, 107, 19, 19, 19, 85, 19, 
	92, 19, 19, 19, 85, 19, 108, 19, 
	19, 19, 85, 19, 109, 19, 19, 19, 
	85, 19, 110, 19, 19, 19, 85, 19, 
	111, 19, 19, 19, 85, 19, 112, 19, 
	19, 19, 85, 19, 113, 19, 19, 19, 
	85, 19, 114, 19, 19, 19, 85, 115, 
	19, 19, 19, 85, 19, 79, 19, 19, 
	19, 85, 118, 117, 117, 116, 119, 75, 
	120, 56, 57, 75, 121, 123, 121, 123, 
	121, 121, 28, 122, 124, 124, 124, 124, 
	122, 124, 124, 124, 124, 125, 126, 122, 
	127, 127, 127, 127, 126, 122, 128, 129, 
	130, 123, 131, 128, 130, 123, 131, 128, 
	128, 57, 122, 124, 124, 124, 124, 28, 
	122, 128, 129, 123, 128, 123, 128, 128, 
	57, 122, 127, 127, 127, 127, 132, 122, 
	127, 127, 127, 127, 133, 133, 133, 122, 
	28, 75, 30, 134, 75, 135, 134, 59, 
	59, 59, 59, 127, 59, 137, 59, 59, 
	59, 136, 59, 138, 59, 59, 59, 136, 
	59, 139, 59, 59, 59, 136, 59, 140, 
	59, 59, 59, 136, 59, 141, 59, 59, 
	59, 136, 59, 142, 59, 59, 59, 136, 
	59, 143, 59, 59, 59, 136, 59, 144, 
	59, 59, 59, 136, 59, 145, 146, 59, 
	59, 59, 136, 59, 147, 59, 59, 59, 
	136, 59, 148, 59, 59, 59, 136, 59, 
	149, 59, 59, 59, 136, 59, 150, 59, 
	59, 59, 136, 59, 151, 59, 59, 59, 
	136, 59, 152, 59, 59, 59, 136, 59, 
	153, 59, 59, 59, 136, 59, 154, 59, 
	59, 59, 136, 155, 156, 157, 158, 59, 
	59, 59, 59, 136, 159, 59, 59, 59, 
	59, 136, 160, 59, 59, 59, 59, 136, 
	161, 59, 59, 59, 59, 136, 59, 162, 
	59, 59, 59, 136, 59, 163, 59, 59, 
	59, 136, 59, 164, 59, 59, 59, 136, 
	59, 165, 59, 59, 59, 136, 59, 166, 
	59, 59, 59, 136, 59, 167, 59, 59, 
	59, 136, 59, 168, 59, 59, 59, 136, 
	59, 169, 59, 59, 59, 136, 59, 170, 
	59, 59, 59, 136, 59, 171, 59, 59, 
	59, 136, 59, 172, 173, 59, 59, 59, 
	136, 59, 148, 59, 59, 59, 136, 59, 
	174, 59, 59, 59, 136, 59, 175, 59, 
	59, 59, 136, 59, 176, 59, 59, 59, 
	136, 59, 177, 59, 59, 59, 136, 59, 
	178, 59, 59, 59, 136, 59, 179, 59, 
	59, 59, 136, 59, 180, 59, 59, 59, 
	136, 59, 181, 59, 59, 59, 136, 59, 
	182, 59, 59, 59, 136, 183, 59, 59, 
	59, 136, 59, 184, 59, 59, 59, 136, 
	59, 185, 59, 59, 59, 136, 59, 186, 
	59, 59, 59, 136, 187, 188, 189, 190, 
	59, 59, 59, 59, 136, 191, 59, 59, 
	59, 59, 136, 192, 59, 59, 59, 59, 
	136, 193, 59, 59, 59, 59, 136, 41, 
	41, 0
};

static const unsigned char _Lexer_trans_targs[] = {
	31, 2, 1, 3, 4, 5, 6, 7, 
	9, 31, 10, 8, 11, 13, 15, 12, 
	14, 16, 31, 35, 31, 18, 31, 19, 
	18, 20, 21, 31, 77, 31, 23, 24, 
	25, 26, 23, 24, 25, 26, 31, 25, 
	28, 0, 140, 30, 141, 31, 31, 32, 
	33, 34, 74, 75, 76, 31, 86, 87, 
	81, 83, 31, 89, 31, 31, 90, 93, 
	98, 105, 111, 114, 116, 121, 125, 31, 
	31, 31, 31, 31, 36, 39, 44, 48, 
	54, 56, 58, 63, 65, 31, 37, 38, 
	17, 40, 41, 42, 43, 45, 46, 47, 
	49, 50, 51, 52, 53, 55, 57, 59, 
	60, 61, 62, 64, 66, 67, 68, 69, 
	70, 71, 72, 73, 31, 18, 19, 31, 
	22, 31, 78, 79, 31, 80, 80, 31, 
	31, 82, 84, 85, 84, 85, 88, 31, 
	31, 91, 92, 89, 94, 95, 96, 97, 
	89, 99, 102, 100, 101, 89, 103, 104, 
	89, 106, 107, 108, 109, 110, 89, 89, 
	89, 89, 112, 113, 89, 115, 89, 117, 
	118, 119, 120, 89, 122, 123, 124, 89, 
	126, 127, 128, 129, 130, 131, 132, 133, 
	134, 135, 136, 137, 138, 139, 89, 89, 
	89, 89
};

static const unsigned char _Lexer_trans_actions[] = {
	63, 0, 0, 0, 0, 0, 0, 0, 
	0, 21, 0, 0, 0, 0, 0, 0, 
	0, 0, 61, 0, 65, 1, 71, 1, 
	0, 0, 0, 67, 0, 74, 0, 0, 
	0, 0, 11, 11, 11, 11, 23, 13, 
	0, 0, 5, 0, 5, 41, 39, 0, 
	19, 0, 19, 0, 19, 25, 0, 19, 
	0, 0, 35, 95, 31, 33, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 27, 
	29, 77, 53, 59, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 51, 0, 19, 
	0, 0, 0, 0, 19, 0, 0, 19, 
	0, 19, 19, 19, 19, 0, 19, 0, 
	0, 0, 19, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 55, 3, 3, 37, 
	0, 45, 0, 0, 47, 89, 86, 69, 
	43, 0, 89, 89, 83, 80, 0, 57, 
	49, 0, 0, 101, 0, 0, 0, 0, 
	131, 0, 0, 0, 0, 92, 0, 0, 
	128, 0, 0, 0, 0, 0, 104, 107, 
	110, 113, 0, 0, 98, 0, 134, 0, 
	0, 0, 0, 137, 0, 0, 0, 140, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 116, 119, 
	122, 125
};

static const unsigned char _Lexer_to_state_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 15, 0, 15, 0, 15, 
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
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0
};

static const unsigned char _Lexer_from_state_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 17, 
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
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0
};

static const unsigned char _Lexer_eof_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 7, 0, 9, 0, 
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
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0
};

static const short _Lexer_eof_trans[] = {
	0, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 19, 21, 21, 21, 21, 28, 30, 
	30, 30, 30, 0, 0, 0, 0, 0, 
	74, 75, 76, 86, 86, 86, 86, 86, 
	86, 86, 86, 86, 86, 86, 86, 86, 
	86, 86, 86, 86, 86, 86, 86, 86, 
	86, 86, 86, 86, 86, 86, 86, 86, 
	86, 86, 86, 86, 86, 86, 86, 86, 
	86, 86, 117, 76, 76, 122, 125, 125, 
	128, 129, 125, 129, 128, 128, 76, 76, 
	136, 128, 137, 137, 137, 137, 137, 137, 
	137, 137, 137, 137, 137, 137, 137, 137, 
	137, 137, 137, 137, 137, 137, 137, 137, 
	137, 137, 137, 137, 137, 137, 137, 137, 
	137, 137, 137, 137, 137, 137, 137, 137, 
	137, 137, 137, 137, 137, 137, 137, 137, 
	137, 137, 137, 137, 0, 0
};

static const int Lexer_start = 31;
static const int Lexer_first_final = 31;
static const int Lexer_error = 0;

static const int Lexer_en_recover_character_literal = 27;
static const int Lexer_en_recover_string_literal = 29;
static const int Lexer_en_main = 31;


#line 144 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"



bool openddl::lex(const std::string & input,std::vector<Token> &tokens,std::vector<TokenError> & errors)
{
	Lexer::Context context(input,tokens,errors);
	
	char const *p = input.c_str();
	char const *char_error = 0;

	//End
	char const *pe = p + input.length();
	char const *eof = pe;

	//State
	int cs = 0, act, have = 0;
	char const *ts = 0; 
	char const *te = 0;
	int done = 0;

	
#line 529 ".\\Lexer.cpp"
	{
	cs = Lexer_start;
	ts = 0;
	te = 0;
	act = 0;
	}

#line 165 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	
#line 535 ".\\Lexer.cpp"
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
#line 554 ".\\Lexer.cpp"
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
#line 23 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{ context.count_character();}
	break;
	case 1:
#line 24 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{ context.reset_count(); }
	break;
	case 2:
#line 25 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{
		error("lex.invalid_character"); 
		{cs = 31; goto _again;}
	}
	break;
	case 5:
#line 37 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{
		error("lex.unterminated_block_comment"); 
		//Skip forward to end of file
		{p = (((pe)))-1;} {p++; goto _out; }
	}
	break;
	case 6:
#line 45 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{ context.new_line(p);}
	break;
	case 7:
#line 55 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{error("lex.nested_block_comment");}
	break;
	case 10:
#line 1 "NONE"
	{te = p+1;}
	break;
	case 11:
#line 81 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{act = 2;}
	break;
	case 12:
#line 82 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{act = 3;}
	break;
	case 13:
#line 83 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{act = 4;}
	break;
	case 14:
#line 86 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{act = 5;}
	break;
	case 15:
#line 89 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{act = 6;}
	break;
	case 16:
#line 92 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{act = 7;}
	break;
	case 17:
#line 94 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{act = 9;}
	break;
	case 18:
#line 97 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{act = 10;}
	break;
	case 19:
#line 98 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{act = 11;}
	break;
	case 20:
#line 99 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{act = 12;}
	break;
	case 21:
#line 100 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{act = 13;}
	break;
	case 22:
#line 101 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{act = 14;}
	break;
	case 23:
#line 102 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{act = 15;}
	break;
	case 24:
#line 103 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{act = 16;}
	break;
	case 25:
#line 104 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{act = 17;}
	break;
	case 26:
#line 105 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{act = 18;}
	break;
	case 27:
#line 106 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{act = 19;}
	break;
	case 28:
#line 107 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{act = 20;}
	break;
	case 29:
#line 108 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{act = 21;}
	break;
	case 30:
#line 109 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{act = 22;}
	break;
	case 31:
#line 110 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{act = 23;}
	break;
	case 32:
#line 116 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p+1;{ literal(openddl::Token::kStringLiteral);}}
	break;
	case 33:
#line 121 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p+1;{ if(context.get_character_count() > 7) error("lex.character_length_error"); else literal(openddl::Token::kCharacterLiteral);}}
	break;
	case 34:
#line 127 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p+1;}
	break;
	case 35:
#line 130 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p+1;{ token(openddl::Token::kComma);}}
	break;
	case 36:
#line 131 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p+1;{ token(openddl::Token::kLeftBrace);}}
	break;
	case 37:
#line 132 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p+1;{ token(openddl::Token::kRightBrace);}}
	break;
	case 38:
#line 133 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p+1;{ token(openddl::Token::kLeftSquareBracket);}}
	break;
	case 39:
#line 134 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p+1;{ token(openddl::Token::kRightSquareBracket);}}
	break;
	case 40:
#line 135 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p+1;{ token(openddl::Token::kEquals);}}
	break;
	case 41:
#line 136 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p+1;{error("lex.trailing_close_comment");}}
	break;
	case 42:
#line 138 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p+1;}
	break;
	case 43:
#line 140 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p+1;{ error("lex.unrecognised_character");}}
	break;
	case 44:
#line 80 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p;p--;{ literal(openddl::Token::kDecimalLiteral); }}
	break;
	case 45:
#line 83 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p;p--;{ literal(openddl::Token::kFloatLiteral);}}
	break;
	case 46:
#line 86 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p;p--;{ error("lex.invalid_literal");}}
	break;
	case 47:
#line 92 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p;p--;{ token(openddl::Token::kName);}}
	break;
	case 48:
#line 93 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p;p--;{ token(openddl::Token::kIdentifier);}}
	break;
	case 49:
#line 118 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p;p--;{ {cs = 29; goto _again;}}}
	break;
	case 50:
#line 123 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p;p--;{ {cs = 27; goto _again;}}}
	break;
	case 51:
#line 126 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p;p--;}
	break;
	case 52:
#line 139 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p;p--;}
	break;
	case 53:
#line 140 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p;p--;{ error("lex.unrecognised_character");}}
	break;
	case 54:
#line 93 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{{p = ((te))-1;}{ token(openddl::Token::kIdentifier);}}
	break;
	case 55:
#line 118 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{{p = ((te))-1;}{ {cs = 29; goto _again;}}}
	break;
	case 56:
#line 123 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{{p = ((te))-1;}{ {cs = 27; goto _again;}}}
	break;
	case 57:
#line 140 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{{p = ((te))-1;}{ error("lex.unrecognised_character");}}
	break;
	case 58:
#line 1 "NONE"
	{	switch( act ) {
	case 2:
	{{p = ((te))-1;} literal(openddl::Token::kHexLiteral);}
	break;
	case 3:
	{{p = ((te))-1;} literal(openddl::Token::kBinaryLiteral);}
	break;
	case 4:
	{{p = ((te))-1;} literal(openddl::Token::kFloatLiteral);}
	break;
	case 5:
	{{p = ((te))-1;} error("lex.invalid_literal");}
	break;
	case 6:
	{{p = ((te))-1;} literal(openddl::Token::kBooleanLiteral);}
	break;
	case 7:
	{{p = ((te))-1;} token(openddl::Token::kName);}
	break;
	case 9:
	{{p = ((te))-1;} token(openddl::Token::kNull);}
	break;
	case 10:
	{{p = ((te))-1;} datatype(openddl::Token::kBool);}
	break;
	case 11:
	{{p = ((te))-1;} datatype(openddl::Token::kInt8);}
	break;
	case 12:
	{{p = ((te))-1;} datatype(openddl::Token::kInt16);}
	break;
	case 13:
	{{p = ((te))-1;} datatype(openddl::Token::kInt32);}
	break;
	case 14:
	{{p = ((te))-1;} datatype(openddl::Token::kInt64);}
	break;
	case 15:
	{{p = ((te))-1;} datatype(openddl::Token::kUnsignedInt8);}
	break;
	case 16:
	{{p = ((te))-1;} datatype(openddl::Token::kUnsignedInt16);}
	break;
	case 17:
	{{p = ((te))-1;} datatype(openddl::Token::kUnsignedInt32);}
	break;
	case 18:
	{{p = ((te))-1;} datatype(openddl::Token::kUnsignedInt64);}
	break;
	case 19:
	{{p = ((te))-1;} datatype(openddl::Token::kFloat);}
	break;
	case 20:
	{{p = ((te))-1;} datatype(openddl::Token::kDouble);}
	break;
	case 21:
	{{p = ((te))-1;} datatype(openddl::Token::kRef);}
	break;
	case 22:
	{{p = ((te))-1;} datatype(openddl::Token::kString);}
	break;
	case 23:
	{{p = ((te))-1;} datatype(openddl::Token::kType);}
	break;
	}
	}
	break;
#line 856 ".\\Lexer.cpp"
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
#line 867 ".\\Lexer.cpp"
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
	case 3:
#line 29 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{
		error("lex.unterminated_character_literal");
	}
	break;
	case 4:
#line 34 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{
		error("lex.unterminated_string_literal");
	}
	break;
#line 895 ".\\Lexer.cpp"
		}
	}
	}

	_out: {}
	}

#line 166 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	
	return (p==pe);
}

bool openddl::has_intervening_whitespace(const Token & a, const Token & b) { return (a.range_start + a.range_length) != b.range_start; }

