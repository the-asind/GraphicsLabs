#pragma once

class Point {
public:
  Point() : x(0), y(0) {}
  Point(double _x, double _y) : x(_x), y(_y) {}

  double getX() const;
  double getY() const;

private:
  double x;
  double y;
};

double Point::getX() const { return x; }

double Point::getY() const { return y; }
