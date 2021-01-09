#include "AIController.h"
#include <GLFW/glfw3.h>


//double currentTime = glfwGetTime();
//double lastProcessTime = currentTime;
//
//void AIController::AI(Game &game, float dt)
//{
//	for (Tank& tank : game.enemyTanks)
//	{
//		tank.changeDir(Direction(rand() % 8));
//		tank.move(dt);
//		if (rand() % 50 == 0)
//		{
//			if (currentTime - lastProcessTime > 0.2)
//			{
//				glm::vec2 center = tank.pos + Size(tank.size.x / 2, tank.size.y / 2);
//				glm::vec2 pos(center.x + 0.65 * tank.size.y * sin(tank.rotation), center.y - 0.65 * tank.size.y * cos(tank.rotation));
//				Bullet bullet(pos, tank.rotation);
//				game.bullets.push_back(bullet);
//				lastProcessTime = currentTime;
//			}
//		}
//	}
//}
