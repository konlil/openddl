
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
	3, 1, 4, 1, 5, 1, 6, 1, 
	7, 1, 8, 1, 9, 1, 10, 1, 
	31, 1, 32, 1, 34, 1, 35, 1, 
	36, 1, 37, 1, 38, 1, 39, 1, 
	40, 1, 41, 1, 42, 1, 43, 1, 
	44, 1, 45, 1, 46, 1, 47, 1, 
	48, 1, 49, 1, 51, 1, 52, 1, 
	53, 1, 54, 1, 55, 1, 56, 2, 
	3, 50, 2, 5, 33, 2, 6, 33, 
	2, 10, 11, 2, 10, 12, 2, 10, 
	13, 2, 10, 14, 2, 10, 15, 2, 
	10, 16, 2, 10, 17, 2, 10, 18, 
	2, 10, 19, 2, 10, 20, 2, 10, 
	21, 2, 10, 22, 2, 10, 23, 2, 
	10, 24, 2, 10, 25, 2, 10, 26, 
	2, 10, 27, 2, 10, 28, 2, 10, 
	29, 2, 10, 30
};

static const short _Lexer_key_offsets[] = {
	0, 0, 2, 16, 18, 20, 22, 24, 
	27, 29, 31, 45, 51, 57, 63, 69, 
	75, 81, 88, 92, 104, 108, 114, 120, 
	122, 125, 128, 131, 134, 139, 143, 144, 
	156, 160, 166, 172, 175, 182, 185, 187, 
	190, 196, 203, 204, 205, 206, 207, 241, 
	241, 255, 268, 275, 283, 291, 299, 307, 
	315, 323, 331, 339, 347, 355, 363, 371, 
	379, 387, 398, 406, 414, 422, 430, 438, 
	446, 454, 462, 470, 478, 486, 494, 502, 
	510, 518, 526, 534, 542, 550, 557, 565, 
	570, 571, 575, 584, 589, 598, 605, 619, 
	626, 636, 643, 654, 656, 658, 659, 666, 
	672, 680, 688, 696, 704, 712, 720, 728, 
	736, 745, 753, 761, 769, 777, 785, 793, 
	801, 809, 820, 828, 836, 844, 852, 860, 
	867, 875, 883, 891, 899, 907, 915, 923, 
	932, 940, 948, 956, 964, 972, 980, 988, 
	996, 1004, 1012, 1019, 1027, 1035, 1043, 1054, 
	1062, 1070, 1078, 1078
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
	10, 42, 47, 10, 42, 47, 92, 32, 
	38, 40, 126, 39, 92, 32, 126, 93, 
	34, 39, 63, 92, 102, 110, 114, 116, 
	118, 120, 97, 98, 39, 92, 32, 126, 
	48, 57, 65, 70, 97, 102, 48, 57, 
	65, 70, 97, 102, 48, 49, 57, 66, 
	88, 93, 98, 120, 48, 57, 93, 48, 
	57, 48, 49, 93, 48, 49, 48, 57, 
	65, 70, 97, 102, 93, 48, 57, 65, 
	70, 97, 102, 39, 39, 34, 34, 10, 
	34, 39, 42, 44, 46, 47, 48, 61, 
	91, 95, 98, 100, 102, 105, 110, 114, 
	115, 116, 117, 123, 125, 1, 32, 36, 
	37, 43, 45, 49, 57, 65, 90, 97, 
	122, -62, -32, -19, -17, 34, 92, -61, 
	-33, -31, -18, -16, -12, 32, 126, 95, 
	98, 100, 102, 105, 114, 115, 116, 117, 
	65, 90, 97, 122, 95, 48, 57, 65, 
	90, 97, 122, 95, 111, 48, 57, 65, 
	90, 97, 122, 95, 111, 48, 57, 65, 
	90, 97, 122, 95, 108, 48, 57, 65, 
	90, 97, 122, 95, 111, 48, 57, 65, 
	90, 97, 122, 95, 117, 48, 57, 65, 
	90, 97, 122, 95, 98, 48, 57, 65, 
	90, 97, 122, 95, 108, 48, 57, 65, 
	90, 97, 122, 95, 101, 48, 57, 65, 
	90, 97, 122, 95, 108, 48, 57, 65, 
	90, 97, 122, 95, 111, 48, 57, 65, 
	90, 97, 122, 95, 97, 48, 57, 65, 
	90, 98, 122, 95, 116, 48, 57, 65, 
	90, 97, 122, 95, 110, 48, 57, 65, 
	90, 97, 122, 95, 116, 48, 57, 65, 
	90, 97, 122, 49, 51, 54, 56, 95, 
	48, 57, 65, 90, 97, 122, 54, 95, 
	48, 57, 65, 90, 97, 122, 50, 95, 
	48, 57, 65, 90, 97, 122, 52, 95, 
	48, 57, 65, 90, 97, 122, 95, 101, 
	48, 57, 65, 90, 97, 122, 95, 102, 
	48, 57, 65, 90, 97, 122, 95, 116, 
	48, 57, 65, 90, 97, 122, 95, 114, 
	48, 57, 65, 90, 97, 122, 95, 105, 
	48, 57, 65, 90, 97, 122, 95, 110, 
	48, 57, 65, 90, 97, 122, 95, 103, 
	48, 57, 65, 90, 97, 122, 95, 121, 
	48, 57, 65, 90, 97, 122, 95, 112, 
	48, 57, 65, 90, 97, 122, 95, 110, 
	48, 57, 65, 90, 97, 122, 95, 115, 
	48, 57, 65, 90, 97, 122, 95, 105, 
	48, 57, 65, 90, 97, 122, 95, 103, 
	48, 57, 65, 90, 97, 122, 95, 110, 
	48, 57, 65, 90, 97, 122, 95, 101, 
	48, 57, 65, 90, 97, 122, 95, 100, 
	48, 57, 65, 90, 97, 122, 95, 48, 
	57, 65, 90, 97, 122, 95, 105, 48, 
	57, 65, 90, 97, 122, 92, 32, 38, 
	40, 126, 47, 46, 48, 49, 57, 44, 
	69, 101, 123, 125, 1, 32, 48, 57, 
	44, 123, 125, 1, 32, 44, 123, 125, 
	1, 32, 43, 45, 48, 57, 44, 123, 
	125, 1, 32, 48, 57, 44, 46, 66, 
	69, 88, 98, 101, 120, 123, 125, 1, 
	32, 48, 57, 44, 123, 125, 1, 32, 
	48, 57, 44, 46, 69, 101, 123, 125, 
	1, 32, 48, 57, 44, 123, 125, 1, 
	32, 48, 49, 44, 123, 125, 1, 32, 
	48, 57, 65, 70, 97, 102, 48, 57, 
	42, 47, 10, 95, 48, 57, 65, 90, 
	97, 122, 39, 43, 45, 48, 49, 57, 
	95, 111, 48, 57, 65, 90, 97, 122, 
	95, 111, 48, 57, 65, 90, 97, 122, 
	95, 108, 48, 57, 65, 90, 97, 122, 
	95, 111, 48, 57, 65, 90, 97, 122, 
	95, 117, 48, 57, 65, 90, 97, 122, 
	95, 98, 48, 57, 65, 90, 97, 122, 
	95, 108, 48, 57, 65, 90, 97, 122, 
	95, 101, 48, 57, 65, 90, 97, 122, 
	95, 97, 108, 48, 57, 65, 90, 98, 
	122, 95, 108, 48, 57, 65, 90, 97, 
	122, 95, 115, 48, 57, 65, 90, 97, 
	122, 95, 101, 48, 57, 65, 90, 97, 
	122, 95, 111, 48, 57, 65, 90, 97, 
	122, 95, 97, 48, 57, 65, 90, 98, 
	122, 95, 116, 48, 57, 65, 90, 97, 
	122, 95, 110, 48, 57, 65, 90, 97, 
	122, 95, 116, 48, 57, 65, 90, 97, 
	122, 49, 51, 54, 56, 95, 48, 57, 
	65, 90, 97, 122, 54, 95, 48, 57, 
	65, 90, 97, 122, 50, 95, 48, 57, 
	65, 90, 97, 122, 52, 95, 48, 57, 
	65, 90, 97, 122, 95, 117, 48, 57, 
	65, 90, 97, 122, 95, 108, 48, 57, 
	65, 90, 97, 122, 95, 48, 57, 65, 
	90, 97, 122, 95, 101, 48, 57, 65, 
	90, 97, 122, 95, 102, 48, 57, 65, 
	90, 97, 122, 95, 116, 48, 57, 65, 
	90, 97, 122, 95, 114, 48, 57, 65, 
	90, 97, 122, 95, 105, 48, 57, 65, 
	90, 97, 122, 95, 110, 48, 57, 65, 
	90, 97, 122, 95, 103, 48, 57, 65, 
	90, 97, 122, 95, 114, 121, 48, 57, 
	65, 90, 97, 122, 95, 117, 48, 57, 
	65, 90, 97, 122, 95, 112, 48, 57, 
	65, 90, 97, 122, 95, 101, 48, 57, 
	65, 90, 97, 122, 95, 110, 48, 57, 
	65, 90, 97, 122, 95, 115, 48, 57, 
	65, 90, 97, 122, 95, 105, 48, 57, 
	65, 90, 97, 122, 95, 103, 48, 57, 
	65, 90, 97, 122, 95, 110, 48, 57, 
	65, 90, 97, 122, 95, 101, 48, 57, 
	65, 90, 97, 122, 95, 100, 48, 57, 
	65, 90, 97, 122, 95, 48, 57, 65, 
	90, 97, 122, 95, 105, 48, 57, 65, 
	90, 97, 122, 95, 110, 48, 57, 65, 
	90, 97, 122, 95, 116, 48, 57, 65, 
	90, 97, 122, 49, 51, 54, 56, 95, 
	48, 57, 65, 90, 97, 122, 54, 95, 
	48, 57, 65, 90, 97, 122, 50, 95, 
	48, 57, 65, 90, 97, 122, 52, 95, 
	48, 57, 65, 90, 97, 122, 0
};

