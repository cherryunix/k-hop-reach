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

void PostOrderTravel(int curId)
{
	dStruct::node &presentNode = VertexSet[curId];
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

void ForwardOrderTravel(int curId)
{
	dStruct::node &presentNode = VertexSet[curId];
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

void ForwardDepth(int curId, int depth)
{
	dStruct::node &presentNode = VertexSet[curId];
	presentNode.depth.first = depth;
	if (presentNode.OutDeg == 0)
		return;
	for (std::vector<int>::iterator it = presentNode.next_node.begin(); it != presentNode.next_node.end(); ++it)
	{
		ForwardDepth(*it, depth + 1);
	}
	return;
}

void BackwordDepth(int curId, int depth)
{
	dStruct::node &presentNode = VertexSet[curId];
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
	std::queue<int> forwardQue;
	std::queue<int> backwardQue;
	int tmpForwardDeg[dStruct::maxNodeNumber];
	int tmpBackwardDeg[dStruct::maxNodeNumber];
	int isInQue[dStruct::maxNodeNumber];
	//Forward Top
	memset(isVisit, 0, sizeof(isVisit));
	memset(isInQue, 0, sizeof(isInQue));
	for (int i = 1; i < dStruct::maxNodeNumber; i++)
	{
		tmpForwardDeg[i] = VertexSet[i].InDeg;
		tmpBackwardDeg[i] = VertexSet[i].OutDeg;
	}
	for (std::vector<int>::iterator it = ForwdStrVertex.begin(); it != ForwdStrVertex.end(); ++it)
	{
		forwardQue.push(*it);
		isInQue[*it] = 1;
		dStruct::node &presentNode = VertexSet[*it];
		presentNode.topOrder.first = 1;
	}
	for (;;)
	{
		if (forwardQue.empty())
			break;
		int curId = forwardQue.front();
		if (!isVisit[curId])
		{
			forwardQue.pop();
			isVisit[curId] = 1;
			isInQue[curId] = 0;
			dStruct::node &fatherNode = VertexSet[curId];
			for (std::vector<int>::iterator jt = fatherNode.next_node.begin(); jt != fatherNode.next_node.end(); ++jt)
				if (!isVisit[*jt] && !isInQue[*jt])
				{
				if (tmpForwardDeg[*jt] == 1)
				{
					dStruct::node &childNode = VertexSet[*jt];
					childNode.topOrder.first = fatherNode.topOrder.first + 1;
					forwardQue.push(*jt);
					isInQue[*jt] = 1;
				}
				tmpForwardDeg[*jt] -= 1;
				}
		}
		else
		{
			forwardQue.pop();
		}
	}
	//BackwardTop
	memset(isVisit, 0, sizeof(isVisit));
	memset(isInQue, 0, sizeof(isInQue));
	for (std::vector<int>::iterator it = BakwdStrVertex.begin(); it != BakwdStrVertex.end(); ++it)
	{
		backwardQue.push(*it);
		isInQue[*it] = 1;
		dStruct::node &presentNode = VertexSet[*it];
		presentNode.topOrder.second = 1;
	}
	for (;;)
	{
		if (backwardQue.empty())
			break;
		int curId = backwardQue.front();
		if (!isVisit[curId])
		{
			backwardQue.pop();
			isVisit[curId] = 1;
			isInQue[curId] = 0;
			dStruct::node &fatherNode = VertexSet[curId];
			for (std::vector<int>::iterator jt = fatherNode.prev_node.begin(); jt != fatherNode.prev_node.end(); ++jt)
				if (!isVisit[*jt] && !isInQue[*jt])
				{
				if (tmpBackwardDeg[*jt] == 1)
				{
					dStruct::node &childNode = VertexSet[*jt];
					childNode.topOrder.second = fatherNode.topOrder.second + 1;
					backwardQue.push(*jt);
					isInQue[*jt] = 1;
				}
				tmpForwardDeg[*jt] -= 1;
				}
		}
		else
		{
			backwardQue.pop();
		}
	}
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
	for (std::vector<int>::iterator it = tNodeList.begin(); it != tNodeList.end(); ++it)
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