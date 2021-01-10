#include "Game.h"
#include <iostream>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <string.h>
#include <algorithm>
#include <ctime>
#include <sstream>
#include <irrKlang/irrKlang.h>
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "UIRenderer.h"
#include "AIController.h"

using namespace std;
using namespace irrklang;

SpriteRenderer* renderer = nullptr;
UIRenderer* ui = nullptr;
ISoundEngine* SoundEngine = createIrrKlangDevice();

GLboolean CheckCollision(GameObject& one, GameObject& two, Velocity velocity = Velocity(0, 0)) //碰撞检测函数
{
	bool collisionX = one.pos.x + velocity.x + one.size.x >= two.pos.x &&
		two.pos.x + two.size.x >= one.pos.x + velocity.x;
	bool collisionY = one.pos.y + velocity.y + one.size.y >= two.pos.y &&
		two.pos.y + two.size.y >= one.pos.y + velocity.y;
	//两个方向都发生碰撞时才发生碰撞
	return collisionX && collisionY;
}

Game::Game(unsigned int height, unsigned int width) : width(width), height(height), mousePos(0, 0), camPostion(0, 0)
{
	viewSize = Size(800, 600);
}

Game::~Game()
{
	delete renderer;
}

void Game::init()
{
	srand(unsigned int(time(NULL)));
	//加载着色器
	ResourceManager::loadShader("sprite.vs", "sprite.fs", nullptr, "sprite").use();
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(viewSize.x), static_cast<float>(viewSize.y), 0.0f, -1.0f, 1.0f);
	ResourceManager::getShader("sprite").SetInteger("sprite", 0);
	ResourceManager::getShader("sprite").SetMatrix4("projection", projection);
	glm::mat4 view(1.0);
	ResourceManager::getShader("sprite").SetMatrix4("view", view);

	renderer = new SpriteRenderer(ResourceManager::getShader("sprite"));
	ui = new UIRenderer(viewSize.x, viewSize.y);
	ui->load("resource/fonts/OCRAEXT.TTF", 24);

	//加载纹理贴图文件
	ResourceManager::loadTexture("resource/texture/Hulls_Color_B/Hull_02_A.png", "Hull_02_A");
	ResourceManager::loadTexture("resource/texture/Hulls_Color_B/Hull_02_B.png", "Hull_02_B");
	ResourceManager::loadTexture("resource/texture/Weapon_Color_B_256X256/Gun_01.png", "Gun_01");
	ResourceManager::loadTexture("resource/texture/Effects/Exhaust_Fire.png", "Shell");

	ResourceManager::loadTexture("resource/texture/Tiles/Ground_Tile_01_A.png", "GT1");
	ResourceManager::loadTexture("resource/texture/Tiles/Ground_Tile_02_A.png", "GT2");
	ResourceManager::loadTexture("resource/texture/Decor_Tiles/Decor_Tile_A_05.png", "BL1");
	ResourceManager::loadTexture("resource/texture/Decor_Tiles/Decor_Tile_A_05_A.png", "BL2");
	ResourceManager::loadTexture("resource/texture/Decor_Tiles/Decor_Tile_A_05_B.png", "BL3");
	ResourceManager::loadTexture("resource/texture/Decor_Tiles/Decor_Tile_A_05_C.png", "BL4");
	ResourceManager::loadTexture("resource/texture/Decor_Tiles/Decor_Tile_B_05.png", "STONE");
	ResourceManager::loadTexture("resource/texture/Tiles/Water.png", "WATER");
	ResourceManager::loadTexture("resource/texture/Props/Tree_05.png", "TREE");
	ResourceManager::loadTexture("resource/texture/Props/Artifact.png", "BASE");
	ResourceManager::loadTexture("resource/texture/Props/Barell_01.png", "BOMBT");
	ResourceManager::loadTexture("resource/texture/Props/Image 1801.png", "TANKBASE");
	ResourceManager::loadTexture("resource/texture/Decor_Tiles/shadow.png", "bomblock");
	ResourceManager::loadTexture("resource/texture/Props/Image 1008.png", "bombt");
	ResourceManager::loadTexture("resource/texture/Props/Rock_01.png", "EXTRA");
	ResourceManager::loadTexture("resource/texture/Props/Rock_03.png", "EXT");

	ResourceManager::loadTexture("resource/texture/Effects/Explosion_A.png", "FIRE1");
	ResourceManager::loadTexture("resource/texture/Effects/Explosion_B.png", "FIRE2");
	ResourceManager::loadTexture("resource/texture/Effects/Explosion_C.png", "FIRE3");
	ResourceManager::loadTexture("resource/texture/Effects/Explosion_D.png", "FIRE4");
	ResourceManager::loadTexture("resource/texture/Effects/Explosion_E.png", "FIRE5");
	ResourceManager::loadTexture("resource/texture/Effects/Explosion_F.png", "FIRE6");
	ResourceManager::loadTexture("resource/texture/Effects/Explosion_G.png", "FIRE7");
	ResourceManager::loadTexture("resource/texture/Effects/Explosion_H.png", "FIRE8");

	ResourceManager::loadTexture("resource/texture/Effects/Flash_A_04.png", "BE1");
	ResourceManager::loadTexture("resource/texture/Effects/Flash_A_05.png", "BE2");

	ResourceManager::loadTexture("resource/texture/Bonus_Items/Speed_Bonus.png", "FAST");
	ResourceManager::loadTexture("resource/texture/Bonus_Items/HP_Bonus.png", "BLOOD");
	ResourceManager::loadTexture("resource/texture/Bonus_Items/Shield_Bonus.png", "ARMOR");
	ResourceManager::loadTexture("resource/texture/Bonus_Items/ARMOR_tank.png", "ARMORTANK");

	ResourceManager::loadTexture("resource/texture/Props/neon fire hud_2.png", "HP");
	ResourceManager::loadTexture("resource/texture/Props/HB_Frames_0059_Package-----------------.png", "KUANG");
	ResourceManager::loadTexture("resource/texture/Props/aigei_com.png", "TANKTU");



	//加载关卡
	GameLevel one; one.load("resource/levels/one2.lvl", lvlWidth, lvlHeight); one.tanks = 20;
	GameLevel two; two.load("resource/levels/two.lvl", lvlWidth, lvlHeight); two.tanks = 20;
	GameLevel three; three.load("resource/levels/three.lvl", lvlWidth, lvlHeight); three.tanks = 20;
	this->levels.push_back(one);
	this->levels.push_back(two);
	this->levels.push_back(three);
	this->level = 2;

	//播放背景音乐
	//SoundEngine->play2D("resource/sound/bgm.mp3", GL_TRUE);

	//初始化GameObjects
	Tank tank(Position((levels[level].width / 2 - 4) * levels[level].unit_width, (levels[level].height - 1) * levels[level].unit_height),
		Size(levels[level].unit_width - 5, levels[level].unit_height - 5));
	tank.isEnemy = false;
	tanks.insert(tanks.begin(), tank);
	player = &tanks[0];
}

