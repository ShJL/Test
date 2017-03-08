//#define ATOM_NDEBUG
#include <string>
#include <gtest/gtest.h>
#include "stack/stack.h"
#include "vector/vector.h"
#include "array/array.h"
#include "exceptions.h"

using namespace atom;


TEST (StackVectorConstructorTest, CheckConstructor) {
	stack_t<std::string> test_obj1;
	stack_t<int>         test_obj2;

	ASSERT_EQ(test_obj1.size(), 0u);
	ASSERT_EQ(test_obj2.size(), 0u);
	ASSERT_EQ(test_obj1.capacity(), 0u);
	ASSERT_EQ(test_obj2.capacity(), 0u);
}

TEST (StackVectorConstructorTest, CheckCopyConstructor) {
	stack_t<float> test_obj1;

	const size_t count_insert = 40;
	for (size_t i = 0; i < count_insert; ++i) {
		test_obj1.push(i);
	}

	stack_t<float> test_obj2(test_obj1);

	ASSERT_EQ(test_obj2.size(), count_insert);
	ASSERT_TRUE(test_obj2.capacity() >= count_insert);

	for (int i = count_insert - 1; i >= 0; --i) {
		ASSERT_FLOAT_EQ(test_obj2.top(), static_cast<float>(i));
		test_obj2.pop();
	}
}

TEST (StackVectorOperatorTest, CheckAssignment) {
	stack_t<float> test_obj1;
	stack_t<float> test_obj2;

	const size_t count_insert = 40;
	for (size_t i = 0; i < count_insert; ++i) {
		test_obj1.push(i);
	}

	test_obj2 = test_obj1;

	ASSERT_EQ(test_obj2.size(), count_insert);
	ASSERT_EQ(test_obj2.capacity(), count_insert);
}

TEST(StackVectorMethodTest, CheckEmpty) {
	stack_t<int>   test_obj1;
	stack_t<int>   test_obj2;
	stack_t<float> test_obj3;

	ASSERT_TRUE(test_obj1.empty());
	ASSERT_TRUE(test_obj2.empty());
	ASSERT_TRUE(test_obj3.empty());

	test_obj3.push(3.2);
	ASSERT_FALSE(test_obj3.empty());

	const int count_insert = 5;
	for (int i = 0; i < count_insert; ++i) {
		test_obj1.push(i);
	}
	for (int i = 0; i < count_insert; ++i) {
		test_obj1.pop();
	}
	ASSERT_TRUE(test_obj1.empty());
}

TEST(StackVectorMethodTest, CheckTop) {
	stack_t<int>  test_obj1;
	stack_t<char> test_obj2;

	ASSERT_ANY_THROW(test_obj1.top());
	ASSERT_ANY_THROW(test_obj2.top());

	test_obj2.push('r');
	ASSERT_EQ(test_obj2.top(), 'r');

	const int count_insert = 6;
	for (int i = 0; i <= count_insert; ++i) {
		test_obj1.push(-i);
	}
	ASSERT_EQ(test_obj1.top(), -count_insert);
}

TEST(StackVectorMethodTest, CheckSize) {
	stack_t<int>  test_obj1;
	stack_t<char> test_obj2;

	ASSERT_EQ(test_obj1.size(), 0u);
	ASSERT_EQ(test_obj2.size(), 0u);

	const std::size_t count_insert = 6;
	for (std::size_t i = 0; i < count_insert; ++i) {
		test_obj1.push(i + 12);
	}
	ASSERT_EQ(test_obj1.size(), count_insert);

	test_obj2.push('3');
	ASSERT_EQ(test_obj2.size(), 1u);
}

TEST(StackVectorMethodTest, CheckPush) {
	stack_t<int>      test_obj1;
	stack_t<unsigned> test_obj2;
	stack_t<char>     test_obj3;

	ASSERT_NO_THROW(test_obj2.push(7));

	for (std::size_t i = 0; i < test_obj1.capacity(); ++i) {
		ASSERT_NO_THROW(test_obj1.push(-i));
	}
	ASSERT_NO_THROW(test_obj1.push(34));

	ASSERT_NO_THROW(test_obj3.push('u'));
	ASSERT_NO_THROW(test_obj3.push('4'));
}

TEST(StackVectorMethodTest, CheckPop) {
	stack_t<int>   test_obj1;
	stack_t<float> test_obj2;
	stack_t<char>  test_obj3;

	ASSERT_NO_THROW(test_obj2.pop());
	ASSERT_TRUE(test_obj2.empty());
	ASSERT_NO_THROW(test_obj1.pop());
	ASSERT_TRUE(test_obj1.empty());

	for (std::size_t i = 1; i < test_obj1.capacity(); ++i) {
		test_obj1.push(i + 1);
	}
	for (std::size_t i = 1; i < test_obj1.capacity(); ++i) {
		ASSERT_NO_THROW(test_obj1.pop());
	}
	ASSERT_NO_THROW(test_obj1.pop());
	ASSERT_TRUE(test_obj1.empty());

	test_obj3.push('o');
	ASSERT_NO_THROW(test_obj3.pop());
	ASSERT_NO_THROW(test_obj3.pop());
	ASSERT_TRUE(test_obj3.empty());
}


