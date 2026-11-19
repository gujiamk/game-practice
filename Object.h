#pragma once
#include <memory>
#include "PhotoDV.h"

class Object
{ 
public:

    Object();
    Object(std::string name, Point point);
    Object(const Object& object);
    virtual ~Object();

    Object& operator=(const Object& obj);

    std::unique_ptr<std::string> name;
    std::unique_ptr<Point> Self_Point;

    //自身提供绘制方法
    virtual void draw_self(const Point* const camera,PhotoDV* picdv) = 0;
    //交互功能
    virtual void func() = 0;
    //判断是否与自身重叠
    virtual bool ishere(Point point);
    
};
