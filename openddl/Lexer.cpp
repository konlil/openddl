
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
	7, 1, 8, 1, 9, 1, 30, 1, 
	32, 1, 33, 1, 34, 1, 35, 1, 
	36, 1, 37, 1, 38, 1, 39, 1, 
	40, 1, 41, 1, 42, 1, 43, 1, 
	44, 1, 45, 1, 46, 1, 47, 1, 
	48, 1, 49, 1, 51, 1, 52, 1, 
	53, 1, 54, 1, 55, 1, 56, 2, 
	0, 31, 2, 5, 50, 2, 9, 10, 
	2, 9, 11, 2, 9, 12, 2, 9, 
	13, 2, 9, 14, 2, 9, 15, 2, 
	9, 16, 2, 9, 17, 2, 9, 18, 
	2, 9, 19, 2, 9, 20, 2, 9, 
	21, 2, 9, 22, 2, 9, 23, 2, 
	9, 24, 2, 9, 25, 2, 9, 26, 
	2, 9, 27, 2, 9, 28, 2, 9, 
	29
};

static const short _Lexer_key_offsets[] = {
	0, 0, 2, 16, 18, 20, 22, 24, 
	27, 29, 31, 45, 51, 57, 63, 69, 
	75, 81, 88, 92, 104, 110, 116, 118, 
	121, 124, 127, 130, 131, 132, 133, 134, 
	169, 169, 183, 196, 203, 211, 219, 227, 
	235, 243, 251, 259, 267, 275, 283, 291, 
	299, 307, 315, 326, 334, 342, 350, 358, 
	366, 374, 382, 390, 398, 406, 414, 422, 
	430, 438, 446, 454, 462, 470, 478, 485, 
	493, 498, 499, 503, 512, 517, 526, 533, 
	547, 554, 564, 571, 582, 584, 586, 587, 
	594, 602, 610, 618, 626, 634, 642, 650, 
	658, 667, 675, 683, 691, 699, 707, 715, 
	723, 731, 742, 750, 758, 766, 774, 782, 
	789, 797, 805, 813, 821, 829, 837, 845, 
	854, 862, 870, 878, 886, 894, 902, 910, 
	918, 926, 934, 941, 949, 957, 965, 976, 
	984, 992, 1000, 1000
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
	69, 93, 101, 125, 1, 32, 48, 57, 
	44, 93, 125, 1, 32, 44, 93, 125, 
	1, 32, 43, 45, 48, 57, 44, 93, 
	125, 1, 32, 48, 57, 44, 46, 66, 
	69, 88, 93, 98, 101, 120, 125, 1, 
	32, 48, 57, 44, 93, 125, 1, 32, 
	48, 57, 44, 46, 69, 93, 101, 125, 
	1, 32, 48, 57, 44, 93, 125, 1, 
	32, 48, 49, 44, 93, 125, 1, 32, 
	48, 57, 65, 70, 97, 102, 48, 57, 
	42, 47, 10, 95, 48, 57, 65, 90, 
	97, 122, 95, 111, 48, 57, 65, 90, 
	97, 122, 95, 111, 48, 57, 65, 90, 
	97, 122, 95, 108, 48, 57, 65, 90, 
	97, 122, 95, 111, 48, 57, 65, 90, 
	97, 122, 95, 117, 48, 57, 65, 90, 
	97, 122, 95, 98, 48, 57, 65, 90, 
	97, 122, 95, 108, 48, 57, 65, 90, 
	97, 122, 95, 101, 48, 57, 65, 90, 
	97, 122, 95, 97, 108, 48, 57, 65, 
	90, 98, 122, 95, 108, 48, 57, 65, 
	90, 97, 122, 95, 115, 48, 57, 65, 
	90, 97, 122, 95, 101, 48, 57, 65, 
	90, 97, 122, 95, 111, 48, 57, 65, 
	90, 97, 122, 95, 97, 48, 57, 65, 
	90, 98, 122, 95, 116, 48, 57, 65, 
	90, 97, 122, 95, 110, 48, 57, 65, 
	90, 97, 122, 95, 116, 48, 57, 65, 
	90, 97, 122, 49, 51, 54, 56, 95, 
	48, 57, 65, 90, 97, 122, 54, 95, 
	48, 57, 65, 90, 97, 122, 50, 95, 
	48, 57, 65, 90, 97, 122, 52, 95, 
	48, 57, 65, 90, 97, 122, 95, 117, 
	48, 57, 65, 90, 97, 122, 95, 108, 
	48, 57, 65, 90, 97, 122, 95, 48, 
	57, 65, 90, 97, 122, 95, 101, 48, 
	57, 65, 90, 97, 122, 95, 102, 48, 
	57, 65, 90, 97, 122, 95, 116, 48, 
	57, 65, 90, 97, 122, 95, 114, 48, 
	57, 65, 90, 97, 122, 95, 105, 48, 
	57, 65, 90, 97, 122, 95, 110, 48, 
	57, 65, 90, 97, 122, 95, 103, 48, 
	57, 65, 90, 97, 122, 95, 114, 121, 
	48, 57, 65, 90, 97, 122, 95, 117, 
	48, 57, 65, 90, 97, 122, 95, 112, 
	48, 57, 65, 90, 97, 122, 95, 101, 
	48, 57, 65, 90, 97, 122, 95, 110, 
	48, 57, 65, 90, 97, 122, 95, 115, 
	48, 57, 65, 90, 97, 122, 95, 105, 
	48, 57, 65, 90, 97, 122, 95, 103, 
	48, 57, 65, 90, 97, 122, 95, 110, 
	48, 57, 65, 90, 97, 122, 95, 101, 
	48, 57, 65, 90, 97, 122, 95, 100, 
	48, 57, 65, 90, 97, 122, 95, 48, 
	57, 65, 90, 97, 122, 95, 105, 48, 
	57, 65, 90, 97, 122, 95, 110, 48, 
	57, 65, 90, 97, 122, 95, 116, 48, 
	57, 65, 90, 97, 122, 49, 51, 54, 
	56, 95, 48, 57, 65, 90, 97, 122, 
	54, 95, 48, 57, 65, 90, 97, 122, 
	50, 95, 48, 57, 65, 90, 97, 122, 
	52, 95, 48, 57, 65, 90, 97, 122, 
	0
};

