#pragma once
#include <iostream>
#include <vector>

constexpr static int WIDTH = 1001;
constexpr static int HEIGHT = 801;
constexpr static int step = 40;

const static int half_step = step / 2;



typedef std::pair<int, int> Point;

//坐标修正法案
class FixPoint
{
public:

    FixPoint();

    //给入窗口的像素坐标，返回修正后的坐标既符合网格地图的左上角像素坐标
    Point operator()(const Point& point);
    //给入地图坐标，和相机坐标，返回修正后的坐标既符合网格视图的左上角像素坐标
    Point operator()(int x, int y,const Point& camera);
    Point operator()(int x, int y, const Point* const camera);
    Point operator()(const Point* const point, const Point* const camera);

    //给入窗口网格坐标，返回修正后的坐标既符合网格的左上角坐标
    Point operator()(int x, int y);

    ~FixPoint();

private:
    Point getFixpoint(const Point& point);

};

