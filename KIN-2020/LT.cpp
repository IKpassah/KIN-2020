#include "stdafx.h"

namespace LT
{
	Entry::Entry() {
		lexema[0] = LEX_NULL;
		lexema[1] = 0;
		sn = -1;
		idxTI = -1;
		position = -1;
	}

	Entry::Entry(char l, int s, int i) {
		lexema[0] = l;
		lexema[1] = 0;
		sn = s;
		idxTI = i;
		position = -1;
	}
	Entry::Entry(char l, int s, int i, char dtype) {
		lexema[0] = l;
		lexema[1] = 0;
		sn = s;
		idxTI = i;
		idDataType = dtype;
		position = -1;
	}
	Entry Putentry(char l, int s) {
		return Entry(l, s, -1);
	}
	Entry Putentry(char l, int s, char dtype) {
		return Entry(l, s, -1, dtype);
	}
	LexTable Create(int size) {
		LexTable Table;
		Table.maxsize = LT_MAXSIZE;
		Table.size = size;
		Table.table = new Entry[LT_MAXSIZE + LT_NULL_START_COUNT];
		Table.table += LT_NULL_START_COUNT; // сдвиг для правильной лексической проверки файла
		return Table;
	}
	bool LexTable::SetEntryIdxTI(int idx) {
		this->table[this->LastId()].idxTI = idx;
		return true;
	}
	bool LexTable::SetFuncIdInTI(int idf) {
		this->funcIdInTI = idf;
		return true;
	}
	int LexTable::LastId() {
		return this->size - 1;
	}

	void Add(LexTable& lextable, Entry entry) {
		if (lextable.size >= LT_MAXSIZE) throw ERROR_THROW(123);
		lextable.table[lextable.size] = entry;
		lextable.table[lextable.size].position = lextable.size;
		lextable.size++;
	}
	Entry Getentry(LexTable& lextable, int n) {
		return lextable.table[n];
	}

	void Delete(LexTable& lextable) {
		lextable.table -= LT_NULL_START_COUNT;
		delete[] lextable.table;
	}

};