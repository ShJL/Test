//#define ATOM_NDEBUG
#include "array/array.h"
#include "exceptions.h"
#include <gtest/gtest.h>
#include <initializer_list>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace atom;


TEST(ArrayConstructorTest, CheckConstructor) {
    array_t<long long, 256> test_obj1;

    ASSERT_EQ(test_obj1.size(), 0u);

    const size_t size_test_obj2 = 15;
    const float value_to_fill = 13.2;
    array_t<float, 256> test_obj2(size_test_obj2, value_to_fill);

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
    array_t<int, 256> test_obj1;
    array_t<int, 256> test_obj2(test_obj1);

    ASSERT_EQ(test_obj2.size(), test_obj1.size());

    const size_t size_test_obj3 = 17;
    array_t<float, 256> test_obj3(size_test_obj3);
    for (size_t i = 0; i < size_test_obj3 - 2; ++i) {
        test_obj3[i] = -i;
    }

    array_t<float, 256> test_obj4(test_obj3);

    ASSERT_TRUE(test_obj4.capacity() == test_obj3.capacity());
    ASSERT_EQ(test_obj4.size(), test_obj3.size());

    for (size_t i = 0; i < size_test_obj3; ++i) {
        ASSERT_TRUE(test_obj4[i] == test_obj3[i]);
    }
}

TEST(ArrayConstructorTest, CheckConstructorInitializerList) {
    const size_t arr_size = 5;
    const int arr[arr_size] = {5, 77, -15, 0, 0};

    array_t<int, 10> test_obj1 = {5, 77, -15, 0, 0};

    ASSERT_EQ(test_obj1.size(), arr_size);

    for (size_t i = 0; i < arr_size; ++i) {
        ASSERT_EQ(test_obj1[i], arr[i]);
    }

    const size_t test_obj2_cap = 40;
    array_t<int, test_obj2_cap> test_obj2 = {};

    ASSERT_EQ(test_obj2.capacity(), test_obj2_cap);
    ASSERT_EQ(test_obj2.size(), 0u);
}

TEST(ArrayConstructorTest, CheckMoveConstructor) {
    array_t<int, 45> test_obj1;
    const size_t test_obj1_size = test_obj1.size();
    const size_t test_obj1_cap = test_obj1.capacity();

    array_t<int, 45> test_obj2(std::move(test_obj1));

    ASSERT_EQ(test_obj2.capacity(), test_obj1_cap);
    ASSERT_EQ(test_obj2.size(), test_obj1_size);

    const size_t size_test_obj3 = 15;
    array_t<float, 250> test_obj3(size_test_obj3);
    for (size_t i = 0; i < size_test_obj3 - 2; ++i) {
        test_obj3[i] = -i;
    }

    const size_t test_obj3_cap = test_obj3.capacity();
    const size_t test_obj3_size = test_obj3.size();

    array_t<float, 250> test_obj4(std::move(test_obj3));

    ASSERT_EQ(test_obj4.capacity(), test_obj3_cap);
    ASSERT_EQ(test_obj4.size(), test_obj3_size);

    for (size_t i = 0; i < size_test_obj3 - 2; ++i) {
        ASSERT_EQ(test_obj4[i], -i);
    }
}

TEST(ArrayOperatorTest, CheckMoveAssignment) {
    array_t<unsigned, 100> test_obj1;

    const size_t size_test_obj2 = 19;
    array_t<unsigned, 100> test_obj2(size_test_obj2);

    const size_t cnt_insert_test_obj1 = 24;
    for (size_t i = 0; i < cnt_insert_test_obj1; ++i) {
        test_obj1.push_back(i);
    }

    const size_t test_obj1_size = test_obj1.size();

    test_obj2 = std::move(test_obj1);

    ASSERT_EQ(test_obj2.size(), test_obj1_size);

    for (size_t i = 0; i < cnt_insert_test_obj1; ++i) {
        ASSERT_EQ(test_obj2[i], i);
    }
}

