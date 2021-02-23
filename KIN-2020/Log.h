#pragma once 
//#include "stdafx.h"

#include <iostream>


#define Null_str ""
#define Zero_t '\0'
#define WNull_str L""
#define CODE_ENDL "\n"
#define STR_MAX_SIZE 500
#define BUFFER_MAX_SIZE 100
#define N_LOG "\n-log: "
#define N_OUT "\n-out: "
#define N_IN "\n-in: "

namespace Log						// –абота с протоколом 
{
	struct LOG
	{
		wchar_t logfile[PARM_MAX_SIZE]; // им€ файла потока
		std::ofstream* stream;			// выходной поток протокола 
	};


	static const LOG INITLOG = { L"", NULL };			// структура дл€ начальной инициализации LOG
	LOG getlog(wchar_t* logfile);						 // сформировать структуру LOG 
	void WriteLine(LOG log_info, const char* str, ...);		 // вывести в протокол конкатенацию строк 
	void WriteLine(LOG log_info, const wchar_t* str, ...);		 // вывести в протокол конкатенацию строк 
	void WriteLog(LOG log_info);								// вывести в протокол заголовок 
	void WriteParm(LOG log_info, Parm::PARM parms);			// вывести в протокол информацию о входных параметрах 
	void WriteIn(LOG log_info, In::IN in);					 // вывести в протокол информацию о входном потоке 
	void WriteError(LOG log_info, Error::ERROR error);		// вывести в протокол информацию об ошибке 
	/*void WriteLtTable(LOG log_info, LT::LexTable lextable);*/
	void Close(LOG log_info);								// закрыть протокол 
};