static const char _Lexer_single_lengths[] = {
	0, 0, 6, 0, 0, 0, 0, 1, 
	0, 0, 10, 0, 0, 0, 0, 0, 
	0, 1, 2, 10, 2, 0, 0, 0, 
	3, 3, 3, 3, 1, 2, 1, 10, 
	2, 0, 0, 1, 5, 1, 0, 1, 
	0, 1, 1, 1, 1, 1, 22, 0, 
	6, 9, 1, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 5, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 1, 2, 1, 
	1, 2, 5, 3, 3, 3, 10, 3, 
	6, 3, 3, 0, 2, 1, 1, 4, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	3, 2, 2, 2, 2, 2, 2, 2, 
	2, 5, 2, 2, 2, 2, 2, 1, 
	2, 2, 2, 2, 2, 2, 2, 3, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 1, 2, 2, 2, 5, 2, 
	2, 2, 0, 0
};

static const char _Lexer_range_lengths[] = {
	0, 1, 4, 1, 1, 1, 1, 1, 
	1, 1, 2, 3, 3, 3, 3, 3, 
	3, 3, 1, 1, 1, 3, 3, 1, 
	0, 0, 0, 0, 2, 1, 0, 1, 
	1, 3, 3, 1, 1, 1, 1, 1, 
	3, 3, 0, 0, 0, 0, 6, 0, 
	4, 2, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 2, 
	0, 1, 2, 1, 3, 2, 2, 2, 
	2, 2, 4, 1, 0, 0, 3, 1, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 0, 0
};

