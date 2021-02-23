#include "stdafx.h"

#define MAIN_STR unsigned char main[7] = "!major";
#define LITERAL_STR  unsigned char Literal[9] =  "!literal"

namespace IT
{
	int Unsignedstrlen(unsigned char* word) {
		int size = 0;
		for (; word[size] != '\0' && size < TI_STR_MAXSIZE; size++) {
		}
		return size;
	}
	Entry::Entry() {
		idxfirstLE = -1;
		iddatatype = IDDATATYPE::NDEFD;
		idtype = IDTYPE::NDEFT;
	}
	Entry::Entry(int idx) {
		idxfirstLE = ID_ENTRY_ENCRYPTION(idx);
		iddatatype = IDDATATYPE::NDEFD;
		idtype = IDTYPE::NDEFT;
	}
	Entry::Entry(int& idxfirst, unsigned char* iD, int funcId, IDDATATYPE& iddat, IDTYPE& idt) {
		idxfirstLE = idxfirst;
		short idSize = Unsignedstrlen(iD);
		int i = 0;
		for (; i < ID_MAXSIZE && i < idSize; i++) {
			id[i] = iD[i];
		}
		id[i] = 0;
		iddatatype = iddat;
		idtype = idt;
		idxFuncIT = funcId;

	}
	int IdTable::LastId() {
		return this->size - 1;
	}
	IdTable Create(int size) {
		IdTable Table;
		Table.maxsize = TI_MAXSIZE;
		Table.size = size;
		Table.table = new Entry[TI_MAXSIZE];
		return Table;
	}
	int Add(IdTable& idtable, const Entry& entry) {
		if (idtable.size >= TI_MAXSIZE) throw ERROR_THROW(124);
		idtable.table[idtable.size] = entry; // новый  идентификатор
		if (entry.idtype == IT::IDTYPE::F && 
			entry.iddatatype != IDDATATYPE::NDEFD || entry.idtype == IT::IDTYPE::DF) { // для функции(не main) добавляем список типов параметров
			idtable.table[idtable.size].parmsTypes = new IT::IDDATATYPE[TI_PARMS_MAXSIZE];
			for (short i = 0; i < TI_PARMS_MAXSIZE; i++) {
				idtable.table[idtable.size].parmsTypes[i] = IT::IDDATATYPE::NDEFD;
			}
		}
		idtable.size++;
		return idtable.size - 1;
	}
	bool PutLiteral(IdTable& idtable, LT::LexTable& lextable, unsigned char* iD,
		IDDATATYPE iddat) {
		IDTYPE idtype = IDTYPE::L;
		LITERAL_STR;
		IT::Add(idtable, Entry(lextable.table[lextable.LastId()].sn, Literal,lextable.funcIdInTI, iddat, idtype));
		int id_in_table = idtable.LastId();

		int i = 0;
		short literalSize = Unsignedstrlen(iD);
		idtable.table[id_in_table].isdefined = true;
		if (idtable.table[id_in_table].iddatatype == IDDATATYPE::BYTE) {
			if (literalSize > TI_BYTE_MAXSIZE) {
				idtable.table[id_in_table].literalValue.len = TI_BYTE_MAXSIZE + 1;
				int bytesDiff =  literalSize - TI_BYTE_MAXSIZE;
				idtable.table[id_in_table].literalValue.str = new char[TI_BYTE_MAXSIZE + 1];
				idtable.table[id_in_table].literalValue.str[TI_BYTE_MAXSIZE] = 0;
				for (i = TI_BYTE_MAXSIZE - 1; i >= 0; i--) {
					idtable.table[id_in_table].literalValue.str[i] = iD[i + bytesDiff];
				}
			}
			else {
				idtable.table[id_in_table].literalValue.len = literalSize + 1;
				idtable.table[id_in_table].literalValue.str = new char[literalSize + 2];
				for (i = 0; i < idtable.table[id_in_table].literalValue.len; i++) {
					idtable.table[id_in_table].literalValue.str[i] = iD[i];
				}
				idtable.table[id_in_table].literalValue.str[i] = 0;
			}
		}
		else if (idtable.table[id_in_table].iddatatype == IDDATATYPE::STR) {
			if (literalSize > TI_STR_MAXSIZE)
				literalSize = TI_STR_MAXSIZE-1;
			else
				literalSize = literalSize - 1;
			idtable.table[id_in_table].literalValue.len = literalSize;
			idtable.table[id_in_table].literalValue.str = new char[literalSize + 2];
			for (i = 0; i < literalSize; i++) {
				idtable.table[id_in_table].literalValue.str[i] = iD[i];
			}
			idtable.table[id_in_table].literalValue.str[i] = '\"';
			i++;
			idtable.table[id_in_table].literalValue.str[i] = 0;
		}

		lextable.SetEntryIdxTI(idtable.LastId());
		return true;
	}
	bool PutMain(IdTable& idtable, LT::LexTable& lextable) {
		IDTYPE idtype = IDTYPE::F;
		IDDATATYPE iddatatype = IDDATATYPE::NDEFD;
		MAIN_STR
		lextable.SetEntryIdxTI(idtable.LastId() + 1);
		IT::Add(idtable, Entry(lextable.table[lextable.LastId()].sn, main, -1, iddatatype, idtype));
		lextable.SetFuncIdInTI(idtable.LastId());
		return true;
	}
	bool Putentry(IdTable& idtable, LT::LexTable& lextable, unsigned char* iD,
		IDDATATYPE iddat, IDTYPE idt) {
		bool isDefined = false;
		idt = IDTYPE::NDEFT;
		int idxFuncIT = -1;
		int elem_num = lextable.size - 2;
		if (lextable.table[elem_num].lexema[0] == LEX_FUNCTION) {
			if (lextable.table[elem_num - 1].lexema[0] == LEX_TYPE) {
				iddat = (IDDATATYPE)lextable.table[elem_num - 1].idDataType;
				if (lextable.table[elem_num - 2].lexema[0] == LEX_DECLARE) {
					idt = IDTYPE::DF;
					idxFuncIT = lextable.funcIdInTI;
				}
				else {
					idt = IDTYPE::F;
					lextable.SetFuncIdInTI(idtable.LastId() + 1);
					//idxFuncIT = -1;
				}
			}
		}
		else if (lextable.table[elem_num].lexema[0] == LEX_TYPE) {
			iddat = (IDDATATYPE)lextable.table[elem_num].idDataType;
			if (lextable.table[elem_num - 1].lexema[0] == LEX_DECLARE) {
				idt = IDTYPE::V;
				idxFuncIT = lextable.funcIdInTI;
			}
			else {
				for (int i = elem_num; i > 0; i--) {
					if (lextable.table[i - 1].lexema[0] == LEX_LEFTHESIS) {
						if (lextable.table[i - 2].lexema[0] == LEX_ID) {
							if (idtable.table[lextable.table[i - 2].idxTI].idtype == IDTYPE::F) {
								idt = IDTYPE::P;
								idxFuncIT = lextable.funcIdInTI;
								isDefined = true;
							}
							else if (idtable.table[lextable.table[i - 2].idxTI].idtype == IDTYPE::DF) {
								idt = IDTYPE::DFP;
								idxFuncIT = lextable.funcIdInTI;
							}
							break;
						}
					}
					else if (lextable.table[i - 1].lexema[0] == LEX_COMMA &&
						lextable.table[i - 2].lexema[0] == LEX_ID &&
						lextable.table[i - 3].lexema[0] == LEX_TYPE) {
							i -= 2;
					}
					else {
						break; }
				}
			}
		}
		else {
			for (elem_num = idtable.size - 1; elem_num >= 0 ; elem_num--) {
				if (idtable.table[elem_num].idtype != IDTYPE::DFP &&
					strcmp((const char*)idtable.table[elem_num].id, (const char*)iD) == 0)
				{
					if (idtable.table[elem_num].idtype == IDTYPE::F || elem_num > lextable.funcIdInTI) {
						lextable.SetEntryIdxTI(elem_num); // Если найден  идентификатор и это функция или для не функции входит в пределы функции
						return true;
					}
					else
						return false; // если имена id совпадают, однако не входит в область функции или не функция			
				}
			}
		}
		if (idt == IDTYPE::NDEFT){
			return false; // если не нашло совпадений
			}
		else
		{
			lextable.SetEntryIdxTI(idtable.LastId() + 1);
			IT::Add(idtable, Entry(lextable.table[lextable.LastId()].sn, iD, idxFuncIT, iddat, idt));
			idtable.table[idtable.LastId()].isdefined = isDefined;
			return true;
		}
	}
	
	
	Entry Getentry(IdTable& idtable, int n) {
		return idtable.table[n];
	}

	void Delete(IdTable& idtable) {
		for (int i = 0; i < idtable.size; i++) {
			/*if (idtable.table[i].idtype == IDTYPE::F && idtable.table[i].iddatatype != IDDATATYPE::NDEFD) {
				delete[] idtable.table[i].parmsTypes;
			}*/
			if (idtable.table[i].idtype == IDTYPE::L) {
				delete[] idtable.table[i].literalValue.str;
			}
		}
		delete[] idtable.table;
	}
};