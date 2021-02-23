#pragma once
#include "stdafx.h"
//#include "Error.h"
//#include "Parm.h"
//#include "In.h"
//#include "Log.h"
//#include "Out.h"
//#include "FST.h"
//#include "IT.h"

#define LEXEMA_FIXSIZE 2
#define LT_MAXSIZE 1500
#define LT_NULL_START_COUNT 5

#define LT_TI_NULLIDX 0xffffffff
#define LEX_TYPE 't'
#define LEX_ID 'i'			//лексема дл€ идентификатора
#define LEX_LITERAL 'l'
#define LEX_FUNCTION 'f'
#define LEX_DECLARE 'd'
#define LEX_RETURN 'r'
#define LEX_PRINT 'p'
#define LEX_SEMICOLON ';'
#define LEX_COMMA ','
#define LEX_LEFTBRACE '{'
#define LEX_BRACELET '}'
#define LEX_LEFTHESIS '('
#define LEX_RIGHTHESIS ')'
#define LEX_PLUS '+'
#define LEX_MINUS '-'
#define LEX_STAR '*'
#define LEX_DIRSLASH '/' 
#define LEX_PERC '%' 
#define LEX_EQUAL '='
#define LEX_WHILE 'w'
#define LEX_BREAK 'b'
#define LEX_IF '1'
#define LEX_ELSE '2'
#define LEX_MORE '>'
#define LEX_LESS '<'
#define LEX_PEER '&'
#define LEX_NPEER '!'






#define LEX_MAIN 'm'
#define LEX_FUNC_PN '@'
#define LEX_NULL 'n'

//#define LEX_NUMBER 'z'

namespace LT
{
	struct Entry						// строка таблицы лексем
	{
		char lexema[LEXEMA_FIXSIZE];					// лексема
		int	 sn;						// номер строки в исходном тексте
		int	 idxTI;						// индекс в таблице идентификаторов
		int  position;
		char idDataType = LEX_NULL; // тип данных дл€ 't'
		Entry();
		Entry(char l, int s, int i);
		Entry(char l, int s, int i, char dtype);
	};

	struct LexTable						// экземпл€р такблицы лексем
	{
		int maxsize;					// емкость таблицы лексем < LT_MAXSIZE
		int size;						// текущий размер таблицы лексем < MAXSIZE
		int funcIdInTI;					// id функции , в которой сейчас происходит разбор
		Entry* table;					// массив строк таблицы лексем
		bool SetEntryIdxTI(int idx);
		bool SetFuncIdInTI(int idf);
		int LastId();
	};

	Entry Putentry(char l, int s);
	Entry Putentry(char l, int s, char dtype);

	LexTable Create(		 // создать таблицу лексем
		int size // емкость таблицы лексем < LT_MAXSIZE
	);
	void Add(					// добавить строку в таблицу лексем 
		LexTable& lextable,	// экземпл€р таблицы лексем
		Entry entry			// строка таблицы лексем
	);
	Entry Getentry(LexTable& lextable, int n);


	void Delete(LexTable& lextable);	// удалить таблицу лексем ( освободить пам€ть )
};