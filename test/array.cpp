//#define ATOM_NDEBUG
#include <gtest/gtest.h>
#include "array/array.h"
#include "exceptions.h"

using namespace atom;


TEST(ArrayConstructorTest, CheckConstructor) {
    array_t<long long> test_obj1;

    ASSERT_EQ(test_obj1.size(), 0u);

    const size_t size_test_obj2 = 15;
    const float value_to_fill = 13.2;
    array_t<float> test_obj2(size_test_obj2, value_to_fill);

    ASSERT_TRUE(test_obj2.capacity());
    ASSERT_EQ(test_obj2.size(), size_test_obj2);

    for (size_t i = 0; i < test_obj2.size(); ++i) {
        ASSERT_FLOAT_EQ(test_obj2[i], value_to_fill);
    }

    const size_t capacity_test_obj3 = 0;
    array_t<int, capacity_test_obj3> test_obj3;

    ASSERT_EQ(test_obj3.capacity(), capacity_test_obj3);
    ASSERT_EQ(test_obj3.size(), capacity_test_obj3);
}

TEST(ArrayConstructorTest, CheckCopyConstructor) {
    array_t<int> test_obj1;
    array_t<int> test_obj2(test_obj1);

    ASSERT_EQ(test_obj2.size(), test_obj1.size());

    const size_t size_test_obj3 = 17;
    array_t<float> test_obj3(size_test_obj3);
    for (size_t i = 0; i < size_test_obj3 - 2; ++i) {
        test_obj3[i] = -i;
    }

    array_t<float> test_obj4(test_obj3);

    ASSERT_TRUE(test_obj4.capacity() == test_obj3.capacity());
    ASSERT_EQ(test_obj4.size(), test_obj3.size());

    for (size_t i = 0; i < size_test_obj3; ++i) {
        ASSERT_TRUE(test_obj4[i] == test_obj3[i]);
    }
}

TEST(ArrayOperatorTest, CheckAssignment) {
    array_t<unsigned> test_obj1;

    const size_t size_test_obj2 = 19;
    array_t<unsigned> test_obj2(size_test_obj2);

    const size_t cnt_insert_test_obj1 = 24;
    for (size_t i = 0; i < cnt_insert_test_obj1; ++i) {
        test_obj1.push_back(i);
    }

    test_obj2 = test_obj1;

    ASSERT_EQ(test_obj2.size(), test_obj1.size());

    for (size_t i = 0; i < cnt_insert_test_obj1; ++i) {
        ASSERT_TRUE(test_obj1[i] == test_obj2[i]);
    }
}

TEST(ArrayOperatorTest, CheckOperatorAddressing) {
    array_t<float> test_obj1;

    ASSERT_ANY_THROW(test_obj1[0]);

    const size_t size_test_obj2 = 24;
    array_t<double> test_obj2(size_test_obj2);

    ASSERT_ANY_THROW(test_obj2[size_test_obj2 + 1]);
    ASSERT_ANY_THROW(test_obj2[-5]);

    const int position_in_test_obj2 = 5;
    const double value_to_fill = 34;
    test_obj2[position_in_test_obj2] = value_to_fill;

    ASSERT_DOUBLE_EQ(test_obj2[position_in_test_obj2], value_to_fill);
}

TEST(ArrayMethodTest, CheckPushBack) {
    array_t<float> test_obj1;

    const size_t size_test_obj1 = 14;

    for (size_t i = 0; i < size_test_obj1; ++i) {
        test_obj1.push_back(-i);
    }

    ASSERT_EQ(test_obj1.size(), size_test_obj1);

    for (size_t i = 0; i < size_test_obj1; ++i) {
        ASSERT_TRUE(test_obj1[i] == static_cast<float>(-i));
    }

    const size_t size_test_obj2 = 10;
    array_t<int> test_obj2(size_test_obj2);

    const size_t count_insert = 11;

    for (size_t i = 0; i < count_insert; ++i) {
        test_obj2.push_back(-i);
    }

    ASSERT_EQ(test_obj2.size(), count_insert + size_test_obj2);

    for (size_t i = 0; i < count_insert + size_test_obj2; ++i) {
        ASSERT_TRUE(test_obj2[i] == (i < size_test_obj2 ? 0 : static_cast<int>(size_test_obj2 - i)));
    }
}