static const short _Lexer_index_offsets[] = {
	0, 0, 2, 13, 15, 17, 19, 21, 
	24, 26, 28, 41, 45, 49, 53, 57, 
	61, 65, 70, 74, 86, 90, 94, 98, 
	100, 104, 108, 112, 116, 120, 124, 126, 
	138, 142, 146, 150, 153, 160, 163, 165, 
	168, 172, 177, 179, 181, 183, 185, 214, 
	215, 226, 238, 243, 249, 255, 261, 267, 
	273, 279, 285, 291, 297, 303, 309, 315, 
	321, 327, 336, 342, 348, 354, 360, 366, 
	372, 378, 384, 390, 396, 402, 408, 414, 
	420, 426, 432, 438, 444, 450, 455, 461, 
	465, 467, 471, 479, 484, 491, 497, 510, 
	516, 525, 531, 539, 541, 544, 546, 551, 
	557, 563, 569, 575, 581, 587, 593, 599, 
	605, 612, 618, 624, 630, 636, 642, 648, 
	654, 660, 669, 675, 681, 687, 693, 699, 
	704, 710, 716, 722, 728, 734, 740, 746, 
	753, 759, 765, 771, 777, 783, 789, 795, 
	801, 807, 813, 818, 824, 830, 836, 845, 
	851, 857, 863, 864
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
	33, 41, 35, 32, 43, 42, 42, 30, 
	45, 46, 44, 30, 47, 30, 48, 48, 
	48, 48, 48, 48, 48, 48, 48, 49, 
	48, 30, 51, 52, 50, 30, 53, 53, 
	53, 30, 48, 48, 48, 30, 54, 55, 
	30, 56, 57, 47, 56, 57, 55, 30, 
	47, 55, 30, 58, 30, 47, 58, 30, 
	59, 59, 59, 30, 47, 59, 59, 59, 
	30, 61, 60, 62, 60, 61, 63, 64, 
	63, 67, 68, 70, 71, 73, 74, 75, 
	76, 78, 80, 79, 81, 82, 83, 84, 
	85, 86, 87, 88, 89, 90, 91, 66, 
	69, 72, 77, 79, 79, 65, 92, 2, 
	4, 6, 7, 9, 10, 3, 5, 8, 
	1, 93, 19, 95, 96, 97, 98, 99, 
	100, 101, 102, 19, 19, 94, 19, 19, 
	19, 19, 103, 19, 104, 19, 19, 19, 
	103, 19, 105, 19, 19, 19, 103, 19, 
	106, 19, 19, 19, 103, 19, 107, 19, 
	19, 19, 103, 19, 108, 19, 19, 19, 
	103, 19, 109, 19, 19, 19, 103, 19, 
	110, 19, 19, 19, 103, 19, 106, 19, 
	19, 19, 103, 19, 111, 19, 19, 19, 
	103, 19, 112, 19, 19, 19, 103, 19, 
	113, 19, 19, 19, 103, 19, 106, 19, 
	19, 19, 103, 19, 114, 19, 19, 19, 
	103, 19, 115, 19, 19, 19, 103, 116, 
	117, 118, 106, 19, 19, 19, 19, 103, 
	106, 19, 19, 19, 19, 103, 106, 19, 
	19, 19, 19, 103, 106, 19, 19, 19, 
	19, 103, 19, 119, 19, 19, 19, 103, 
	19, 106, 19, 19, 19, 103, 19, 120, 
	19, 19, 19, 103, 19, 121, 19, 19, 
	19, 103, 19, 122, 19, 19, 19, 103, 
	19, 123, 19, 19, 19, 103, 19, 106, 
	19, 19, 19, 103, 19, 124, 19, 19, 
	19, 103, 19, 110, 19, 19, 19, 103, 
	19, 125, 19, 19, 19, 103, 19, 126, 
	19, 19, 19, 103, 19, 127, 19, 19, 
	19, 103, 19, 128, 19, 19, 19, 103, 
	19, 129, 19, 19, 19, 103, 19, 130, 
	19, 19, 19, 103, 19, 131, 19, 19, 
	19, 103, 132, 19, 19, 19, 103, 19, 
	98, 19, 19, 19, 103, 135, 134, 134, 
	133, 136, 94, 137, 76, 77, 94, 138, 
	140, 140, 138, 138, 138, 31, 139, 141, 
	141, 141, 141, 139, 141, 141, 141, 141, 
	142, 143, 139, 144, 144, 144, 144, 143, 
	139, 145, 146, 147, 140, 148, 147, 140, 
	148, 145, 145, 145, 77, 139, 141, 141, 
	141, 141, 31, 139, 145, 146, 140, 140, 
	145, 145, 145, 77, 139, 144, 144, 144, 
	144, 149, 139, 144, 144, 144, 144, 150, 
	150, 150, 139, 31, 94, 32, 151, 94, 
	152, 151, 79, 79, 79, 79, 144, 153, 
	154, 154, 54, 55, 94, 79, 156, 79, 
	79, 79, 155, 79, 157, 79, 79, 79, 
	155, 79, 158, 79, 79, 79, 155, 79, 
	159, 79, 79, 79, 155, 79, 160, 79, 
	79, 79, 155, 79, 161, 79, 79, 79, 
	155, 79, 162, 79, 79, 79, 155, 79, 
	163, 79, 79, 79, 155, 79, 164, 165, 
	79, 79, 79, 155, 79, 166, 79, 79, 
	79, 155, 79, 167, 79, 79, 79, 155, 
	79, 168, 79, 79, 79, 155, 79, 169, 
	79, 79, 79, 155, 79, 170, 79, 79, 
	79, 155, 79, 171, 79, 79, 79, 155, 
	79, 172, 79, 79, 79, 155, 79, 173, 
	79, 79, 79, 155, 174, 175, 176, 177, 
	79, 79, 79, 79, 155, 178, 79, 79, 
	79, 79, 155, 179, 79, 79, 79, 79, 
	155, 180, 79, 79, 79, 79, 155, 79, 
	181, 79, 79, 79, 155, 79, 182, 79, 
	79, 79, 155, 79, 79, 79, 79, 155, 
	79, 183, 79, 79, 79, 155, 79, 184, 
	79, 79, 79, 155, 79, 185, 79, 79, 
	79, 155, 79, 186, 79, 79, 79, 155, 
	79, 187, 79, 79, 79, 155, 79, 188, 
	79, 79, 79, 155, 79, 189, 79, 79, 
	79, 155, 79, 190, 191, 79, 79, 79, 
	155, 79, 167, 79, 79, 79, 155, 79, 
	192, 79, 79, 79, 155, 79, 193, 79, 
	79, 79, 155, 79, 194, 79, 79, 79, 
	155, 79, 195, 79, 79, 79, 155, 79, 
	196, 79, 79, 79, 155, 79, 197, 79, 
	79, 79, 155, 79, 198, 79, 79, 79, 
	155, 79, 199, 79, 79, 79, 155, 79, 
	200, 79, 79, 79, 155, 201, 79, 79, 
	79, 155, 79, 202, 79, 79, 79, 155, 
	79, 203, 79, 79, 79, 155, 79, 204, 
	79, 79, 79, 155, 205, 206, 207, 208, 
	79, 79, 79, 79, 155, 209, 79, 79, 
	79, 79, 155, 210, 79, 79, 79, 79, 
	155, 211, 79, 79, 79, 79, 155, 61, 
	61, 0
};

