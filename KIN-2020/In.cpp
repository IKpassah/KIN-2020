#include "stdafx.h"

#define END_OF_STR '|'
#define Space 0x20
using namespace In;
IN In::getin(wchar_t* infile, Error::ErrorTable errorTable) {
	IN inInfo;
	std::ifstream file_in;
	file_in.open(infile);
	if (!file_in.is_open()) {
		throw ERROR_THROW(110);
	}
	else {
		char ch;
		unsigned char table_symbol;
		unsigned short symbol_count = 0;
		unsigned short symbol_inString_count = 0;
		bool space = false;
		bool newStr = true;
		bool isString = false;
		unsigned char *text = new unsigned char [IN_MAX_LEN_TEXT];
		unsigned short maxLen = IN_MAX_LEN_TEXT - 5;
		while (symbol_count < maxLen) {
			file_in.get(ch);
			if (file_in.eof()) break;
			table_symbol = (unsigned char)ch;
			if (table_symbol == IN_CODE_QUOTES2) {
				if (isString == false) {
					isString = true;
				}
				else {
					isString = false;
				}
			}
			if(isString){
				text[symbol_count] = table_symbol;
				symbol_count++;
				symbol_inString_count++;
			}
			else if (table_symbol == IN_CODE_ENDL) {
				inInfo.lines++;
				symbol_inString_count = 0;
				text[symbol_count] = END_OF_STR;
				symbol_count++;
				text[symbol_count] = IN_CODE_ENDL;
				symbol_count++;
				newStr = true;
			}
			else if(inInfo.code[table_symbol] == inInfo.T) {
				if (table_symbol == Space) {
					if (!newStr) {
						if (!space) {
							space = true;
						}
						else {
							inInfo.ignor++;
							symbol_inString_count++;
							continue; 
						}
					}
				}
				else { space = false; newStr = false; }
				text[symbol_count] = table_symbol;
				symbol_count++;
				symbol_inString_count++;
			}
			else if (inInfo.code[table_symbol] == inInfo.F) {
				errorTable.addError(111, inInfo.lines, symbol_inString_count);
			}
			else if (inInfo.code[table_symbol] == inInfo.I) {
				inInfo.ignor++;
				symbol_inString_count++;
			}			
		}
		if(symbol_count) inInfo.lines++;
		text[symbol_count] = CODE_NULL;
		inInfo.text = text;
		inInfo.size = symbol_count;
	}
	file_in.close();
	return inInfo;
}