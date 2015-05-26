#include "stdafx.h"

std::vector<int> ForwdStrVertex;
std::vector<int> BakwdStrVertex;
extern dStruct::node VertexSet[dStruct::maxNodeNumber];
static int isVisit[dStruct::maxNodeNumber] = { 0 };

inline int min(int a, int b)
{
	return a < b ? a : b;
}

void init()
{
	int FromID;
	int ToID;
	std::ifstream InFile;
	InFile.open("C:\\Users/cherryunix/Desktop/Cit-HepTh_exp.txt");
	for (int i = 1; i <= dStruct::maxEdgeNumber; i++)
	{
		InFile >> FromID >> ToID;
		VertexSet[FromID].OutDeg++;
		VertexSet[FromID].next_node.push_back(ToID);
		VertexSet[ToID].InDeg++;
		VertexSet[ToID].prev_node.push_back(FromID);
	}
	for (int i = 1; i < dStruct::maxNodeNumber; i++)
	{
		if (VertexSet[i].InDeg == 0)
			ForwdStrVertex.push_back(i);
		if (VertexSet[i].OutDeg == 0)
			BakwdStrVertex.push_back(i);
	}
}

static int travelOrder = 1;

void PostOrderTravel(int curNode)
{
	dStruct::node &presentNode = VertexSet[curNode];
	if (presentNode.OutDeg == 0)
	{
		presentNode.indexP = std::make_pair(travelOrder, travelOrder);
		travelOrder++;
		return;
	}
	int minChild = MAXINT;
	for (std::vector<int>::iterator it = presentNode.next_node.begin(); it != presentNode.next_node.end(); ++it)
		if (!isVisit[*it])
	{
		isVisit[*it] = 1;
		PostOrderTravel(*it);
		dStruct::node &tNode = VertexSet[*it];
		minChild = min(minChild, tNode.indexP.second);
	}
	presentNode.indexP = std::make_pair(minChild, travelOrder);
	travelOrder++;
	return;
}

void ForwardOrderTravel(int curNode)
{
	dStruct::node &presentNode = VertexSet[curNode];
	if (presentNode.OutDeg == 0)
	{
		presentNode.indexF = std::make_pair(travelOrder, travelOrder);
		travelOrder++;
		return;
	}
	int minChild = MAXINT;
	for (std::vector<int>::iterator it = presentNode.next_node.end(); it != presentNode.next_node.begin(); --it)
		if (!isVisit[*it])
		{
		isVisit[*it] = 1;
		ForwardOrderTravel(*it);
		dStruct::node &tNode = VertexSet[*it];
		minChild = min(minChild, tNode.indexP.second);
		}
	presentNode.indexF = std::make_pair(minChild, travelOrder);
	travelOrder++;
	return;
}

void ForwardDepth(int curNode, int depth)
{
	dStruct::node &presentNode = VertexSet[curNode];
	presentNode.depth.first = depth;
	if (presentNode.OutDeg == 0)
		return;
	for (std::vector<int>::iterator it = presentNode.next_node.begin(); it != presentNode.next_node.end(); ++it)
	{
		ForwardDepth(*it, depth + 1);
	}
	return;
}

void BackwordDepth(int curNode, int depth)
{
	dStruct::node &presentNode = VertexSet[curNode];
	presentNode.depth.second = depth;
	if (presentNode.InDeg == 0)
		return;
	for (std::vector<int>::iterator it = presentNode.prev_node.begin(); it != presentNode.prev_node.end(); ++it)
	{
		BackwordDepth(*it, depth + 1);
	}
	return;
}

void TopTravel()
{

}

void DepthTravel()
{
	for (std::vector<int>::iterator it = ForwdStrVertex.begin(); it != ForwdStrVertex.end(); it++)
	{
		ForwardDepth(*it, 1);
	}

	for (std::vector<int>::iterator it = BakwdStrVertex.begin(); it != BakwdStrVertex.end(); it++)
	{
		BackwordDepth(*it, 1);
	}
}

void travel()
{
	std::vector<int> tNodeList = ForwdStrVertex;
	for (std::vector<int>::iterator it = tNodeList.begin();it != tNodeList.end();++it)
	{
			PostOrderTravel(*it);
	}
	isVisit[dStruct::maxNodeNumber] = { 0 };
	travelOrder = 1;
	for (std::vector<int>::iterator it = tNodeList.begin(); it != tNodeList.end(); ++it)
	{
		ForwardOrderTravel(*it);
	}
}

int main()
{
	return 0;
}