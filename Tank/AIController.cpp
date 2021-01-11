#include "AIController.h"
#include <GLFW/glfw3.h>

extern double currentTime;
extern GLboolean CheckCollision(GameObject& one, GameObject& two, Velocity velocity = Velocity(0, 0)); //Åö×²¼ì²âº¯Êý
double lastAITime = currentTime;
double lastEnemyTime = currentTime;

void AIController::AI(Game& game, float dt)
{
	bool ai = currentTime - lastAITime > 1;
	for (int i = 1; i < game.tanks.size(); i++)
	{
		Tank &tank = game.tanks[i];
		if (ai)
		{
			if (rand() % 4 == 0)
			{
				tank.changeDir(Direction(rand() % 8));
			}
		}
		for (Block& block : game.levels[game.level].blocks)
		{
			Position pos = tank.pos + tank.velocity * dt;
			while (pos.x < 0 || pos.y < 0 || 
				pos.x + tank.size.x > game.lvlWidth || pos.y + tank.size.y > game.lvlHeight || 
				!block.tankable && block.blood > 0 && CheckCollision(tank, block, tank.velocity * dt)) //Óë×©¿é·¢ÉúÅö×²
			{
				tank.changeDir(Direction(rand() % 8));
				pos = tank.pos + tank.velocity * dt;
			}
		}
		//for (Tank& t : game.tanks)
		//{
		//	while (CheckCollision(tank, t, tank.velocity * dt)) //Óë×©¿é·¢ÉúÅö×²
		//	{
		//		tank.changeDir(Direction(rand() % 8));
		//	}
		//}
 
		tank.move(dt);
		if (ai)
		{
			if (rand() % 3 == 0)
			{
				tank.turnTo(game.player->pos);
			}
			else
			{
				tank.turnTo(game.levels[game.level].blocks[0].pos);
			}
			if (rand() % 3 == 0)
			{
				glm::vec2 center = tank.pos + Size(tank.size.x / 2, tank.size.y / 2);
				glm::vec2 pos(center.x + 0.65 * tank.size.y * sin(tank.rotation), center.y - 0.65 * tank.size.y * cos(tank.rotation));
				Bullet bullet(pos, tank.rotation);
				bullet.isEnemy = true;
				game.bullets.push_back(bullet);
			}
		}
	}
	if (ai)
	{
		lastAITime = currentTime;
	}
}

void AIController::generateEnemy(Game& game, float dt)
{
	if (currentTime - lastEnemyTime > 4 && game.tanks.size() < 6 && game.levels[game.level].tanks > 0)
	{
		int base = rand() % game.levels[game.level].tankBase.size();
		Tank enemy(game.levels[game.level].tankBase[base].pos, Size(game.levels[game.level].unit_width - 5, game.levels[game.level].unit_height - 5), 180);
		enemy.changeDir(Direction(rand() % 8));
		enemy.isEnemy = true;
		game.tanks.push_back(enemy);
		lastEnemyTime = currentTime;
		game.levels[game.level].tanks--;
	}

}


