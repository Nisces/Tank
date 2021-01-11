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
	openList.push_back(new Node(start->x, start->y)); //�������,��������һ���ڵ㣬�������
	while (!openList.empty())
	{
		auto curNode = getLeastNode(); //�ҵ�Fֵ��С�ĵ�
		openList.remove(curNode); //�ӿ����б���ɾ��
		closeList.push_back(curNode); //�ŵ��ر��б�
		//1,�ҵ���ǰ��Χ�˸����п���ͨ���ĸ���
		auto surroundPoints = getSurroundNodes(curNode);
		for (auto& target : surroundPoints)
		{
			//2,��ĳһ�����ӣ���������ڿ����б��У����뵽�����б����õ�ǰ��Ϊ�丸�ڵ㣬����F G H
			if (!inList(openList, target))
			{
				target->parent = curNode;

				target->g = calcG(curNode, target);
				target->h = manhattan(target);
				target->f = target->g + target->h;

				openList.push_back(target);
			}
			//3����ĳһ�����ӣ����ڿ����б��У�����Gֵ, �����ԭ���Ĵ�, ��ʲô������, �����������ĸ��ڵ�Ϊ��ǰ��,������G��F
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
				return true; //����ͨ��
		}
	}
	return false;
}

list<Node*> AStar::getPath(Node* start, Node* end)
{
	Node* result = this->end;
	std::list<Node*> path;
	//����·�������û�ҵ�·�������ؿ�����
	if (search(start, end))
	{
		while (result)
		{
			path.push_front(result);
			result = result->parent;
		}
	}

	// �����ʱ�����б���ֹ�ظ�ִ��GetPath���½���쳣
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
		|| inList(closeList, target)) //������뵱ǰ�ڵ��غϡ�������ͼ�����ϰ�������ڹر��б��У�����false
		return false;
	else
	{
		if (abs(point->x - target->x) + abs(point->y - target->y) == 1) //��б�ǿ���
		{
			return true;
		}
		else
		{
			//б�Խ�Ҫ�ж��Ƿ��ס
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
	int parentG = cur->parent == NULL ? 0 : cur->parent->g; //����ǳ�ʼ�ڵ㣬���丸�ڵ��ǿ�
	return parentG + extraG;
}
