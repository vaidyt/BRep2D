#include "pch.h"


using namespace Geometry;

TEST(Test1, HorizontalLineSeg) {
	// Horizontal Line Seg to a point
	// Distance between (0.5,0.5) to line segment [0,0]-[1,0]
	Geometry::Point p1(0, 0, 0);
	Geometry::Point p2(1, 0, 0);
	Geometry::Point p(0.5, 0.5, 0);

	Geometry::LineSegment L(p1, p2);

	double dist = L.distanceFromPoint(p);

	EXPECT_DOUBLE_EQ(dist, 0.5);
}
TEST(Test1, VerticalLineSeg) {
	// Vertical Line Seg to a point
	// Distance between (0.5,0.5) to line segment [0,0]-[0,1]
	Geometry::Point p1(0, 0, 0);
	Geometry::Point p2(0, 1, 0);
	Geometry::Point p(0.5, 0.5, 0);

	Geometry::LineSegment L(p1, p2);

	double dist = L.distanceFromPoint(p);

	EXPECT_DOUBLE_EQ(dist, 0.5);
}

TEST(Test1, InclidedLine45) {

	// 45 degree line to a point
	// Distance between (0.5,0.5) to line segment [0,0]-[1,1]
	Geometry::Point p1(0, 0, 0);
	Geometry::Point p2(1, 1, 0);
	Geometry::Point p(0.5, 0.5, 0);

	Geometry::LineSegment L(p1, p2);

	double dist = L.distanceFromPoint(p);

	EXPECT_TRUE(abs(dist) <= 1e-15);
}


TEST(Test1, ArbitraryLine) {
	// Arbitrarily inclined line to a point
	// Distance between (2,3) to line segment [-20,0]-[0,10]
	Geometry::Point p1(-20, 0, 0);
	Geometry::Point p2(0, 10, 0);
	Geometry::Point p(-5, -5, 0);

	LineSegment L(p1, p2);

	double dist = L.distanceFromPoint(p);

	EXPECT_DOUBLE_EQ(dist, 11.180339887498949);
}

TEST(Test1, ArbitraryLine_EndPt) {
	// Arbitrarily inclined line to a point
	// Distance between (2,3) to line segment [-20,0]-[0,10]
	Geometry::Point p1(-20, 0, 0);
	Geometry::Point p2(0, 10, 0);
	Geometry::Point p(p2);

	LineSegment L(p1, p2);

	double dist = L.distanceFromPoint(p);

	EXPECT_DOUBLE_EQ(dist, 0);
}

TEST(Test1, ArbitraryLine_StartPt) {
	// Arbitrarily inclined line to a point
	// Distance between (2,3) to line segment [-20,0]-[0,10]
	Geometry::Point p1(-20, 0, 0);
	Geometry::Point p2(0, 10, 0);
	Geometry::Point p(p1);

	LineSegment L(p1, p2);

	double dist = L.distanceFromPoint(p);

	EXPECT_DOUBLE_EQ(dist, 0);
}

TEST(Test1, PointIn3D_1) {
	// Point in 3D - Ref: https://www.geeksforgeeks.org/shortest-distance-between-a-line-and-a-point-in-a-3-d-plane/
	Geometry::Point p1(5, 2, 1);
	Geometry::Point p2(3, 1, -1);
	Geometry::Point p(0, 2, 3);

	LineSegment L(p1, p2);

	double dist = L.distanceFromPoint(p);

	EXPECT_DOUBLE_EQ(dist, 5);
}

TEST(Test1, PointIn3D_2) {
	// Point in 3D and infinite line - Ref: https://www.geeksforgeeks.org/shortest-distance-between-a-line-and-a-point-in-a-3-d-plane/
	Geometry::Point p1(4, 2, 1);
	Geometry::Point p2(3, 2, 1);
	Geometry::Point p(0, 2, 0);

	Geometry::LineSegment L(p1, p2);

	double dist = L.distanceFromPoint(p, true);

	EXPECT_DOUBLE_EQ(dist, 1);
}

TEST(Test1, LineSegIntersection_1){
	// Horizontal and vertical intersecting lines
	Geometry::Point p1(0, 0);
	Geometry::Point p2(1, 0);
	Geometry::Point p3(0.5, -0.5);
	Geometry::Point p4(0.5, 0.5);

	Geometry::LineSegment L1(p1, p2);
	Geometry::LineSegment L2(p3, p4);

	Geometry::Point interPt;
	bool isIntersecting = L1.isIntersecting(L2,interPt);

	EXPECT_DOUBLE_EQ(interPt.getX(), 0.5);
	EXPECT_DOUBLE_EQ(interPt.getY(), 0);

	EXPECT_TRUE(isIntersecting == true);

}


