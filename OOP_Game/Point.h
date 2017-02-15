#pragma once

class Point
{
public:
	void setX(int );
	void setY(int );
	int getX() const;
	int getY() const;
	bool operator==(const Point&) const; //kind of unnecessary
private:
	int x;
	int y;
};