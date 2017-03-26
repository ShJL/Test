//#define ATOM_NDEBUG
#include "vector/vector.h"
#include "exceptions.h"
#include <initializer_list>
#include <gtest/gtest.h>
#include <algorithm>
#include <vector>
#include <iostream>

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

TEST(VectorConstructorTest, CheckConstructorInitializerList) {
    const size_t arr_size = 5;
    const int arr[arr_size] = {5, 77, -15, 0, 0};

    vector_t<int> test_obj1 = {5, 77, -15, 0, 0};

    ASSERT_EQ(test_obj1.capacity(), arr_size);
    ASSERT_EQ(test_obj1.size(), arr_size);

    for (size_t i = 0; i < arr_size; ++i) {
        ASSERT_EQ(test_obj1[i], arr[i]);
    }

    vector_t<int> test_obj2 = {};

    ASSERT_EQ(test_obj2.capacity(), 0u);
    ASSERT_EQ(test_obj2.size(), 0u);
}

TEST(VectorConstructorTest, CheckMoveConstructor) {
    vector_t<int> test_obj1;
    const size_t test_obj1_cap = test_obj1.capacity();
    const size_t test_obj1_size = test_obj1.size();

    vector_t<int> test_obj2(std::move(test_obj1));

    ASSERT_EQ(test_obj2.capacity(), test_obj1_cap);
    ASSERT_EQ(test_obj2.size(), test_obj1_size);

    const size_t size_test_obj3 = 15;
    vector_t<float> test_obj3(size_test_obj3);
    for (size_t i = 0; i < size_test_obj3 - 2; ++i) {
        test_obj3[i] = -i;
    }

    const size_t test_obj3_cap = test_obj3.capacity();
    const size_t test_obj3_size = test_obj3.size();

    vector_t<float> test_obj4(std::move(test_obj3));

    ASSERT_EQ(test_obj4.capacity(), test_obj3_cap);
    ASSERT_EQ(test_obj4.size(), test_obj3_size);

    for (size_t i = 0; i < size_test_obj3 - 2; ++i) {
        ASSERT_EQ(test_obj4[i], -i);
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
        ASSERT_EQ(test_obj4[i], test_obj3[i]);
    }
}