static const unsigned char _Lexer_trans_targs[] = {
	46, 2, 1, 3, 4, 5, 6, 7, 
	9, 46, 10, 8, 11, 13, 15, 12, 
	14, 16, 46, 50, 46, 18, 46, 19, 
	20, 21, 18, 46, 19, 22, 46, 90, 
	24, 25, 26, 27, 24, 25, 26, 27, 
	46, 26, 29, 31, 29, 30, 31, 46, 
	32, 33, 29, 30, 31, 34, 36, 37, 
	38, 40, 39, 41, 43, 0, 154, 45, 
	155, 46, 46, 47, 48, 49, 87, 88, 
	89, 46, 99, 100, 94, 96, 46, 102, 
	103, 104, 107, 112, 119, 125, 128, 130, 
	135, 139, 46, 46, 46, 46, 46, 51, 
	54, 59, 63, 69, 71, 76, 78, 46, 
	52, 53, 17, 55, 56, 57, 58, 60, 
	61, 62, 64, 65, 66, 67, 68, 70, 
	72, 73, 74, 75, 77, 79, 80, 81, 
	82, 83, 84, 85, 86, 46, 18, 19, 
	46, 23, 46, 91, 92, 46, 93, 93, 
	46, 46, 95, 97, 98, 97, 98, 101, 
	46, 28, 35, 46, 105, 106, 102, 108, 
	109, 110, 111, 102, 113, 116, 114, 115, 
	102, 117, 118, 102, 120, 121, 122, 123, 
	124, 102, 102, 102, 102, 126, 127, 129, 
	102, 131, 132, 133, 134, 102, 136, 137, 
	138, 102, 140, 141, 142, 143, 144, 145, 
	146, 147, 148, 149, 150, 151, 152, 153, 
	102, 102, 102, 102
};

