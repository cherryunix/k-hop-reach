namespace dStruct{
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
	
}