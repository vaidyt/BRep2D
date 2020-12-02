// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//#include <iostream>
//
//
//#include "Point.h"
//#include "Vector.h"
//#include "LineSegment.h"
//#include "Ellipse.h"
//
//constexpr double eps = std::numeric_limits<double>::epsilon();
//
//using namespace std;
//using namespace Geometry;
//
//
//int main()
//{
//	Ellipse e(0,0, 1, 1);
//	Geometry::Point p(1.1, 1.1);
//	Geometry::Point nearestPt;
//	const auto dist = e.distanceFromPt(p, nearestPt);
//	bool isInside = e.isPointInside(p);
//	string insideOutside = isInside ? "Inside" : "Outside";
//	std::cout << "Ellipse -> " << e.toString() << std::endl;
//	std::cout << "Query Pt -> " << p.toString() << " " << "is " << insideOutside << std::endl;
//	std::cout << "Nearest Pt -> " << nearestPt.toString() << std::endl;
//	std::cout << "Shortest Distance -> " << dist << std::endl;
//}



//#include "Ellipse.h"
//#include "Point.h"
//#include "Vector.h"
//
//namespace Geometry
//{
//	static double getShortestDistance(double a, double b, double p1x, double p1y, double& px, double& py)
//	{
//		Ellipse e(a, b);
//		Geometry::Point p(p1x, p1y);
//		Geometry::Point nearestPt;
//		auto d = e.distanceFromPt(p, nearestPt);
//
//		px = nearestPt.getX();
//		py = nearestPt.getY();
//
//		return d;
//	}
//}