static const char _Lexer_single_lengths[] = {
	0, 0, 6, 0, 0, 0, 0, 1, 
	0, 0, 10, 0, 0, 0, 0, 0, 
	0, 1, 2, 10, 0, 0, 0, 3, 
	3, 3, 3, 1, 1, 1, 1, 23, 
	0, 6, 9, 1, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 5, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 1, 2, 
	1, 1, 2, 5, 3, 3, 3, 10, 
	3, 6, 3, 3, 0, 2, 1, 1, 
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
	3, 3, 1, 1, 3, 3, 1, 0, 
	0, 0, 0, 0, 0, 0, 0, 6, 
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
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 0, 0
};

static const short _Lexer_index_offsets[] = {
	0, 0, 2, 13, 15, 17, 19, 21, 
	24, 26, 28, 41, 45, 49, 53, 57, 
	61, 65, 70, 74, 86, 90, 94, 96, 
	100, 104, 108, 112, 114, 116, 118, 120, 
	150, 151, 162, 174, 179, 185, 191, 197, 
	203, 209, 215, 221, 227, 233, 239, 245, 
	251, 257, 263, 272, 278, 284, 290, 296, 
	302, 308, 314, 320, 326, 332, 338, 344, 
	350, 356, 362, 368, 374, 380, 386, 391, 
	397, 401, 403, 407, 415, 420, 427, 433, 
	446, 452, 461, 467, 475, 477, 480, 482, 
	487, 493, 499, 505, 511, 517, 523, 529, 
	535, 542, 548, 554, 560, 566, 572, 578, 
	584, 590, 599, 605, 611, 617, 623, 629, 
	634, 640, 646, 652, 658, 664, 670, 676, 
	683, 689, 695, 701, 707, 713, 719, 725, 
	731, 737, 743, 748, 754, 760, 766, 775, 
	781, 787, 793, 794
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
	30, 31, 32, 29, 34, 35, 36, 33, 
	30, 31, 37, 29, 30, 38, 32, 29, 
	40, 39, 41, 39, 40, 42, 43, 42, 
	46, 47, 49, 50, 52, 53, 54, 55, 
	57, 59, 60, 58, 61, 62, 63, 64, 
	65, 66, 67, 68, 69, 70, 71, 45, 
	48, 51, 56, 58, 58, 44, 72, 2, 
	4, 6, 7, 9, 10, 3, 5, 8, 
	1, 73, 19, 75, 76, 77, 78, 79, 
	80, 81, 82, 19, 19, 74, 19, 19, 
	19, 19, 83, 19, 84, 19, 19, 19, 
	83, 19, 85, 19, 19, 19, 83, 19, 
	86, 19, 19, 19, 83, 19, 87, 19, 
	19, 19, 83, 19, 88, 19, 19, 19, 
	83, 19, 89, 19, 19, 19, 83, 19, 
	90, 19, 19, 19, 83, 19, 86, 19, 
	19, 19, 83, 19, 91, 19, 19, 19, 
	83, 19, 92, 19, 19, 19, 83, 19, 
	93, 19, 19, 19, 83, 19, 86, 19, 
	19, 19, 83, 19, 94, 19, 19, 19, 
	83, 19, 95, 19, 19, 19, 83, 96, 
	97, 98, 86, 19, 19, 19, 19, 83, 
	86, 19, 19, 19, 19, 83, 86, 19, 
	19, 19, 19, 83, 86, 19, 19, 19, 
	19, 83, 19, 99, 19, 19, 19, 83, 
	19, 86, 19, 19, 19, 83, 19, 100, 
	19, 19, 19, 83, 19, 101, 19, 19, 
	19, 83, 19, 102, 19, 19, 19, 83, 
	19, 103, 19, 19, 19, 83, 19, 86, 
	19, 19, 19, 83, 19, 104, 19, 19, 
	19, 83, 19, 90, 19, 19, 19, 83, 
	19, 105, 19, 19, 19, 83, 19, 106, 
	19, 19, 19, 83, 19, 107, 19, 19, 
	19, 83, 19, 108, 19, 19, 19, 83, 
	19, 109, 19, 19, 19, 83, 19, 110, 
	19, 19, 19, 83, 19, 111, 19, 19, 
	19, 83, 112, 19, 19, 19, 83, 19, 
	78, 19, 19, 19, 83, 115, 114, 114, 
	113, 116, 74, 117, 55, 56, 74, 118, 
	120, 118, 120, 118, 118, 28, 119, 121, 
	121, 121, 121, 119, 121, 121, 121, 121, 
	122, 123, 119, 124, 124, 124, 124, 123, 
	119, 125, 126, 127, 120, 128, 125, 127, 
	120, 128, 125, 125, 56, 119, 121, 121, 
	121, 121, 28, 119, 125, 126, 120, 125, 
	120, 125, 125, 56, 119, 124, 124, 124, 
	124, 129, 119, 124, 124, 124, 124, 130, 
	130, 130, 119, 28, 74, 29, 131, 74, 
	132, 131, 58, 58, 58, 58, 124, 58, 
	134, 58, 58, 58, 133, 58, 135, 58, 
	58, 58, 133, 58, 136, 58, 58, 58, 
	133, 58, 137, 58, 58, 58, 133, 58, 
	138, 58, 58, 58, 133, 58, 139, 58, 
	58, 58, 133, 58, 140, 58, 58, 58, 
	133, 58, 141, 58, 58, 58, 133, 58, 
	142, 143, 58, 58, 58, 133, 58, 144, 
	58, 58, 58, 133, 58, 145, 58, 58, 
	58, 133, 58, 146, 58, 58, 58, 133, 
	58, 147, 58, 58, 58, 133, 58, 148, 
	58, 58, 58, 133, 58, 149, 58, 58, 
	58, 133, 58, 150, 58, 58, 58, 133, 
	58, 151, 58, 58, 58, 133, 152, 153, 
	154, 155, 58, 58, 58, 58, 133, 156, 
	58, 58, 58, 58, 133, 157, 58, 58, 
	58, 58, 133, 158, 58, 58, 58, 58, 
	133, 58, 159, 58, 58, 58, 133, 58, 
	160, 58, 58, 58, 133, 58, 58, 58, 
	58, 133, 58, 161, 58, 58, 58, 133, 
	58, 162, 58, 58, 58, 133, 58, 163, 
	58, 58, 58, 133, 58, 164, 58, 58, 
	58, 133, 58, 165, 58, 58, 58, 133, 
	58, 166, 58, 58, 58, 133, 58, 167, 
	58, 58, 58, 133, 58, 168, 169, 58, 
	58, 58, 133, 58, 145, 58, 58, 58, 
	133, 58, 170, 58, 58, 58, 133, 58, 
	171, 58, 58, 58, 133, 58, 172, 58, 
	58, 58, 133, 58, 173, 58, 58, 58, 
	133, 58, 174, 58, 58, 58, 133, 58, 
	175, 58, 58, 58, 133, 58, 176, 58, 
	58, 58, 133, 58, 177, 58, 58, 58, 
	133, 58, 178, 58, 58, 58, 133, 179, 
	58, 58, 58, 133, 58, 180, 58, 58, 
	58, 133, 58, 181, 58, 58, 58, 133, 
	58, 182, 58, 58, 58, 133, 183, 184, 
	185, 186, 58, 58, 58, 58, 133, 187, 
	58, 58, 58, 58, 133, 188, 58, 58, 
	58, 58, 133, 189, 58, 58, 58, 58, 
	133, 40, 40, 0
};