TEST(Test1, LineSegIntersection_2) {
	// Horizontal and vertical non-intersecting lines
	Geometry::Point p1(0, 0);
	Geometry::Point p2(1, 0);
	Geometry::Point p3(1.5, -1.5);
	Geometry::Point p4(1.5, 1.5);

	Geometry::LineSegment L1(p1, p2);
	Geometry::LineSegment L2(p3, p4);

	Geometry::Point interPt;
	bool isIntersecting = L1.isIntersecting(L2, interPt);

	EXPECT_TRUE(isIntersecting == false);

}

TEST(Test1, LineSegIntersection_3) {
	// Horizontal and vertical non-intersecting lines
	Geometry::Point p1(0, 0);
	Geometry::Point p2(1, 0);
	Geometry::Point p3(-1.5, -1.5);
	Geometry::Point p4(-1.5, 1.5);

	Geometry::LineSegment L1(p1, p2);
	Geometry::LineSegment L2(p3, p4);

	Geometry::Point interPt;
	bool isIntersecting = L1.isIntersecting(L2, interPt);

	EXPECT_TRUE(isIntersecting == false);

}

TEST(Test1, LineSegIntersection_4) {
	// Horizontal and vertical lines intersecting at one of the vertices
	Geometry::Point p1(0, 0);
	Geometry::Point p2(1, 0);
	Geometry::Point p3(0, 0);
	Geometry::Point p4(0, 1);

	Geometry::LineSegment L1(p1, p2);
	Geometry::LineSegment L2(p3, p4);

	Geometry::Point interPt;
	bool isIntersecting = L1.isIntersecting(L2, interPt);

	EXPECT_DOUBLE_EQ(interPt.getX(), 0);
	EXPECT_DOUBLE_EQ(interPt.getY(), 0);

	EXPECT_TRUE(isIntersecting == true);

}

TEST(Test1, LineSegIntersection_5) {
	// Horizontal and vertical lines intersecting at one of the vertices
	Geometry::Point p1(0, 0);
	Geometry::Point p2(1, 0);
	Geometry::Point p3(1, 0);
	Geometry::Point p4(1, 1);

	Geometry::LineSegment L1(p1, p2);
	Geometry::LineSegment L2(p3, p4);

	Geometry::Point interPt;
	bool isIntersecting = L1.isIntersecting(L2, interPt);

	EXPECT_DOUBLE_EQ(interPt.getX(), 1);
	EXPECT_DOUBLE_EQ(interPt.getY(), 0);

	EXPECT_TRUE(isIntersecting == true);

}

TEST(Test1, LineSegIntersection_6) {
	// Two 45 degree lines intersecting at origin
	Geometry::Point p1(-0.5, -0.5);
	Geometry::Point p2(0.5, 0.5);
	Geometry::Point p3(0.5, -0.5);
	Geometry::Point p4(-0.5, 0.5);

	Geometry::LineSegment L1(p1, p2);
	Geometry::LineSegment L2(p3, p4);

	Geometry::Point interPt;
	bool isIntersecting = L1.isIntersecting(L2, interPt);

	EXPECT_DOUBLE_EQ(interPt.getX(), 0);
	EXPECT_DOUBLE_EQ(interPt.getY(), 0);

	EXPECT_TRUE(isIntersecting == true);

}


TEST(Test1, LineSegIntersection_7) {
	// Arbitrarily inclined line segments
	Geometry::Point p1(0, 1);
	Geometry::Point p2(5, 2);
	Geometry::Point p3(1, 0);
	Geometry::Point p4(0, 2);

	Geometry::LineSegment L1(p1, p2);
	Geometry::LineSegment L2(p3, p4);

	Geometry::Point interPt;
	bool isIntersecting = L1.isIntersecting(L2, interPt);

	EXPECT_DOUBLE_EQ(interPt.getX(), 0.45454545454545459);
	EXPECT_DOUBLE_EQ(interPt.getY(), 1.0909090909090908);

	EXPECT_TRUE(isIntersecting == true);

}

//ToDo: Overlapping Line cases

