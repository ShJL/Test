#include <iostream>
#include <string>
#include <gtest/gtest.h>
#define NDEBUG
#include "stack.h"

using namespace stk;


TEST (StackMethodTest, CheckConstructor) {
	const size_t n = 45;
	stack_t<std::string> test_obj1(n);
	stack_t<>            test_obj2;

	ASSERT_EQ(test_obj1.capacity(), n);
	ASSERT_EQ(test_obj2.capacity(), 0u);
}

TEST (StackMethodTest, CheckCopy) {
	stack_t<float> test_obj1(1);

	const size_t n = 40;
	for (size_t i = 0; i < n; ++i) {
		test_obj1.push(i);
	}

	stack_t<float> test_obj2(test_obj1);

	ASSERT_EQ(test_obj2.size(), n);
	ASSERT_EQ(test_obj2.capacity(), n);
}

TEST (StackMethodTest, CheckAssignment) {
	stack_t<float> test_obj1(1);
	stack_t<float> test_obj2(5);

	const size_t n = 40;
	for (size_t i = 0; i < n; ++i) {
		test_obj1.push(i);
	}

	test_obj2 = test_obj1;

	ASSERT_EQ(test_obj2.size(), n);
	ASSERT_EQ(test_obj2.capacity(), n);
}

TEST(StackMethodTest, CheckEmpty) {
	stack_t<>      test_obj1;
	stack_t<int>   test_obj2(5);
	stack_t<float> test_obj3(1);

	ASSERT_TRUE(test_obj1.empty());
	ASSERT_TRUE(test_obj2.empty());
	ASSERT_TRUE(test_obj3.empty());

	test_obj3.push(3.2);
	ASSERT_FALSE(test_obj3.empty());

	const int n = 5;
	for (int i = 0; i < n; ++i) {
		test_obj1.push(i);
	}
	for (int i = 0; i < n; ++i) {
		test_obj1.pop();
	}
	ASSERT_TRUE(test_obj1.empty());
}

TEST(StackMethodTest, CheckTop) {
	stack_t<>     test_obj1(3);
	stack_t<int>  test_obj2;
	stack_t<char> test_obj3;

	ASSERT_ANY_THROW(test_obj2.top());
	ASSERT_ANY_THROW(test_obj3.top());

	test_obj3.push('r');
	ASSERT_EQ(test_obj3.top(), 'r');

	const int n = 6;
	for (int i = 0; i <= n; ++i) {
		test_obj1.push(-i);
	}
	ASSERT_EQ(test_obj1.top(), -n);
}

TEST(StackMethodTest, CheckSize) {
	stack_t<>     test_obj1(2);
	stack_t<int>  test_obj2(10);
	stack_t<char> test_obj3;

	ASSERT_EQ(test_obj1.size(), 0u);
	ASSERT_EQ(test_obj2.size(), 0u);
	ASSERT_EQ(test_obj3.size(), 0u);

	const std::size_t n = 6;
	for (std::size_t i = 0; i < n; ++i) {
		test_obj1.push(i + 12);
	}
	ASSERT_EQ(test_obj1.size(), n);

	test_obj3.push('3');
	ASSERT_EQ(test_obj3.size(), 1u);
}

TEST(StackMethodTest, CheckPush) {
	stack_t<>     test_obj1(4);
	stack_t<int>  test_obj2;
	stack_t<char> test_obj3(1);

	ASSERT_NO_THROW(test_obj2.push(7));

	for (std::size_t i = 0; i < test_obj1.capacity(); ++i) {
		ASSERT_NO_THROW(test_obj1.push(-i));
	}
	ASSERT_NO_THROW(test_obj1.push(34));

	ASSERT_NO_THROW(test_obj3.push('u'));
	ASSERT_NO_THROW(test_obj3.push('4'));
}

TEST(StackMethodTest, CheckPop) {
	stack_t<>     test_obj1(12);
	stack_t<int>  test_obj2;
	stack_t<char> test_obj3;

	ASSERT_ANY_THROW(test_obj2.pop());
	ASSERT_ANY_THROW(test_obj1.pop());

	for (std::size_t i = 1; i < test_obj1.capacity(); ++i) {
		test_obj1.push(i + 1);
	}
	for (std::size_t i = 1; i < test_obj1.capacity(); ++i) {
		ASSERT_NO_THROW(test_obj1.pop());
	}
	ASSERT_ANY_THROW(test_obj1.pop());

	test_obj3.push('o');
	ASSERT_NO_THROW(test_obj3.pop());
	ASSERT_ANY_THROW(test_obj3.pop());
}


int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
