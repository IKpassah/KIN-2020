#pragma once
#include "stdafx.h"
#include "FST.h"
#include "LT.h"
#include "IT.h"


#define STANDART_FUNC1 "abs"
#define STANDART_FUNC2 "pow"
#define STANDART_FUNC3 "strcat"

#define SPACE_RG ' '

#define PHRASES_MAXSIZE 31

#define FSTS

#ifdef FSTS
#pragma once

#define EQUAL_FST\
	{ {\
	(unsigned char*)"",\
	 2,\
	FST::NODE(1, FST::RELATION('=', 1)),\
	FST::NODE()},LEX_EQUAL, IT::IDTYPE::NDEFT, IT::IDDATATYPE::NDEFD}

#define SEMICOLON_FST\
	{ {\
	(unsigned char*)"",\
	2,\
	FST::NODE(1, FST::RELATION(';', 1)),\
	FST::NODE()},LEX_SEMICOLON, IT::IDTYPE::NDEFT, IT::IDDATATYPE::NDEFD}

#define COMMA_FST\
	{ {\
	(unsigned char*)"",\
	2,\
	FST::NODE(1, FST::RELATION(',', 1)),\
	FST::NODE()},LEX_COMMA, IT::IDTYPE::NDEFT, IT::IDDATATYPE::NDEFD}

#define LEFTBRACE_FST\
	{ {\
	(unsigned char*)"",\
	2,\
	FST::NODE(1, FST::RELATION('{', 1)),\
	FST::NODE()},LEX_LEFTBRACE, IT::IDTYPE::NDEFT, IT::IDDATATYPE::NDEFD}

#define BRACELET_FST\
	{ {\
	(unsigned char*)"",\
	2,\
	FST::NODE(1, FST::RELATION('}', 1)),\
	FST::NODE()},LEX_BRACELET, IT::IDTYPE::NDEFT, IT::IDDATATYPE::NDEFD}

#define LEFTHESIS_FST\
	{ {\
	(unsigned char*)"",\
	2,\
	FST::NODE(1, FST::RELATION('(', 1)),\
	FST::NODE()},LEX_LEFTHESIS,IT::IDTYPE::NDEFT, IT::IDDATATYPE::NDEFD}

#define RIGHTHESIS_FST\
	{ {\
	(unsigned char*)"",\
	2,\
	FST::NODE(1, FST::RELATION(')', 1)),\
	FST::NODE()},LEX_RIGHTHESIS, IT::IDTYPE::NDEFT, IT::IDDATATYPE::NDEFD}

#define PLUS_FST\
	{ { (unsigned char*)"", 2,\
	FST::NODE(1, FST::RELATION('+', 1)),\
	FST::NODE() }, LEX_PLUS, IT::IDTYPE::NDEFT, IT::IDDATATYPE::NDEFD }

#define DIRSLASH_FST\
		{ { (unsigned char*)"", 2,\
	FST::NODE(1, FST::RELATION('/', 1)),\
	FST::NODE() }, LEX_DIRSLASH, IT::IDTYPE::NDEFT, IT::IDDATATYPE::NDEFD }

#define MINUS_FST\
	{ { (unsigned char*)"", 2,\
	FST::NODE(1, FST::RELATION('-', 1)),\
	FST::NODE() }, LEX_MINUS, IT::IDTYPE::NDEFT, IT::IDDATATYPE::NDEFD }
#define STAR_FST\
	{ { (unsigned char*)"", 2,\
	FST::NODE(1, FST::RELATION('*', 1)),\
	FST::NODE() }, LEX_STAR, IT::IDTYPE::NDEFT, IT::IDDATATYPE::NDEFD }
#define PERC_FST\
	{ { (unsigned char*)"", 2,\
	FST::NODE(1, FST::RELATION('%', 1)),\
	FST::NODE() }, LEX_PERC, IT::IDTYPE::NDEFT, IT::IDDATATYPE::NDEFD }

#define MORE_FST\
	{ { (unsigned char*)"", 2,\
	FST::NODE(1, FST::RELATION('>', 1)),\
	FST::NODE() }, LEX_MORE, IT::IDTYPE::NDEFT, IT::IDDATATYPE::NDEFD }
