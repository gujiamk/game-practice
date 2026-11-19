#pragma once
#include "PhotoDV.h"
#include "Chara.h"

inline constexpr const char* Game_info = "rabish//Game_info.txt";

class Game
{
public:
	friend Game* getGame();
	~Game();

	//运行游戏
	void run();

private:
	Game();
	Game(const Game& Game)=delete;

	Game& operator=(const Game& Game)=delete;
	bool isnewone;

	//玩家
	std::unique_ptr<Chara> player{ nullptr };

	//地图
	std::vector<std::vector<int>> map;

    //摄像机坐标
	std::unique_ptr<Point> camera{ nullptr };

	//图像输出对象
	std::unique_ptr<PhotoDV> picdv{ nullptr };

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