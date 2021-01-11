#pragma once
#include <vector>
#include <list>

using namespace std;

class Node
{
public:
	int x, y;
	float f, g, h;
	bool walkable;
	Node* parent;
	Node(int x, int y) :f(0), g(0), h(0), parent(nullptr), walkable(false)
	{
		this->x = x;
		this->y = y;
	}
	bool operator==(const Node &rhs) const
	{
		return this->x == rhs.x && this->y == rhs.y;
	}
};

class AStar
{
public:
	void initAStar(vector<vector<int>>& map);
	bool search(Node* start, Node* end);
	list<Node*> getPath(Node* start, Node* end);
private:
	vector<Node*> getSurroundNodes(const Node* node);
	bool canReach(const Node* point, const Node* target);
	bool inList(const list<Node*> &ls, const Node* node);  //�ж�ĳ������Ƿ�������б���
	Node* getLeastNode();  //�ӿ��б��л�ȡ������С�Ľڵ�
	float manhattan(Node* node);
	float calcG(Node* prev, Node* cur);
private:
	float straightCost = 1;
	float diagCost = 1.41421356237;
	Node* start;
	Node* end;
	vector<vector<int>> map;
	list<Node*> openList;
	list<Node*> closeList;
	list<Node*> path;
};

