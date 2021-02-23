#pragma once 
#include <fstream> 
#include "In.h" 
#include "Parm.h" 
#include "Error.h"

#define Null_str ""
#define Zero_t '\0'
#define WNull_str L""
#define CODE_ENDL "\n"
#define STR_MAX_SIZE 500
#define BUFFER_MAX_SIZE 100
#define N_LOG "\n-log: "
#define N_OUT "\n-out: "
#define N_IN "\n-in: "

namespace Out				
{
	struct OUT
	{
		wchar_t outfile[PARM_MAX_SIZE]; // имя файла потока
		std::ofstream* stream;			// выходной поток протокола 
	};
	static const OUT INITOUT = { L"", NULL };
	OUT getout(wchar_t* outfile);
	//void WriteOut(OUT out_info, In::IN in);
	void Close(OUT out_info);
};