static const unsigned char _Lexer_trans_targs[] = {
	31, 2, 1, 3, 4, 5, 6, 7, 
	9, 31, 10, 8, 11, 13, 15, 12, 
	14, 16, 31, 35, 31, 18, 31, 19, 
	18, 20, 21, 31, 75, 23, 24, 25, 
	26, 23, 24, 25, 26, 31, 25, 28, 
	0, 138, 30, 139, 31, 31, 32, 33, 
	34, 72, 73, 74, 31, 84, 85, 79, 
	81, 31, 87, 31, 31, 88, 91, 96, 
	103, 109, 112, 114, 119, 123, 31, 31, 
	31, 31, 31, 36, 39, 44, 48, 54, 
	56, 61, 63, 31, 37, 38, 17, 40, 
	41, 42, 43, 45, 46, 47, 49, 50, 
	51, 52, 53, 55, 57, 58, 59, 60, 
	62, 64, 65, 66, 67, 68, 69, 70, 
	71, 31, 18, 19, 31, 22, 31, 76, 
	77, 31, 78, 78, 31, 31, 80, 82, 
	83, 82, 83, 86, 31, 31, 89, 90, 
	87, 92, 93, 94, 95, 87, 97, 100, 
	98, 99, 87, 101, 102, 87, 104, 105, 
	106, 107, 108, 87, 87, 87, 87, 110, 
	111, 113, 87, 115, 116, 117, 118, 87, 
	120, 121, 122, 87, 124, 125, 126, 127, 
	128, 129, 130, 131, 132, 133, 134, 135, 
	136, 137, 87, 87, 87, 87
};

