#include "LR.h"

namespace Lr {
	Phrase::Phrase() {
		this->fst = { (unsigned char*)"", 1, FST::NODE() };
		this->lex = LEX_NULL;
		this->type = IT::IDTYPE::NDEFT;
		this->dtype = IT::IDDATATYPE::NDEFD;
	}
	Phrase::Phrase(FST::FST fst, unsigned char lex, IT::IDTYPE type, IT::IDDATATYPE dtype) {
		this->fst = fst;
		this->lex = lex;
		this->type = type;
		this->dtype = dtype;
	}
	void Phrase::SetPhrase(unsigned char* lex) {
		this->fst.position = -1;
		this->fst.string = lex;
		this->fst.rstates[0] = 0;
	}
	
	PhraseTable::PhraseTable() {
		this->tsize = PHRASES_MAXSIZE;
		Phrase fst_table[] = {
			NODEF_FST,
			EQUAL_FST, SEMICOLON_FST, COMMA_FST, LEFTBRACE_FST, BRACELET_FST,
			LEFTHESIS_FST, RIGHTHESIS_FST,
			PLUS_FST, DIRSLASH_FST, MINUS_FST, STAR_FST, PERC_FST,
			MORE_FST, LESS_FST, PEER_FST, NPEER_FST,
			BYTE_FST, STRING_FST, //BOOL_FST,
			PRINT_FST, DECLARE_FST, WHILE_FST, BREAK_FST, IF_FST, ELSE_FST,
			FUNCTION_FST, MAIN_FST, RETURN_FST,
			//TRUE_FST, FALSE_FST,
			ID_FST, LITERAL_BYTE_FST, LITERAL_STR_FST
		};
		phrases = new Phrase[PHRASES_MAXSIZE];
		for (int i = 0; i < PHRASES_MAXSIZE; i++) {
			this->phrases[i] = fst_table[i];
		}

	}
	bool DeletePhraseTable(PhraseTable& ptable) {
		if (ptable.phrases == nullptr) return false;
		delete[] ptable.phrases;
		return true;
	}
	void ShowIDType(std::ostream& stream, IT::IDTYPE type) {
		switch (type)
		{
		case IT::IDTYPE::F: {
			stream << "F";
			break;
		}
		case IT::IDTYPE::P: {
			stream << "P";
			break;
		}
		case IT::IDTYPE::V: {
			stream << "V";
			break;
		}
		case IT::IDTYPE::L: {
			stream << "L";
			break;
		}
		case IT::IDTYPE::NDEFT: {
			stream << "NODEF";
			break;
		}
		case IT::IDTYPE::DF: {
			stream << "DF";
			break;
		}
		case IT::IDTYPE::DFP: {
			stream << "DFP";
			break;
		}
		default:
			stream << "??";
			break;
		}
	}