TEST (StackArrayConstructorTest, CheckConstructor) {
	stack_t<std::string, array_t<std::string> > test_obj1;
	stack_t<int, array_t<int> >                 test_obj2;

	const size_t default_capacity = 256;

	ASSERT_EQ(test_obj1.size(), 0u);
	ASSERT_EQ(test_obj2.size(), 0u);
	ASSERT_EQ(test_obj1.capacity(), default_capacity);
	ASSERT_EQ(test_obj2.capacity(), default_capacity);
}

TEST (StackArrayConstructorTest, CheckCopyConstructor) {
	stack_t<float, array_t<float> > test_obj1;

	const size_t count_insert = 40;
	for (size_t i = 0; i < count_insert; ++i) {
		test_obj1.push(i);
	}

	stack_t<float, array_t<float> > test_obj2(test_obj1);

	ASSERT_EQ(test_obj2.size(), count_insert);

	for (int i = count_insert - 1; i >= 0; --i) {
		ASSERT_FLOAT_EQ(test_obj2.top(), static_cast<float>(i));
		test_obj2.pop();
	}
}

TEST (StackArrayOperatorTest, CheckAssignment) {
	stack_t<float, array_t<float> > test_obj1;
	stack_t<float, array_t<float> > test_obj2;

	const size_t count_insert = 40;
	for (size_t i = 0; i < count_insert; ++i) {
		test_obj1.push(i);
	}

	test_obj2 = test_obj1;

	ASSERT_EQ(test_obj2.size(), count_insert);
}

TEST(StackArrayMethodTest, CheckEmpty) {
	stack_t<int, array_t<int> >     test_obj1;
	stack_t<int, array_t<int> >     test_obj2;
	stack_t<float, array_t<float> > test_obj3;

	ASSERT_TRUE(test_obj1.empty());
	ASSERT_TRUE(test_obj2.empty());
	ASSERT_TRUE(test_obj3.empty());

	test_obj3.push(3.2);
	ASSERT_FALSE(test_obj3.empty());

	const int count_insert = 5;
	for (int i = 0; i < count_insert; ++i) {
		test_obj1.push(i);
	}
	for (int i = 0; i < count_insert; ++i) {
		test_obj1.pop();
	}
	ASSERT_TRUE(test_obj1.empty());
}

TEST(StackArrayMethodTest, CheckTop) {
	stack_t<int, array_t<int> >   test_obj1;
	stack_t<char, array_t<char> > test_obj2;

	ASSERT_ANY_THROW(test_obj1.top());
	ASSERT_ANY_THROW(test_obj2.top());

	test_obj2.push('r');
	ASSERT_EQ(test_obj2.top(), 'r');

	const int count_insert = 6;
	for (int i = 0; i <= count_insert; ++i) {
		test_obj1.push(-i);
	}
	ASSERT_EQ(test_obj1.top(), -count_insert);
}

TEST(StackArrayMethodTest, CheckSize) {
	stack_t<int, array_t<int> >   test_obj1;
	stack_t<char, array_t<char> > test_obj2;

	ASSERT_EQ(test_obj1.size(), 0u);
	ASSERT_EQ(test_obj2.size(), 0u);

	const std::size_t count_insert = 6;
	for (std::size_t i = 0; i < count_insert; ++i) {
		test_obj1.push(i + 12);
	}
	ASSERT_EQ(test_obj1.size(), count_insert);

	test_obj2.push('3');
	ASSERT_EQ(test_obj2.size(), 1u);
}

TEST(StackArrayMethodTest, CheckPush) {
	stack_t<int, array_t<int> >           test_obj1;
	stack_t<unsigned, array_t<unsigned> > test_obj2;
	stack_t<char, array_t<char> >         test_obj3;

	ASSERT_NO_THROW(test_obj2.push(7));

	for (std::size_t i = 0; i < test_obj1.capacity(); ++i) {
		ASSERT_NO_THROW(test_obj1.push(-i));
	}
	ASSERT_ANY_THROW(test_obj1.push(34));

	ASSERT_NO_THROW(test_obj3.push('u'));
	ASSERT_NO_THROW(test_obj3.push('4'));
}

TEST(StackArrayMethodTest, CheckPop) {
	stack_t<int, array_t<int> >     test_obj1;
	stack_t<float, array_t<float> > test_obj2;
	stack_t<char, array_t<char> >   test_obj3;

	ASSERT_NO_THROW(test_obj2.pop());
	ASSERT_TRUE(test_obj2.empty());
	ASSERT_NO_THROW(test_obj1.pop());
	ASSERT_TRUE(test_obj1.empty());

	for (std::size_t i = 1; i < test_obj1.capacity(); ++i) {
		test_obj1.push(i + 1);
	}
	for (std::size_t i = 1; i < test_obj1.capacity(); ++i) {
		ASSERT_NO_THROW(test_obj1.pop());
	}
	ASSERT_NO_THROW(test_obj1.pop());
	ASSERT_TRUE(test_obj1.empty());

	test_obj3.push('o');
	ASSERT_NO_THROW(test_obj3.pop());
	ASSERT_NO_THROW(test_obj3.pop());
	ASSERT_TRUE(test_obj3.empty());
}


int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