TEST(VectorOperatorTest, CheckMoveAssignment) {
    vector_t<unsigned> test_obj1;

    const size_t size_test_obj2 = 19;
    vector_t<unsigned> test_obj2(size_test_obj2);

    const size_t cnt_insert_test_obj1 = 24;
    for (size_t i = 0; i < cnt_insert_test_obj1; ++i) {
        test_obj1.push_back(i);
    }

    const size_t test_obj1_cap = test_obj1.capacity();
    const size_t test_obj1_size = test_obj1.size();

    test_obj2 = std::move(test_obj1);

    ASSERT_TRUE(test_obj2.capacity() <= test_obj1_cap);
    ASSERT_EQ(test_obj2.size(), test_obj1_size);

    for (size_t i = 0; i < cnt_insert_test_obj1; ++i) {
        ASSERT_EQ(test_obj2[i], i);
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

TEST(VectorMethodTest, CheckIterators) {
    const size_t list_size = 4;

    vector_t<int> test_obj1 = {5, -9, 0, 11};

    int i = 0;
    for (vector_t<int>::iterator it = test_obj1.begin(); it != test_obj1.end(); ++it) {
        ASSERT_EQ(test_obj1[i++], *it);
    }

    vector_t<float> test_obj2;

    ASSERT_THROW(test_obj2.begin(), atom::outOfRange);
    ASSERT_THROW(test_obj2.end(), atom::outOfRange);

    std::vector<int> tmp_vec(list_size);
    std::copy(test_obj1.begin(), test_obj1.end(), tmp_vec.begin());

    for (size_t j = 0; j < tmp_vec.size(); ++j) {
        ASSERT_EQ(test_obj1[j], tmp_vec[j]);
    }
}

//-------------------------------------------------<bool>------------------------------------------------------

TEST(VectorBoolConstructorTest, CheckConstructor) {
    vector_t<bool> test_obj1;

    ASSERT_EQ(test_obj1.capacity(), 0u);
    ASSERT_EQ(test_obj1.size(), 0u);

    const size_t size_test_obj2 = 65;
    vector_t<bool> test_obj2(size_test_obj2);

    ASSERT_TRUE(test_obj2.capacity() >= size_test_obj2);
    ASSERT_EQ(test_obj2.size(), size_test_obj2);

    vector_t<bool> test_obj3(0);

    ASSERT_EQ(test_obj3.capacity(), 0u);
    ASSERT_EQ(test_obj3.size(), 0u);

    const size_t size_test_obj4 = 15;
    const bool value_to_fill = true;
    vector_t<bool> test_obj4(size_test_obj4, value_to_fill);

    ASSERT_TRUE(test_obj4.capacity() >= 1u);
    ASSERT_EQ(test_obj4.size(), size_test_obj4);

    for (size_t i = 0; i < test_obj4.size(); ++i) {
        ASSERT_EQ(test_obj4[i], value_to_fill);
    }

    vector_t<bool> test_obj5(1);
    ASSERT_TRUE(test_obj5.capacity() == atom::BIT_BLOCK_SIZE);
    ASSERT_EQ(test_obj5.size(), 1u);
}

TEST(VectorBoolConstructorTest, CheckMoveConstructor) {
    vector_t<bool> test_obj1;
    const size_t test_obj1_cap = test_obj1.capacity();
    const size_t test_obj1_size = test_obj1.size();

    vector_t<bool> test_obj2(std::move(test_obj1));

    ASSERT_EQ(test_obj2.capacity(), test_obj1_cap);
    ASSERT_EQ(test_obj2.size(), test_obj1_size);

    const size_t size_test_obj3 = 95;
    vector_t<bool> test_obj3(size_test_obj3);

    for (size_t i = 0; i < size_test_obj3 - 2; ++i) {
        test_obj3[i] = i & 1;
    }

    const size_t test_obj3_cap = test_obj3.capacity();
    const size_t test_obj3_size = test_obj3.size();

    vector_t<bool> test_obj4(std::move(test_obj3));

    ASSERT_EQ(test_obj4.capacity(), test_obj3_cap);
    ASSERT_EQ(test_obj4.size(), test_obj3_size);

    for (size_t i = 0; i < size_test_obj3 - 2; ++i) {
        ASSERT_EQ(test_obj4[i], i & 1);
    }
}

TEST(VectorBoolConstructorTest, CheckCopyConstructor) {
    vector_t<bool> test_obj1;
    vector_t<bool> test_obj2(test_obj1);

    ASSERT_EQ(test_obj2.capacity(), 0u);
    ASSERT_EQ(test_obj2.size(), test_obj1.size());

    const size_t size_test_obj3 = 63;
    vector_t<bool> test_obj3(size_test_obj3);
    for (size_t i = 0; i < size_test_obj3 - 2; ++i) {
        test_obj3[i] = ~(i & 1) & 1;
    }

    vector_t<bool> test_obj4(test_obj3);

    ASSERT_TRUE(test_obj4.capacity() <= test_obj3.capacity());
    ASSERT_EQ(test_obj4.size(), size_test_obj3);

    for (size_t i = 0; i < size_test_obj3; ++i) {
        ASSERT_EQ(test_obj4[i], test_obj3[i]);
    }
}

TEST(VectorBoolOperatorTest, CheckMoveAssignment) {
    vector_t<bool> test_obj1;

    const size_t size_test_obj2 = 64;
    vector_t<bool> test_obj2(size_test_obj2);

    const size_t cnt_insert_test_obj1 = 24;
    for (size_t i = 0; i < cnt_insert_test_obj1; ++i) {
        test_obj1.push_back(i & 1);
    }

    const size_t test_obj1_cap = test_obj1.capacity();
    const size_t test_obj1_size = test_obj1.size();

    test_obj2 = std::move(test_obj1);

    ASSERT_TRUE(test_obj2.capacity() <= test_obj1_cap);
    ASSERT_EQ(test_obj2.size(), test_obj1_size);

    for (size_t i = 0; i < cnt_insert_test_obj1; ++i) {
        ASSERT_EQ(test_obj2[i], i & 1);
    }
}

TEST(VectorBoolOperatorTest, CheckAssignment) {
    vector_t<bool> test_obj1;

    const size_t size_test_obj2 = 542;
    vector_t<bool> test_obj2(size_test_obj2);

    const size_t cnt_insert_test_obj1 = 420;
    for (size_t i = 0; i < cnt_insert_test_obj1; ++i) {
        test_obj1.push_back((i >> 2) & 1);
    }

    test_obj2 = test_obj1;

    ASSERT_TRUE(test_obj2.capacity() <= test_obj1.capacity());
    ASSERT_EQ(test_obj2.size(), test_obj1.size());

    for (size_t i = 0; i < cnt_insert_test_obj1; ++i) {
        ASSERT_EQ(test_obj1[i], test_obj2[i]);
    }
}

TEST(VectorBoolOperatorTest, CheckOperatorAddressing) {
    vector_t<bool> test_obj1;

    ASSERT_ANY_THROW(test_obj1[0]);

    const size_t size_test_obj2 = 123;
    vector_t<bool> test_obj2(size_test_obj2);

    ASSERT_ANY_THROW(test_obj2[size_test_obj2 + 1]);
    ASSERT_ANY_THROW(test_obj2[-5]);

    const int position_test_obj2 = 111;
    const bool value_to_fill = true;
    test_obj2[position_test_obj2] = value_to_fill;
    ASSERT_EQ(test_obj2[position_test_obj2], value_to_fill);

    vector_t<bool> test_obj3(100, true);

    test_obj3[90].operator=(false);
    test_obj3[65] = test_obj3[90];
    bool bit = test_obj3[65];

    std::cerr << test_obj3[67];

    ASSERT_EQ(test_obj3[65], false);
    ASSERT_EQ(test_obj3[90], false);
    ASSERT_EQ(bit, false);
}

TEST(VectorBoolMethodTest, CheckPushBack) {
    vector_t<bool> test_obj1;

    const size_t cnt_insert_test_obj1 = 1125;

    for (size_t i = 0; i < cnt_insert_test_obj1; ++i) {
        test_obj1.push_back(i & 1);
    }

    ASSERT_TRUE(test_obj1.capacity() >= cnt_insert_test_obj1);
    ASSERT_EQ(test_obj1.size(), cnt_insert_test_obj1);

    for (size_t i = 0; i < cnt_insert_test_obj1; ++i) {
        ASSERT_TRUE(test_obj1[i] == (i & 1));
    }

    const size_t size_test_obj2 = 1997;
    vector_t<bool> test_obj2(size_test_obj2, true);

    const size_t cnt_insert_test_obj2 = 1753;

    for (size_t i = 0; i < cnt_insert_test_obj2; ++i) {
        test_obj2.push_back(~(i & 1) & 1);
    }

    ASSERT_TRUE(test_obj2.capacity() >= (cnt_insert_test_obj2 + size_test_obj2));
    ASSERT_EQ(test_obj2.size(), cnt_insert_test_obj2 + size_test_obj2);

    for (size_t i = 0; i < cnt_insert_test_obj2 + size_test_obj2; ++i) {
        ASSERT_TRUE(test_obj2[i] == (i < size_test_obj2 ? true : ~((i - size_test_obj2) & 1) & 1));
    }

    vector_t<bool> test_obj3(1);
    ASSERT_EQ(test_obj3.capacity(), atom::BIT_BLOCK_SIZE);
    ASSERT_EQ(test_obj3.size(), 1u);

    for (int i = 0; i < 456; ++i) {
        test_obj3.push_back(i & 1);
    }

    ASSERT_EQ(test_obj3[0], false);
    for (size_t i = 1; i < 457; ++i) {
        ASSERT_EQ(test_obj3[i], (i - 1) & 1);
    }
}

TEST(VectorBoolMemoryTest, CheckReserve) {
    vector_t<bool> test_obj1;

    test_obj1.reserve(0);
    ASSERT_EQ(test_obj1.capacity(), 0u);

    const size_t new_capacity_test_obj1 = 300;
    test_obj1.reserve(new_capacity_test_obj1);

    ASSERT_TRUE(test_obj1.capacity() >= new_capacity_test_obj1);

    const size_t cur_capacity_obj1 = test_obj1.capacity();
    test_obj1.reserve(new_capacity_test_obj1 - 2);

    ASSERT_EQ(test_obj1.capacity(), cur_capacity_obj1);

    const size_t size_test_obj2 = 50;
    vector_t<bool> test_obj2(size_test_obj2);

    const size_t cur_capacity_obj2 = test_obj2.capacity();
    const size_t new_capacity_test_obj2 = 202;
    test_obj2.reserve(new_capacity_test_obj2);

    ASSERT_TRUE(test_obj2.capacity() >= std::max(cur_capacity_obj2, new_capacity_test_obj2));
}

TEST(VectorBoolMemoryTest, CheckResize) {
    vector_t<bool> test_obj1;

    test_obj1.resize(0);
    ASSERT_EQ(test_obj1.capacity(), 0u);

    const size_t new_size_test_obj1 = 325;
    test_obj1.resize(new_size_test_obj1);

    ASSERT_EQ(test_obj1.size(), new_size_test_obj1);
    ASSERT_TRUE(test_obj1.capacity() >= new_size_test_obj1);

    test_obj1.resize(new_size_test_obj1 - 100);

    ASSERT_EQ(test_obj1.size(), new_size_test_obj1 - 100);
    ASSERT_TRUE(test_obj1.capacity() >= new_size_test_obj1 - 100);

    const size_t size_test_obj2 = 8;
    vector_t<bool> test_obj2(size_test_obj2);

    for (size_t i = 2; i < size_test_obj2; ++i) {
        test_obj2[i] = i & 1;
    }

    const size_t new_size_test_obj2 = 70;
    test_obj2.resize(new_size_test_obj2);

    ASSERT_EQ(test_obj2.size(), new_size_test_obj2);
    ASSERT_TRUE(test_obj2.capacity() >= new_size_test_obj2);
    for (size_t i = 2; i < size_test_obj2; ++i) {
        ASSERT_TRUE(test_obj2[i] == (i & 1));
    }

    test_obj2.resize(new_size_test_obj2 - 10);

    ASSERT_EQ(test_obj2.size(), new_size_test_obj2 - 10);
    ASSERT_TRUE(test_obj2.capacity() >= new_size_test_obj2 - 10);
    for (size_t i = 2; i < size_test_obj2; ++i) {
        ASSERT_EQ(test_obj2[i], i & 1);
    }

    test_obj2.resize(0);
    ASSERT_EQ(test_obj2.size(), 0u);
    ASSERT_FALSE(test_obj2.capacity());

    test_obj2.resize(new_size_test_obj2);

    ASSERT_EQ(test_obj2.size(), new_size_test_obj2);
    ASSERT_TRUE(test_obj2.capacity() >= new_size_test_obj2);
}

TEST(VectorBoolMethodTest, CheckSize) {
    vector_t<bool> test_obj1;

    ASSERT_FALSE(test_obj1.size());

    const size_t size_test_obj2 = 1561;
    vector_t<bool> test_obj2(size_test_obj2);

    ASSERT_EQ(test_obj2.size(), size_test_obj2);
}

TEST(VectorBoolMethodTest, CheckSwap) {
    vector_t<bool> test_obj1;

    const size_t cnt_insert_test_obj1 = 151;
    for(size_t i = 0; i < cnt_insert_test_obj1; ++i) {
        test_obj1.push_back(i & 1);
    }

    const int size_test_obj2 = 132;
    vector_t<bool> test_obj2(size_test_obj2);

    const size_t cnt_insert_test_obj2 = 65;
    for(size_t i = 0; i < cnt_insert_test_obj2; ++i) {
        test_obj2.push_back(i & 1);
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

    for(size_t i = 0; i < cnt_insert_test_obj1; ++i) {
        ASSERT_EQ(test_obj2[i], i & 1);
    }
    for(size_t i = 0; i < cnt_insert_test_obj2; ++i) {
        ASSERT_EQ(test_obj1[i], (i < size_test_obj2 ? false : ((i - size_test_obj2) & 1)));
    }

    test_obj1.swap(test_obj1);

    for(size_t i = 0; i < cnt_insert_test_obj2; ++i) {
        ASSERT_EQ(test_obj1[i], (i < size_test_obj2 ? false : ((i - size_test_obj2) & 1)));
    }
}

TEST(VectorBoolMethodTest, CheckErase) {
    vector_t<bool> test_obj1;

    ASSERT_NO_THROW(test_obj1.erase(0));
    ASSERT_TRUE(test_obj1.empty());

    const size_t size_test_obj1 = 150;
    const int value_to_fill = true;
    test_obj1.resize(size_test_obj1, value_to_fill);

    test_obj1[size_test_obj1 - 20] = !value_to_fill;
    test_obj1.erase(size_test_obj1 - 20);

    ASSERT_EQ(test_obj1[size_test_obj1 - 20], value_to_fill);
    ASSERT_EQ(test_obj1.size(), size_test_obj1 - 1);

    test_obj1[size_test_obj1 - 2] = !value_to_fill;
    test_obj1.erase(size_test_obj1 - 2);

    ASSERT_THROW(test_obj1[size_test_obj1 - 2], atom::outOfRange);
    ASSERT_EQ(test_obj1.size(), size_test_obj1 - 2);
}

TEST(VectorBoolMethodTest, CheckClear) {
    vector_t<bool> test_obj1;
    test_obj1.clear();

    ASSERT_EQ(test_obj1.size(), 0u);
    ASSERT_EQ(test_obj1.capacity(), 0u);

    const size_t count_insert = 119;
    for (size_t i = 0; i < count_insert; ++i) {
        ASSERT_NO_THROW(test_obj1.push_back(i & 1));
    }
    for (size_t i = 0; i < count_insert; ++i) {
        ASSERT_EQ(test_obj1[i], i & 1);
    }

    ASSERT_EQ(test_obj1.size(), count_insert);
    ASSERT_TRUE(test_obj1.capacity() >= count_insert);

    const size_t size_test_obj2 = 18;
    vector_t<bool> test_obj2(size_test_obj2);
    test_obj2.clear();

    ASSERT_EQ(test_obj2.size(), 0u);
    ASSERT_EQ(test_obj2.capacity(), 0u);
}

TEST(VectorBoolMethodTest, CheckIterators) {
    const size_t list_size = 129;

    vector_t<bool> test_obj1;
    for (size_t i = 0; i < list_size; ++i) {
        test_obj1.push_back(i & 1);
    }

    int i = 0;
    for (vector_t<bool>::iterator it = test_obj1.begin(); it != test_obj1.end(); ++it) {
        ASSERT_EQ(test_obj1[i++], *it);
    }

    vector_t<bool> test_obj2;

    ASSERT_THROW(test_obj2.begin(), atom::outOfRange);
    ASSERT_THROW(test_obj2.end(), atom::outOfRange);

    std::vector<int> tmp_vec(list_size);
    std::copy(test_obj1.begin(), test_obj1.end(), tmp_vec.begin());

    for (size_t j = 0; j < tmp_vec.size(); ++j) {
        ASSERT_EQ(test_obj1[j], tmp_vec[j]);
    }
}

TEST(VectorBoolMethodTest, CheckInvert) {
    vector_t<bool> test_obj1;

    int size_test_obj1 = 1123;
    for (int i = 0; i < size_test_obj1; ++i) {
        test_obj1.push_back(i & 1);
    }

    test_obj1.invert();


    for (int i = 0; i < size_test_obj1; ++i) {
        ASSERT_EQ(test_obj1[i], !(i & 1));
    }

    int size_test_obj2 = 134;
    vector_t<bool> test_obj2(size_test_obj2, true);

    int plus_size_test_obj2 = 112;
    for (int i = 0; i < plus_size_test_obj2; ++i) {
        test_obj2.push_back(i & 1);
    }

    test_obj2.invert();

    for (int i = 0; i < size_test_obj2; ++i) {
        ASSERT_EQ(test_obj2[i], false);
    }
    for (int i = 0; i < plus_size_test_obj2; ++i) {
        ASSERT_EQ(test_obj2[i + size_test_obj2], !(i & 1));
    }
}

TEST(VectorBoolMethodTest, CheckFlip) {
    int size_test_obj1 = 134;
    vector_t<bool> test_obj1(size_test_obj1, true);

    test_obj1.flip(65);
    ASSERT_EQ(test_obj1[65], false);

    test_obj1.flip(0);
    ASSERT_EQ(test_obj1[0], false);

    ASSERT_THROW(test_obj1.flip(-5), atom::outOfRange);

    vector_t<bool> test_obj2;
    ASSERT_THROW(test_obj2.flip(0), atom::outOfRange);
}

TEST(VectorBoolMethodTest, CheckSet) {
    int size_test_obj1 = 134;
    vector_t<bool> test_obj1(size_test_obj1);

    test_obj1.set(65);
    ASSERT_TRUE(test_obj1[65]);

    test_obj1.set(0);
    ASSERT_TRUE(test_obj1[0]);

    ASSERT_THROW(test_obj1.set(-5), atom::outOfRange);

    vector_t<bool> test_obj2;
    ASSERT_THROW(test_obj2.set(0), atom::outOfRange);
}

TEST(VectorBoolMethodTest, CheckReset) {
    int size_test_obj1 = 134;
    vector_t<bool> test_obj1(size_test_obj1);

    test_obj1.reset(65);
    ASSERT_FALSE(test_obj1[65]);

    test_obj1.reset(0);
    ASSERT_FALSE(test_obj1[0]);

    ASSERT_THROW(test_obj1.reset(-5), atom::outOfRange);

    vector_t<bool> test_obj2;
    ASSERT_THROW(test_obj2.reset(0), atom::outOfRange);
}

TEST(VectorBoolMethodTest, CheckCount) {
    size_t size_test_obj1 = 134;
    vector_t<bool> test_obj1(size_test_obj1, true);

    int plus_size_test_obj1 = 1123;
    for (int i = 0; i < plus_size_test_obj1; ++i) {
        test_obj1.push_back(i & 1);
    }

    ASSERT_EQ(test_obj1.count(), size_test_obj1 + plus_size_test_obj1 / 2);

    vector_t<bool> test_obj2;
    ASSERT_EQ(test_obj2.count(), 0u);
}


int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
