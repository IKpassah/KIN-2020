#include "SemanticAnalyzer.h"

#define FUNC_ID_ORDER 2

namespace SA {
	bool Analyzer(LT::LexTable& lexTable, IT::IdTable& idTable, MFST::Mfst& mfst, Error::ErrorTable& errorTable) {
		const GRBALPHABET N_S = GRB::Rule::Chain::N(START_SYMBOL_GBR); // стартовый символ
		const GRBALPHABET N_F = GRB::Rule::Chain::N(PARMS_GBR); // параметр
		const GRBALPHABET N_N = GRB::Rule::Chain::N(SEQUENCE_OF_OPERATORS_GBR); // оператор или последовательность 
		const GRBALPHABET N_M = GRB::Rule::Chain::N(MRULE_GBR); // операция 
		const GRBALPHABET T_m = GRB::Rule::Chain::T('m'); // major функция  

		const GRBALPHABET T_t = GRB::Rule::Chain::T('t'); // тип
		const GRBALPHABET T_d = GRB::Rule::Chain::T('d'); // объявление
		const GRBALPHABET T_r = GRB::Rule::Chain::T('r'); // возврат
		const GRBALPHABET T_i = GRB::Rule::Chain::T('i'); //  идентификатор
		const GRBALPHABET T_p = GRB::Rule::Chain::T('p'); // вывод

		const GRBALPHABET T_w = GRB::Rule::Chain::T('w'); // цикл while 
		const GRBALPHABET T_1 = GRB::Rule::Chain::T('1'); // if
		MFST::MfstState state;
		GRB::Rule rule;
		int mfstSize = mfst.storestate.size() - 1;
		int a = 0;
		int b = 0;
		IT::Entry* funcInIT = nullptr;
		int parmsCounter = 0;
		int idXTi = 0;
		int idxFuncIT = 0;
		char idName[11] = "";
		IT::IDDATATYPE funcReturnType = IT::IDDATATYPE::BYTE;
		for (int chainIndex = 0; chainIndex < mfstSize; chainIndex++)
		{
			state = mfst.storestate[chainIndex];
			rule = mfst.grebach.getRule(state.nrule);
			if (rule.chains[state.nrulechain].chainOfTerm_nTerm[0] == T_t) { // если не major записать параметры
				idXTi = lexTable.table[state.lenta_position + FUNC_ID_ORDER].idxTI;
				idxFuncIT = idXTi;
				funcInIT = &idTable.table[idXTi];
				IT::IDDATATYPE funcType = funcInIT->iddatatype;
				funcReturnType = funcInIT->iddatatype;
				idXTi++; // получение индекса первого параметра
				chainIndex++;
				state = mfst.storestate[chainIndex];
				rule = mfst.grebach.getRule(state.nrule);
				while (rule.nn == N_F && parmsCounter < 6) { // запись типов формальных параметров(функция имеет хотя бы один параметр) 
					funcInIT->parmsTypes[parmsCounter] =
						idTable.table[idXTi].iddatatype;
					if (funcType != idTable.table[idXTi].iddatatype) {
						errorTable.addError(620, lexTable.table[state.lenta_position].sn, 0);
					}
					idXTi++;
					parmsCounter++;
					chainIndex++;
					state = mfst.storestate[chainIndex];
					rule = mfst.grebach.getRule(state.nrule);
				}
				if (parmsCounter == 6) {
					errorTable.addError(621, lexTable.table[state.lenta_position].sn, 0);
				}
				parmsCounter = 0;
			}
			else {
				idxFuncIT = lexTable.table[state.lenta_position].idxTI;
				funcReturnType = IT::IDDATATYPE::BYTE;
				chainIndex++;
				state = mfst.storestate[chainIndex];
				rule = mfst.grebach.getRule(state.nrule);
			}
			while (rule.nn != N_S && chainIndex < mfstSize) { // проход по операторам
				if (rule.nn == N_N) {
					if (rule.chains[state.nrulechain].chainOfTerm_nTerm[0] == T_d) { // проверка верности объявления и добавление типов параметров функции
						if (lexTable.table[state.lenta_position + FUNC_ID_ORDER].lexema[0] == LEX_FUNCTION) {
							idXTi = lexTable.table[state.lenta_position + FUNC_ID_ORDER + 1].idxTI;
							funcInIT = &idTable.table[idXTi];
							int tempID = idXTi;
							chainIndex++;
							idXTi++;
							state = mfst.storestate[chainIndex];
							rule = mfst.grebach.getRule(state.nrule);
							while (rule.nn == N_F) { // запись типов формальных параметров
								funcInIT->parmsTypes[parmsCounter] =
									idTable.table[idXTi].iddatatype;
								parmsCounter++;
								idXTi++;
								chainIndex++;
								state = mfst.storestate[chainIndex];
								rule = mfst.grebach.getRule(state.nrule);
							}
							parmsCounter = 0;
							chainIndex--;
							idXTi = tempID;
							bool isStandart = false;
							if (strcmp((const char*)funcInIT->id, STANDART_FUNC1) == 0) {
								if (funcInIT->iddatatype == IT::IDDATATYPE::BYTE &&
									funcInIT->parmsTypes[0] == IT::IDDATATYPE::BYTE &&
									funcInIT->parmsTypes[1] == IT::IDDATATYPE::NDEFD)
									isStandart = true;
							}
							else if ((strcmp((const char*)funcInIT->id, STANDART_FUNC2) == 0)) {
								if (funcInIT->iddatatype == IT::IDDATATYPE::BYTE &&
									funcInIT->parmsTypes[0] == IT::IDDATATYPE::BYTE &&
									funcInIT->parmsTypes[1] == IT::IDDATATYPE::BYTE &&
									funcInIT->parmsTypes[2] == IT::IDDATATYPE::NDEFD)
									isStandart = true;
							}
							else if ((strcmp((const char*)funcInIT->id, STANDART_FUNC3) == 0)) {
								if (funcInIT->iddatatype == IT::IDDATATYPE::STR &&
									funcInIT->parmsTypes[0] == IT::IDDATATYPE::STR &&
									funcInIT->parmsTypes[1] == IT::IDDATATYPE::STR &&
									funcInIT->parmsTypes[2] == IT::IDDATATYPE::NDEFD)
									isStandart = true;
							}
							if(!isStandart)
								errorTable.addError(611, lexTable.table[state.lenta_position].sn, 0);
							strcpy_s(idName, (const char*)funcInIT->id);
						}
						else {
							idXTi = lexTable.table[state.lenta_position + FUNC_ID_ORDER].idxTI;
							strcpy_s(idName, (const char*)idTable.table[idXTi].id);
						}
						for (int backCounter = idXTi - 1; idTable.table[backCounter].idxFuncIT == idxFuncIT; backCounter--) {
							if(idTable.table[backCounter].idtype != IT::IDTYPE::DFP)
								if (strcmp((const char*)idTable.table[backCounter].id, (const char*)idName) == 0) {
									errorTable.addError(610, idTable.table[idXTi].idxfirstLE, 0);
									break;
								}
						}
					}
					else if (rule.chains[state.nrulechain].chainOfTerm_nTerm[0] == T_i ||
						rule.chains[state.nrulechain].chainOfTerm_nTerm[0] == T_r ||
						rule.chains[state.nrulechain].chainOfTerm_nTerm[0] == T_p) { // i = ...
						short lexPosition = state.lenta_position;
						bool* isDefined = &idTable.table[lexTable.table[lexPosition].idxTI].isdefined;
						IT::Entry idEntry;
						IT::IDDATATYPE dataType;
						int polishPosition = lexPosition+1;
						if (rule.chains[state.nrulechain].chainOfTerm_nTerm[0] == T_i) {
							dataType = idTable.table[lexTable.table[lexPosition].idxTI].iddatatype;
							polishPosition++;
						}
						else if (rule.chains[state.nrulechain].chainOfTerm_nTerm[0] == T_r) {
							dataType = funcReturnType;
						}
						else if (rule.chains[state.nrulechain].chainOfTerm_nTerm[0] == T_p) {
							short pos = lexPosition;
							for (; lexTable.table[pos].idxTI == -1; pos++);
							dataType = idTable.table[lexTable.table[pos].idxTI].iddatatype;
						}
						for (lexPosition++; lexTable.table[lexPosition].lexema[0] != LEX_SEMICOLON; lexPosition++)
						{
							if (lexTable.table[lexPosition].lexema[0] == LEX_ID ||
								lexTable.table[lexPosition].lexema[0] == LEX_LITERAL) {
								int idStr = lexTable.table[lexPosition].sn;
								if (idTable.table[lexTable.table[lexPosition].idxTI].iddatatype == dataType) { // проверка соответствия типов
									idEntry = idTable.table[lexTable.table[lexPosition].idxTI];
									if (idEntry.idtype == IT::IDTYPE::F || idEntry.idtype == IT::IDTYPE::DF) { // проверка соответствия формальных и фактических параметров
										if (lexTable.table[lexPosition + 1].lexema[0] == LEX_LEFTHESIS) {
											lexPosition += 2;
											int i = 0;
											for (; idEntry.parmsTypes[i] != IT::IDDATATYPE::NDEFD && lexTable.table[lexPosition].lexema[0] != LEX_RIGHTHESIS; lexPosition++) {
												if (lexTable.table[lexPosition].lexema[0] != LEX_COMMA) {
													if (idTable.table[lexTable.table[lexPosition].idxTI].iddatatype == idEntry.parmsTypes[i]) {
														if (!idTable.table[lexTable.table[lexPosition].idxTI].isdefined)
															errorTable.addError(612, idStr, 0);
														i++;
													}

												}
											}
											if (idEntry.parmsTypes[i] != IT::IDDATATYPE::NDEFD || lexTable.table[lexPosition].lexema[0] != LEX_RIGHTHESIS) {
												errorTable.addError(612, idStr, 0);
											}
											lexPosition--;
										}
										else {
											errorTable.addError(614, idStr, 0);
										}
									}
									else {
										if (!idTable.table[lexTable.table[lexPosition].idxTI].isdefined)
											errorTable.addError(618, idStr, 0);
									}
								}
								else {
									errorTable.addError(613, idStr, 0);
									break; // если типы не совпадают 
								}
							}
						}
						*isDefined = true;
						bool isTrue = true;
						if (dataType == IT::IDDATATYPE::STR) {
							
							do {
								chainIndex++;
								state = mfst.storestate[chainIndex];
								rule = mfst.grebach.getRule(state.nrule);
								if (rule.nn == N_M) {
									errorTable.addError(615, lexTable.table[state.lenta_position].sn, 0);
									isTrue = false;
									break;
								}
							} while (rule.nn != N_N && rule.nn != N_S && chainIndex < mfstSize - 2);
							chainIndex--;
						}
						if(isTrue) {
							if (!errorTable.haveErrors()) {
								if (!PN::PolishNotation(polishPosition, lexTable)) {
									errorTable.addError(101, lexTable.table[polishPosition].sn, 0);
								}
							}
						}
					}
					else if (rule.chains[state.nrulechain].chainOfTerm_nTerm[0] == T_w ||
						rule.chains[state.nrulechain].chainOfTerm_nTerm[0] == T_1) {
						chainIndex++;
						state = mfst.storestate[chainIndex];
						rule = mfst.grebach.getRule(state.nrule);
						if (idTable.table[lexTable.table[state.lenta_position].idxTI].iddatatype != idTable.table[lexTable.table[state.lenta_position + 2].idxTI].iddatatype ||
							idTable.table[lexTable.table[state.lenta_position].idxTI].iddatatype != IT::IDDATATYPE::BYTE)
							errorTable.addError(616, lexTable.table[state.lenta_position].sn, 0);
						short lexPosition = state.lenta_position;

						while (lexTable.table[lexPosition].lexema[0] != LEX_BRACELET) {
							if (lexTable.table[lexPosition].lexema[0] == LEX_DECLARE) {
								errorTable.addError(617, lexTable.table[lexPosition].sn, 0);
							}
							lexPosition++;
						}
						lexPosition++;

						if (lexTable.table[lexPosition].lexema[0] == LEX_ELSE)
							while (lexTable.table[lexPosition].lexema[0] != LEX_BRACELET) {
								if (lexTable.table[lexPosition].lexema[0] == LEX_DECLARE) {
									errorTable.addError(617, lexTable.table[lexPosition].sn, 0);
								}
								lexPosition++;
							}
					}
				}
				chainIndex++;
				state = mfst.storestate[chainIndex];
				rule = mfst.grebach.getRule(state.nrule);
			}
			 // проверка правильности последнего оператора return функции
			int backchainIndex;
			for (backchainIndex = chainIndex; mfst.storestate[backchainIndex].nrule != 1; backchainIndex--);
			state = mfst.storestate[backchainIndex];
			rule = mfst.grebach.getRule(state.nrule);
			if (rule.chains[state.nrulechain].chainOfTerm_nTerm[0] != T_r) {
				errorTable.addError(619, lexTable.table[state.lenta_position].sn, 0);
			}
			chainIndex--;
		}
		return true;
	}
}