double currentTime = glfwGetTime();
double lastAttackTime = currentTime;
double lastAnimeTime = currentTime;
double lastEnemyTime = currentTime;
double lastbeTime = currentTime;

void Game::resetPlayer()
{
	player->pos = Position((levels[level].width / 2 - 4) * levels[level].unit_width, (levels[level].height - 1) * levels[level].unit_height);
	player->blood = 1000;
}

void Game::resetLevel()
{

}

int Game::update(float dt)
{
	player = &tanks[0];
	updateView();
	currentTime = glfwGetTime();
	//我方坦克移动
	bool moveable = true;
	for (Block& block : levels[level].blocks)
	{
		if (!block.tankable && block.blood > 0 && CheckCollision(*player, block, player->velocity * dt)) //与砖块发生碰撞
		{
			Velocity v(0, 0);
			if (player->dir == Direction::UL || player->dir == Direction::UR || player->dir == Direction::DL || player->dir == Direction::DR)
			{
				if (!CheckCollision(*player, block, Velocity(0, player->velocity.y) * dt))
				{
					v.y = player->velocity.y;
				}
				if (!CheckCollision(*player, block, Velocity(player->velocity.x, 0) * dt))
				{
					v.x = player->velocity.x;
				}
			}
			player->velocity = v;
		}
	}

	//检测地图边界
	Position pos = player->pos + player->velocity * dt;
	if (pos.x < 0 || pos.y < 0 || pos.x + player->size.x > lvlWidth || pos.y + player->size.y > lvlHeight)
	{
		player->velocity = Velocity(0, 0);
	}


	static bool moveSound = false;
	if (moveable)
	{
		player->move(dt);
		static ISound* snd;
		if (!moveSound && !player->stop)
		{
			snd = SoundEngine->play2D("resource/sound/Move.wav", true, false, true);
			moveSound = true;
		}
		if (player->stop)
		{
			moveSound = false;

			if (snd)
			{
				snd->stop();
				snd->drop();
				snd = 0;
			}
		}
	}

	for (auto it = tanks.begin(); it != tanks.end(); it++)
	{
		if (it->attacked == 1 && currentTime - lastAttackTime > 0.05)
		{
			it->attacked = 0;
		}
	}

	//生成新敌人
	if (currentTime - lastEnemyTime > 5 && tanks.size() < 6 && levels[level].tanks > 0)
	{
		int base = rand() % levels[level].tankBase.size();
		Tank enemy(levels[level].tankBase[base].pos, Size(levels[level].unit_width - 5, levels[level].unit_height - 5));
		enemy.changeDir(Direction(rand() % 8));
		enemy.isEnemy = true;
		tanks.push_back(enemy);
		lastEnemyTime = currentTime;
		levels[level].tanks--;
	}

	AIController::AI(*this, dt);

	//玩家与道具的碰撞检测 - 获得道具
	for (auto& it : this->bonusItems)
	{
		if (it.obtainable && !it.activated && CheckCollision(*player, it))
		{
			SoundEngine->play2D("resource/sound/obtain.wav");
			it.activated = true;
			if (it.type == "FAST")
			{
				player->speed = 250;
			}
			else if (it.type == "BLOOD")
			{
				player->blood = 1000;
			}
			else if (it.type == "ARMOR")
			{
				player->armor = true;
			}
		}
	}
	this->updateBonus(dt);

	//子弹飞行过程及碰撞检测
	for (auto it = bullets.begin(); it != bullets.end();)
	{
		bool hitTank = false;  //击中坦克
		bool hitBlock = false; //击中地图物体
		for (auto t = tanks.begin(); t != tanks.end(); t++)
		{
			if ((it->isEnemy ^ t->isEnemy) && CheckCollision(*it, *t)) //异或操作，坦克的敌人属性和子弹的敌人属性不一样
			{
				hitTank = true;
				if (!t->armor)
				{
					t->blood -= it->damage;
				}
				t->attacked = 1;
				lastAttackTime = currentTime;
				SoundEngine->play2D("resource/sound/GetHurt.wav", GL_FALSE);
				if (t->blood <= 0)
				{
					SoundEngine->play2D("resource/sound/Explosion.wav", GL_FALSE);
					explosions.push_back(Explosion(t->pos + Size(t->size.x / 2, t->size.y / 2) - Size(100 / 2, 100 / 2), Size(100, 100)));
					if (player->blood <= 0)
					{
						resetPlayer();
					}
					else
					{
						this->spawnBonus(*t);   //随机生成道具  加入到bonusItem列表中
						t = tanks.erase(t);
					}
				}
				break;
			}
		}
		for (auto& block : levels[level].blocks)
		{
			if (!block.bulletable && block.blood > 0 && CheckCollision(*it, block))
			{
				hitBlock = true;
				SoundEngine->play2D("resource/sound/GetHurt.wav", GL_FALSE);
				if (block.breakable)
				{
					block.blood -= it->damage;
					if (block.blood <= 0)
					{
						if (block.type == BOMBT)
						{
							SoundEngine->play2D("resource/sound/Explosion.wav", GL_FALSE);
							explosions.push_back(Explosion(block.pos + Size(block.size.x / 2, block.size.y / 2) - Size(100 / 2, 100 / 2), Size(100, 100), 500));
						}
					}
				}
				break;
			}
		}
		if (hitTank || hitBlock)
		{
			bulleterase.push_back(BulletErase(it->pos + Size(it->size.x / 2, it->size.y / 2) - Size(50 / 2, 50 / 2), Size(50, 50), it->rotation));
		}
		if (hitTank || hitBlock || it->biu(dt, glm::vec2(lvlWidth, lvlHeight)))
		{
			it = bullets.erase(it);
		}
		else
		{
			++it;
		}
	}


	//更新爆炸过程，应用爆炸伤害
	for (auto& explosion : explosions)
	{
		if (explosion.count == 1 || explosion.damage != 0)
		{
			for (auto& block : levels[level].blocks)
			{
				if (!block.bulletable && block.blood > 0 && CheckCollision(explosion, block))
				{
					if (block.breakable)
					{
						block.blood -= explosion.damage;
						if (block.blood <= 0)
						{
							if (block.type == BOMBT)
							{
								SoundEngine->play2D("resource/sound/Explosion.wav", GL_FALSE);
								explosions.push_back(Explosion(block.pos + Size(block.size.x / 2, block.size.y / 2) - Size(100 / 2, 100 / 2), Size(100, 100), 500));
							}
						}
					}
				}
			}
			//检查 炸药爆炸 和坦克
			for (auto it = this->tanks.begin(); it != this->tanks.end(); ++it)
			{
				if (CheckCollision(explosion, *it))
				{
					if (!it->armor)
					{
						it->blood -= explosion.damage;
					}
					if (it->blood <= 0)
					{
						explosions.push_back(Explosion(it->pos + Size(it->size.x / 2, it->size.y / 2) - Size(100 / 2, 100 / 2), Size(100, 100)));
						if (player->blood <= 0)
						{
							resetPlayer();
						}
						else
						{
							this->spawnBonus(*it);   //随机生成道具  加入到bonusItem列表中
							it = tanks.erase(it);
						}
					}
				}
			}
		}
		if (currentTime - lastAnimeTime > 0.03)
		{
			explosion.count++;
		}
	}
	this->explosions.erase(std::remove_if(this->explosions.begin(), this->explosions.end(),
		[](const Explosion& explosion) { return explosion.count >= 8; }
	), this->explosions.end());

	for (auto& be : bulleterase)
	{
		if (currentTime - lastbeTime > 0.04)
		{
			be.count++;
		}
	}
	this->bulleterase.erase(std::remove_if(this->bulleterase.begin(), this->bulleterase.end(),
		[](const BulletErase& be) { return be.count >= 2; }
	), this->bulleterase.end());

	if (currentTime - lastAnimeTime > 0.03)
	{
		lastAnimeTime = currentTime;
	}
	if (currentTime - lastbeTime > 0.04)
	{
		lastbeTime = currentTime;
	}

	return 0;
}