static const unsigned char _Lexer_trans_actions[] = {
	63, 0, 0, 0, 0, 0, 0, 0, 
	0, 21, 0, 0, 0, 0, 0, 0, 
	0, 0, 61, 0, 65, 1, 71, 1, 
	0, 0, 0, 67, 0, 0, 0, 0, 
	0, 11, 11, 11, 11, 23, 13, 0, 
	0, 5, 0, 5, 41, 39, 0, 19, 
	0, 19, 0, 19, 25, 0, 19, 0, 
	0, 35, 92, 31, 33, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 27, 29, 
	74, 53, 59, 0, 0, 0, 0, 0, 
	0, 0, 0, 51, 0, 19, 0, 0, 
	0, 0, 19, 0, 0, 19, 0, 19, 
	19, 19, 19, 19, 0, 0, 0, 19, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 55, 3, 3, 37, 0, 45, 0, 
	0, 47, 86, 83, 69, 43, 0, 86, 
	86, 80, 77, 0, 57, 49, 0, 0, 
	95, 0, 0, 0, 0, 125, 0, 0, 
	0, 0, 89, 0, 0, 122, 0, 0, 
	0, 0, 0, 98, 101, 104, 107, 0, 
	0, 0, 128, 0, 0, 0, 0, 131, 
	0, 0, 0, 134, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 110, 113, 116, 119
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
	0, 0, 0, 0
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
	0, 0, 0, 0
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
	0, 0, 0, 0
};

