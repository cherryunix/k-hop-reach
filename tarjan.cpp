#include "stdafx.h"

struct node{
	std::vector<int> next_node;
	std::vector<int> prev_node;
	int InDeg;
	int OutDeg;
	int Index_D1[2];
	int Index_D2[2];
	int belong;
	std::vector<int> super_node;
};

std::vector<int> ForwdStrVertex;
std::vector<int> BakwdStrVertex;
node VertexSet[27773];

void init()
{
	int FromID;
	int ToID;
	std::ifstream InFile;
	InFile.open("C:\\Users/cherryunix/Desktop/Cit-HepTh_exp.txt");
	for (int i = 1; i <= 352807; i++)
	{
		InFile >> FromID >> ToID;
		VertexSet[FromID].OutDeg++;
		VertexSet[FromID].next_node.push_back(ToID);
		VertexSet[ToID].InDeg++;
		VertexSet[ToID].prev_node.push_back(FromID);
	}
	for (int i = 1; i <= 27770; i++)
	{
		if (VertexSet[i].InDeg == 0)
			ForwdStrVertex.push_back(i);
		if (VertexSet[i].OutDeg == 0)
			BakwdStrVertex.push_back(i);
	}
}

int DFN[27771];
int LOW[27771];
int Dindex;
int instack[27771];
int Stop;
int Bcnt;
int Stap[27771];

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
			VertexSet[i].super_node.push_back(j);
		} while (j != i);
	}
}
void solve()
{
	int i;
	Stop = Bcnt = Dindex = 0;
	memset(DFN, 0, sizeof(DFN));
	for (i = 1; i <= 27771; i++)
		if (!DFN[i])
			tarjan(i);
}

void PostTravl()
{

}

int main()
{
	init();
	solve();

	return 0;
}