//更新摄像机镜头视角
void Game::updateView()
{
	Point center = player->pos + player->size * Size(0.5, 0.5);
	if (center.x < viewSize.x / 2)
	{
		camPostion.x = 0;
	}
	else if (center.x > lvlWidth - viewSize.x / 2)
	{
		camPostion.x = lvlWidth - viewSize.x;
	}
	else
	{
		camPostion.x = center.x - viewSize.x / 2;
	}

	if (center.y < viewSize.y / 2)
	{
		camPostion.y = 0;
	}
	else if (center.y > lvlHeight - viewSize.y / 2)
	{
		camPostion.y = lvlHeight - viewSize.y;
	}
	else
	{
		camPostion.y = center.y - viewSize.y / 2;
	}
	glm::mat4 view;
	glm::vec3 cameraPos = glm::vec3(camPostion, 0);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	ResourceManager::getShader("sprite").SetMatrix4("view", view, true);
}

void Game::drawUI() {
	for (int i = 0; i < lives; i++) {
		ui->renderImage(ResourceManager::getTexture("Hull_02_A"), Position(90 + i * 25, 65), Size(15, 15));
	}
	ui->renderImage(ResourceManager::getTexture("TANKTU"), Position(40, 20), Size(80, 80));
	ui->renderImage(ResourceManager::getTexture("KUANG"), Position(90, 40), Size(100, 20));
	ui->renderImage(ResourceManager::getTexture("HP"), Position(92, 44), Size(95 * (float(player->blood) / 1000), 12));
	ui->renderText(to_string(player->blood), Position(100, 45), 0.7, Color(0));
	ui->renderImage(ResourceManager::getTexture("Hull_02_A"), Position(680, 40), Size(40, 40));
	ui->renderText(to_string(levels[level].tanks), Position(730, 50), 1.0);
	float time[2] = { 0,0 };
	for (Bonus& b : bonusItems) {
		if (b.activated) {
			if (b.type == "FAST")
			{
				time[0] = (time[0] > b.validTime) ? time[0] : b.validTime;
			}
			else if (b.type == "ARMOR")
			{

				time[1] = (time[1] > b.validTime) ? time[1] : b.validTime;
			}
		}
	}
	if (time[0])
	{
		ui->renderImage(ResourceManager::getTexture("FAST"), Position(40, 80), Size(40, 40));
		ui->renderText(to_string(int(time[0])), Position(80, 90), 1.0);
		if (time[1])
		{
			ui->renderImage(ResourceManager::getTexture("ARMOR"), Position(40, 120), Size(40, 40));
			ui->renderText(to_string(int(time[1])), Position(80, 130), 1.0);
		}
	}
	else if (time[1])
	{
		ui->renderImage(ResourceManager::getTexture("ARMOR"), Position(40, 80), Size(40, 40));
		ui->renderText(to_string(int(time[1])), Position(80, 90), 1.0);
	}
}

