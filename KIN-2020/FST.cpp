#include "stdafx.h"

int Unsignedstrlen(unsigned char* word) {
	int size = 0;
	for (; word[size] != '\0'; size++) {
	}
	return size;
}

FST::RELATION::RELATION(unsigned char c, short ns)
	: symbol(c), nnode(ns)
{	}

FST::NODE::NODE() //по умолчанию
	: n_relation(0), relations(nullptr)
{	}

FST::NODE::NODE(short n, RELATION rel, ...) //с параметрами
{
	n_relation = n;
	RELATION* p = &rel;
	relations = new RELATION[n];
	for (short i = 0; i < n; i++)
		relations[i] = p[i];
};

FST::FST::FST(unsigned char* s, short ns, NODE n, ...)
{
	string = s;
	nstates = ns;
	nodes = new NODE[ns];
	NODE* p = &n;
	for (int k = 0; k < ns; k++)
		nodes[k] = p[k];
	rstates = new short[nstates];
	memset(rstates, 0xff, sizeof(short) * nstates);
	rstates[0] = 0;
	position = -1;
};

bool step(FST::FST& fst, short*& rstates) //один шаг автомата
{
	bool rc = false;
	std::swap(rstates, fst.rstates); // смена массивов
	for (short i = 0; i < fst.nstates; i++)
	{
		if (rstates[i] == fst.position)
			for (short j = 0; j < fst.nodes[i].n_relation; j++)
			{
				if (fst.nodes[i].relations[j].symbol == fst.string[fst.position])
				{
					fst.rstates[fst.nodes[i].relations[j].nnode] = fst.position + 1;
					rc = true;
				};
			};
	};
	return rc;
}

bool FST::execute(FST& fst) //выполнить распознование цепочки
{
	short* rstates = new short[fst.nstates];
	memset(rstates, 0xff, sizeof(short) * fst.nstates);
	short lstring = Unsignedstrlen(fst.string);
	bool rc = true;
	for (short i = 0; i < lstring && rc; i++)
	{
		fst.position++;			//продвинули позицию
		rc = step(fst, rstates); //один шаг автомата
	}
	delete[] rstates;
	return (rc ? (fst.rstates[fst.nstates - 1] == lstring) : rc);
}