#define LESS_FST\
	{ { (unsigned char*)"", 2,\
	FST::NODE(1, FST::RELATION('<', 1)),\
	FST::NODE() }, LEX_LESS, IT::IDTYPE::NDEFT, IT::IDDATATYPE::NDEFD }
#define PEER_FST\
	{ { (unsigned char*)"", 2,\
	FST::NODE(1, FST::RELATION('&', 1)),\
	FST::NODE() }, LEX_PEER, IT::IDTYPE::NDEFT, IT::IDDATATYPE::NDEFD }
#define NPEER_FST\
	{ { (unsigned char*)"", 2,\
	FST::NODE(1, FST::RELATION('!', 1)),\
	FST::NODE() }, LEX_NPEER, IT::IDTYPE::NDEFT, IT::IDDATATYPE::NDEFD }

#define MAIN_FST\
	{ {\
	(unsigned char*)"",\
	6,\
	FST::NODE(1, FST::RELATION('m', 1)),\
	FST::NODE(1, FST::RELATION('a', 2)),\
	FST::NODE(1, FST::RELATION('j', 3)),\
	FST::NODE(1, FST::RELATION('o', 4)),\
	FST::NODE(1, FST::RELATION('r', 5)),\
	FST::NODE()},LEX_MAIN, IT::IDTYPE::F, IT::IDDATATYPE::NDEFD}

#define PRINT_FST\
	{ {\
	(unsigned char*)"",\
	7,\
	FST::NODE(1, FST::RELATION('o', 1)),\
	FST::NODE(1, FST::RELATION('u', 2)),\
	FST::NODE(1, FST::RELATION('t', 3)),\
	FST::NODE(1, FST::RELATION('p', 4)),\
	FST::NODE(1, FST::RELATION('u', 5)),\
	FST::NODE(1, FST::RELATION('t', 6)),\
	FST::NODE()},LEX_PRINT,IT::IDTYPE::NDEFT, IT::IDDATATYPE::NDEFD}

#define BYTE_FST\
	{ {\
	(unsigned char*)"",\
	5,\
	FST::NODE(1, FST::RELATION('b', 1)),\
	FST::NODE(1, FST::RELATION('y', 2)),\
	FST::NODE(1, FST::RELATION('t', 3)),\
	FST::NODE(1, FST::RELATION('e', 4)),\
	FST::NODE()},LEX_TYPE,IT::IDTYPE::NDEFT, IT::IDDATATYPE::BYTE}

#define BOOL_FST\
	{ {\
	(unsigned char*)"",\
	5,\
	FST::NODE(1, FST::RELATION('b', 1)),\
	FST::NODE(1, FST::RELATION('o', 2)),\
	FST::NODE(1, FST::RELATION('o', 3)),\
	FST::NODE(1, FST::RELATION('l', 4)),\
	FST::NODE()},LEX_TYPE,IT::IDTYPE::NDEFT, IT::IDDATATYPE::BOOL}

#define INTEGER_FST\
	{ {\
	(unsigned char*)"",\
	4,\
	FST::NODE(1, FST::RELATION('i', 1)),\
	FST::NODE(1, FST::RELATION('n', 2)),\
	FST::NODE(1, FST::RELATION('t', 3)),\
	FST::NODE()},LEX_TYPE,IT::IDTYPE::NDEFT,IT::IDDATATYPE::INT}

#define  STRING_FST\
	{ {\
	(unsigned char*)"",\
	4,\
	FST::NODE(1, FST::RELATION('s', 1)),\
	FST::NODE(1, FST::RELATION('t', 2)),\
	FST::NODE(1, FST::RELATION('r', 3)),\
	FST::NODE()},LEX_TYPE, IT::IDTYPE::NDEFT, IT::IDDATATYPE::STR}