static const short _Lexer_eof_trans[] = {
	0, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 19, 21, 21, 21, 21, 28, 28, 
	28, 28, 28, 0, 0, 0, 0, 0, 
	73, 74, 75, 84, 84, 84, 84, 84, 
	84, 84, 84, 84, 84, 84, 84, 84, 
	84, 84, 84, 84, 84, 84, 84, 84, 
	84, 84, 84, 84, 84, 84, 84, 84, 
	84, 84, 84, 84, 84, 84, 84, 84, 
	114, 75, 75, 119, 122, 122, 125, 126, 
	122, 126, 125, 125, 75, 75, 133, 125, 
	134, 134, 134, 134, 134, 134, 134, 134, 
	134, 134, 134, 134, 134, 134, 134, 134, 
	134, 134, 134, 134, 134, 134, 134, 134, 
	134, 134, 134, 134, 134, 134, 134, 134, 
	134, 134, 134, 134, 134, 134, 134, 134, 
	134, 134, 134, 134, 134, 134, 134, 134, 
	134, 134, 0, 0
};

static const int Lexer_start = 31;
static const int Lexer_first_final = 31;
static const int Lexer_error = 0;

static const int Lexer_en_recover_character_literal = 27;
static const int Lexer_en_recover_string_literal = 29;
static const int Lexer_en_main = 31;


#line 139 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"



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

	
#line 523 ".\\Lexer.cpp"
	{
	cs = Lexer_start;
	ts = 0;
	te = 0;
	act = 0;
	}

#line 160 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	
#line 529 ".\\Lexer.cpp"
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
	case 8:
#line 1 "NONE"
	{ts = p;}
	break;
#line 548 ".\\Lexer.cpp"
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
#line 40 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{ context.new_line(p);}
	break;
	case 6:
#line 50 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{error("lex.nested_block_comment");}
	break;
	case 9:
#line 1 "NONE"
	{te = p+1;}
	break;
	case 10:
#line 76 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{act = 2;}
	break;
	case 11:
#line 77 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{act = 3;}
	break;
	case 12:
#line 78 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{act = 4;}
	break;
	case 13:
#line 81 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{act = 5;}
	break;
	case 14:
#line 84 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{act = 6;}
	break;
	case 15:
#line 87 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{act = 7;}
	break;
	case 16:
#line 92 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{act = 10;}
	break;
	case 17:
