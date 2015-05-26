#include "stdafx.h"

std::vector<int> ForwdStrVertex;
std::vector<int> BakwdStrVertex;
extern dStruct::node VertexSet[27773];

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

void travel(std::vector<int> *startList)
{
	for (std::vector<int>::iterator it = *startList.begin();it != *startList.end();++it)
	{
		
	}
}

int main()
{
	return 0;
}