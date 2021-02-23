#include "CodeGeneration.h"
#pragma warning(disable: 4996)
#define GEN_MAX_BYTE_LEN 10
namespace CG {
	Generator::Generator(LT::LexTable* lextable, IT::IdTable* idtable, std::ofstream * stream) {
		tempStr[0] = 0;
		tempComp[0] = 0;
		tempWord[0] = 0;
		tempName[0] = 0;
		StartInfo = new char[CG_SEGMENT_MAXSIZE];
		strcpy(StartInfo, (const char*)CG_START_INFO);
		StartInfo[strlen(CG_START_INFO)] = 0;

		Constants= new char[CG_SEGMENT_MAXSIZE];
		strcpy(Constants, (const char *)CG_CONST);
		Constants[strlen(CG_CONST)] = 0;

		Data= new char[CG_SEGMENT_MAXSIZE];
		strcpy(Data, CG_DATA);
		Data[strlen(CG_DATA)] = 0;
		
		Code = new char[CG_CODE_MAXSIZE];
		strcpy(Code, CG_CODE);
		Code[strlen(CG_CODE)] = 0;
		lexTable = lextable;
		idTable = idtable;
		AsmResult = stream;
	} 
	void Generator::GenOp(char lex) {
		tempStr[0] = 0;
		// jno // переход, если нет переполнения при mov sub
		// jnc // переход, если нет выхода за разрядную сетку для imul
		switch (lex) {
		case LEX_PLUS: {
			sprintf(tempStr, GEN_ADD);
			itsOkCounter++;
			// вызываем поп, автоматически записывается в al 1) в bl 2) остается в al \ результат суммы автоматически в al
			break;
		}
		case LEX_MINUS: {
			sprintf(tempStr, GEN_SUB);
			itsOkCounter++;
			break;
		} // call __pop\n mov bl, al == pop bl , pop al == call __pop
		case LEX_STAR: {
			sprintf(tempStr, GEN_IMUL);
			itsOkCounter++;
			break;
		} // call __pop\n mov bl, al\ncall __pop\n mov ax,  // pop bl\npop ax\nidiv bl\npush al\n
		case LEX_DIRSLASH: {
			sprintf(tempStr, GEN_IDIV);
			break;
		} // call __pop\n mov bl, al\ncall __pop\n mov ax\nidiv bl\ncall __push\n
		case LEX_PERC: {
			sprintf(tempStr, GEN_PERC);
			break;
		}
		}
	}
	void Generator::GetComp(char co) {
		tempComp[0] = 0;
		switch (co) {
		case LEX_PEER: {
			sprintf(tempComp, "==");
			break;
		}
		case LEX_NPEER: {
			sprintf(tempComp, "!=");
			break;
		}
		case LEX_MORE: {
			sprintf(tempComp, ">");
			break;
		}
		case LEX_LESS: {
			sprintf(tempComp, "<");
			break;
		}
		}
	}