#define DECLARE_FST\
	{ {\
	(unsigned char*)"",\
	8,\
	FST::NODE(1, FST::RELATION('d', 1)),\
	FST::NODE(1, FST::RELATION('e', 2)),\
	FST::NODE(1, FST::RELATION('c', 3)),\
	FST::NODE(1, FST::RELATION('l', 4)),\
	FST::NODE(1, FST::RELATION('a', 5)),\
	FST::NODE(1, FST::RELATION('r', 6)),\
	FST::NODE(1, FST::RELATION('e', 7)),\
	FST::NODE()},LEX_DECLARE, IT::IDTYPE::NDEFT, IT::IDDATATYPE::NDEFD}

#define RETURN_FST\
	{ {\
	(unsigned char*)"",\
	7,\
	FST::NODE(1, FST::RELATION('r', 1)),\
	FST::NODE(1, FST::RELATION('e', 2)),\
	FST::NODE(1, FST::RELATION('t', 3)),\
	FST::NODE(1, FST::RELATION('u', 4)),\
	FST::NODE(1, FST::RELATION('r', 5)),\
	FST::NODE(1, FST::RELATION('n', 6)),\
	FST::NODE()}, LEX_RETURN, IT::IDTYPE::NDEFT, IT::IDDATATYPE::NDEFD}

#define FUNCTION_FST\
	{ {\
	(unsigned char*)"",\
	9,\
	FST::NODE(1, FST::RELATION('f', 1)),\
	FST::NODE(1, FST::RELATION('u', 2)),\
	FST::NODE(1, FST::RELATION('n', 3)),\
	FST::NODE(1, FST::RELATION('c', 4)),\
	FST::NODE(1, FST::RELATION('t', 5)),\
	FST::NODE(1, FST::RELATION('i', 6)),\
	FST::NODE(1, FST::RELATION('o', 7)),\
	FST::NODE(1, FST::RELATION('n', 8)),\
	FST::NODE()}, LEX_FUNCTION, IT::IDTYPE::F, IT::IDDATATYPE::NDEFD}

#define TRUE_FST\
	{ {\
	(unsigned char*)"",\
	5,\
	FST::NODE(1, FST::RELATION('t', 1)),\
	FST::NODE(1, FST::RELATION('r', 2)),\
	FST::NODE(1, FST::RELATION('u', 3)),\
	FST::NODE(1, FST::RELATION('e', 4)),\
	FST::NODE()},LEX_LITERAL,IT::IDTYPE:L:, IT::IDDATATYPE::BOOL}

#define FALSE_FST\
	{ {\
	(unsigned char*)"",\
	6,\
	FST::NODE(1, FST::RELATION('f', 1)),\
	FST::NODE(1, FST::RELATION('a', 2)),\
	FST::NODE(1, FST::RELATION('l', 3)),\
	FST::NODE(1, FST::RELATION('s', 4)),\
	FST::NODE(1, FST::RELATION('e', 5)),\
	FST::NODE()},LEX_LITERAL,IT::IDTYPE::L, IT::IDDATATYPE::BOOL}

#define WHILE_FST\
	{ {\
	(unsigned char*)"",\
	6,\
	FST::NODE(1, FST::RELATION('w', 1)),\
	FST::NODE(1, FST::RELATION('h', 2)),\
	FST::NODE(1, FST::RELATION('i', 3)),\
	FST::NODE(1, FST::RELATION('l', 4)),\
	FST::NODE(1, FST::RELATION('e', 5)),\
	FST::NODE()},LEX_WHILE,IT::IDTYPE::NDEFT, IT::IDDATATYPE::NDEFD}

#define BREAK_FST\
	{ {\
	(unsigned char*)"",\
	6,\
	FST::NODE(1, FST::RELATION('b', 1)),\
	FST::NODE(1, FST::RELATION('r', 2)),\
	FST::NODE(1, FST::RELATION('e', 3)),\
	FST::NODE(1, FST::RELATION('a', 4)),\
	FST::NODE(1, FST::RELATION('k', 5)),\
	FST::NODE()},LEX_BREAK,IT::IDTYPE::NDEFT, IT::IDDATATYPE::NDEFD}

