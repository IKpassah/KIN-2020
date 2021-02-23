#pragma once
#include "stdafx.h"

namespace PN {
	short GetPriority(char lex);
	bool PriorityMoreOrEqual(char first, char second);
	bool PolishNotation(int lextable_pos, LT::LexTable& lextable);
}