int Game::render()
{
	levels[level].draw(*renderer);
	for (auto& t : tanks)
	{
		t.draw(*renderer);
	}

	for (int i = 0; i < bullets.size(); ++i)
	{
		bullets[i].draw(*renderer);
	}
	for (int i = 0; i < explosions.size(); ++i)
	{
		explosions[i].draw(*renderer);
	}
	for (int i = 0; i < bulleterase.size(); ++i)
	{
		bulleterase[i].draw(*renderer);
	}

	for (auto& it : this->bonusItems)
	{
		if (it.obtainable && !it.outoftime && !it.activated)  //画出 还没过时且未被激活的道具
		{
			it.draw(*renderer);
		}
	}

	levels[level].drawTree(*renderer);
	this->drawUI();
	return 0;
}


double lastProcessTime = currentTime;
void Game::processInput(float dt)
{
	if (keys[GLFW_KEY_W] && keys[GLFW_KEY_A])
	{
		player->changeDir(Direction::UL);
	}
	else if (keys[GLFW_KEY_W] && keys[GLFW_KEY_D])
	{
		player->changeDir(Direction::UR);
	}
	else if (keys[GLFW_KEY_S] && keys[GLFW_KEY_A])
	{
		player->changeDir(Direction::DL);
	}
	else if (keys[GLFW_KEY_S] && keys[GLFW_KEY_D])
	{
		player->changeDir(Direction::DR);
	}
	else if (keys[GLFW_KEY_W])
	{
		player->changeDir(Direction::UP);
	}
	else if (keys[GLFW_KEY_S])
	{
		player->changeDir(Direction::DOWN);
	}
	else if (keys[GLFW_KEY_A])
	{
		player->changeDir(Direction::LEFT);
	}
	else if (keys[GLFW_KEY_D])
	{
		player->changeDir(Direction::RIGHT);
	}
	else
	{
		player->stop = true;
	}
	if (mouseKeys[GLFW_MOUSE_BUTTON_LEFT])
	{
		if (!mouseKeysProcessed[GLFW_MOUSE_BUTTON_LEFT] || currentTime - lastProcessTime > 0.2)
		{
			Point center = player->pos + Size(player->size.x / 2, player->size.y / 2);
			Position pos(center.x + 0.65 * player->size.y * sin(player->rotation), center.y - 0.65 * player->size.y * cos(player->rotation));
			Bullet bullet(pos, player->rotation);
			bullet.isEnemy = false;
			bullets.push_back(bullet);
			SoundEngine->play2D("resource/sound/Fire.wav", GL_FALSE);
			mouseKeysProcessed[GLFW_MOUSE_BUTTON_LEFT] = true;
			lastProcessTime = currentTime;
		}
	}

	player->turnTo(mousePos / Size(width, height) * viewSize + camPostion);
}

