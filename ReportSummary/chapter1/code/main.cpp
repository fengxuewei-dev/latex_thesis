#include <iostream>
#include "Astar.h"
using namespace std;
 
int main()
{
	vector<vector<int>> maze = {
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1 },
		{ 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1 },
		{ 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
	};
	Astar astar;
	astar.InitAstar(maze);
 
	Point start(1, 1);
	Point end(6, 10);
	list<Point *> path = astar.GetPath(start, end, false);
	for (auto &p : path)
		cout << '(' << p->x << ',' << p->y << ')' << endl;
 
	system("pause");
	return 0;
}