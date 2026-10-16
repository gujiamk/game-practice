#pragma once
#include <filesystem>
#include "PhotoDV.h"
#include "Chara.h"

inline constexpr const char* Game_info = "rabish//Game_info.txt";
//test
class Game
{
public:
	friend Game* getGame();

	//运行游戏
	void run();

private:
	Game();
	Game(const Game& Game);
	~Game();

	Game& operator=(const Game& Game);
	bool isnewone;

	//玩家
	Chara* player;

	//地图
	std::vector<std::vector<int>> map;

    //摄像机坐标
	Point* camera;

	//创建角色
    void create_chara();

	//登录流程
    void login();

	//新玩家流程
	void welconme();

	//加载地图
	bool loadgame();

	void savegame();
};

extern Game* getGame();