TEST(Test1, LineSegIntersection_8) {
	// Arbitrarily inclined line segments overlapping fully (i.e. identical line segments)
	Geometry::Point p1(0, 1);
	Geometry::Point p2(5, 2);
	Geometry::Point p3(0, 1);
	Geometry::Point p4(5, 2);

	Geometry::LineSegment L1(p1, p2);
	Geometry::LineSegment L2(p3, p4);

	Geometry::Point interPt;
	bool isIntersecting = L1.isIntersecting(L2, interPt);


	EXPECT_TRUE(isIntersecting == true);
	EXPECT_TRUE(interPt.isValid());
}

TEST(Test1, LineSegIntersection_9) {
	// Arbitrarily inclined line segments overlapping partially
	Geometry::Point p1(0, 0);
	Geometry::Point p2(1, 1);
	Geometry::Point p3(0.5, 0.5);
	Geometry::Point p4(2, 2);

	Geometry::LineSegment L1(p1, p2);
	Geometry::LineSegment L2(p3, p4);

	Geometry::Point interPt;
	bool isIntersecting = L1.isIntersecting(L2, interPt);


	EXPECT_TRUE(isIntersecting == true);
	EXPECT_TRUE(interPt.isValid());
}



// QuadCircle intersection tests
TEST(Test1, QuadCircleIntersection_1) 
{
	// First quadrant and line through origin intersection
	Geometry::Point p1(1, 0);
	Geometry::Point p2(0, 1);
	Geometry::Arc q(p1, p2);

	Geometry::Point p3(0, 0);
	Geometry::Point p4(2, 2);
	Geometry::LineSegment L(p3, p4);
	Geometry::Point interPt1, interPt2;

	bool isIntersecting = L.isIntersecting(q, interPt1, interPt2);

	Geometry::Point interPt;

	if (interPt1.isValid())
	{
		interPt = interPt1;
	}

	if (interPt2.isValid())
	{
		interPt = interPt2;
	}

	EXPECT_DOUBLE_EQ(interPt.getX(), 1/sqrt(2));
	EXPECT_DOUBLE_EQ(interPt.getY(), 1 / sqrt(2));


	EXPECT_TRUE(isIntersecting == true);


}

TEST(Test1, QuadCircleIntersection_2)
{
	// Second quadrant and line through origin intersection
	Geometry::Point p1(0,1);
	Geometry::Point p2(-1, 0);
	Geometry::Arc q(p1, p2);

	Geometry::Point p3(0, 0);
	Geometry::Point p4(-2, 2);
	Geometry::LineSegment L(p3, p4);
	Geometry::Point interPt1, interPt2;

	bool isIntersecting = L.isIntersecting(q, interPt1, interPt2);

	Geometry::Point interPt;

	if (interPt1.isValid())
	{
		interPt = interPt1;
	}

	if (interPt2.isValid())
	{
		interPt = interPt2;
	}

	EXPECT_DOUBLE_EQ(interPt.getX(), -1 / sqrt(2));
	EXPECT_DOUBLE_EQ(interPt.getY(), 1 / sqrt(2));


	EXPECT_TRUE(isIntersecting == true);


}


TEST(Test1, QuadCircleIntersection_3)
{
	// Third quadrant and line through origin intersection
	Geometry::Point p1(-1,0);
	Geometry::Point p2(0, -1);
	Geometry::Arc q(p1, p2);

	Geometry::Point p3(0, 0);
	Geometry::Point p4(-2, -2);
	Geometry::LineSegment L(p3, p4);
	Geometry::Point interPt1, interPt2;

	bool isIntersecting = L.isIntersecting(q, interPt1, interPt2);

	Geometry::Point interPt;

	if (interPt1.isValid())
	{
		interPt = interPt1;
	}

	if (interPt2.isValid())
	{
		interPt = interPt2;
	}

	EXPECT_DOUBLE_EQ(interPt.getX(), -1 / sqrt(2));
	EXPECT_DOUBLE_EQ(interPt.getY(), -1 / sqrt(2));


	EXPECT_TRUE(isIntersecting == true);
}

TEST(Test1, QuadCircleIntersection_4)
{
	// Fourth quadrant and line through origin intersection
	Geometry::Point p1(0, -1);
	Geometry::Point p2(1, 0);
	Geometry::Arc q(p1, p2);

	Geometry::Point p3(0, 0);
	Geometry::Point p4(2, -2);
	Geometry::LineSegment L(p3, p4);
	Geometry::Point interPt1, interPt2;

	bool isIntersecting = L.isIntersecting(q, interPt1, interPt2);

	Geometry::Point interPt;

	if (interPt1.isValid())
	{
		interPt = interPt1;
	}

	if (interPt2.isValid())
	{
		interPt = interPt2;
	}

	EXPECT_DOUBLE_EQ(interPt.getX(), 1 / sqrt(2));
	EXPECT_DOUBLE_EQ(interPt.getY(), -1 / sqrt(2));


	EXPECT_TRUE(isIntersecting == true);


}