TEST(ArrayMethodTest, CheckSize) {
    array_t<char> test_obj1;

    ASSERT_FALSE(test_obj1.size());

    const size_t size_test_obj2 = 11;
    array_t<double> test_obj2(size_test_obj2);

    ASSERT_EQ(test_obj2.size(), size_test_obj2);
}

TEST(ArrayMethodTest, CheckSwap) {
    array_t<int> test_obj1;

    const size_t cnt_insert_test_obj1 = 15;
    for(size_t i = 0; i < cnt_insert_test_obj1; ++i) {
        test_obj1.push_back(-i);
    }

    const int size_test_obj2 = 13;
    array_t<int> test_obj2(size_test_obj2);

    const size_t cnt_insert_test_obj2 = 7;
    for(size_t i = 0; i < cnt_insert_test_obj2; ++i) {
        test_obj2.push_back(i);
    }

    const size_t cap1  = test_obj1.capacity();
    const size_t size1 = test_obj1.size();

    const size_t cap2  = test_obj2.capacity();
    const size_t size2 = test_obj2.size();

    test_obj1.swap(test_obj2);

    ASSERT_EQ(test_obj1.size(), size2);
    ASSERT_EQ(test_obj2.size(), size1);
    ASSERT_EQ(test_obj1.capacity(), cap2);
    ASSERT_EQ(test_obj2.capacity(), cap1);

    for(int i = 0; i < static_cast<int>(cnt_insert_test_obj1); ++i) {
        ASSERT_TRUE(test_obj2[i] == -i);
    }
    for(int i = 0; i < static_cast<int>(cnt_insert_test_obj2); ++i) {
        ASSERT_TRUE(test_obj1[i] == (i < size_test_obj2  ? 0 : size_test_obj2  - i));
    }

    test_obj1.swap(test_obj1);

    for(int i = 0; i < static_cast<int>(cnt_insert_test_obj2); ++i) {
        ASSERT_TRUE(test_obj1[i] == (i < size_test_obj2 ? 0 : size_test_obj2 - i));
    }
}

TEST(ArrayMethodTest, CheckErase) {
    array_t<int> test_obj1;

    ASSERT_NO_THROW(test_obj1.erase(0));
    ASSERT_TRUE(test_obj1.empty());

    const size_t size_test_obj1 = 15;
    const int value_to_fill = 4;
    test_obj1.use_array(size_test_obj1);

    test_obj1[size_test_obj1 - 1] = value_to_fill;
    test_obj1[size_test_obj1 - 2] = value_to_fill - 4;
    test_obj1.erase(size_test_obj1 - 2);

    ASSERT_EQ(test_obj1[size_test_obj1 - 2], value_to_fill);
    ASSERT_EQ(test_obj1.size(), size_test_obj1 - 1);

    test_obj1[size_test_obj1 - 2] = value_to_fill - 4;
    test_obj1.erase(size_test_obj1 - 2);

    ASSERT_THROW(test_obj1[size_test_obj1 - 2], atom::outOfRange);
    ASSERT_EQ(test_obj1.size(), size_test_obj1 - 2);
}

TEST(ArrayMethodTest, CheckFill) {
    const size_t size_test_obj1 = 10;
    array_t<char> test_obj1(size_test_obj1);

    const char value_to_fill = 't';
    test_obj1.fill(value_to_fill);

    for (size_t i = 0; i < test_obj1.size(); ++i) {
        ASSERT_EQ(test_obj1[i], value_to_fill);
    }
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}