TEST(ArrayOperatorTest, CheckAssignment) {
    array_t<unsigned, 256> test_obj1;

    const size_t size_test_obj2 = 19;
    array_t<unsigned, 256> test_obj2(size_test_obj2);

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
    array_t<float, 256> test_obj1;

    ASSERT_ANY_THROW(test_obj1[0]);

    const size_t size_test_obj2 = 24;
    array_t<double, 256> test_obj2(size_test_obj2);

    ASSERT_ANY_THROW(test_obj2[size_test_obj2 + 1]);
    ASSERT_ANY_THROW(test_obj2[-5]);

    const int position_in_test_obj2 = 5;
    const double value_to_fill = 34;
    test_obj2[position_in_test_obj2] = value_to_fill;

    ASSERT_DOUBLE_EQ(test_obj2[position_in_test_obj2], value_to_fill);
}

TEST(ArrayMethodTest, CheckPushBack) {
    array_t<float, 256> test_obj1;

    const size_t size_test_obj1 = 14;

    for (size_t i = 0; i < size_test_obj1; ++i) {
        test_obj1.push_back(-i);
    }

    ASSERT_EQ(test_obj1.size(), size_test_obj1);

    for (size_t i = 0; i < size_test_obj1; ++i) {
        ASSERT_TRUE(test_obj1[i] == static_cast<float>(-i));
    }

    const size_t size_test_obj2 = 10;
    array_t<int, 256> test_obj2(size_test_obj2);

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
    array_t<char, 256> test_obj1;

    ASSERT_FALSE(test_obj1.size());

    const size_t size_test_obj2 = 11;
    array_t<double, 256> test_obj2(size_test_obj2);

    ASSERT_EQ(test_obj2.size(), size_test_obj2);
}

