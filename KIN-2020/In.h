#pragma once
#define IN_MAX_LEN_TEXT 1024*4	// ����������� ������ ��������� ����(1 ��������)

#define IN_CODE_ENDL '\n'				//������ ����� ������
#define IN_CODE_QUOTES2 '\"'
#define CODE_NULL '\0'				//������ ����� ������
//������� �������� ������� ���������� ,������ = ��� (Windows 1251) �������
//���� 0<= �������� <256 - �� �������� ������ ��������
#define IN_CODE_TABLE {\
IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,\
IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,\
IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,\
IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,\
IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,\
IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::I, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,\
IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,\
IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::F, IN::T,\
IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,\
IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,\
\
IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,\
IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,\
IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,\
IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,\
IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,\
IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,\
}
// 0	 1		2		3	  4		 5		6		7	 8	    9		A		B	  C		  D		E		F

//������ ���� 2001 = ca e0 f8 e0 e5 e4 20 c8 e2 e0 ed 20 32 30 30 31
//Kashayed Ivan = 4b 61 73 68 61 79 65 64 20 49 76 61 6e
// A = c0
// X = 58
// - = 2d
// \0 = 00 \n = 0a

//#define OUT_A_TO_MIN '-'

namespace In
{
	struct IN				// �������� ������
	{
		enum { T = 1024, F = 2048, I = 4096 };	// � ���������� ������, F ������������ ������,I ������������ ����� ��������
		int size = 0;								// ������ ��������� ����
		int lines = 0;								// ���������� �����
		int ignor = 0;								// ���������� ����������������� ��������
		unsigned char* text;					// �������� ���(Windows 1251)
		int code[256] = IN_CODE_TABLE;		// ������� �������� T,F,I ����� ��������
	};
	IN getin(wchar_t* infile, Error::ErrorTable errorTable);					//������ � ��������� ������� �����
};