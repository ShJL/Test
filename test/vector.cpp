//#define ATOM_NDEBUG
#include <gtest/gtest.h>
#include "vector/vector.h"
#include "exceptions.h"

using namespace atom;


TEST(VectorConstructorTest, CheckConstructor) {
    vector_t<long long> test_obj1;

    ASSERT_EQ(test_obj1.capacity(), 0u);
    ASSERT_EQ(test_obj1.size(), 0u);

    const size_t size_test_obj2 = 15;
    vector_t<float> test_obj2(size_test_obj2);

    ASSERT_TRUE(test_obj2.capacity() >= size_test_obj2);
    ASSERT_EQ(test_obj2.size(), size_test_obj2);

    vector_t<int> test_obj3(0);

    ASSERT_EQ(test_obj3.capacity(), 0u);
    ASSERT_EQ(test_obj3.size(), 0u);

    const size_t size_test_obj4 = 15;
    const short value_to_fill = 13;
    vector_t<short> test_obj4(size_test_obj4, value_to_fill);

    ASSERT_TRUE(test_obj4.capacity() >= size_test_obj4);
    ASSERT_EQ(test_obj4.size(), size_test_obj4);

    for (size_t i = 0; i < test_obj4.size(); ++i) {
        ASSERT_EQ(test_obj4[i], value_to_fill);
    }
}

TEST(VectorConstructorTest, CheckCopyConstructor) {
    vector_t<int> test_obj1;
    vector_t<int> test_obj2(test_obj1);

    ASSERT_EQ(test_obj2.capacity(), 0u);
    ASSERT_EQ(test_obj2.size(), test_obj1.size());

    const size_t size_test_obj3 = 15;
    vector_t<float> test_obj3(size_test_obj3);
    for (size_t i = 0; i < size_test_obj3 - 2; ++i) {
        test_obj3[i] = -i;
    }

    vector_t<float> test_obj4(test_obj3);

    ASSERT_TRUE(test_obj4.capacity() <= test_obj3.capacity());
    ASSERT_EQ(test_obj4.size(), test_obj3.size());

    for (size_t i = 0; i < size_test_obj3; ++i) {
        ASSERT_TRUE(test_obj4[i] == test_obj3[i]);
    }
}

TEST(VectorOperatorTest, CheckAssignment) {
    vector_t<unsigned> test_obj1;

    const size_t size_test_obj2 = 19;
    vector_t<unsigned> test_obj2(size_test_obj2);

    const size_t cnt_insert_test_obj1 = 24;
    for (size_t i = 0; i < cnt_insert_test_obj1; ++i) {
        test_obj1.push_back(i);
    }

    test_obj2 = test_obj1;

    ASSERT_TRUE(test_obj2.capacity() <= test_obj1.capacity());
    ASSERT_EQ(test_obj2.size(), test_obj1.size());

    for (size_t i = 0; i < cnt_insert_test_obj1; ++i) {
        ASSERT_TRUE(test_obj1[i] == test_obj2[i]);
    }
}

TEST(VectorOperatorTest, CheckOperatorAddressing) {
    vector_t<float> test_obj1;

    ASSERT_ANY_THROW(test_obj1[0]);

    const size_t size_test_obj2 = 24;
    vector_t<double> test_obj2(size_test_obj2);

    ASSERT_ANY_THROW(test_obj2[size_test_obj2 + 1]);
    ASSERT_ANY_THROW(test_obj2[-5]);

    const int position_test_obj2 = 5;
    const double value_to_fill = 34;
    test_obj2[position_test_obj2] = value_to_fill;
    ASSERT_DOUBLE_EQ(test_obj2[position_test_obj2], value_to_fill);
}

TEST(VectorMethodTest, CheckPushBack) {
    vector_t<float> test_obj1;

    const size_t cnt_insert_test_obj1 = 14;

    for (size_t i = 0; i <cnt_insert_test_obj1; ++i) {
        test_obj1.push_back(-i);
    }

    ASSERT_TRUE(test_obj1.capacity() >= cnt_insert_test_obj1);
    ASSERT_EQ(test_obj1.size(), cnt_insert_test_obj1);

    for (size_t i = 0; i < cnt_insert_test_obj1; ++i) {
        ASSERT_TRUE(test_obj1[i] == static_cast<float>(-i));
    }

    const size_t size_test_obj2 = 10;
    vector_t<int> test_obj2(size_test_obj2);

    const size_t cnt_insert_test_obj2 = 11;

    for (size_t i = 0; i < cnt_insert_test_obj2; ++i) {
        test_obj2.push_back(-i);
    }

    ASSERT_TRUE(test_obj2.capacity() >= cnt_insert_test_obj2 + size_test_obj2);
    ASSERT_EQ(test_obj2.size(), cnt_insert_test_obj2 + size_test_obj2);

    for (size_t i = 0; i < cnt_insert_test_obj2 + size_test_obj2; ++i) {
        ASSERT_TRUE(test_obj2[i] == (i < size_test_obj2 ? 0 : static_cast<int>(size_test_obj2 - i)));
    }
}

TEST(VectorMemoryTest, CheckReserve) {
    vector_t<float> test_obj1;

    test_obj1.reserve(0);
    ASSERT_EQ(test_obj1.capacity(), 0u);

    const size_t new_capacity_test_obj1 = 3;
    test_obj1.reserve(new_capacity_test_obj1);

    ASSERT_TRUE(test_obj1.capacity() >= new_capacity_test_obj1);

    const size_t cur_capacity_obj1 = test_obj1.capacity();
    test_obj1.reserve(new_capacity_test_obj1 - 2);

    ASSERT_EQ(test_obj1.capacity(), cur_capacity_obj1);

    const size_t size_test_obj2 = 5;
    vector_t<int> test_obj2(size_test_obj2);

    const size_t cur_capacity_obj2 = test_obj2.capacity();
    const size_t new_capacity_test_obj2 = 22;
    test_obj2.reserve(new_capacity_test_obj2);

    ASSERT_TRUE(test_obj2.capacity() >= cur_capacity_obj2 + new_capacity_test_obj2);
}