#define IF_FST\
	{ {\
	(unsigned char*)"",\
	3,\
	FST::NODE(1, FST::RELATION('i', 1)),\
	FST::NODE(1, FST::RELATION('f', 2)),\
	FST::NODE()},LEX_IF,IT::IDTYPE::NDEFT, IT::IDDATATYPE::NDEFD}

#define ELSE_FST\
	{ {\
	(unsigned char*)"",\
	5,\
	FST::NODE(1, FST::RELATION('e', 1)),\
	FST::NODE(1, FST::RELATION('l', 2)),\
	FST::NODE(1, FST::RELATION('s', 3)),\
	FST::NODE(1, FST::RELATION('e', 4)),\
	FST::NODE()},LEX_ELSE,IT::IDTYPE::NDEFT, IT::IDDATATYPE::NDEFD}

#define ID_FST\
	{ {\
	(unsigned char*)"",\
	2,\
	FST::NODE(52,\
		FST::RELATION('a', 0), FST::RELATION('b', 0), FST::RELATION('c', 0), FST::RELATION('d', 0),\
	    FST::RELATION('e', 0), FST::RELATION('f', 0), FST::RELATION('g', 0), FST::RELATION('h', 0),\
		FST::RELATION('i', 0), FST::RELATION('j', 0), FST::RELATION('k', 0), FST::RELATION('l', 0),\
		FST::RELATION('m', 0), FST::RELATION('n', 0), FST::RELATION('o', 0), FST::RELATION('p', 0),\
		FST::RELATION('q', 0), FST::RELATION('r', 0), FST::RELATION('s', 0), FST::RELATION('t', 0),\
		FST::RELATION('u', 0), FST::RELATION('v', 0), FST::RELATION('w', 0), FST::RELATION('x', 0),\
		FST::RELATION('y', 0), FST::RELATION('z', 0), FST::RELATION('a', 1), FST::RELATION('b', 1),\
		FST::RELATION('c', 1), FST::RELATION('d', 1), FST::RELATION('e', 1), FST::RELATION('f', 1),\
		FST::RELATION('g', 1), FST::RELATION('h', 1), FST::RELATION('i', 1), FST::RELATION('j', 1),\
		FST::RELATION('k', 1), FST::RELATION('l', 1), FST::RELATION('m', 1), FST::RELATION('n', 1),\
		FST::RELATION('o', 1), FST::RELATION('p', 1), FST::RELATION('q', 1), FST::RELATION('r', 1),\
		FST::RELATION('s', 1), FST::RELATION('t', 1), FST::RELATION('u', 1), FST::RELATION('v', 1),\
		FST::RELATION('w', 1), FST::RELATION('x', 1), FST::RELATION('y', 1), FST::RELATION('z', 1)),\
		FST::NODE()},LEX_ID, IT::IDTYPE::NDEFT,IT::IDDATATYPE::NDEFD}

#define  LITERAL_BYTE_FST\
	{ {(unsigned char*)"", 2,\
	FST::NODE(3,\
		FST::RELATION('0', 0),FST::RELATION('1', 0), FST::RELATION('b', 1)),\
	    FST::NODE()}, LEX_LITERAL, IT::IDTYPE::L,IT::IDDATATYPE::BYTE}

#define  LITERAL_NUM_FST\
	{ {(unsigned char*)"", 2,\
	FST::NODE(20,\
		FST::RELATION('0', 0), FST::RELATION('0', 1),\
		FST::RELATION('1', 0), FST::RELATION('1', 1),\
		FST::RELATION('2', 0), FST::RELATION('2', 1),\
		FST::RELATION('3', 0), FST::RELATION('3', 1),\
		FST::RELATION('4', 0), FST::RELATION('4', 1),\
		FST::RELATION('5', 0), FST::RELATION('5', 1),\
		FST::RELATION('6', 0), FST::RELATION('6', 1),\
		FST::RELATION('7', 0), FST::RELATION('7', 1),\
		FST::RELATION('8', 0), FST::RELATION('8', 1),\
		FST::RELATION('9', 0), FST::RELATION('9', 1)),\
	    FST::NODE()}, LEX_LITERAL, IT::IDTYPE::L,IT::IDDATATYPE::INT}

