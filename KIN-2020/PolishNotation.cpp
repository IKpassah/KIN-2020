#include "PolishNotation.h"

namespace PN {

	struct stackNode {
		char lex;
		stackNode* nextNode;
		stackNode(char l, stackNode* nNode) {
			lex = l;
			nextNode = nNode;
		}
	};
	struct stacker {
		stackNode* head;
		stacker() {
			head = NULL;
		}
		bool isEmpty() {
			return head == NULL ? true : false;
		}
		void push(char l) {
			head = new stackNode(l, head);
		}
		char pop() {
			char lex;
			lex = head->lex;
			stackNode* node = head;
			head = head->nextNode;
			delete node;
			return lex;
		}
		char getHead() {
			return head->lex;
		}
	};
	short GetPriority(char lex) {
		if (lex == LEX_LEFTHESIS || lex == LEX_RIGHTHESIS) return 0;
		if (lex == LEX_COMMA) return 1;
		if (lex == LEX_STAR || lex == LEX_DIRSLASH || lex == LEX_PERC) return 2;
		if (lex == LEX_PLUS || lex == LEX_MINUS) return 3;
		return -1;
	}

	bool PriorityMoreOrEqual(char first, char second) {
		return GetPriority(first) >= GetPriority(second) ? true : false;
	}
	bool PolishNotation(int lextable_pos, LT::LexTable& lextable) {
		LT::LexTable table = LT::Create(0);
		char firststr[50];
		char secondstr[50];
		for (int poslex = lextable_pos; lextable.table[poslex].lexema[0] != LEX_SEMICOLON; poslex++) {
			firststr[poslex - lextable_pos] = lextable.table[poslex].lexema[0];
			secondstr[poslex - lextable_pos] = '1';
		}
		short secstrcount = 0;
		stacker stack;
		short parmsCounter = 1;
		LT::Entry function_info;
		int pos;
		for (pos = lextable_pos;
			lextable.table[pos].lexema[0] != LEX_SEMICOLON; pos++) {
			if (lextable.table[pos].idxTI != -1) {
				if (lextable.table[pos-1].idxTI != -1) return false;
				if (lextable.table[pos + 1].lexema[0] == LEX_LEFTHESIS) {
					function_info = lextable.table[pos];
					stack.push(LEX_FUNC_PN);
					parmsCounter = 1;
				}
				else {
					LT::Add(table, lextable.table[pos]);
					secondstr[secstrcount++] = lextable.table[pos].lexema[0]; /// debug
				}
			}
			else if (lextable.table[pos].lexema[0] == LEX_PLUS ||
				lextable.table[pos].lexema[0] == LEX_MINUS ||
				lextable.table[pos].lexema[0] == LEX_STAR ||
				lextable.table[pos].lexema[0] == LEX_DIRSLASH ||
				lextable.table[pos].lexema[0] == LEX_PERC ||
				lextable.table[pos].lexema[0] == LEX_PEER  )
			{
				if (GetPriority(lextable.table[pos - 1].lexema[0]) >= 1 &&
					GetPriority(lextable.table[pos - 1].lexema[0]) <= 3 ||
					lextable.table[pos - 1].lexema[0] == LEX_LEFTHESIS
					)
					return false;
				if (stack.isEmpty() || stack.getHead() == LEX_LEFTHESIS) {}
				else if (GetPriority(stack.getHead()) <= GetPriority(lextable.table[pos].lexema[0]))
				{
					while (!stack.isEmpty() && GetPriority(stack.getHead()) <= GetPriority(lextable.table[pos].lexema[0])) {
						secondstr[secstrcount++] = stack.getHead(); /// debug
						LT::Add(table, LT::Putentry(stack.pop(), 0));
					}
					//stack.push(lextable.table[pos].lexema[0]);
				}
				stack.push(lextable.table[pos].lexema[0]);
			}
			else if (lextable.table[pos].lexema[0] == LEX_COMMA) {
				if (!stack.isEmpty()) {
					while (stack.getHead() != LEX_LEFTHESIS) {
						secondstr[secstrcount++] = stack.getHead(); /// debug
						LT::Add(table, LT::Putentry(stack.pop(), 0));
					}
				}
				parmsCounter++;
			}
			else if (lextable.table[pos].lexema[0] == LEX_LEFTHESIS) {
				stack.push(lextable.table[pos].lexema[0]);
			}
			else if (lextable.table[pos].lexema[0] == LEX_RIGHTHESIS) {
				if (lextable.table[pos - 1].idxTI != -1 ||
					GetPriority(lextable.table[pos - 1].lexema[0]) == 0)
				{
					while (!stack.isEmpty() && stack.getHead() != LEX_LEFTHESIS) {
						secondstr[secstrcount++] = stack.getHead(); /// debug
						LT::Add(table, LT::Putentry(stack.pop(), 0));
					}
					if (stack.isEmpty())
						return false;
					stack.pop();
					if (!stack.isEmpty() && stack.getHead() == LEX_FUNC_PN) {
						secondstr[secstrcount++] = LEX_ID; /// debug
						secondstr[secstrcount++] = LEX_FUNC_PN; /// debug
						secondstr[secstrcount++] = (char)((int)'0' + parmsCounter); /// debug
						LT::Add(table, function_info);
						LT::Add(table, LT::Putentry(stack.pop(), 0));
						//LT::Add(table, LT::Putentry((char)((int)'0' + parmsCounter), 0));
					}
				}
				else
					return false;
			}
			else
				return false;
		}
		while (!stack.isEmpty()) {
			secondstr[secstrcount++] = stack.getHead(); /// debug
			if (stack.getHead() == LEX_LEFTHESIS) return false;
			LT::Add(table, LT::Putentry(stack.pop(), 0));
		}
		int lex_override_position;
		int new_table_size = lextable_pos + table.size;
		for (lex_override_position = lextable_pos; lex_override_position < new_table_size; lex_override_position++) {
			lextable.table[lex_override_position] = table.table[lex_override_position - lextable_pos];
		}
		lextable.table[lex_override_position] = lextable.table[pos];
		for (lex_override_position++; lex_override_position <= pos; lex_override_position++) {
			lextable.table[lex_override_position] = LT::Putentry(LEX_NULL, 0);
		}
		secondstr[secstrcount] = '\0';
		//std::cout << secondstr << " ";
		LT::Delete(table);
		return true;
	}
}