static const unsigned char _Lexer_trans_actions[] = {
	63, 0, 0, 0, 0, 0, 0, 0, 
	0, 25, 0, 0, 0, 0, 0, 0, 
	0, 0, 61, 0, 65, 11, 74, 11, 
	0, 0, 13, 77, 13, 0, 67, 0, 
	0, 0, 0, 0, 7, 7, 7, 7, 
	27, 9, 15, 15, 11, 11, 11, 23, 
	0, 0, 13, 13, 13, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 1, 0, 
	1, 41, 39, 0, 21, 0, 21, 0, 
	21, 29, 0, 21, 0, 0, 35, 95, 
	21, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 31, 33, 71, 53, 59, 0, 
	0, 0, 0, 0, 0, 0, 0, 51, 
	0, 21, 0, 0, 0, 0, 21, 0, 
	0, 21, 0, 21, 21, 21, 21, 21, 
	0, 0, 0, 21, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 55, 15, 15, 
	37, 0, 45, 0, 0, 47, 89, 86, 
	69, 43, 0, 89, 89, 83, 80, 0, 
	57, 0, 0, 49, 0, 0, 98, 0, 
	0, 0, 0, 128, 0, 0, 0, 0, 
	92, 0, 0, 125, 0, 0, 0, 0, 
	0, 101, 104, 107, 110, 0, 0, 0, 
	131, 0, 0, 0, 0, 134, 0, 0, 
	0, 137, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	113, 116, 119, 122
};

