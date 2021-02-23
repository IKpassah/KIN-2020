#include "Error.h"



namespace Error
{
	// серии ошибок: 0 - 99 - системные ошибки 
	// 100 - 109 - ошибки параметров 
	// 110 - 119 - ошибки открытия и чтения файлов 
	ERROR errors[ERROR_MAX_ENTRY] = //таблица ошибок 
	{
	ERROR_ENTRY(0, "Недопустимый код ошибки"), // код ошибки вне диапазона 0 - ERROR_MAX_ENTRY 
	ERROR_ENTRY(1, "Системный сбой"),
	ERROR_ENTRY(2, "Таблица ошибок переполнена"),
	ERROR_ENTRY(3, "Превышен максимальный размер информации CODEGENERATOR"),
	ERROR_ENTRY_NODEF(4),ERROR_ENTRY_NODEF(5),
	ERROR_ENTRY_NODEF(6),ERROR_ENTRY_NODEF(7),ERROR_ENTRY_NODEF(8),ERROR_ENTRY_NODEF(9),
	ERROR_ENTRY_NODEF10(10), ERROR_ENTRY_NODEF10(20), ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40), ERROR_ENTRY_NODEF10(50),
	ERROR_ENTRY_NODEF10(60), ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80), ERROR_ENTRY_NODEF10(90),
	ERROR_ENTRY(100, "Параметр -in должен быть задан"),
	ERROR_ENTRY(101, "Цепочка не распознана в польскую запись"), ERROR_ENTRY_NODEF(102), ERROR_ENTRY_NODEF(103),
	ERROR_ENTRY(104, "Превышена длина входного параметра"),
	ERROR_ENTRY_NODEF(105), ERROR_ENTRY_NODEF(106), ERROR_ENTRY_NODEF(107),
	ERROR_ENTRY_NODEF(108), ERROR_ENTRY_NODEF(109),
	ERROR_ENTRY(110, "Ошибка при открытии файла с исходным кодом (-in)"),
	ERROR_ENTRY(111, "Недопустимый символ в исходном файле (-in)"),
	ERROR_ENTRY(112, "Ошибка при создании файла протокола (-log)"),
	ERROR_ENTRY(113, "Ошибка при создании файла вывода (-out)"),
	ERROR_ENTRY_NODEF(114), ERROR_ENTRY_NODEF(115), ERROR_ENTRY_NODEF(116),
	ERROR_ENTRY_NODEF(117), ERROR_ENTRY_NODEF(118), ERROR_ENTRY_NODEF(119),
	ERROR_ENTRY(120, "Ошибка при распознавании лексемы"),
	ERROR_ENTRY(121, "Идентификатор не определен"),
	ERROR_ENTRY(122, "Строка превышает максимально допустимый размер"),
	ERROR_ENTRY(123, "Таблица лексем переполнена"),
	ERROR_ENTRY(124, "Таблица идентификаторов переполнена"),
	ERROR_ENTRY(125, "Идентификатор уже занят в стандартной библиотеке"),
	ERROR_ENTRY(126, "Закрывающая кавычка не найдена"),
	ERROR_ENTRY_NODEF(127), ERROR_ENTRY_NODEF(128), ERROR_ENTRY_NODEF(129),
	ERROR_ENTRY_NODEF10(130), ERROR_ENTRY_NODEF10(140), ERROR_ENTRY_NODEF10(150),
	ERROR_ENTRY_NODEF10(160), ERROR_ENTRY_NODEF10(170), ERROR_ENTRY_NODEF10(180), ERROR_ENTRY_NODEF10(190),
	ERROR_ENTRY_NODEF100(200), ERROR_ENTRY_NODEF100(300), ERROR_ENTRY_NODEF100(400), ERROR_ENTRY_NODEF100(500),
	ERROR_ENTRY(600, "Неверная структура программы"),
	ERROR_ENTRY(601, "Ошибочный оператор"),
	ERROR_ENTRY(602, "Ошибка в выражении"),
	ERROR_ENTRY(603, "Ошибка в параметрах функции"),
	ERROR_ENTRY(604, "Ошибка в параметрах вызываемой функции"),
	ERROR_ENTRY(605, "Ошибка в условии"),
	ERROR_ENTRY_NODEF(606),ERROR_ENTRY_NODEF(607),ERROR_ENTRY_NODEF(608),
	ERROR_ENTRY_NODEF(609),
	ERROR_ENTRY(610, "Повторное объявление идентификатора"),
	ERROR_ENTRY(611, "Определенная функция не соответствует функциям стандартной библиотеки"),
	ERROR_ENTRY(612, "Формальные и фактические параметры функции не совпадают"),
	ERROR_ENTRY(613, "Типы идентификаторов выражения не совпадают"),
	ERROR_ENTRY(614, "Функция должна иметь параметры"),
	ERROR_ENTRY(615, "К строкам нельзя применять операции"),
	ERROR_ENTRY(616, "Типы сравниваемых значений должны быть byte"),
	ERROR_ENTRY(617, "Объявлять внутри if else и while блоков запрещено"),
	ERROR_ENTRY(618, "Переменная должна быть определена перед её использованием"),
	ERROR_ENTRY(619, "Последний оператор функции должен быть return"),
	ERROR_ENTRY(620, "Типы параметров должны совпадать с типом функции"),
	ERROR_ENTRY(621, "Максимальное число параметров функции 5"),
	ERROR_ENTRY(622, "Главная функция major должна быть задана один раз"),
	ERROR_ENTRY_NODEF(623), ERROR_ENTRY_NODEF(624),ERROR_ENTRY_NODEF(625),ERROR_ENTRY_NODEF(626),ERROR_ENTRY_NODEF(627),
	ERROR_ENTRY_NODEF(628),ERROR_ENTRY_NODEF(629),
	ERROR_ENTRY_NODEF10(630),
	ERROR_ENTRY_NODEF10(640),ERROR_ENTRY_NODEF10(650),ERROR_ENTRY_NODEF10(660),ERROR_ENTRY_NODEF10(670),
	ERROR_ENTRY_NODEF10(680),ERROR_ENTRY_NODEF10(690),
	ERROR_ENTRY_NODEF100(700), ERROR_ENTRY_NODEF100(800), ERROR_ENTRY_NODEF100(900)
	};
	ERROR geterror(int id) {
		ERROR check;
		if (id < 0 || id >= ERROR_MAX_ENTRY)
			check = errors[0];
		else
			check = errors[id];
		return check;
	}
	ERROR geterrorin(int id, int line = -1, int col = -1) {
		ERROR check = geterror(id);
		check.inext = { (short)(line),(short)(col) };
		return check;
	}
	void ErrorTable::addError(int i, int l = -1, int p = -1) {
		if (i < 0) return;
		if (this->errorCount > ERR_TABLE_MAX_SIZE) throw geterror(2);
		this->errorTable[this->errorCount].id = i;
		this->errorTable[this->errorCount].line = l;
		this->errorTable[this->errorCount].pos = p;
		this->errorCount++;
	}
	void ErrorTable::addError(Error error) {
		if (this->errorCount > ERR_TABLE_MAX_SIZE) throw geterror(2);
		if (error.id != -1) {
			this->errorTable[this->errorCount] = error;
			this->errorCount++;
		}
	}

};