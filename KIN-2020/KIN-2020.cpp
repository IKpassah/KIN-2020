#include "stdafx.h"

#include "MFST.h"
#include "SemanticAnalyzer.h"
#include "CodeGeneration.h"
#define COUT_ERR std::cout << "----- ПРОЦЕСС ПРЕРВАН ----\n"\
<< "----- Дополнительная информация находится в файле log ----\n\n";
int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "Rus");
	Log::LOG log = Log::INITLOG;
	Out::OUT out = Out::INITOUT;
	Error::ErrorTable errorTable;

	try {
		std::cout << "----- НАЧАЛО РАБОТЫ КОМПИЛЯТОРА ----";
		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::getlog(parm.log);
		Log::WriteLog(log);
		Log::WriteParm(log, parm);

		In::IN in = In::getin(parm.in, errorTable);
		Log::WriteIn(log, in);
		if (errorTable.haveErrors()) {
			for (short i = 0; i < errorTable.errorCount; i++) {
				Log::WriteError(log, Error::geterrorin(errorTable.errorTable[i].id, errorTable.errorTable[i].line, errorTable.errorTable[i].pos));
			}
			Log::Close(log);
			COUT_ERR
			return 0;
		}
		out = Out::getout(parm.out);
		IT::IdTable idTable = IT::Create(0);
		LT::LexTable lexTable = LT::Create(0);
		Lr::Analyzer(in, lexTable, idTable, errorTable);
		if (errorTable.haveErrors()) {
			for (short i = 0; i < errorTable.errorCount; i++) {
				Log::WriteError(log, Error::geterrorin(errorTable.errorTable[i].id, errorTable.errorTable[i].line, errorTable.errorTable[i].pos));
			}
			Log::Close(log);
			COUT_ERR
			return 0;
		}
		std::ostream* stream = out.stream;
		*stream << "Таблица лексем:\n";
		Lr::PrintLexTable(*stream, lexTable, idTable);
		*stream << "\nТаблица идентификаторов:\n";
		Lr::PrintIdTable(*stream, lexTable, idTable);

		MFST::Mfst mfst(lexTable, GRB::getGreibach());
		if (mfst.start()) {
			mfst.savededucation();
			*stream << "\nДерево разбора:\n";
			mfst.printRules(*stream);
		}
		else {
			errorTable.addError(mfst.getError());
		}

		if (errorTable.haveErrors()) {
			for (short i = 0; i < errorTable.errorCount; i++) {
				Log::WriteError(log, Error::geterrorin(errorTable.errorTable[i].id, errorTable.errorTable[i].line, errorTable.errorTable[i].pos));
			}
			Log::Close(log);
			COUT_ERR
			return 0;
		}
		SA::Analyzer(lexTable, idTable, mfst, errorTable);
		if (errorTable.haveErrors()) {
			for (short i = 0; i < errorTable.errorCount; i++) {
				Log::WriteError(log, Error::geterrorin(errorTable.errorTable[i].id, errorTable.errorTable[i].line, errorTable.errorTable[i].pos));
			}
			Log::Close(log);
			COUT_ERR
			return 0;
		}
		mfst.DeleteMfst();

		*stream << "Таблица лексем после преобразования:\n";
		Lr::PrintLexTable(*stream, lexTable, idTable);
		Out::Close(out);
		std::ofstream fstream; 
		fstream.open("C:\\Users\\Vanna\\source\\repos\\KIN-2020\\GenCode\\GeneratedAsm.asm");
		CG::Generator generator = CG::Generator(&lexTable, &idTable, &fstream);
		generator.GenerateAsm();		
		generator.DeleteGenerator();
		LT::Delete(lexTable);
		//IT::Delete(idTable);
		fstream.close();
		Log::Close(log);
		std::cout << "----- ЗАВЕРШЕНО УСПЕШНО ----\n\n";
	}
	catch (Error::ERROR e) {
		if (errorTable.haveErrors()) {
			for (short i = 0; i < errorTable.errorCount; i++) {
				Log::WriteError(log, Error::geterrorin(errorTable.errorTable[i].id, errorTable.errorTable[i].line, errorTable.errorTable[i].pos));
			}
			return 0;
		}
		COUT_ERR
		Log::WriteError(log, e);
		Log::Close(log);
	}
	system("pause");
	return 0;
}