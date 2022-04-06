#pragma once
class Point
{
public:
	Point() { x = -1; y = -1; }
	Point(int _x, int _y) { x = _x; y = _y; }
	int GetX() { return x; }
	int GetY() { return y; }
	void SetX(int _x) { x = _x; }
	void SetY(int _y) { y = _y; }

	bool operator==(Point p) 
	{
		return (x == p.GetX() && y == p.GetY());
	}
private:
	int x, y;//The coordinates of the point
};