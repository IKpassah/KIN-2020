#pragma once
#include "stdafx.h"
//#include "Error.h"
//#include "Parm.h"
//#include "In.h"
//#include "Log.h"
//#include "Out.h"
//#include "LT.h"
//#include "IT.h"


namespace FST
{
	struct RELATION //ребро:символ -> вершина графа переходов КА
	{
		unsigned char symbol; //символ перехода
		short nnode; //номер смежной вершины
		RELATION(
			unsigned char c = 0x00, // символ перехода
			short ns = NULL //новое состояние
		);
	};
	struct NODE	//вершина графа переходов
	{
		short n_relation;	//количество инцендентных ребер 
		RELATION* relations; //инцидентные ребра
		NODE();
		NODE(
			short n,		//количество инцендентных ребер
			RELATION rel, ... //список ребер
		);
	};
	struct FST	//недетерминированный конечный автомат
	{
		unsigned char* string; //цепочка (строка, завершается 0х00)
		short position; //текущая позиция в цепочке
		short nstates; //количество состояний автомата
		NODE* nodes;	//граф переходов: [0] - начальное состояние, [nstate-1] - конечное
		short* rstates; //возможные состояния автомата на данной позиции
		FST(
			unsigned char* s, //цепочка(строка, завершается 0х00)
			short ns, //количество состояний автомата
			NODE n, ...	//список состояний (граф переходов)
		);
		FST() {
			this->string = nullptr;
			this->position = -1;
			this->nstates = -1;
			this->nodes = nullptr;
			this->rstates = nullptr;
		}

	};
	bool execute(FST& fst);
}