bool randomSpawn(unsigned int chance)
{
	unsigned int random = rand() % chance;
	return random == 0;
}

//产生道具
void Game::spawnBonus(GameObject& obj)
{
	if (randomSpawn(3))
		this->bonusItems.push_back(Bonus("FAST", obj.pos, glm::vec2(50, 50)));
	else if (randomSpawn(3))
		this->bonusItems.push_back(Bonus("BLOOD", obj.pos, glm::vec2(50, 50)));
	else if (randomSpawn(3))
		this->bonusItems.push_back(Bonus("ARMOR", obj.pos, glm::vec2(50, 50)));
}

bool isOtherBonusActivate(vector<Bonus>& bonusItem, string type)
{
	for (auto& it : bonusItem)
	{
		if (it.activated && !it.runout && it.type == type)
			return true;
	}
	return false;
}

//道具判断
void Game::updateBonus(float dt)
{
	for (auto& it : this->bonusItems)
	{
		//道具延时显示时间
		if (currentTime - lastAnimeTime > 0.03)
		{
			if (!it.obtainable)
			{
				it.delay++;
				if (it.delay >= 9)
					it.obtainable = true;
			}
		}
		if (it.activated)  //如果被坦克获得
		{
			it.validTime -= dt;  //生效时间
			if (it.validTime <= 0.0f)  //当失效时
			{
				it.runout = true;
				// deactivate effects
				if (it.type == "FAST")
				{
					if (!isOtherBonusActivate(this->bonusItems, "FAST"))
					{
						player->speed = 200;   //恢复原速度
					}
				}
				else if (it.type == "ARMOR")
				{
					if (!isOtherBonusActivate(this->bonusItems, "ARMOR"))
					{
						player->armor = false;
					}
				}
			}
		}
		else  //判断道具是否 过时
		{
			it.exitTime -= dt;
			if (it.exitTime <= 0.0f)
			{
				it.outoftime = true;
			}
		}
	}
	//移除所有已经失效 或者 过时的道具
	/*this->bonusItems.erase(std::remove_if(this->bonusItems.begin(), this->bonusItems.end(),
		[](const Bonus &bonus) {return bonus.outoftime && bonus.runout;}
		), this->bonusItems.end());*/
	for (auto it = this->bonusItems.begin(); it != this->bonusItems.end();)
	{
		if (it->outoftime || it->runout)
		{
			bonusItems.erase(it);
		}
		else
		{
			++it;
		}
	}
}
