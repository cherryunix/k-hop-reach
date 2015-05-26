namespace dStruct{
	struct node{
	std::vector<int> next_node;
	std::vector<int> prev_node;
	int InDeg;
	int OutDeg;
	std::pair<int, int> depth;
	std::pair<int, int> topOrder;
	std::pair<int,int> indexP;
	std::pair<int,int> indexF;
	int belong;
	std::vector<int> super_node;
	};
	const int maxNodeNumber = 27771;
	const int maxEdgeNumber = 352807;

}

#define MAXINT 214747384