static const unsigned char _Lexer_to_state_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 17, 0, 17, 0, 17, 0, 
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
	0, 0, 0, 0
};

static const unsigned char _Lexer_from_state_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 19, 0, 
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
	0, 0, 0, 0
};

static const unsigned char _Lexer_eof_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 3, 0, 5, 0, 0, 
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
	0, 0, 0, 0
};

static const short _Lexer_eof_trans[] = {
	0, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 19, 21, 21, 21, 21, 21, 31, 
	31, 31, 31, 31, 31, 31, 31, 31, 
	31, 31, 31, 31, 31, 31, 31, 31, 
	31, 31, 0, 0, 0, 0, 0, 93, 
	94, 95, 104, 104, 104, 104, 104, 104, 
	104, 104, 104, 104, 104, 104, 104, 104, 
	104, 104, 104, 104, 104, 104, 104, 104, 
	104, 104, 104, 104, 104, 104, 104, 104, 
	104, 104, 104, 104, 104, 104, 104, 134, 
	95, 95, 139, 142, 142, 145, 146, 142, 
	146, 145, 145, 95, 95, 153, 145, 95, 
	156, 156, 156, 156, 156, 156, 156, 156, 
	156, 156, 156, 156, 156, 156, 156, 156, 
	156, 156, 156, 156, 156, 156, 156, 156, 
	156, 156, 156, 156, 156, 156, 156, 156, 
	156, 156, 156, 156, 156, 156, 156, 156, 
	156, 156, 156, 156, 156, 156, 156, 156, 
	156, 156, 0, 0
};

static const int Lexer_start = 46;
static const int Lexer_first_final = 46;
static const int Lexer_error = 0;

static const int Lexer_en_recover_character_literal = 42;
static const int Lexer_en_recover_string_literal = 44;
static const int Lexer_en_main = 46;


#line 135 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"



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

	
#line 563 ".\\Lexer.cpp"
	{
	cs = Lexer_start;
	ts = 0;
	te = 0;
	act = 0;
	}

#line 156 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	
#line 569 ".\\Lexer.cpp"
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
#line 588 ".\\Lexer.cpp"
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
	{
		error("lex.invalid_character"); 
		{cs = 46; goto _again;}
	}
	break;
	case 3:
#line 38 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{ context.line++; context.line_start = p;}
	break;
	case 4:
#line 48 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{error("lex.nested_block_comment");}
	break;
	case 5:
#line 55 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{context.characters_consumed++;}
	break;
	case 6:
#line 55 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{context.characters_consumed++;}
	break;
	case 7:
#line 55 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{context.characters_consumed = 0;}
	break;
	case 10:
