#include "gtest/gtest.h"
#include "sequence.h"


TEST(Sequence, size) {
    Sequence<int, int> test;

    // initially sequence should have size 0
    ASSERT_EQ(test.size(), 0);

    test.push_front(1, 1);
    ASSERT_EQ(test.size(), 1);

    test.push_front(1, 2);
    test.push_front(1, 3);
    ASSERT_EQ(test.size(), 3);

    test.pop_front();
    ASSERT_EQ(test.size(), 2);

    test.pop_front();
    test.pop_front();
    ASSERT_EQ(test.size(), 0);

    // popping from empty list should not reduce size
    test.pop_front();
    ASSERT_EQ(test.size(), 0);
}

TEST(Sequence, pop_front) {
    Sequence<int, int> test;

    // popping from empty list should return false
    ASSERT_EQ(test.pop_front(), false);

    test.push_front(1,1);
    test.push_front(1,2);
    ASSERT_EQ(test.pop_front(), true);
    ASSERT_EQ(test.pop_front(), true);
    ASSERT_EQ(test.pop_front(), false);
}

TEST(Sequence, copy_constructor) {}

TEST(Sequence, assignment_operator) {}
