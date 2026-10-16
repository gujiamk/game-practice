#include "Tool.h"

FixPoint::FixPoint()
{

}

Point FixPoint::getFixpoint(const Point& point)
{
	int x = 0 + step * (point.first / step);
	int y = 0 + step * (point.second / step);

	return Point(x, y);
}

Point FixPoint::operator()(const Point& point)
{
	return this->getFixpoint(point);
}

Point FixPoint::operator()(const int x,const int y, const Point& camera)
{
	int fx = (x-camera.first) * step;
    int fy = (y-camera.second) * step;

	Point point(fx, fy);
    return FixPoint()(point);
}

Point FixPoint::operator()(int x, int y, const Point* const camera)
{
	int fx = (x - camera->first) * step;
	int fy = (y - camera->second) * step;

	Point point(fx, fy);
	return FixPoint()(point);
}

Point FixPoint::operator()(const Point* const point, const Point* const camera)
{
	int fx = (point->first - camera->first) * step;
	int fy = (point->second - camera->second) * step;

	Point p(fx, fy);
	return p;
}

Point FixPoint::operator()(int x, int y)
{
	int fx = x * step;
    int fy = y * step;

	Point point(fx, fy);
	return point;
}

FixPoint::~FixPoint()
{

}