#line 1 "NONE"
	{te = p+1;}
	break;
	case 11:
#line 74 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{act = 2;}
	break;
	case 12:
#line 75 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{act = 3;}
	break;
	case 13:
#line 76 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{act = 4;}
	break;
	case 14:
#line 79 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{act = 5;}
	break;
	case 15:
#line 82 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{act = 6;}
	break;
	case 16:
#line 85 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{act = 7;}
	break;
	case 17:
#line 90 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{act = 10;}
	break;
	case 18:
#line 91 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{act = 11;}
	break;
	case 19:
#line 92 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{act = 12;}
	break;
	case 20:
#line 93 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{act = 13;}
	break;
	case 21:
#line 94 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{act = 14;}
	break;
	case 22:
#line 95 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{act = 15;}
	break;
	case 23:
#line 96 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{act = 16;}
	break;
	case 24:
#line 97 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{act = 17;}
	break;
	case 25:
#line 98 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{act = 18;}
	break;
	case 26:
#line 99 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{act = 19;}
	break;
	case 27:
#line 100 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{act = 20;}
	break;
	case 28:
#line 101 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{act = 21;}
	break;
	case 29:
#line 102 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{act = 22;}
	break;
	case 30:
#line 103 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{act = 23;}
	break;
	case 31:
#line 105 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p+1;{ arraytype();}}
	break;
	case 32:
#line 109 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p+1;{ literal(openddl::Token::kStringLiteral);}}
	break;
	case 33:
#line 114 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p+1;{ if(context.characters_consumed > 7) error("lex.character_length_error"); else literal(openddl::Token::kCharacterLiteral);}}
	break;
	case 34:
#line 120 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p+1;}
	break;
	case 35:
#line 123 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p+1;{ token(openddl::Token::kComma);}}
	break;
	case 36:
#line 124 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p+1;{ token(openddl::Token::kLeftBrace);}}
	break;
	case 37:
#line 125 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p+1;{ token(openddl::Token::kRightBrace);}}
	break;
	case 38:
#line 126 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p+1;{ token(openddl::Token::kEquals);}}
	break;
	case 39:
#line 127 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p+1;{error("lex.trailing_close_comment");}}
	break;
	case 40:
#line 129 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p+1;}
	break;
	case 41:
#line 131 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p+1;{ error("lex.unrecognised_character");}}
	break;
	case 42:
#line 73 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p;p--;{ literal(openddl::Token::kDecimalLiteral); }}
	break;
	case 43:
#line 76 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p;p--;{ literal(openddl::Token::kFloatLiteral);}}
	break;
	case 44:
#line 79 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p;p--;{ error("lex.invalid_literal");}}
	break;
	case 45:
#line 85 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p;p--;{ token(openddl::Token::kName);}}
	break;
	case 46:
#line 86 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p;p--;{ token(openddl::Token::kIdentifier);}}
	break;
	case 47:
#line 111 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p;p--;{ {cs = 44; goto _again;}}}
	break;
	case 48:
#line 116 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p;p--;{ {cs = 42; goto _again;}}}
	break;
	case 49:
#line 119 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p;p--;}
	break;
	case 50:
#line 130 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p;p--;}
	break;
	case 51:
#line 131 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p;p--;{ error("lex.unrecognised_character");}}
	break;
	case 52:
#line 86 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{{p = ((te))-1;}{ token(openddl::Token::kIdentifier);}}
	break;
	case 53:
#line 111 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{{p = ((te))-1;}{ {cs = 44; goto _again;}}}
	break;
	case 54:
#line 116 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{{p = ((te))-1;}{ {cs = 42; goto _again;}}}
	break;
	case 55:
#line 131 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{{p = ((te))-1;}{ error("lex.unrecognised_character");}}
	break;
	case 56:
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
#line 877 ".\\Lexer.cpp"
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
#line 888 ".\\Lexer.cpp"
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
#line 27 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{
		error("lex.unterminated_character_literal");
	}
	break;
	case 2:
#line 32 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{
		error("lex.unterminated_string_literal");
	}
	break;
#line 916 ".\\Lexer.cpp"
		}
	}
	}

	_out: {}
	}

#line 157 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	
	return (p==pe);
}

