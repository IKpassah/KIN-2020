#pragma once
#include "stdafx.h"
#include "Error.h"

#define CG_SEGMENT_MAXSIZE 2000
#define CG_CODE_MAXSIZE 10000

#define CG_START_INFO ".586\n\
.model flat, stdcall\n\
includelib kernel32.lib\n\
includelib ../Debug/MASMStaticLib.lib\n\
\n\
STD_OUTPUT			EQU - 11 \n\
ExitProcess			PROTO : DWORD \n\
GetStdHandle		PROTO : DWORD; \n\
WriteConsoleA		PROTO : DWORD, : DWORD, : DWORD, : DWORD, : DWORD \n\
SetConsoleTitleA	PROTO : DWORD  \n\
byte_to_char			PROTO : SBYTE , : DWORD \n\
_pow					PROTO : SBYTE, : SBYTE  \n\
_abs					PROTO : SBYTE  \n\
_strcat					PROTO : DWORD, : DWORD \n\
__push					PROTO \n\
__pop					PROTO \n\
fill_str				PROTO : DWORD,: DWORD\n\
find_len				PROTO\n\
"
#define CG_STACKSIZE "\n.stack 4098\n"
#define CG_CONST "\n.const\n\
newStr BYTE 10, 13\n\
newStr_len BYTE 2\n\
zeroEx BYTE \"Division by zero\", 0\n\
"
#define CG_DATA "\n.data\n\
buffer BYTE 10 dup(0)\n\
bufferstr BYTE 255 dup(0)\n\
bufferstrSymbol dword 0\n\
consoleOutHandle	dword ? \n"
#define CG_CODE "\n.code\n"
#define INVOKE_CONSOLE "invoke WriteConsoleA, consoleOutHandle, offset buffer, sizeof buffer, 0, 0\n\
invoke WriteConsoleA, consoleOutHandle, offset newStr , newStr_len, 0, 0\n\
"
#define LITERALN_MAXSIZE 12
#define LITERALN_N_POS 7
#define FIND_LEN 
#define GEN_ADD "\
\nmov	eax, 0b\n\
call	__pop\n\
mov		bl, al\n\
call	__pop\n\
add		al, bl\n\
jno		isOk%d\n\
mov		al, 0b\n\
isOk%d:\n\
call	__push\n",\
itsOkCounter, itsOkCounter
#define GEN_SUB "\
\nmov	eax, 0b\n\
call	__pop\n\
mov		bl, al\n\
call	__pop\n\
sub		al, bl\n\
jno		isOk%d\n\
mov		al, 0b\n\
isOk%d:\n\
call	__push\n",\
itsOkCounter, itsOkCounter
#define GEN_IMUL "\
\nmov	eax, 0b\n\
call	__pop\n\
mov		bl, al\n\
call	__pop\n\
imul	bl\n\
jnc		isOk%d\n\
mov		al, 0b\n\
isOk%d:\n\
call	__push\n",\
itsOkCounter, itsOkCounter
#define GEN_IDIV "\
\nmov	eax, 0b\n\
call	__pop\n\
mov		bl, al\n\
.if bl == 0\n\
 invoke WriteConsoleA, consoleOutHandle, offset zeroEx , lengthof zeroEx, 0, 0\n\
 invoke		ExitProcess, 1\n\
.endif\n\
call	__pop\n\
CBW\n\
idiv	bl\n\
call	__push\n"
#define GEN_PERC "\
\nmov	eax, 0b\n\
call	__pop\n\
mov		bl, al\n\
.if bl == 0\n\
 invoke WriteConsoleA, consoleOutHandle, offset zeroEx , lengthof zeroEx, 0, 0\n\
 invoke		ExitProcess, 1\n\
.endif\n\
call	__pop\n\
CBW\n\
idiv	bl\n\
mov		al, ah\n\
call	__push\n\
"

namespace CG {
	struct Generator {
		int whileCounter = 0;
		int strCounter = 0;
		int itsOkCounter = 0;
		int firstComp = 0;
		int secondComp = 0;
		bool isWhile = false;
		bool isIf = false;
		bool isElse = false;

		char tempComp[3];
		char tempName[30];
		char tempWord[50];
		char tempStr[400];
		char* StartInfo;
		char* Constants;
		char* Data;
		char* Code;
		std::ofstream* AsmResult;
		
		LT::LexTable* lexTable;
		IT::IdTable* idTable;
		Generator(LT::LexTable* lextable, IT::IdTable* idtable, std::ofstream* stream);
		void GetName(int idxLex);
		void GetComp(char co);
		void GenOp(char lex);
		bool GenPreCode();
		bool GenCode();
		bool GenerateAsm();
		bool DeleteGenerator();
		//bool GenOperator(char* word);
	};
};