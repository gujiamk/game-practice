#pragma once
#include "Object.h"

//该注释仅为测试
//角色档案储存路径
inline constexpr const char* Chara_info= "rabish//charainfo.txt";

class Chara : public Object
{
public:
	friend std::ofstream& operator<<(std::ofstream& out, const Chara* const chara);

	Chara();
    Chara(const std::string& name,const Point& point ,int health, int attack, int defense);
	Chara(Chara&& player) noexcept;
	Chara(const Chara& player)=delete;
	Chara& operator=(const Chara& player)=delete;

	//自身提供绘制方法
	void draw_self(const Point* const camera, PhotoDV* picdv);

	//给入地图和相机坐标指针，在对应相机网格视图上移动角色
	void move(const std::vector<std::vector<int>>& map,Point* const camera ,BYTE vkcode);


	void func();

protected:

	//生命值
	std::unique_ptr<int> health;
	//攻击力
	std::unique_ptr<int> attack;
    //防御力
    std::unique_ptr<int> defense;

public:
    ~Chara();
};

std::ofstream& operator<<(std::ofstream& out, const Chara* const chara);
