#include "Object.h"

Object::Object()
{
	this->name = new std::string("无名");
	this->Self_Point = new Point(12,10);
}

Object::Object(std::string name,Point point)
{
	this->name = new std::string(name);
	this->Self_Point = new Point(point);
}

Object::Object(const Object& object)
{
	this->name = new std::string(*object.name);
	this->Self_Point = new Point(*object.Self_Point);
}

Object& Object::operator=(const Object& obj)
{
	if(this->name != nullptr) delete this->name;
    this->name = new std::string(*obj.name);

    if(this->Self_Point != nullptr) delete this->Self_Point;
    this->Self_Point = new Point(*obj.Self_Point);

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
	if (name != nullptr)
	{
		delete name;
		name = nullptr;
	}

	if (Self_Point != nullptr)
	{
		delete Self_Point;
		Self_Point = nullptr;
	}

	std::cout<<"Object的析构函数调用"<<std::endl;
}