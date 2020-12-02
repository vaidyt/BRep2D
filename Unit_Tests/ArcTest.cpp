#include "pch.h"


TEST(Test2, QuadCircleIntersection_1)
{
	// First quadrant and second quadrant intersection
	Geometry::Point p1(1, 0);
	Geometry::Point p2(0, 1);
	Geometry::Arc q1(p1, p2);

	Geometry::Point p3(1, 1);
	Geometry::Point p4(0, 0);
	Geometry::Arc q2(p3, p4);
	Geometry::Point interPt1, interPt2;

	bool isIntersecting = q1.isIntersecting(q2, interPt1, interPt2);

	Geometry::Point interPt;

	EXPECT_TRUE(isIntersecting == true);
	EXPECT_TRUE(interPt1.isValid() == true || interPt2.isValid() == true);

	if (interPt1.isValid())
		interPt = interPt1;
	else
		interPt = interPt2;

	EXPECT_DOUBLE_EQ(interPt.getX(), 0.5);
	EXPECT_DOUBLE_EQ(interPt.getY(), 0.866025403784439);

}

TEST(Test2, QuadCircleIntersection_2)
{
	// First quadrant and fourth quadrant intersection
	Geometry::Point p1(1, 0);
	Geometry::Point p2(0, 1);
	Geometry::Arc q1(p1, p2);

	Geometry::Point p3(0, 0);
	Geometry::Point p4(1, 1);
	Geometry::Arc q2(p3, p4);
	Geometry::Point interPt1, interPt2;

	bool isIntersecting = q1.isIntersecting(q2, interPt1, interPt2);

	Geometry::Point interPt;

	EXPECT_TRUE(isIntersecting == true);
	EXPECT_TRUE(interPt1.isValid() == true || interPt2.isValid() == true);

	if (interPt1.isValid())
		interPt = interPt1;
	else
		interPt = interPt2;

	EXPECT_DOUBLE_EQ(interPt.getX(), 0.866025403784439);
	EXPECT_DOUBLE_EQ(interPt.getY(), 0.5);

}

TEST(Test2, QuadCircleIntersection_3)
{
	// First quadrant and second quadrant touching each other
	Geometry::Point p1(1, 0);
	Geometry::Point p2(0, 1);
	Geometry::Arc q1(p1, p2);

	Geometry::Point p3(0, 1);
	Geometry::Point p4(-1, 0);
	Geometry::Arc q2(p3, p4);
	Geometry::Point interPt1, interPt2;

	bool isIntersecting = q1.isIntersecting(q2, interPt1, interPt2);

	Geometry::Point interPt;

	EXPECT_TRUE(isIntersecting == true);
	EXPECT_TRUE(interPt1.isValid() == true || interPt2.isValid() == true);

	if (interPt1.isValid())
		interPt = interPt1;
	else
		interPt = interPt2;

	EXPECT_DOUBLE_EQ(interPt.getX(), 0);
	EXPECT_DOUBLE_EQ(interPt.getY(), 1);

}


TEST(Test2, QuadCircleIntersection_4)
{
	// First quadrant and second quadrant at an offset in the y-direction but not touching
	Geometry::Point p1(1, 0);
	Geometry::Point p2(0, 1);
	Geometry::Arc q1(p1, p2);

	Geometry::Point p3(0, 0.8);
	Geometry::Point p4(-1, -0.2);
	Geometry::Arc q2(p3, p4);
	Geometry::Point interPt1, interPt2;

	bool isIntersecting = q1.isIntersecting(q2, interPt1, interPt2);

	Geometry::Point interPt;

	EXPECT_TRUE(isIntersecting == false);
	EXPECT_TRUE(interPt1.isValid() == false && interPt2.isValid() == false);
}

TEST(Test2, QuadCircleIntersection_5)
{
	// First quadrant and third quadrant not touching
	Geometry::Point p1(1, 0);
	Geometry::Point p2(0, 1);
	Geometry::Arc q1(p1, p2);

	Geometry::Point p3(-1, 0);
	Geometry::Point p4(0, 1);
	Geometry::Arc q2(p3, p4);
	Geometry::Point interPt1, interPt2;

	bool isIntersecting = q1.isIntersecting(q2, interPt1, interPt2);

	Geometry::Point interPt;

	EXPECT_TRUE(isIntersecting == false);
	EXPECT_TRUE(interPt1.isValid() == false && interPt2.isValid() == false);
}

TEST(Test2, QuadCircleIntersection_6)
{
	// First quadrant and fourth quadrant just touching
	Geometry::Point p1(1, 0);
	Geometry::Point p2(0, 1);
	Geometry::Arc q1(p1, p2);

	Geometry::Point p3(0, -1);
	Geometry::Point p4(1, 0);
	Geometry::Arc q2(p3, p4);
	Geometry::Point interPt1, interPt2;

	bool isIntersecting = q1.isIntersecting(q2, interPt1, interPt2);

	Geometry::Point interPt;

	EXPECT_TRUE(isIntersecting == true);
	EXPECT_TRUE(interPt1.isValid() == true || interPt2.isValid() == true);

	if (interPt1.isValid() == true)
	{
		interPt = interPt1;
	}
	else
	{
		interPt = interPt2;
	}

	EXPECT_DOUBLE_EQ(interPt.getX(), 1);
	EXPECT_DOUBLE_EQ(interPt.getY(), 0);

}

TEST(Test2, QuadCircleIntersection_7)
{
	// First quadrant and first quadrant within each other - no intersection
	Geometry::Point p1(1, 0);
	Geometry::Point p2(0, 1);
	Geometry::Arc q1(p1, p2);

	Geometry::Point p3(0.5, 0);
	Geometry::Point p4(0, 0.5);
	Geometry::Arc q2(p3, p4);
	Geometry::Point interPt1, interPt2;

	bool isIntersecting = q1.isIntersecting(q2, interPt1, interPt2);

	Geometry::Point interPt;

	EXPECT_TRUE(isIntersecting == false);
	EXPECT_TRUE(interPt1.isValid() == false && interPt2.isValid() == false);
}


TEST(Test2, QuadCircleIntersection_8)
{
	// First quadrant and first quadrant within each other - no intersection
	Geometry::Point p1(1, 0);
	Geometry::Point p2(0, 1);
	Geometry::Arc q1(p1, p2);

	Geometry::Point p3(2, 0);
	Geometry::Point p4(1, 1);
	Geometry::Arc q2(p3, p4);
	Geometry::Point interPt1, interPt2;

	bool isIntersecting = q1.isIntersecting(q2, interPt1, interPt2);

	Geometry::Point interPt;

	EXPECT_TRUE(isIntersecting == false);
	EXPECT_TRUE(interPt1.isValid() == false && interPt2.isValid() == false);
}

TEST(Test2, QuadCircleIntersection_9)
{
	// First quadrant overlapping
	Geometry::Point p1(1, 0);
	Geometry::Point p2(0, 1);
	Geometry::Arc q1(p1, p2);

	Geometry::Point p3(1, 0);
	Geometry::Point p4(0, 1);
	Geometry::Arc q2(p3, p4);
	Geometry::Point interPt1, interPt2;

	bool isIntersecting = q1.isIntersecting(q2, interPt1, interPt2);

	Geometry::Point interPt;

	EXPECT_TRUE(isIntersecting == true);
	EXPECT_TRUE(interPt1.isValid() == true && interPt2.isValid() == true);
}