TEST(Test1, QuadCircleIntersection_5)
{
	// First quadrant with non-zero origin and horizontal line segment cutting through
	Geometry::Point p1(4, 1);
	Geometry::Point p2(1, 4);
	Geometry::Arc q(p1, p2);

	Geometry::Point p3(0, 2);
	Geometry::Point p4(5, 2);
	Geometry::LineSegment L(p3, p4);
	Geometry::Point interPt1, interPt2;

	bool isIntersecting = L.isIntersecting(q, interPt1, interPt2);

	Geometry::Point interPt;

	if (interPt1.isValid())
	{
		interPt = interPt1;
	}

	if (interPt2.isValid())
	{
		interPt = interPt2;
	}

	EXPECT_DOUBLE_EQ(interPt.getX(), 1+2*sqrt(2));
	EXPECT_DOUBLE_EQ(interPt.getY(), 2);


	EXPECT_TRUE(isIntersecting == true);


}

TEST(Test1, QuadCircleIntersection_6)
{
	// First quadrant with non-zero origin and vertical line segment cutting through
	Geometry::Point p1(4, 1);
	Geometry::Point p2(1, 4);
	Geometry::Arc q(p1, p2);

	Geometry::Point p3(3, 0);
	Geometry::Point p4(3, 5);
	Geometry::LineSegment L(p3, p4);
	Geometry::Point interPt1, interPt2;

	bool isIntersecting = L.isIntersecting(q, interPt1, interPt2);

	Geometry::Point interPt;

	if (interPt1.isValid())
	{
		interPt = interPt1;
	}

	if (interPt2.isValid())
	{
		interPt = interPt2;
	}

	EXPECT_DOUBLE_EQ(interPt.getX(), 3);
	EXPECT_DOUBLE_EQ(interPt.getY(), 1 + sqrt(5));


	EXPECT_TRUE(isIntersecting == true);


}


TEST(Test1, QuadCircleIntersection_7)
{
	// First quadrant with non-zero origin and Horizontal line just touching one of the vertices
	Geometry::Point p1(4, 1);
	Geometry::Point p2(1, 4);
	Geometry::Arc q(p1, p2);

	Geometry::Point p3(0, 4);
	Geometry::Point p4(5, 4);
	Geometry::LineSegment L(p3, p4);
	Geometry::Point interPt1, interPt2;

	bool isIntersecting = L.isIntersecting(q, interPt1, interPt2);

	Geometry::Point interPt;

	if (interPt1.isValid())
	{
		interPt = interPt1;
	}

	if (interPt2.isValid())
	{
		interPt = interPt2;
	}

	EXPECT_DOUBLE_EQ(interPt.getX(), 1);
	EXPECT_DOUBLE_EQ(interPt.getY(), 4);


	EXPECT_TRUE(isIntersecting == true);


}

TEST(Test1, QuadCircleIntersection_8)
{
	// First quadrant with non-zero origin and Vertical line just touching one of the vertices
	Geometry::Point p1(4, 1);
	Geometry::Point p2(1, 4);
	Geometry::Arc q(p1, p2);

	Geometry::Point p3(4, 0);
	Geometry::Point p4(4, 5);
	Geometry::LineSegment L(p3, p4);
	Geometry::Point interPt1, interPt2;

	bool isIntersecting = L.isIntersecting(q, interPt1, interPt2);

	Geometry::Point interPt;

	if (interPt1.isValid())
	{
		interPt = interPt1;
	}

	if (interPt2.isValid())
	{
		interPt = interPt2;
	}

	EXPECT_DOUBLE_EQ(interPt.getX(), 4);
	EXPECT_DOUBLE_EQ(interPt.getY(), 1);


	EXPECT_TRUE(isIntersecting == true);


}

TEST(Test1, QuadCircleIntersection_9)
{
	// First quadrant with non-zero origin and line segment not touching
	Geometry::Point p1(4, 1);
	Geometry::Point p2(1, 4);
	Geometry::Arc q(p1, p2);

	Geometry::Point p3(2.2071, 0);
	Geometry::Point p4(2.2071, 2.2071);
	Geometry::LineSegment L(p3, p4);
	Geometry::Point interPt1, interPt2;

	bool isIntersecting = L.isIntersecting(q, interPt1, interPt2);

	EXPECT_TRUE(isIntersecting == false);
}

