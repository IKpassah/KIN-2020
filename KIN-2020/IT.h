#pragma once
#include "stdafx.h"

//#include "LT.h"

#define	ID_MAXSIZE		10			// максимальное количество символов в идентификаторе
#define	TI_MAXSIZE		500		// максимальное количество строк в таблице идентификаторов
#define	TI_INT_DEFAULT	0x00	// значение по умолчанию для типа int
#define	TI_STR_DEFAULT	0x00		// значеник по умолчанию для типа string
#define	TI_NULLIDX		0xffffffff	// нет элемента таблицы идентификаторов
#define	TI_STR_MAXSIZE	255
#define	TI_BYTE_MAXSIZE	9
#define	TI_PARMS_MAXSIZE	10 // максимальное число параметров функции

#define FUNC_ID_TI -1 // functIdxIt для функции
#define NODEF_FUNC_ID_TI -3 // functIdxIt неопределен

#define ERROR_ID_NODEF -2 //  идентификатор не определен для возврата ADD 
#define ID_ENTRY_ENCRYPTION(idx) -idx - 5 //шифрование номера идентификатора

namespace IT
{
	enum class IDDATATYPE {
		NDEFD = 'n',
		STR = 's',
		BYTE = 'b',
	};
	enum class IDTYPE
	{
		NDEFT = 0,	//неопределен
		V = 1,		//переменная
		F = 2,		//функция
		L = 3,		//литерал
		P = 4,      //параметр
		DF = 5,		//объявленная функции
		DFP = 6,	//параметр объявленной функции
	};
	struct Entry // строка таблицы идентификаторов
	{
		int			idxfirstLE;	// индекс первой строки в таблице лексем
		int			idxFuncIT = -1; // индекс функции, которой принадлежит  идентификатор(для функций -1)
		unsigned char id[ID_MAXSIZE + 1] = "";//  идентификатор (автоматически усекается до ID_MAXSIZE)
		IDDATATYPE	iddatatype;	// тип данных
		IDTYPE		idtype;   // тип идентификатора
		IDDATATYPE* parmsTypes; // типы параметров для семантической проверки
		bool		isdefined = false; // было ли присвоено какое либо значение
		Entry();
		Entry(int idxIT); // если найден  идентификатор, шифрует
		Entry(int& idxfirst, unsigned char* iD, int funcId, IDDATATYPE& iddat, IDTYPE& idtype);
		struct
		{
				short len;
				char* str;
		}	literalValue;
	};

	struct  IdTable	// экземпляр таблицы идентификаторов
	{
		int maxsize;// емкость таблицы идентификаторов < TI_MAXSIZE
		int size;	// текущий размер таблицы идентификаторов < maxsize
		Entry* table;// массив строк таблицы идентификаторов
		int LastId();
	};
	bool PutLiteral(IdTable& idtable, LT::LexTable& lextable, unsigned char* iD,
		IDDATATYPE iddat);
	bool Putentry(IdTable& idtable, LT::LexTable& lextable,  unsigned char* iD,
		IDDATATYPE iddat, IDTYPE idt);
	bool PutMain(IdTable& idtable, LT::LexTable& lextable);
	IdTable Create(						// создать таблицу идентификаторов
		int size			// емкость таблицы идентификаторов < TI_MAXSIZE
	);
	int Add(							// добавить строку в таблицу идентификаторов
		IdTable& idtable,		// экземпляр таблицы идентификаторов
		const Entry& entry			// строка таблицы идентификаторов
	);
	Entry Getentry(IdTable& idtable, int n);


	void Delete(IdTable& idtable);		// удалить таблицу идентификаторов ( освободить память );
}