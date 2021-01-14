#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING
#include <memory>

#include"gtest/gtest.h"
#include "Logic.h"

class A
{
public:
	int val;
	virtual int foo() { return 0; };
	A() : val(foo()) {};
};

class B : public A
{
public:
	virtual int foo() { return 1; };
};

TEST(ABvirtual, foo)
{
	A a;
	EXPECT_EQ(a.val, 0);
	
	B b;
	EXPECT_EQ(b.val, 0);
}

TEST(Point, std_swap)
{
	Point arr[2] = { {0,0}, {1,1} };
	std::swap(arr[0], arr[1]);

	EXPECT_EQ(arr[0].x, 1);
	EXPECT_EQ(arr[0].y, 1);

	EXPECT_EQ(arr[1].x, 0);
	EXPECT_EQ(arr[1].y, 0);
}

TEST(Integer, std_swap)
{
	int a = 0;
	int b = 1;
	std::swap(a, b);

	EXPECT_EQ(a, 1);
	EXPECT_EQ(b, 0);
}

TEST(vector, erase)
{
	std::vector<int> v = { 0,1,2,3,4,5 };

	auto it = v.begin();
	for (; *it != 4; ++it);
	v.erase(it);

	EXPECT_EQ(v.size(), 5);
}

class C
{
public:
	virtual int foo() { return 1; };
};

class D : public C
{
public:
	virtual int foo() { return 2; };
};

int foo(C & c)
{
	return c.foo();
}

TEST(shared_ptr, virtual)
{	
	D t;
	D &rt = t;
	std::shared_ptr<C*> c = std::make_shared<C*>(&rt);
	std::shared_ptr<D*> d = std::make_shared<D*>(new D());
	EXPECT_EQ((*c)->foo(), 2);
	EXPECT_EQ((*d)->foo(), 2);

	EXPECT_EQ(foo(**c), 2);
	EXPECT_EQ(foo(**d), 2);
}