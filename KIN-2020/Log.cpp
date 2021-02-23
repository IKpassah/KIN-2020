#include "stdafx.h"

//#pragma warning(disable: 4996)
namespace Log
{
	LOG getlog(wchar_t* logfile) {
		std::ofstream *log_out = new std::ofstream();
		log_out->open(logfile);
		if (!log_out->is_open()) {
			throw ERROR_THROW(112);
		}
		else {
			LOG log_info;
			wcscpy_s(log_info.logfile, logfile);
			log_info.stream = log_out;
	
		return log_info;
		}
	}
	void WriteLine(LOG log_info, const char* str, ...) {
		const char** string = &str;
		char temp[STR_MAX_SIZE] = Null_str;
		while (strcmp(*string, Null_str)) {
			strcat_s(temp, *string);
			string++;
		}
		strcat_s(temp, CODE_ENDL);
		*log_info.stream << temp;
	}
	void WriteLine(LOG log_info, const wchar_t* str, ...) {
		const wchar_t** string = &str;
		wchar_t temp[STR_MAX_SIZE] = WNull_str;
		while (wcscmp(*string, WNull_str)) {
			wcscat_s(temp, *string);
			string++;
		}
		char ascStr[STR_MAX_SIZE] = Null_str;
		wcstombs_s(nullptr, ascStr, temp, wcslen(temp) + 1);
		strcat_s(ascStr, CODE_ENDL);
		*log_info.stream << ascStr;
	}
	void WriteLog(LOG log_info) {
		char temp[STR_MAX_SIZE] = "----- Протокол ----- Дата: ";
		time_t rawtime;
		struct tm timeinfo;
		char buffer[BUFFER_MAX_SIZE];
		time(&rawtime);
		localtime_s(&timeinfo, &rawtime);
		strftime(buffer, BUFFER_MAX_SIZE, "%d.%m.%Y  %H:%M:%S -----\n", &timeinfo);
		strcat_s(temp, buffer);
		*log_info.stream << temp;
	}
	void WriteParm(LOG log_info, Parm::PARM parms) {
		char temp[STR_MAX_SIZE] = "----- Параметры ----- ";
		strcat_s(temp, N_LOG);
		char ascStr[STR_MAX_SIZE] = Null_str;
		wcstombs_s(nullptr, ascStr, parms.log, wcslen(parms.log) + 1);
		strcat_s(temp, ascStr);
		strcat_s(temp, N_OUT);
		wcstombs_s(nullptr, ascStr, parms.out, wcslen(parms.out) + 1);
		strcat_s(temp, ascStr);
		strcat_s(temp, N_IN);
		wcstombs_s(nullptr, ascStr, parms.in, wcslen(parms.in) + 1);
		strcat_s(temp, ascStr);
		strcat_s(temp, CODE_ENDL);
		*log_info.stream << temp;
	}
	void WriteIn(LOG log_info, In::IN in) {
		*log_info.stream << CODE_ENDL <<
			"Количество символов: " << in.size << CODE_ENDL <<
			"Количество строк: " << in.lines << CODE_ENDL <<
			"Проигнорировано: " << in.ignor << CODE_ENDL;
	}
	void WriteError(LOG log_info, Error::ERROR error) {
		std::ostream& output = log_info.stream && log_info.stream->good() && log_info.stream->is_open() ? *log_info.stream : std::cout;

		output << "Ошибка " << error.id << ": " << error.message << CODE_ENDL;
		if (error.inext.line != -1) {
			output << "Строка " << error.inext.line << " позиция " << error.inext.col << CODE_ENDL;
		}

		output << "\n";
	}

	void Close(LOG log_info) {
		if (log_info.stream && log_info.stream->good() && log_info.stream->is_open()) {
			log_info.stream->close();
			delete log_info.stream;
		}
	}
}