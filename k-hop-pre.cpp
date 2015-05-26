#include "stdafx.h"

std::map<int, int> book;
std::vector<int> sort_seq;
void Discretization()
{
	int FromId;
	int ToId;
	std::ifstream InFile;
	std::ofstream OutFile;
	InFile.open("C:\\Users/cherryunix/Desktop/Cit-HepTh_use.txt");
	OutFile.open("C:\\Users/cherryunix/Desktop/Cit-HepTh_exp.txt");
	book.clear();
	sort_seq.clear();
	for (int i = 1; i <= 352807; i++)
	{
		InFile >> FromId >> ToId;
		if (!book[FromId])
		{
			sort_seq.push_back(FromId);
			book[FromId] = 1;
		}
		if (!book[ToId])
		{
			sort_seq.push_back(ToId);
			book[ToId] = 1;
		}
	}
	InFile.close();
	InFile.open("C:\\Users/cherryunix/Desktop/Cit-HepTh_use.txt");
	std::sort(sort_seq.begin(), sort_seq.end());
	int len = sort_seq.size();
	for (int i = 0; i < len; i++)
	{
		int tmp = sort_seq[i];
		book[tmp] = i+1;
	}
	for (int i = 1; i <352807; i++)
	{
		InFile >> FromId >> ToId;
		OutFile << book[FromId] << " " << book[ToId] << std::endl;
	}
	InFile.close();
	OutFile.close();
}