TEST(VectorMemoryTest, CheckResize) {
    vector_t<float> test_obj1;

    test_obj1.resize(0);
    ASSERT_EQ(test_obj1.capacity(), 0u);

    const size_t new_size_test_obj1 = 3;
    test_obj1.resize(new_size_test_obj1);

    ASSERT_EQ(test_obj1.size(), new_size_test_obj1);
    ASSERT_EQ(test_obj1.capacity(), new_size_test_obj1);

    test_obj1.resize(new_size_test_obj1 - 1);

    ASSERT_EQ(test_obj1.size(), new_size_test_obj1 - 1);
    ASSERT_EQ(test_obj1.capacity(), new_size_test_obj1 - 1);

    const size_t size_test_obj2 = 8;
    vector_t<int> test_obj2(size_test_obj2);

    for (size_t i = 2; i < size_test_obj2; ++i) {
        test_obj2[i] = i;
    }

    const size_t new_size_test_obj2 = 22;
    test_obj2.resize(new_size_test_obj2);

    ASSERT_EQ(test_obj2.size(), new_size_test_obj2);
    ASSERT_EQ(test_obj2.capacity(), new_size_test_obj2);
    for (int i = 2; i < static_cast<int>(size_test_obj2); ++i) {
        ASSERT_TRUE(test_obj2[i] == i);
    }

    test_obj2.resize(size_test_obj2 - 3);

    ASSERT_TRUE(test_obj2.size() == size_test_obj2 - 3);
    ASSERT_TRUE(test_obj2.capacity() == size_test_obj2 - 3);
    for (int i = 2; i < static_cast<int>(size_test_obj2 - 3); ++i) {
        ASSERT_TRUE(test_obj2[i] == i);
    }

    test_obj2.resize(0);
    ASSERT_EQ(test_obj2.size(), 0u);
    ASSERT_FALSE(test_obj2.capacity());

    test_obj2.resize(new_size_test_obj2);

    ASSERT_EQ(test_obj2.size(), new_size_test_obj2);
    ASSERT_EQ(test_obj2.capacity(), new_size_test_obj2);
}

TEST(VectorMethodTest, CheckSize) {
    vector_t<char> test_obj1;

    ASSERT_FALSE(test_obj1.size());

    const size_t size_test_obj2 = 11;
    vector_t<double> test_obj2(size_test_obj2);

    ASSERT_EQ(test_obj2.size(), size_test_obj2);
}

TEST(VectorMethodTest, CheckSwap) {
    vector_t<int> test_obj1;

    const size_t cnt_insert_test_obj1 = 15;
    for(size_t i = 0; i < cnt_insert_test_obj1; ++i) {
        test_obj1.push_back(-i);
    }

    const int size_test_obj2 = 13;
    vector_t<int> test_obj2(size_test_obj2);

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
        ASSERT_EQ(test_obj2[i], -i);
    }
    for(int i = 0; i < static_cast<int>(cnt_insert_test_obj2); ++i) {
        ASSERT_TRUE(test_obj1[i] == (i < size_test_obj2 ? 0 : size_test_obj2 - i));
    }

    test_obj1.swap(test_obj1);

    for(int i = 0; i < static_cast<int>(cnt_insert_test_obj2); ++i) {
        ASSERT_TRUE(test_obj1[i] == (i < size_test_obj2 ? 0 : size_test_obj2 - i));
    }
}

TEST(VectorMethodTest, CheckErase) {
    vector_t<int> test_obj1;

    ASSERT_NO_THROW(test_obj1.erase(0));
    ASSERT_TRUE(test_obj1.empty());

    const size_t size_test_obj1 = 15;
    const int value_to_fill = 4;
    test_obj1.resize(size_test_obj1, value_to_fill);

    test_obj1[size_test_obj1 - 2] = value_to_fill - 4;
    test_obj1.erase(size_test_obj1 - 2);

    ASSERT_EQ(test_obj1[size_test_obj1 - 2], value_to_fill);
    ASSERT_EQ(test_obj1.size(), size_test_obj1 - 1);

    test_obj1[size_test_obj1 - 2] = value_to_fill - 4;
    test_obj1.erase(size_test_obj1 - 2);

    ASSERT_THROW(test_obj1[size_test_obj1 - 2], atom::outOfRange);
    ASSERT_EQ(test_obj1.size(), size_test_obj1 - 2);
}

TEST(VectorMethodTest, CheckClear) {
    vector_t<int> test_obj1;
    test_obj1.clear();

    ASSERT_EQ(test_obj1.size(), 0u);
    ASSERT_EQ(test_obj1.capacity(), 0u);

    const size_t count_insert = 19;
    for (size_t i = 0; i < count_insert; ++i) {
        ASSERT_NO_THROW(test_obj1.push_back(-i));
    }
    for (size_t i = 0; i < count_insert; ++i) {
        ASSERT_EQ(test_obj1[i], static_cast<int>(-i));
    }

    ASSERT_EQ(test_obj1.size(), count_insert);
    ASSERT_TRUE(test_obj1.capacity() >= count_insert);

    const size_t size_test_obj2 = 18;
    vector_t<int> test_obj2(size_test_obj2);
    test_obj2.clear();

    ASSERT_EQ(test_obj2.size(), 0u);
    ASSERT_EQ(test_obj2.capacity(), 0u);
}


int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