#define LITERAL_STR_FST\
	{ { (unsigned char*)"", 4,\
	FST::NODE(1, FST::RELATION('"', 1)),\
	FST::NODE(178+128,\
FST::RELATION('à', 1), FST::RELATION('á', 1), FST::RELATION('â', 1), FST::RELATION('ã', 1),\
FST::RELATION('ä', 1), FST::RELATION('å', 1), FST::RELATION('æ', 1), FST::RELATION('ç', 1),\
FST::RELATION('è', 1), FST::RELATION('é', 1), FST::RELATION('ê', 1), FST::RELATION('ë', 1),\
FST::RELATION('ì', 1), FST::RELATION('í', 1), FST::RELATION('î', 1), FST::RELATION('ï', 1),\
FST::RELATION('ð', 1), FST::RELATION('ñ', 1), FST::RELATION('ò', 1), FST::RELATION('ó', 1),\
FST::RELATION('ô', 1), FST::RELATION('õ', 1), FST::RELATION('ö', 1), FST::RELATION('÷', 1),\
FST::RELATION('ø', 1), FST::RELATION('ù', 1), FST::RELATION('ú', 1), FST::RELATION('û', 1),\
FST::RELATION('ü', 1), FST::RELATION('ý', 1), FST::RELATION('þ', 1), FST::RELATION('ÿ', 1),\
FST::RELATION('À', 1), FST::RELATION('Á', 1), FST::RELATION('Â', 1), FST::RELATION('Ã', 1),\
FST::RELATION('Ä', 1), FST::RELATION('Å', 1), FST::RELATION('Æ', 1), FST::RELATION('Ç', 1),\
FST::RELATION('È', 1), FST::RELATION('É', 1), FST::RELATION('Ê', 1), FST::RELATION('Ë', 1),\
FST::RELATION('Ì', 1), FST::RELATION('Í', 1), FST::RELATION('Î', 1), FST::RELATION('Ï', 1),\
FST::RELATION('Ð', 1), FST::RELATION('Ñ', 1), FST::RELATION('Ò', 1), FST::RELATION('Ó', 1),\
FST::RELATION('Ô', 1), FST::RELATION('Õ', 1), FST::RELATION('Ö', 1), FST::RELATION('×', 1),\
FST::RELATION('Ø', 1), FST::RELATION('Ù', 1), FST::RELATION('Ú', 1), FST::RELATION('Û', 1),\
FST::RELATION('Ü', 1), FST::RELATION('Ý', 1), FST::RELATION('Þ', 1), FST::RELATION('ß', 1),\
FST::RELATION('a', 1), FST::RELATION('b', 1), FST::RELATION('c', 1), FST::RELATION('d', 1),\
FST::RELATION('e', 1), FST::RELATION('f', 1), FST::RELATION('g', 1), FST::RELATION('h', 1),\
FST::RELATION('i', 1), FST::RELATION('g', 1), FST::RELATION('k', 1), FST::RELATION('l', 1),\
FST::RELATION('m', 1), FST::RELATION('n', 1), FST::RELATION('o', 1), FST::RELATION('p', 1),\
FST::RELATION('q', 1), FST::RELATION('r', 1), FST::RELATION('s', 1), FST::RELATION('t', 1),\
FST::RELATION('u', 1), FST::RELATION('v', 1), FST::RELATION('w', 1), FST::RELATION('x', 1),\
FST::RELATION('y', 1), FST::RELATION('z', 1), FST::RELATION('A', 1), FST::RELATION('B', 1),\
FST::RELATION('C', 1), FST::RELATION('D', 1), FST::RELATION('E', 1), FST::RELATION('F', 1),\
FST::RELATION('G', 1), FST::RELATION('H', 1), FST::RELATION('I', 1), FST::RELATION('J', 1),\
FST::RELATION('K', 1), FST::RELATION('L', 1), FST::RELATION('M', 1), FST::RELATION('N', 1),\
FST::RELATION('O', 1), FST::RELATION('P', 1), FST::RELATION('Q', 1), FST::RELATION('R', 1),\
FST::RELATION('S', 1), FST::RELATION('T', 1), FST::RELATION('U', 1), FST::RELATION('V', 1),\
FST::RELATION('W', 1), FST::RELATION('X', 1), FST::RELATION('Y', 1), FST::RELATION('Z', 1),\
FST::RELATION('1', 1), FST::RELATION('2', 1),\
FST::RELATION('3', 1), FST::RELATION('4', 1), FST::RELATION('5', 1), FST::RELATION('6', 1),\
FST::RELATION('7', 1), FST::RELATION('8', 1), FST::RELATION('9', 1), FST::RELATION('0', 1),\
FST::RELATION('-', 1), FST::RELATION('=', 1), FST::RELATION('_', 1), FST::RELATION('+', 1),\
FST::RELATION('!', 1), FST::RELATION('"', 1), FST::RELATION('¹', 1), FST::RELATION(';', 1),\
FST::RELATION('%', 1), FST::RELATION(':', 1), FST::RELATION('?', 1), FST::RELATION('*', 1),\
FST::RELATION('(', 1), FST::RELATION(')', 1), FST::RELATION('~', 1), FST::RELATION('@', 1),\
FST::RELATION('#', 1), FST::RELATION('$', 1), FST::RELATION('%', 1), FST::RELATION('^', 1),\
FST::RELATION('&', 1), FST::RELATION('<', 1), FST::RELATION('>', 1), FST::RELATION(',', 1),\
FST::RELATION('.', 1), FST::RELATION(' ', 1),FST::RELATION('/', 1), FST::RELATION(' ', 2),\
FST::RELATION('à', 2), FST::RELATION('á', 2), FST::RELATION('â', 2), FST::RELATION('ã', 2),\
FST::RELATION('ä', 2), FST::RELATION('å', 2), FST::RELATION('æ', 2), FST::RELATION('ç', 2),\
FST::RELATION('è', 2), FST::RELATION('é', 2), FST::RELATION('ê', 2), FST::RELATION('ë', 2),\
FST::RELATION('ì', 2), FST::RELATION('í', 2), FST::RELATION('î', 2), FST::RELATION('ï', 2),\
FST::RELATION('ð', 2), FST::RELATION('ñ', 2), FST::RELATION('ò', 2), FST::RELATION('ó', 2),\
FST::RELATION('ô', 2), FST::RELATION('õ', 2), FST::RELATION('ö', 2), FST::RELATION('÷', 2),\
FST::RELATION('ø', 2), FST::RELATION('ù', 2), FST::RELATION('ú', 2), FST::RELATION('û', 2),\
FST::RELATION('ü', 2), FST::RELATION('ý', 2), FST::RELATION('þ', 2), FST::RELATION('ÿ', 2),\
FST::RELATION('À', 2), FST::RELATION('Á', 2), FST::RELATION('Â', 2), FST::RELATION('Ã', 2), \
FST::RELATION('Ä', 2), FST::RELATION('Å', 2), FST::RELATION('Æ', 2), FST::RELATION('Ç', 2), \
FST::RELATION('È', 2), FST::RELATION('É', 2), FST::RELATION('Ê', 2), FST::RELATION('Ë', 2), \
FST::RELATION('Ì', 2), FST::RELATION('Í', 2), FST::RELATION('Î', 2), FST::RELATION('Ï', 2), \
FST::RELATION('Ð', 2), FST::RELATION('Ñ', 2), FST::RELATION('Ò', 2), FST::RELATION('Ó', 2), \
FST::RELATION('Ô', 2), FST::RELATION('Õ', 2), FST::RELATION('Ö', 2), FST::RELATION('×', 2), \
FST::RELATION('Ø', 2), FST::RELATION('Ù', 2), FST::RELATION('Ú', 2), FST::RELATION('Û', 2), \
FST::RELATION('Ü', 2), FST::RELATION('Ý', 2), FST::RELATION('Þ', 2), FST::RELATION('ß', 2), \
FST::RELATION('a', 2), FST::RELATION('b', 2), FST::RELATION('c', 2), FST::RELATION('d', 2),\
FST::RELATION('e', 2), FST::RELATION('f', 2), FST::RELATION('g', 2), FST::RELATION('h', 2),\
FST::RELATION('i', 2), FST::RELATION('g', 2), FST::RELATION('k', 2), FST::RELATION('l', 2),\
FST::RELATION('m', 2), FST::RELATION('n', 2), FST::RELATION('o', 2), FST::RELATION('p', 2),\
FST::RELATION('q', 2), FST::RELATION('r', 2), FST::RELATION('s', 2), FST::RELATION('t', 2),\
FST::RELATION('u', 2), FST::RELATION('v', 2), FST::RELATION('w', 2), FST::RELATION('x', 2),\
FST::RELATION('y', 2), FST::RELATION('z', 2), FST::RELATION('A', 2), FST::RELATION('B', 2),\
FST::RELATION('C', 2), FST::RELATION('D', 2), FST::RELATION('E', 2), FST::RELATION('F', 2),\
FST::RELATION('G', 2), FST::RELATION('H', 2), FST::RELATION('I', 2), FST::RELATION('J', 2),\
FST::RELATION('K', 2), FST::RELATION('L', 2), FST::RELATION('M', 2), FST::RELATION('N', 2),\
FST::RELATION('O', 2), FST::RELATION('P', 2), FST::RELATION('Q', 2), FST::RELATION('R', 2),\
FST::RELATION('S', 2), FST::RELATION('T', 2), FST::RELATION('U', 2), FST::RELATION('V', 2),\
FST::RELATION('W', 2), FST::RELATION('X', 2), FST::RELATION('Y', 2), FST::RELATION('Z', 2),\
FST::RELATION('1', 2), FST::RELATION('2', 2),\
FST::RELATION('3', 2), FST::RELATION('4', 2), FST::RELATION('5', 2), FST::RELATION('6', 2),\
FST::RELATION('7', 2), FST::RELATION('8', 2), FST::RELATION('9', 2), FST::RELATION('0', 2),\
FST::RELATION('-', 2), FST::RELATION('=', 2), FST::RELATION('_', 2), FST::RELATION('+', 2),\
FST::RELATION('!', 2), FST::RELATION('"', 2), FST::RELATION('¹', 2), FST::RELATION(';', 2),\
FST::RELATION('%', 2), FST::RELATION(':', 2), FST::RELATION('?', 2), FST::RELATION('*', 2),\
FST::RELATION('(', 2), FST::RELATION(')', 2), FST::RELATION('~', 2), FST::RELATION('@', 2),\
FST::RELATION('#', 2), FST::RELATION('$', 2), FST::RELATION('%', 2), FST::RELATION('^', 2),\
FST::RELATION('&', 2), FST::RELATION('<', 2), FST::RELATION('>', 2),FST::RELATION('/', 2), FST::RELATION(',', 2),\
FST::RELATION('.', 2)),\
	FST::NODE(1, FST::RELATION('"', 3)), \
	FST::NODE() }, LEX_LITERAL, IT::IDTYPE::L, IT::IDDATATYPE::STR }

#define  NODEF_FST\
	{ {(unsigned char*)"", 1,\
	    FST::NODE()}, LEX_NULL, IT::IDTYPE::NDEFT,IT::IDDATATYPE::NDEFD}



#endif // do not open plz
namespace Lr {
	struct Phrase {
		FST::FST fst;
		unsigned char lex;
		IT::IDTYPE type;
		IT::IDDATATYPE dtype;
		Phrase();
		Phrase(FST::FST fst, unsigned char lex, IT::IDTYPE type, IT::IDDATATYPE dtype);
		void SetPhrase(unsigned char* lex);
	};
	struct PhraseTable {
		short tsize;
		Phrase* phrases;
		PhraseTable();
	};
	void Analyzer(In::IN& in, LT::LexTable& lexTable, IT::IdTable& idTable, Error::ErrorTable& errorTable);
	void PrintLexTable(std::ostream& stream, LT::LexTable& lexTable, IT::IdTable& idTable);
	void PrintIdTable(std::ostream& stream, LT::LexTable& lexTable, IT::IdTable& idTable);
}

