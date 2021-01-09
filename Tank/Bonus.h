#pragma once
#ifndef	 _Tank_
#define  _Tank_
#include "GameObject.h"
#include "Tank.h"
#include <string>

enum class BonusType
{
	FAST, BLOOD, ARMOR
};
class Bonus : public GameObject
{
public:
	Bonus(string type, Position pos, Size size);
	//bool draw(SpriteRenderer& renderer);

	bool outoftime;   //���� �Ƿ� ��ʱ
	bool activated;   //�����Ƿ�̹�˻��
	bool runout;   //�����Ƿ�ʧЧ
	int delay;   //��ʱ��ʾ����
	bool obtainable; //������ʾ��ſ��Ա���ȡ

	std::string type;
	float exitTime;
	float validTime;  //��Чʱ��
};

#endif