TEST(Test1, QuadCircleIntersection_10)
{
	// First quadrant with non-zero origin and line passing through both the vertices of the quadrant
	Geometry::Point p1(4, 1);
	Geometry::Point p2(1, 4);
	Geometry::Arc q(p1, p2);

	Geometry::Point p3(1, 4);
	Geometry::Point p4(4, 1);
	Geometry::LineSegment L(p3, p4);
	Geometry::Point interPt1, interPt2;

	bool isIntersecting = L.isIntersecting(q, interPt1, interPt2);

	Geometry::Point interPt;

	EXPECT_TRUE(interPt1.isValid() == true);
	EXPECT_TRUE(interPt2.isValid() == true);

	EXPECT_DOUBLE_EQ(interPt1.getX(), 4);
	EXPECT_DOUBLE_EQ(interPt1.getY(), 1);

	EXPECT_DOUBLE_EQ(interPt2.getX(), 1);
	EXPECT_DOUBLE_EQ(interPt2.getY(), 4);


	EXPECT_TRUE(isIntersecting == true);


}

TEST(Test1, QuadCircleIntersection_11)
{
	// First quadrant with non-zero origin and line passing through both the vertices of the quadrant
	Geometry::Point p1(4, 1);
	Geometry::Point p2(1, 4);
	Geometry::Arc q(p1, p2);

	Geometry::Point p3(2, 1+2*sqrt(2));
	Geometry::Point p4(3, 1+sqrt(5));
	Geometry::LineSegment L(p3, p4);
	Geometry::Point interPt1, interPt2;

	bool isIntersecting = L.isIntersecting(q, interPt1, interPt2);

	Geometry::Point interPt;

	EXPECT_TRUE(interPt1.isValid() == true);
	EXPECT_TRUE(interPt2.isValid() == true);
	
	auto tol = 1e-14;

	ASSERT_NEAR(interPt1.getX(), 3, tol);
	ASSERT_NEAR(interPt1.getY(), 1.0 + sqrt(5), tol);

	ASSERT_NEAR(interPt2.getX(), 2, tol);
	ASSERT_NEAR(interPt2.getY(), 1.0 + 2 * sqrt(2), tol);




	EXPECT_TRUE(isIntersecting == true);
}

TEST(Test1, QuadCircleIntersection_12)
{
	// First quadrant with non-zero origin and line segement very close to the boundary but not touching
	Geometry::Point p1(4, 1);
	Geometry::Point p2(1, 4);
	Geometry::Arc q(p1, p2);

	double eps = 0.001;

	Geometry::Point p3(0, 0);
	Geometry::Point p4(3/sqrt(2) - eps, 3 / sqrt(2) - eps);
	Geometry::LineSegment L(p3, p4);
	Geometry::Point interPt1, interPt2;

	bool isIntersecting = L.isIntersecting(q, interPt1, interPt2);

	Geometry::Point interPt;

	EXPECT_TRUE(isIntersecting == false);
	EXPECT_TRUE(interPt1.isValid() == false);
	EXPECT_TRUE(interPt2.isValid() == false);
}

TEST(Test1, QuadCircleIntersection_14)
{
	// First quadrant with non-zero origin and line segement tangent somewhere in between
	Geometry::Point p1(4, 1);
	Geometry::Point p2(1, 4);
	Geometry::Arc q(p1, p2);

	double eps = 0.001;

	Geometry::Point p3(4, 1);
	Geometry::Point p4(1, 8.242640687119284);
	Geometry::LineSegment L(p3, p4);
	Geometry::Point interPt1, interPt2;

	bool isIntersecting = L.isIntersecting(q, interPt1, interPt2);

	Geometry::Point interPt;

	EXPECT_TRUE(isIntersecting == true);
	EXPECT_TRUE(interPt1.isValid() == true || interPt2.isValid() == true);

	if (interPt1.isValid())
	{
		interPt = interPt1;
	}
	else
	{
		interPt = interPt2;
	}

	EXPECT_DOUBLE_EQ(interPt1.getX(), 1+ 3/sqrt(2));
	EXPECT_DOUBLE_EQ(interPt1.getY(), 1 + 3/sqrt(2));
	
}