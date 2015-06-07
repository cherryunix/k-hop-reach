#include "stdafx.h"

extern dStruct::node VertexSet[27773];

int DFN[dStruct::maxNodeNumber];
int LOW[dStruct::maxNodeNumber];
int Dindex;
int instack[dStruct::maxNodeNumber];
int Stop;
int Bcnt;
int Stap[dStruct::maxNodeNumber];

void tarjan(int i)
{
	int j;
	DFN[i] = LOW[i] = ++Dindex;
	instack[i] = true;
	Stap[++Stop] = i;
	for (std::vector<int>::iterator it = VertexSet[i].next_node.begin(); it != VertexSet[i].next_node.end();++it)
	{
		j = *it;
		if (!DFN[j])
		{
			tarjan(j);
			if (LOW[j]<LOW[i])
				LOW[i] = LOW[j];
		}
		else if (instack[j] && DFN[j]<LOW[i])
			LOW[i] = DFN[j];
	}
	if (DFN[i] == LOW[i])
	{
		Bcnt++;
		do
		{
			j = Stap[Stop--];
			instack[j] = false;
			VertexSet[j].belong = i;
			//VertexSet[i].super_node.push_back(j);
		} while (j != i);
	}
}
void solve()
{
	int i;
	Stop = Bcnt = Dindex = 0;
	memset(DFN, 0, sizeof(DFN));
	for (i = 1; i <= dStruct::maxNodeNumber; i++)
		if (!DFN[i])
			tarjan(i);
}