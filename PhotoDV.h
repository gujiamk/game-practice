#pragma once
#include <graphics.h>
#include <string>
#include <map>
#include <fstream>
#include "Tool.h"

#define GRASS 1001
#define ROAD 1002
#define HUOSE 1003
#define TREE 1004
#define SS 1005

inline constexpr const char* mansRoad = "PictureRoad//mans.txt";
inline constexpr const char* maproad = "rabish//map.txt";

//地图坐标x轴最大值
const static int stepx = WIDTH * 2 / step;

//地图坐标y轴最大值
const static int stepy = HEIGHT * 2 / step;

//给出素材名，返回素材编号
int view(std::string name);

//在指定左上角打印文字,默认白色，背景模式为不透明！
void print_word(const std::string& text,Point leftpoint,int size=40,bool isfix=true);
void print_word(const std::string& text,int x,int y,int size=40,bool isfix=true);

extern Point camera;

//绘图工具
class PhotoDV
{
public:

	friend PhotoDV* getPhtoDv();

	//提供素材名字，地图坐标和相机坐标的指针，在视图网格坐标左上角的像素坐标处绘制素材
	void operator()(const std::string& name,const Point* const camera,int x,int y);
	//提供素材名字，地图坐标，在视图网格坐标左上角的像素坐标处绘制素材
	void operator()(const std::string& name,int x,int y);

	//地图编辑模式
	void Edit_map();

	//提供素材名字，地图坐标和相机坐标的指针，在视图网格坐标左上角的像素坐标处绘制素材
	void draw_on_map(std::string name,const Point* point,const Point* camera);

	~PhotoDV();
private:
	
	PhotoDV();
	std::map<std::string, IMAGE*> picres;

	//编辑模式专用
	void loadmap(std::vector<std::vector<int>>& map);
	void savemap(std::vector<std::vector<int>>& map);

};

//一个phtoDV对象的指针
extern PhotoDV* picdv;

extern PhotoDV* getPhtoDv();