	void Generator::GetName(int idxTi) {
		tempName[0] = 0;
		switch (idTable->table[idxTi].idtype) {
		case IT::IDTYPE::F :{
			sprintf(tempName, "_%s", idTable->table[idxTi].id);
			break;
		}
		case IT::IDTYPE::L: {
			sprintf(tempName, "literal%d", idxTi);
			break;

		}
		case IT::IDTYPE::P: {
			sprintf(tempName, "%s%d", idTable->table[idxTi].id, idTable->table[idxTi].idxFuncIT);
			break;

		}
		case IT::IDTYPE::V: {
			sprintf(tempName, "_%d%s", idTable->table[idxTi].idxFuncIT, idTable->table[idxTi].id);
			break;
		}
		case IT::IDTYPE::DF: {
			sprintf(tempName, "_%s", idTable->table[idxTi].id);
			break;
		}
		}
	}
	bool Generator::GenPreCode() {
		for (int idPos = 0; idPos < idTable->size; idPos++) {
			if (idTable->table[idPos].idtype == IT::IDTYPE::L) {
				GetName(idPos);
				if (idTable->table[idPos].iddatatype == IT::IDDATATYPE::BYTE) {
					if(idTable->table[idPos].literalValue.len == GEN_MAX_BYTE_LEN && 
						idTable->table[idPos].literalValue.str[0] == '1')
						idTable->table[idPos].literalValue.str[0] = '-';
					sprintf(tempStr, "%s SBYTE %s\n", tempName, idTable->table[idPos].literalValue.str);
				}
				else if (idTable->table[idPos].iddatatype == IT::IDDATATYPE::STR)
					sprintf(tempStr, "%s BYTE %s, 0 \n", tempName, idTable->table[idPos].literalValue.str);
				strcat(this->Constants, tempStr);
			}
			else if (idTable->table[idPos].idtype == IT::IDTYPE::V) {
				GetName(idPos);
				if (idTable->table[idPos].iddatatype == IT::IDDATATYPE::BYTE)
					sprintf(tempStr, "%s SBYTE 0b\n", tempName);
				else if (idTable->table[idPos].iddatatype == IT::IDDATATYPE::STR)
					sprintf(tempStr, "%s DWORD 0\n", tempName);
					//sprintf(tempStr, "%s BYTE 255 dup(0)\n%slastSymId dword 0\n", tempName, tempName);
				strcat(this->Data, tempStr);
			}
			else if (idTable->table[idPos].idtype == IT::IDTYPE::F && idTable->table[idPos].iddatatype != IT::IDDATATYPE::NDEFD) {
				GetName(idPos);
				sprintf(tempStr, "%s PROTO ", tempName);
				int i = 0;
				for (; idTable->table[idPos].parmsTypes[i] != IT::IDDATATYPE::NDEFD; i++) {
					if (idTable->table[idPos].parmsTypes[i] == IT::IDDATATYPE::BYTE)
						strcat(tempStr, ": SBYTE,");
					if (idTable->table[idPos].parmsTypes[i] == IT::IDDATATYPE::STR)
						strcat(tempStr, ": DWORD,");
				}
				tempStr[strlen(tempStr) - 1] = '\n';
				strcat(this->StartInfo, tempStr);
			}
			tempStr[0] = 0;
			tempWord[0] = 0;
		}
		return true;
	}
	bool Generator::GenCode() {
		int codesize;
		int size = lexTable->size - 1;
		for (int lexPos = 0; lexPos < size; lexPos++) {
			codesize = CG_CODE_MAXSIZE - strlen(this->Code) - 402;
			if(codesize < 0)
				throw ERROR_THROW(3);
			if (lexTable->table[lexPos].lexema[0] == LEX_TYPE &&
				lexTable->table[lexPos + 1].lexema[0] == LEX_FUNCTION) {
				if (idTable->table[lexTable->table[lexPos + 2].idxTI].idtype == IT::IDTYPE::F) {
					lexPos += 2;
					GetName(lexTable->table[lexPos].idxTI);
					sprintf(tempStr, "%s PROC ", tempName);
					int i = 0;
					for (; idTable->table[lexTable->table[lexPos].idxTI].parmsTypes[i] != IT::IDDATATYPE::NDEFD; i++) {
						GetName(lexTable->table[lexPos].idxTI + i +1);
						if (idTable->table[lexTable->table[lexPos].idxTI].parmsTypes[i] == IT::IDDATATYPE::BYTE)
							sprintf(tempWord, " %s: SBYTE,", tempName);
						else if (idTable->table[lexTable->table[lexPos].idxTI].parmsTypes[i] == IT::IDDATATYPE::STR)
							sprintf(tempWord, " %s: DWORD,", tempName);
						strcat(tempStr, tempWord);
					}
					tempStr[strlen(tempStr) - 1] = '\n';
					strcat(this->Code, tempStr);
					tempStr[0] = 0;
					tempWord[0] = 0;
				}
			}
			else if (lexTable->table[lexPos].lexema[0] == LEX_BRACELET && lexTable->table[lexPos + 1].lexema[0] == LEX_SEMICOLON) {
				int tempos = lexPos;
				for (; lexTable->table[tempos].lexema[0] != LEX_ID; tempos--);
				GetName(idTable->table[lexTable->table[tempos].idxTI].idxFuncIT);
				strcpy(tempWord, tempName);
				if (tempWord[1] == '!') ///
					strcpy(tempWord, "\ninvoke ExitProcess, 0\nmain");
				sprintf(tempStr, "%s ENDP\n", tempWord);
				strcat(this->Code, tempStr);
			}
			else if (lexTable->table[lexPos].lexema[0] == LEX_MAIN) {
				sprintf(tempStr, "main PROC\ninvoke	GetStdHandle, STD_OUTPUT \nmov	consoleOutHandle, eax\n");
				strcat(this->Code, tempStr);
				lexPos++;
			}
			else if (lexTable->table[lexPos].lexema[0] == LEX_ID && lexTable->table[lexPos + 1].lexema[0] == LEX_EQUAL
				|| lexTable->table[lexPos].lexema[0] == LEX_PRINT
				|| lexTable->table[lexPos].lexema[0] == LEX_RETURN) {
				int tempPos = lexPos;
				int i = lexPos + 1;
				if (lexTable->table[i].lexema[0] == LEX_EQUAL)
					i++;
				/*if (lexTable->table[i + 1].lexema[0] = LEX_SEMICOLON) {
					GetName(lexTable->table[i].idxTI);
					sprintf(tempStr, "mov al, %s\nmove\n", tempName);
				}*/
				LT::Entry lexEntry;
				if (idTable->table[lexTable->table[i].idxTI].iddatatype == IT::IDDATATYPE::BYTE) {
					for (; lexTable->table[i].lexema[0] != LEX_SEMICOLON; i++) {
						if (lexTable->table[i].idxTI != -1) {
							if (idTable->table[lexTable->table[i].idxTI].idtype != IT::IDTYPE::F &&
								idTable->table[lexTable->table[i].idxTI].idtype != IT::IDTYPE::DF) {
								GetName(lexTable->table[i].idxTI);
								sprintf(tempStr, "mov al, %s\ncall __push\n", tempName);
							}
							else {
								tempStr[0] = 0;
							}
						}
						else if (lexTable->table[i].lexema[0] == LEX_FUNC_PN) {
							int funcId = i - 1;
							tempStr[0] = 0;
							for (int parmCounter = 0; idTable->table[lexTable->table[funcId].idxTI].parmsTypes[parmCounter] != IT::IDDATATYPE::NDEFD; parmCounter++) {
								strcat(tempStr, "call __pop\npush eax\n");
							}
							GetName(lexTable->table[funcId].idxTI);
							sprintf(tempWord, "call %s\ncall __push\n", tempName);
							strcat(tempStr, tempWord);
						}
						else {
							GenOp(lexTable->table[i].lexema[0]);
						}
						strcat(this->Code, tempStr);
					}
					if (lexTable->table[lexPos + 1].lexema[0] == LEX_EQUAL) {
						GetName(lexTable->table[lexPos].idxTI);
						sprintf(tempStr, "call __pop\n mov %s, al\n", tempName);
					}
					else if (lexTable->table[lexPos].lexema[0] == LEX_PRINT) {
						sprintf(tempStr, "call __pop\ninvoke	byte_to_char, al, offset buffer\n%s\n", INVOKE_CONSOLE);
					}
					else if (lexTable->table[lexPos].lexema[0] == LEX_RETURN) {
						sprintf(tempStr, "call __pop\nret\n");
					}
					else {
						tempStr[0] = 0;
					}
					strcat(this->Code, tempStr);
				}
				else {
					int tempPos = i;
					int idLastSym = i;
					for (; lexTable->table[idLastSym].lexema[0] != LEX_SEMICOLON && lexTable->table[idLastSym].lexema[0] != LEX_FUNC_PN; idLastSym++);
					i = idLastSym - 1;
					//idLastSym = lexPos;
					if (lexTable->table[idLastSym].lexema[0] == LEX_SEMICOLON) {
						GetName(lexTable->table[i].idxTI);
						if (idTable->table[lexTable->table[i].idxTI].idtype == IT::IDTYPE::L) {
							sprintf(tempStr, "mov eax, offset %s\n", tempName);
						}
						else {
							sprintf(tempStr, "mov eax, %s\n", tempName);
						}
					}
					else if(lexTable->table[idLastSym].lexema[0] == LEX_FUNC_PN){
						i--;
						GetName(lexTable->table[idLastSym-1].idxTI);
						sprintf(tempStr, "invoke %s, ", tempName);
						for (int j = tempPos; idTable->table[lexTable->table[j].idxTI].idtype != IT::IDTYPE::F &&
							idTable->table[lexTable->table[j].idxTI].idtype != IT::IDTYPE::DF; j++) {
							GetName(lexTable->table[j].idxTI);
							if (idTable->table[lexTable->table[j].idxTI].idtype == IT::IDTYPE::V ||
								idTable->table[lexTable->table[j].idxTI].idtype == IT::IDTYPE::P) {
								sprintf(tempWord, " %s,", tempName);
							}
							else {
								sprintf(tempWord, " offset %s,", tempName);
							}
							strcat(tempStr, tempWord);
						}
						tempStr[strlen(tempStr) - 1] = '\n';
					}
					strcat(this->Code, tempStr);
					if (lexTable->table[lexPos + 1].lexema[0] == LEX_EQUAL) {
						sprintf(tempStr, "str%d byte 255 dup(0)\n", strCounter);
						strcat(this->Data, tempStr);
						GetName(lexTable->table[lexPos].idxTI);
						sprintf(tempStr, "invoke fill_str, offset str%d, eax\nmov %s,eax\n", strCounter, tempName);
						strCounter++;
					}
					else if (lexTable->table[lexPos].lexema[0] == LEX_PRINT) {
						sprintf(tempStr, "str%d byte 255 dup(0)\n", strCounter);
						strcat(this->Data, tempStr);
						sprintf(tempStr, "invoke fill_str, offset str%d, eax\ncall find_len\n", strCounter);
						strcat(this->Code, tempStr);
						sprintf(tempStr, "\ninvoke WriteConsoleA, consoleOutHandle, eax, edx, 0, 0\ninvoke WriteConsoleA, consoleOutHandle, offset newStr , newStr_len, 0, 0\n");
						strCounter++;
					}
					else if (lexTable->table[lexPos].lexema[0] == LEX_RETURN) {
						sprintf(tempStr, "str%d byte 255 dup(0)\n", strCounter);
						strcat(this->Data, tempStr);
						sprintf(tempStr, "invoke fill_str, offset str%d, eax\n\n", strCounter);
						strCounter++;
						strcat(tempStr, "ret\n");
					}
					else {
						tempStr[0] = 0;
					}
					strcat(this->Code, tempStr);
				}
			}
			else if (lexTable->table[lexPos].lexema[0] == LEX_WHILE) {
				isWhile = true;
				GetName(lexTable->table[lexPos + 2].idxTI);
				strcpy(tempWord, tempName);
				GetComp(lexTable->table[lexPos + 3].lexema[0]);
				GetName(lexTable->table[lexPos + 4].idxTI);
				sprintf(tempStr, "mov ecx, 2\nwhile%d:\nmov ah, %s\nmov al, %s\n\
.if ah %s al\nmov ecx, 2\n.else\njmp while%dend\n.endif\n", whileCounter, tempWord, tempName, tempComp, whileCounter);
				strcat(this->Code, tempStr);
			}
			else if (lexTable->table[lexPos].lexema[0] == LEX_IF) {
			isIf = true;
			GetName(lexTable->table[lexPos + 2].idxTI);
			strcpy(tempWord, tempName);
			GetComp(lexTable->table[lexPos + 3].lexema[0]);
			GetName(lexTable->table[lexPos + 4].idxTI);
			sprintf(tempStr, "mov ah, %s\nmov al, %s\n.if ah %s al\n", tempWord, tempName, tempComp);
			strcat(this->Code, tempStr);
			}
			else if (lexTable->table[lexPos].lexema[0] == LEX_BRACELET && lexTable->table[lexPos + 1].lexema[0] != LEX_SEMICOLON) {
			if (isWhile) {
				sprintf(tempStr, "loop while%d\nwhile%dend:\n", whileCounter, whileCounter);
				whileCounter++;
				isWhile = false;
				}
			else if (isIf) {
				if (lexTable->table[lexPos + 1].lexema[0] == LEX_ELSE) {
					sprintf(tempStr, ".else\n");
				}
				else {
					sprintf(tempStr, ".endif\n");
					isIf = false;
				}
			}
			strcat(this->Code, tempStr);
			}
			tempStr[0] = 0;
			tempWord[0] = 0;
		}
		return true;
	}
	bool Generator::GenerateAsm() {
		GenPreCode();
		GenCode();
		*AsmResult << this->StartInfo;
		*AsmResult << this->Constants;
		*AsmResult << this->Data;
		*AsmResult << this->Code;
		*AsmResult << "end\n";
		return true;
	}
	bool Generator::DeleteGenerator() {
		delete[] this->StartInfo;
		delete[] this->Constants;
		delete[] this->Data;
		delete[] this->Code;
		return true;
	}
}