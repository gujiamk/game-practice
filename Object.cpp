#include "Object.h"

Object::Object()
{
	this->name = std::make_unique<std::string>("无名");
	this->Self_Point = std::make_unique<Point>(12, 10);
}

Object::Object(std::string name,Point point)
{
	this->name = std::make_unique<std::string>(name);
	this->Self_Point = std::make_unique<Point>(point);
}

Object::Object(const Object& object)
{
	this->name = std::make_unique<std::string>(*object.name);
	this->Self_Point = std::make_unique<Point>(*object.Self_Point);
}


Object& Object::operator=(const Object& obj)
{
	this->name.reset(new std::string(*obj.name));
    this->Self_Point.reset(new Point(*obj.Self_Point));

    return *this;
}

bool Object::ishere(Point point)
{
	int dx = point.first - this->Self_Point->first;
	int dy = point.second - this->Self_Point->second;

	if (dx * dx < step * step && dy * dy < step * step)
	{
        return true;
	}
	else return false;
}

Object::~Object()
{
	
}