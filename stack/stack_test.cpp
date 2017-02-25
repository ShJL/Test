#include <iostream>
#include <gtest/gtest.h>
#define NDEBUG
#include "stack.h"

using namespace stk;


TEST(StackMethodTest, CheckEmpty) {
	stack_t<>           test_obj1;
	stack_t<int, 0>     test_obj2;
	stack_t<float, 100> test_obj3;
	stack_t<char, 1>    test_obj4;

	ASSERT_TRUE(test_obj1.empty());
	ASSERT_TRUE(test_obj2.empty());
	ASSERT_TRUE(test_obj3.empty());
	ASSERT_TRUE(test_obj4.empty());

	const int n = 5;
	for (int i = 0; i < n; ++i) {
		test_obj1.push(i);
	}
	for (int i = 0; i < n; ++i) {
		test_obj1.pop();
	}
	ASSERT_TRUE(test_obj1.empty());

	test_obj4.push('q');
	test_obj4.pop();
	ASSERT_TRUE(test_obj4.empty());
}

TEST(StackMethodTest, CheckFull) {
	stack_t<>           test_obj1;
	stack_t<int, 0>     test_obj2;
	stack_t<char, 1>    test_obj3;

	const int n = test_obj1.capacity();
	for (int i = 0; i < n; ++i) {
		ASSERT_FALSE(test_obj1.full());
		test_obj1.push(i);
	}
	ASSERT_TRUE(test_obj1.full());

	ASSERT_TRUE(test_obj2.full());

	test_obj3.push('q');
	ASSERT_TRUE(test_obj3.full());
}

TEST(StackMethodTest, CheckTop) {
	stack_t<>           test_obj1;
	stack_t<int, 0>     test_obj2;
	stack_t<float, 100> test_obj3;
	stack_t<char, 1>    test_obj4;

	ASSERT_ANY_THROW(test_obj2.top());
	ASSERT_ANY_THROW(test_obj3.top());

	test_obj4.push('r');
	ASSERT_EQ(test_obj4.top(), 'r');

	const int n = 6;
	for (int i = 0; i <= n; ++i) {
		test_obj1.push(-i);
	}
	ASSERT_EQ(test_obj1.top(), -n);
}

TEST(StackMethodTest, CheckSize) {
	stack_t<>           test_obj1;
	stack_t<int, 0>     test_obj2;
	stack_t<char, 1>    test_obj3;

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
	stack_t<>           test_obj1;
	stack_t<int, 0>     test_obj2;
	stack_t<char, 1>    test_obj3;

	ASSERT_ANY_THROW(test_obj2.push(7));

	for (std::size_t i = 0; i < test_obj1.capacity(); ++i) {
		ASSERT_NO_THROW(test_obj1.push(-i));
	}
	ASSERT_ANY_THROW(test_obj1.push(34));

	ASSERT_NO_THROW(test_obj3.push('u'));
	ASSERT_ANY_THROW(test_obj3.push('4'));
}

TEST(StackMethodTest, CheckPop) {
	stack_t<>           test_obj1;
	stack_t<int, 0>     test_obj2;
	stack_t<char, 1>    test_obj3;

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
