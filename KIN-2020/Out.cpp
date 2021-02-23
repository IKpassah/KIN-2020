#include "stdafx.h"

//#include <fstream>
//#include <cstring>
//#include <ctime>
//#include "Log.h"
//#include "Error.h"
//#include "Parm.h"
//#include "Out.h"



namespace Out
{
	
	OUT getout(wchar_t* outfile) {
		static std::ofstream out_file;
		out_file.open(outfile);
		if (!out_file.is_open()) {
			throw ERROR_THROW(113);
		}
		else {
			OUT out_info;
			wcscpy_s(out_info.outfile, outfile);
			out_info.stream = &out_file;
			return out_info;
		}
	}

	/*void WriteOut(OUT out_info, In::IN in) {
		*out_info.stream  << in.text;
	}*/

	void Close(OUT out_info) {
		if(out_info.stream && out_info.stream->is_open())
			out_info.stream->close();
	}
	
};