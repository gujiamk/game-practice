#pragma once
#include "Object.h"
#include "PhotoDV.h"

//角色档案储存路径
inline constexpr const char* Chara_info= "rabish//charainfo.txt";

class Chara : public Object
{
public:
	friend std::ofstream& operator<<(std::ofstream& out, const Chara* const chara);

	Chara();
	Chara(std::string name);
    Chara(const std::string& name,const Point& point ,int health, int attack, int defense);
	Chara(const Chara& player);
	Chara& operator=(const Chara& player);
	
	//在对应相机网格视图上绘制角色
	void draw_self(const Point* const camera);
	
	//给入地图和相机坐标指针，在对应相机网格视图上移动角色
	void move(std::vector<std::vector<int>> map,Point* const camera ,BYTE vkcode);


	void func();

protected:

	//生命值
	int* health;

	//攻击力
    int* attack;

    //防御力
    int* defense;

public:
    ~Chara();
};

std::ofstream& operator<<(std::ofstream& out, const Chara* const chara);