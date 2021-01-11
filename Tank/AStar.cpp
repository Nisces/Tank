#include "AStar.h"
#include <cmath>

void AStar::initAStar(vector<vector<int>>& map)
{
	this->map = map;
}

bool AStar::search(Node* start, Node* end)
{
	this->start = start;
	this->end = end;
	openList.push_back(new Node(start->x, start->y)); //置入起点,拷贝开辟一个节点，内外隔离
	while (!openList.empty())
	{
		auto curNode = getLeastNode(); //找到F值最小的点
		openList.remove(curNode); //从开启列表中删除
		closeList.push_back(curNode); //放到关闭列表
		//1,找到当前周围八个格中可以通过的格子
		auto surroundPoints = getSurroundNodes(curNode);
		for (auto& target : surroundPoints)
		{
			//2,对某一个格子，如果它不在开启列表中，加入到开启列表，设置当前格为其父节点，计算F G H
			if (!inList(openList, target))
			{
				target->parent = curNode;

				target->g = calcG(curNode, target);
				target->h = manhattan(target);
				target->f = target->g + target->h;

				openList.push_back(target);
			}
			//3，对某一个格子，它在开启列表中，计算G值, 如果比原来的大, 就什么都不做, 否则设置它的父节点为当前点,并更新G和F
			else
			{
				int tempG = calcG(curNode, target);
				if (tempG < target->g)
				{
					target->parent = curNode;

					target->g = tempG;
					target->f = target->g + target->h;
				}
			}
			bool res = inList(openList, this->end);
			if (res)
				return true; //可以通行
		}
	}
	return false;
}

list<Node*> AStar::getPath(Node* start, Node* end)
{
	Node* result = this->end;
	std::list<Node*> path;
	//返回路径，如果没找到路径，返回空链表
	if (search(start, end))
	{
		while (result)
		{
			path.push_front(result);
			result = result->parent;
		}
	}

	// 清空临时开闭列表，防止重复执行GetPath导致结果异常
	openList.clear();
	closeList.clear();

	return path;
}

vector<Node*> AStar::getSurroundNodes(const Node* node)
{
	std::vector<Node*> surroundPoints;

	for (int x = node->x - 1; x <= node->x + 1; x++)
	{
		for (int y = node->y - 1; y <= node->y + 1; y++)
		{
			if (canReach(node, &Node(x, y)))
			{
				surroundPoints.push_back(new Node(x, y));
			}
		}
	}
	return surroundPoints;
}

bool AStar::canReach(const Node* point, const Node* target)
{
	if (target->x<0 || target->x>map.size() - 1
		|| target->y<0 || target->y>map[0].size() - 1
		|| map[target->x][target->y] == 0
		|| *target == *point
		|| inList(closeList, target)) //如果点与当前节点重合、超出地图、是障碍物、或者在关闭列表中，返回false
		return false;
	else
	{
		if (abs(point->x - target->x) + abs(point->y - target->y) == 1) //非斜角可以
		{
			return true;
		}
		else
		{
			//斜对角要判断是否绊住
			if (map[point->x][target->y] == 0 && map[target->x][point->y] == 0)
				return true;
			else
				return false;
		}
	}
}

bool AStar::inList(const list<Node*>& ls, const Node* node)
{
	for (auto& n : ls)
	{
		if (*n == *node)
		{
			return true;
		}
	}
	return false;
}

Node* AStar::getLeastNode()
{
	if (!openList.empty())
	{
		auto resPoint = openList.front();
		for (auto& point : openList)
		{
			if (point->f < resPoint->f)
			{
				resPoint = point;
			}
		}
		return resPoint;
	}
	return nullptr;
}

float AStar::manhattan(Node* node)
{
	return abs(node->x - this->end->x) * this->straightCost + abs(node->y - this->end->y) * this->straightCost;
}

float AStar::calcG(Node* prev, Node* cur)
{
	int extraG = (abs(cur->x - prev->x) + abs(cur->y - prev->y)) == 1 ? straightCost : diagCost;
	int parentG = cur->parent == NULL ? 0 : cur->parent->g; //如果是初始节点，则其父节点是空
	return parentG + extraG;
}