TEST(ArrayMethodTest, CheckSwap) {
    array_t<int, 256> test_obj1;

    const size_t cnt_insert_test_obj1 = 15;
    for(size_t i = 0; i < cnt_insert_test_obj1; ++i) {
        test_obj1.push_back(-i);
    }

    const int size_test_obj2 = 13;
    array_t<int, 256> test_obj2(size_test_obj2);

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
    array_t<int, 256> test_obj1;

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

TEST(ArrayMethodTest, CheckClear) {
    array_t<int, 480> test_obj1;
    test_obj1.clear();

    ASSERT_EQ(test_obj1.size(), 0u);

    const int count_insert = 119;
    for (int i = 0; i < count_insert; ++i) {
        ASSERT_NO_THROW(test_obj1.push_back(-i));
    }
    for (int i = 0; i < count_insert; ++i) {
        ASSERT_EQ(test_obj1[i], -i);
    }

    ASSERT_EQ(test_obj1.size(), static_cast<size_t>(count_insert));

    const size_t size_test_obj2 = 18;
    array_t<char, 100> test_obj2(size_test_obj2);
    test_obj2.clear();

    ASSERT_EQ(test_obj2.size(), 0u);
}

TEST(ArrayMethodTest, CheckFill) {
    const size_t size_test_obj1 = 10;
    array_t<char, 256> test_obj1(size_test_obj1);

    const char value_to_fill = 't';
    test_obj1.fill(value_to_fill);

    for (size_t i = 0; i < test_obj1.size(); ++i) {
        ASSERT_EQ(test_obj1[i], value_to_fill);
    }
}

TEST(ArrayMethodTest, CheckIterators) {
    const size_t list_size = 4;

    const size_t test_obj1_cap = 10;
    array_t<int, test_obj1_cap> test_obj1 = {5, -9, 0, 11};

    int i = 0;
    for (array_t<int, test_obj1_cap>::iterator it = test_obj1.begin(); it != test_obj1.end(); ++it) {
        ASSERT_EQ(test_obj1[i++], *it);
    }

    const size_t test_obj2_cap = 100;
    array_t<float, test_obj2_cap> test_obj2;

    int counter = 0;
    for (array_t<float, test_obj2_cap>::iterator it = test_obj2.begin(); it != test_obj2.end(); ++it) {
        ++counter;
    }

    ASSERT_EQ(counter, 0);

    std::vector<int> tmp_vec(list_size);
    std::copy(test_obj1.begin(), test_obj1.end(), tmp_vec.begin());

    for (size_t j = 0; j < tmp_vec.size(); ++j) {
        ASSERT_EQ(test_obj1[j], tmp_vec[j]);
    }
}

//-------------------------------------------------<bool>------------------------------------------------------

TEST(ArrayBoolConstructorTest, CheckConstructor) {
    array_t<bool, 2050> test_obj1;

    ASSERT_EQ(test_obj1.size(), 0u);

    const size_t size_test_obj2 = 65;
    array_t<bool, 4000> test_obj2(size_test_obj2);

    ASSERT_EQ(test_obj2.size(), size_test_obj2);

    array_t<bool, 4000> test_obj3(0);

    ASSERT_EQ(test_obj3.size(), 0u);

    const size_t size_test_obj4 = 15;
    const bool value_to_fill = true;
    array_t<bool, 4000> test_obj4(size_test_obj4, value_to_fill);

    ASSERT_EQ(test_obj4.size(), size_test_obj4);

    for (size_t i = 0; i < test_obj4.size(); ++i) {
        ASSERT_EQ(test_obj4[i], value_to_fill);
    }

    array_t<bool, 4000> test_obj5(1);
    ASSERT_EQ(test_obj5.size(), 1u);
}

TEST(ArrayBoolConstructorTest, CheckMoveConstructor) {
    array_t<bool, 4000> test_obj1;
    const size_t test_obj1_size = test_obj1.size();

    array_t<bool, 4000> test_obj2(std::move(test_obj1));

    ASSERT_EQ(test_obj2.size(), test_obj1_size);

    const size_t size_test_obj3 = 95;
    array_t<bool, 4000> test_obj3(size_test_obj3);

    for (size_t i = 0; i < size_test_obj3 - 2; ++i) {
        test_obj3[i] = i & 1;
    }

    const size_t test_obj3_cap = test_obj3.capacity();
    const size_t test_obj3_size = test_obj3.size();

    array_t<bool, 4000> test_obj4(std::move(test_obj3));

    ASSERT_EQ(test_obj4.capacity(), test_obj3_cap);
    ASSERT_EQ(test_obj4.size(), test_obj3_size);

    for (size_t i = 0; i < size_test_obj3 - 2; ++i) {
        ASSERT_EQ(test_obj4[i], i & 1);
    }
}

TEST(ArrayBoolConstructorTest, CheckCopyConstructor) {
    array_t<bool, 4000> test_obj1;
    array_t<bool, 4000> test_obj2(test_obj1);

    ASSERT_EQ(test_obj2.capacity(), 4000u);
    ASSERT_EQ(test_obj2.size(), test_obj1.size());

    const size_t size_test_obj3 = 63;
    array_t<bool, 4000> test_obj3(size_test_obj3);
    for (size_t i = 0; i < size_test_obj3 - 2; ++i) {
        test_obj3[i] = ~(i & 1) & 1;
    }

    array_t<bool, 4000> test_obj4(test_obj3);

    ASSERT_EQ(test_obj4.size(), size_test_obj3);

    for (size_t i = 0; i < size_test_obj3; ++i) {
        ASSERT_EQ(test_obj4[i], test_obj3[i]);
    }
}

TEST(ArrayBoolOperatorTest, CheckMoveAssignment) {
    array_t<bool, 4000> test_obj1;

    const size_t size_test_obj2 = 64;
    array_t<bool, 4000> test_obj2(size_test_obj2);

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

TEST(ArrayBoolOperatorTest, CheckAssignment) {
    array_t<bool, 4000> test_obj1;

    const size_t size_test_obj2 = 542;
    array_t<bool, 4000> test_obj2(size_test_obj2);

    const size_t cnt_insert_test_obj1 = 420;
    for (size_t i = 0; i < cnt_insert_test_obj1; ++i) {
        test_obj1.push_back((i >> 2) & 1);
    }

    test_obj2 = test_obj1;

    ASSERT_EQ(test_obj2.size(), test_obj1.size());

    for (size_t i = 0; i < cnt_insert_test_obj1; ++i) {
        ASSERT_EQ(test_obj1[i], test_obj2[i]);
    }
}

TEST(ArrayBoolOperatorTest, CheckOperatorAddressing) {
    array_t<bool, 4000> test_obj1;

    ASSERT_ANY_THROW(test_obj1[0]);

    const size_t size_test_obj2 = 123;
    array_t<bool, 4000> test_obj2(size_test_obj2);

    ASSERT_ANY_THROW(test_obj2[size_test_obj2 + 1]);
    ASSERT_ANY_THROW(test_obj2[-5]);

    const int position_test_obj2 = 111;
    const bool value_to_fill = true;
    test_obj2[position_test_obj2] = value_to_fill;
    ASSERT_EQ(test_obj2[position_test_obj2], value_to_fill);

    array_t<bool, 4000> test_obj3(100, true);

    test_obj3[90].operator=(false);
    test_obj3[65] = test_obj3[90];
    bool bit = test_obj3[65];

    std::cerr << test_obj3[67];

    ASSERT_EQ(test_obj3[65], false);
    ASSERT_EQ(test_obj3[90], false);
    ASSERT_EQ(bit, false);
}

TEST(ArrayBoolMethodTest, CheckPushBack) {
    array_t<bool, 4000> test_obj1;

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
    array_t<bool, 4000> test_obj2(size_test_obj2, true);

    const size_t cnt_insert_test_obj2 = 1753;

    for (size_t i = 0; i < cnt_insert_test_obj2; ++i) {
        test_obj2.push_back(~(i & 1) & 1);
    }

    ASSERT_TRUE(test_obj2.capacity() >= (cnt_insert_test_obj2 + size_test_obj2));
    ASSERT_EQ(test_obj2.size(), cnt_insert_test_obj2 + size_test_obj2);

    for (size_t i = 0; i < cnt_insert_test_obj2 + size_test_obj2; ++i) {
        ASSERT_TRUE(test_obj2[i] == (i < size_test_obj2 ? true : ~((i - size_test_obj2) & 1) & 1));
    }

    array_t<bool, 4000> test_obj3(1);
    ASSERT_EQ(test_obj3.size(), 1u);

    for (int i = 0; i < 456; ++i) {
        test_obj3.push_back(i & 1);
    }

    ASSERT_EQ(test_obj3[0], false);
    for (size_t i = 1; i < 457; ++i) {
        ASSERT_EQ(test_obj3[i], (i - 1) & 1);
    }
}

TEST(ArrayBoolMethodTest, CheckSize) {
    array_t<bool, 4000> test_obj1;

    ASSERT_FALSE(test_obj1.size());

    const size_t size_test_obj2 = 1561;
    array_t<bool, 4000> test_obj2(size_test_obj2);

    ASSERT_EQ(test_obj2.size(), size_test_obj2);
}

TEST(ArrayBoolMethodTest, CheckSwap) {
    array_t<bool, 4000> test_obj1;

    const size_t cnt_insert_test_obj1 = 151;
    for(size_t i = 0; i < cnt_insert_test_obj1; ++i) {
        test_obj1.push_back(i & 1);
    }

    const int size_test_obj2 = 132;
    array_t<bool, 4000> test_obj2(size_test_obj2);

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

TEST(ArrayBoolMethodTest, CheckErase) {
    array_t<bool, 4000> test_obj1;

    ASSERT_NO_THROW(test_obj1.erase(0));
    ASSERT_TRUE(test_obj1.empty());

    size_t size_test_obj2 = 157;
    bool value_to_fill = true;
    array_t<bool, 300> test_obj2(size_test_obj2, value_to_fill);

    test_obj2[size_test_obj2 - 30] = !value_to_fill;
    test_obj2.erase(size_test_obj2 - 30);

    ASSERT_EQ(test_obj2[size_test_obj2 - 30], value_to_fill);
    ASSERT_EQ(test_obj2.size(), size_test_obj2 - 1);

    test_obj2[size_test_obj2 - 2] = !value_to_fill;
    test_obj2.erase(size_test_obj2 - 2);

    ASSERT_THROW(test_obj2[size_test_obj2 - 2], atom::outOfRange);
    ASSERT_EQ(test_obj2.size(), size_test_obj2 - 2);
}

TEST(ArrayBoolMethodTest, CheckClear) {
    array_t<bool, 4000> test_obj1;
    test_obj1.clear();

    ASSERT_EQ(test_obj1.size(), 0u);

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
    array_t<bool, 4000> test_obj2(size_test_obj2);
    test_obj2.clear();

    ASSERT_EQ(test_obj2.size(), 0u);
}

TEST(ArrayBoolMethodTest, CheckIterators) {
    const size_t list_size = 129;

    array_t<bool, 4000> test_obj1;
    for (size_t i = 0; i < list_size; ++i) {
        test_obj1.push_back(i & 1);
    }

    int i = 0;
    for (array_t<bool, 4000>::iterator it = test_obj1.begin(); it != test_obj1.end(); ++it) {
        ASSERT_EQ(test_obj1[i++], *it);
    }

    array_t<bool, 4000> test_obj2;

    ASSERT_THROW(test_obj2.begin(), atom::outOfRange);
    ASSERT_THROW(test_obj2.end(), atom::outOfRange);

    std::vector<int> tmp_vec(list_size);
    std::copy(test_obj1.begin(), test_obj1.end(), tmp_vec.begin());

    for (size_t j = 0; j < tmp_vec.size(); ++j) {
        ASSERT_EQ(test_obj1[j], tmp_vec[j]);
    }
}

TEST(ArrayBoolMethodTest, CheckInvert) {
    array_t<bool, 4000> test_obj1;

    int size_test_obj1 = 1123;
    for (int i = 0; i < size_test_obj1; ++i) {
        test_obj1.push_back(i & 1);
    }

    test_obj1.invert();


    for (int i = 0; i < size_test_obj1; ++i) {
        ASSERT_EQ(test_obj1[i], !(i & 1));
    }

    int size_test_obj2 = 134;
    array_t<bool, 4000> test_obj2(size_test_obj2, true);

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

TEST(ArrayBoolMethodTest, CheckFlip) {
    int size_test_obj1 = 134;
    array_t<bool, 4000> test_obj1(size_test_obj1, true);

    test_obj1.flip(65);
    ASSERT_EQ(test_obj1[65], false);

    test_obj1.flip(0);
    ASSERT_EQ(test_obj1[0], false);

    ASSERT_THROW(test_obj1.flip(-5), atom::outOfRange);

    array_t<bool, 4000> test_obj2;
    ASSERT_THROW(test_obj2.flip(0), atom::outOfRange);
}

TEST(ArrayBoolMethodTest, CheckSet) {
    int size_test_obj1 = 134;
    array_t<bool, 4000> test_obj1(size_test_obj1);

    test_obj1.set(65);
    ASSERT_TRUE(test_obj1[65]);

    test_obj1.set(0);
    ASSERT_TRUE(test_obj1[0]);

    ASSERT_THROW(test_obj1.set(-5), atom::outOfRange);

    array_t<bool, 4000> test_obj2;
    ASSERT_THROW(test_obj2.set(0), atom::outOfRange);
}

TEST(ArrayBoolMethodTest, CheckReset) {
    int size_test_obj1 = 134;
    array_t<bool, 4000> test_obj1(size_test_obj1);

    test_obj1.reset(65);
    ASSERT_FALSE(test_obj1[65]);

    test_obj1.reset(0);
    ASSERT_FALSE(test_obj1[0]);

    ASSERT_THROW(test_obj1.reset(-5), atom::outOfRange);

    array_t<bool, 4000> test_obj2;
    ASSERT_THROW(test_obj2.reset(0), atom::outOfRange);
}

TEST(ArrayBoolMethodTest, CheckCount) {
    size_t size_test_obj1 = 134;
    array_t<bool, 4000> test_obj1(size_test_obj1, true);

    int plus_size_test_obj1 = 1123;
    for (int i = 0; i < plus_size_test_obj1; ++i) {
        test_obj1.push_back(i & 1);
    }

    ASSERT_EQ(test_obj1.count(), size_test_obj1 + plus_size_test_obj1 / 2);

    array_t<bool, 4000> test_obj2;
    ASSERT_EQ(test_obj2.count(), 0u);
}


int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
