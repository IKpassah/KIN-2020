#pragma once
#include "stdafx.h" 
//#include "MFST.h"

typedef short GRBALPHABET;	// символы алфавита грамматики терминалы > 0,нетерминалы < 0

#define BOTTOM_STACK_GBR '$' // ДНО СТЕКА
#define START_SYMBOL_GBR 'S' // СТАРТОВЫЙ СИМВОЛ
#define SEQUENCE_OF_OPERATORS_GBR 'N' // ПОСЛЕДОВАТЕЛЬНОСТЬ ОПЕРАТОРОВ
#define EXPRESSION_GBR 'E' // ВЫРАЖЕНИЕ
#define PARMS_GBR 'F' // ПАРАМЕТРЫ
#define UNDER_EXPRESSION_GBR 'W' // ПОДВЫРАЖЕНИЕ
#define CONDITION_GBR 'C' // УСЛОВИЕ
#define MRULE_GBR 'M'

namespace GRB
{
	struct Rule //правило в грамматике 
	{
		GRBALPHABET nn; // нетерминал(левый символ правила) 
		int iderror; //  идентификатор диагностики
		short size; // количество цепочек

		struct Chain
		{
			short size; // длина цепочки
			GRBALPHABET* chainOfTerm_nTerm; // цепочка терминалов(>0) и нетерминалов(<0)

			Chain()
			{
				this->size = 0;
				this->chainOfTerm_nTerm = 0;
			};

			Chain(short symbolCount, GRBALPHABET s, ...);

			char* getCChain(char* b);		//получить правую сторону правила
			static GRBALPHABET T(char t) { return GRBALPHABET(t); } // получить терминал
			static GRBALPHABET N(char n) { return -GRBALPHABET(n); } // получить нетерминал
			static bool isT(GRBALPHABET s) { return s > 0; } // это терминал?
			static bool isN(GRBALPHABET s) { return s < 0; } // это нетерменал?
			static char alphabet_to_char(GRBALPHABET s) { return (isT(s) ? char(s) : char(-s)); } // перевод в символ
		}*chains;

		Rule()
		{
			this->nn = 0x00;
			this->size = 0;
			this->chains = nullptr;
			this->iderror = -1;
		}
		Rule(GRBALPHABET pnn, int iderror, short psize, Chain c, ...);

		char* getCRule(char* b, short nchain); // получить правило для печати
		short getNextChain(GRBALPHABET t, Rule::Chain& pchain, short j); // получить следующую за j подходящую цепочку, вернуть номер, если нет такой -1
	};

	struct Greibach // грамматика Грейбах
	{
		short size; //количество правил
		GRBALPHABET startN;		//стартовый символ
		GRBALPHABET stbottomT;  //дно стека
		Rule* rules; // множество правил

		Greibach()
		{
			this->size = 0;
			this->startN = 0;
			this->stbottomT = 0;
			this->rules = 0;
		};
		Greibach(GRBALPHABET pstartN, GRBALPHABET pstbottomT, short psize, Rule r, ...);

		short getRule(GRBALPHABET pnn, Rule& prule); // получить номер правила, если нет -1
		Rule getRule(short n); // получить правило по номеру
	};

	Greibach getGreibach(); // получить грамматику Грейбха
}
