#ifdef LAB_TEST
#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING
#include "gtest/gtest.h"

#include "Logic.h"

TEST(Rectangle, isCollision_Point)
{
	Rectangle rect({ 0,0 }, { 1,1 });
	Point p1(1, 0);
	Point p2(2, 2);
	ASSERT_EQ(true, rect.isCollision(p1));
	ASSERT_EQ(false, rect.isCollision(p2));
}

TEST(Rectangle, isCollision_Rectangle_1)
{
	Rectangle rect1({ 0,0 }, { 1,1 });
	Rectangle rect2({ 0,0 }, { 0,0 });

	EXPECT_EQ(rect1.isCollision(rect2), true);
	EXPECT_EQ(rect2.isCollision(rect1), true);
}

TEST(Rectangle, isCollision_Rectangle_2)
{
	Rectangle rect1({ 0,0 }, { 1,1 });
	Rectangle rect2({ 0,0 }, { 2,2 });

	EXPECT_EQ(rect1.isCollision(rect2), true);
	EXPECT_EQ(rect2.isCollision(rect1), true);
}

TEST(Rectangle, isCollision_Rectangle_3)
{
	Rectangle rect1({0, 0}, {1, 1});
	Rectangle rect2({-1, -1}, {1, 0});

	EXPECT_EQ(rect1.isCollision(rect2), true);
	EXPECT_EQ(rect2.isCollision(rect1), true);
}

TEST(Rectangle, getWidth)
{
	Rectangle rect({ 0,0 }, { 3,1 });

	ASSERT_EQ(rect.getWidth(), 4);
}

TEST(Rectangle, getHeigth)
{
	Rectangle rect({ 0,0 }, { 3,1 });

	ASSERT_EQ(rect.getHeigth(), 2);
}

TEST(Rectangle, bind)
{
	Rectangle rect(4, 2);
	rect.bind({ 10,10 });

	EXPECT_EQ(rect.isCollision(Point(10, 10)), true);
	EXPECT_EQ(rect.isCollision(Point(13, 11)), true);
	EXPECT_EQ(rect.isCollision(Point(10, 11)), true);
	EXPECT_EQ(rect.isCollision(Point(13, 10)), true);
	
	EXPECT_EQ(rect.isCollision(Point(9, 10)), false);
	EXPECT_EQ(rect.isCollision(Point(13, 12)), false);
	EXPECT_EQ(rect.isCollision(Point(9, 11)), false);
	EXPECT_EQ(rect.isCollision(Point(14, 10)), false);
}

TEST(Rectangle, transport)
{
	Rectangle rect(3, 2);
	
	EXPECT_EQ(rect.isCollision(Point(0, 0)), true);
	EXPECT_EQ(rect.isCollision(Point(2, 1)), true);
	
	rect.transport();

	EXPECT_EQ(rect.isCollision(Point(0, 0)), true);
	EXPECT_EQ(rect.isCollision(Point(2, 1)), false);
	EXPECT_EQ(rect.isCollision(Point(1, 2)), true);
}
#endif