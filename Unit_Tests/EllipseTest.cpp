#include "pch.h"

#include "../TestPrj_CPP/Point.h"
#include "../TestPrj_CPP/Vector.h"
#include "../TestPrj_CPP/LineSegment.h"
#include "../TestPrj_CPP/Ellipse.h"

using namespace Geometry;

TEST(Test2, CircleTest1)
{
	Ellipse e(0, 0, 1, 1);
	Geometry::Point p(0, 0);
	Geometry::Point nearestPt;
	double distance = e.distanceFromPt(p, nearestPt);
	EXPECT_DOUBLE_EQ(distance, 1);
}

TEST(Test2, CircleTest2)
{
	Ellipse e(0, 0, 1, 1);
	Geometry::Point p(0.5, 0.5);
	Geometry::Point nearestPt;
	double distance = e.distanceFromPt(p, nearestPt);
	EXPECT_NEAR(distance, 0.29289321881, 1e-10);
}

TEST(Test2, EllipseTest1)
{
	Ellipse e(0, 0, 0.5, 0.3);
	Geometry::Point p(0, 0);
	Geometry::Point nearestPt;
	double distance = e.distanceFromPt(p, nearestPt);
	EXPECT_DOUBLE_EQ(distance, 0.3);
}

TEST(Test2, EllipseTest2)
{
	Ellipse e(0, 0, 0.3, 0.5);
	Geometry::Point p(0, 0);
	Geometry::Point nearestPt;
	double distance = e.distanceFromPt(p, nearestPt);
	EXPECT_DOUBLE_EQ(distance, 0.3);
}

TEST(Test2, EllipseTest3)
{
	Ellipse e(0, 0, 0.3, 0.5);
	Geometry::Point p(0.4, 0);
	Geometry::Point nearestPt;
	double distance = e.distanceFromPt(p, nearestPt);
	EXPECT_DOUBLE_EQ(distance, 0.1);
}

TEST(Test2, EllipseTest4)
{
	Ellipse e(0, 0, 0.3, 0.5);
	Geometry::Point p(0, 0.6);
	Geometry::Point nearestPt;
	double distance = e.distanceFromPt(p, nearestPt);
	EXPECT_DOUBLE_EQ(distance, 0.1);
}

TEST(Test2, EllipseTest5)
{
	Ellipse e(0, 0, 0.3, 0.5);
	Geometry::Point p(0.3, 0);
	Geometry::Point nearestPt;
	double distance = e.distanceFromPt(p, nearestPt);
	EXPECT_DOUBLE_EQ(distance, 0.0);
}

TEST(Test2, EllipseTest6)
{
	Ellipse e(0, 0, 0.3, 0.5);
	Geometry::Point p(-0.35, 0);
	Geometry::Point nearestPt;
	double distance = e.distanceFromPt(p, nearestPt);
	EXPECT_DOUBLE_EQ(distance, 0.05);

}

TEST(Test2, EllipseTest7)
{
	Ellipse e(0, 0, 0.3, 0.5);
	Geometry::Point p(0, 0.6);
	Geometry::Point nearestPt;
	double distance = e.distanceFromPt(p, nearestPt);
	EXPECT_DOUBLE_EQ(distance, 0.1);
}

TEST(Test2, EllipseTest8)
{
	Ellipse e(0, 0, 0.3, 0.5);
	Geometry::Point p(0, -0.6);
	Geometry::Point nearestPt;
	double distance = e.distanceFromPt(p, nearestPt);
	EXPECT_DOUBLE_EQ(distance, 0.1);
}

TEST(Test2, EllipseTest9)
{
	Ellipse e(1, 1, 0.3, 0.5);
	Geometry::Point p(2, 1);
	Geometry::Point nearestPt;
	double distance = e.distanceFromPt(p, nearestPt);
	EXPECT_DOUBLE_EQ(distance, 0.7);
}