	Phrase WordAnalyzer(unsigned char* word, PhraseTable& table) {
		for (int i = 1; i < table.tsize; i++) {
			table.phrases[i].SetPhrase(word);
			if (FST::execute(table.phrases[i].fst)) {
				return table.phrases[i];
			}
		}
		return table.phrases[0];
	}
	void Analyzer(In::IN& in, LT::LexTable& lexTable, 
		IT::IdTable& idTable, Error::ErrorTable& errorTable)
	{
		unsigned char* text = in.text;
		unsigned short string_counter = 0;
		unsigned short symbol_inString_count = 0;
		unsigned char* word = new unsigned char[TI_STR_MAXSIZE];
		unsigned char* letter = new unsigned char[2];
		word[0] = '\0';
		unsigned short letter_num = 0;
		bool mainMark = false;
		PhraseTable phraseTable;
		Phrase temp = NODEF_FST;

		for (int symbol_num = 0; symbol_num < in.size;) {
			if (0x61 <= (int)text[symbol_num] && (int)text[symbol_num] <= 0x7A
				|| 0x30 <= (int)text[symbol_num] && (int)text[symbol_num] <= 0x39
				|| text[symbol_num] == '\"') {
				if (text[symbol_num] != '\"') {
					word[letter_num] = text[symbol_num];
					letter_num++;
				}
				else {
					word[letter_num] = text[symbol_num];
					letter_num++;
					symbol_num++;
					unsigned short STRmaxSize = TI_STR_MAXSIZE - 3;
					while (text[symbol_num] != '\"' && text[symbol_num] != 0 && letter_num < STRmaxSize) {
						word[letter_num] = text[symbol_num];
						symbol_num++;
						letter_num++;
					}
					if (letter_num == STRmaxSize) {
						errorTable.addError(122, string_counter, 0);
					}
					else if (text[symbol_num] == 0) {
						errorTable.addError(126, string_counter, 0);
					}
					else
					   word[letter_num] = '\"';
					letter_num++;
				}
			}
			else {
				if (word[0] != '\0') {
					word[letter_num] = '\0';
					temp = WordAnalyzer(word, phraseTable);
					if (temp.lex == LEX_NULL) {
						int tempPosition = symbol_inString_count - (unsigned short)strlen((char*)word);
						if (tempPosition < 0) tempPosition = 0;
						errorTable.addError(120, string_counter, tempPosition);
					}
					else {
						LT::Add(lexTable, LT::Putentry(temp.lex, string_counter, (char)temp.dtype));
						if (temp.lex == LEX_LITERAL) {
							IT::PutLiteral(idTable, lexTable, word, temp.dtype);
						}
						else if (temp.lex == LEX_ID) {
							if (!IT::Putentry(idTable, lexTable, word, temp.dtype, temp.type))
								errorTable.addError(121, string_counter, symbol_inString_count - (unsigned short)strlen((char*)word));
							if(idTable.table[lexTable.table[lexTable.LastId()].idxTI].idtype != IT::IDTYPE::DF)
								if (strcmp((const char*)word, STANDART_FUNC1) == 0 ||
								strcmp((const char*)word, STANDART_FUNC2) == 0 ||
									strcmp((const char*)word, STANDART_FUNC3) == 0) {
									errorTable.addError(125, string_counter, symbol_inString_count - (unsigned short)strlen((char*)word));
								}
						}
						else if (temp.lex == LEX_MAIN) {
							if(mainMark) errorTable.addError(622, string_counter, symbol_inString_count - (unsigned short)strlen((char*)word));
							IT::PutMain(idTable, lexTable);
							mainMark = true;
						}
					} 
					word[0] = '\0';
					letter_num = 0;
				}
				if (text[symbol_num] == ' ' ||
					text[symbol_num] == '\t' ||
					text[symbol_num] == '\n' ||
					text[symbol_num] == '|') {
					if (text[symbol_num] == '\n'){ 
						string_counter++;
						symbol_inString_count = 0;
					}
				}
				else {
					letter[0] = text[symbol_num];
					letter[1] = 0;
					temp = WordAnalyzer(letter, phraseTable);
					if (temp.lex == LEX_NULL)
						errorTable.addError(120, string_counter, symbol_inString_count - (unsigned short)strlen((char*)word));
					else {
						LT::Add(lexTable, LT::Putentry(temp.lex, string_counter, (char)temp.dtype));
						if (temp.lex == LEX_LITERAL) {
							IT::PutLiteral(idTable, lexTable, word, temp.dtype);
						}
						else if (temp.lex == LEX_ID) {
							if (!IT::Putentry(idTable, lexTable, word, temp.dtype, temp.type))
								errorTable.addError(121, string_counter, symbol_inString_count - (unsigned short)strlen((char*)word));
						}
					}
				}
			}
			symbol_num++;
			symbol_inString_count++;
		}
		delete[] word;
		delete[] letter;
		DeletePhraseTable(phraseTable);
	}
	void PrintLexTable(std::ostream& stream, LT::LexTable& lexTable, IT::IdTable& idTable) {
		short strmark = lexTable.table[0].sn;
		for (int number = 0; number < lexTable.size; number++) {
			if (strmark == lexTable.table[number].sn) {
				stream << "\n" << strmark << "\t";
				strmark++;
			}
			else if (strmark < lexTable.table[number].sn) {
				short buf = lexTable.table[number].sn + 1;
				while (strmark != buf) {
					stream << "\n" << strmark << "\t";
					strmark++;
				}

			}
			stream << lexTable.table[number].lexema[0];
			if (lexTable.table[number].idxTI != -1) {
				if (idTable.table[lexTable.table[number].idxTI].idtype == IT::IDTYPE::L) {
					stream << "(" << idTable.table[lexTable.table[number].idxTI].literalValue.str << ")";
				}
				else {
					stream << "[" << lexTable.table[number].idxTI;
					ShowIDType(stream,idTable.table[lexTable.table[number].idxTI].idtype);
					stream << "]";
				}
			}
		}
		std::cout << "\n\n";
	}
	void PrintIdTable(std::ostream& stream,LT::LexTable& lexTable, IT::IdTable& idTable) {
		for (int number = 0; number < idTable.size; number++) {
			stream << number << ": " << idTable.table[number].idxFuncIT << "/" << idTable.table[number].id << "(" << (char)idTable.table[number].iddatatype;
			if (idTable.table[number].idtype == IT::IDTYPE::L) {
				stream << "L = " << idTable.table[number].literalValue.str;
			}
			else
				ShowIDType(stream, idTable.table[number].idtype);
			stream << ") : " << idTable.table[number].idxfirstLE << "\n";
		}
	}
}