#line 93 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{act = 11;}
	break;
	case 18:
#line 94 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{act = 12;}
	break;
	case 19:
#line 95 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{act = 13;}
	break;
	case 20:
#line 96 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{act = 14;}
	break;
	case 21:
#line 97 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{act = 15;}
	break;
	case 22:
#line 98 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{act = 16;}
	break;
	case 23:
#line 99 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{act = 17;}
	break;
	case 24:
#line 100 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{act = 18;}
	break;
	case 25:
#line 101 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{act = 19;}
	break;
	case 26:
#line 102 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{act = 20;}
	break;
	case 27:
#line 103 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{act = 21;}
	break;
	case 28:
#line 104 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{act = 22;}
	break;
	case 29:
#line 105 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{act = 23;}
	break;
	case 30:
#line 111 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p+1;{ literal(openddl::Token::kStringLiteral);}}
	break;
	case 31:
#line 116 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p+1;{ if(context.get_character_count() > 7) error("lex.character_length_error"); else literal(openddl::Token::kCharacterLiteral);}}
	break;
	case 32:
#line 122 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p+1;}
	break;
	case 33:
#line 125 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p+1;{ token(openddl::Token::kComma);}}
	break;
	case 34:
#line 126 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p+1;{ token(openddl::Token::kLeftBrace);}}
	break;
	case 35:
#line 127 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p+1;{ token(openddl::Token::kRightBrace);}}
	break;
	case 36:
#line 128 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p+1;{ token(openddl::Token::kLeftSquareBracket);}}
	break;
	case 37:
#line 129 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p+1;{ token(openddl::Token::kRightSquareBracket);}}
	break;
	case 38:
#line 130 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p+1;{ token(openddl::Token::kEquals);}}
	break;
	case 39:
#line 131 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p+1;{error("lex.trailing_close_comment");}}
	break;
	case 40:
#line 133 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p+1;}
	break;
	case 41:
#line 135 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p+1;{ error("lex.unrecognised_character");}}
	break;
	case 42:
#line 75 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p;p--;{ literal(openddl::Token::kDecimalLiteral); }}
	break;
	case 43:
#line 78 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p;p--;{ literal(openddl::Token::kFloatLiteral);}}
	break;
	case 44:
#line 81 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p;p--;{ error("lex.invalid_literal");}}
	break;
	case 45:
#line 87 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p;p--;{ token(openddl::Token::kName);}}
	break;
	case 46:
#line 88 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p;p--;{ token(openddl::Token::kIdentifier);}}
	break;
	case 47:
#line 113 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p;p--;{ {cs = 29; goto _again;}}}
	break;
	case 48:
#line 118 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p;p--;{ {cs = 27; goto _again;}}}
	break;
	case 49:
#line 121 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p;p--;}
	break;
	case 50:
#line 134 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p;p--;}
	break;
	case 51:
#line 135 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{te = p;p--;{ error("lex.unrecognised_character");}}
	break;
	case 52:
#line 88 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{{p = ((te))-1;}{ token(openddl::Token::kIdentifier);}}
	break;
	case 53:
#line 113 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{{p = ((te))-1;}{ {cs = 29; goto _again;}}}
	break;
	case 54:
#line 118 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	{{p = ((te))-1;}{ {cs = 27; goto _again;}}}
	break;
	case 55:
#line 135 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
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
#line 837 ".\\Lexer.cpp"
		}
	}

_again:
	_acts = _Lexer_actions + _Lexer_to_state_actions[cs];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 ) {
		switch ( *_acts++ ) {
	case 7:
#line 1 "NONE"
	{ts = 0;}
	break;
#line 848 ".\\Lexer.cpp"
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
#line 876 ".\\Lexer.cpp"
		}
	}
	}

	_out: {}
	}

#line 161 "C:/Users/Denis/Development/openddl/openddl/Lexer.rl"
	
	return (p==pe);
}

