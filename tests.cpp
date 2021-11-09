#include <string>
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

    Sequence<string, int> test2;

    // initially sequence should have size 0
    ASSERT_EQ(test2.size(), 0);

    test2.push_front(string("John"), 1);
    ASSERT_EQ(test2.size(), 1);

    test2.push_front(string("Mary"), 2);
    test2.push_front(string("Adam"), 3);
    ASSERT_EQ(test2.size(), 3);

    test2.pop_front();
    ASSERT_EQ(test2.size(), 2);

    test2.pop_front();
    test2.pop_front();
    ASSERT_EQ(test2.size(), 0);

    // popping from empty list should not reduce size
    test2.pop_front();
    ASSERT_EQ(test2.size(), 0);
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

    Sequence<double, string> test2;

    // popping from empty list should return false
    ASSERT_EQ(test2.pop_front(), false);

    test2.push_front(2.5,string("first"));
    test2.push_front(3.14,string("second"));
    ASSERT_EQ(test2.pop_front(), true);
    ASSERT_EQ(test2.pop_front(), true);
    ASSERT_EQ(test2.pop_front(), false);
}

TEST(Sequence, copy_constructor) {
    Sequence<string, int> *test = new Sequence<string, int>;
    test->push_front(string("a"), 1);
    test->push_front(string("b"), 2);
    test->push_front(string("c"), 3);

    Sequence<string, int> test2(*test);
    delete test;
    ASSERT_EQ(test2.size(), 3);
    ASSERT_EQ(test2.pop_front(), true);
    ASSERT_EQ(test2.size(), 2);
    ASSERT_EQ(test2.pop_front(), true);
    ASSERT_EQ(test2.size(), 1);
    ASSERT_EQ(test2.pop_front(), true);
    ASSERT_EQ(test2.size(), 0);
    ASSERT_EQ(test2.pop_front(), false);
    ASSERT_EQ(test2.size(), 0);
    ASSERT_EQ(test2.pop_front(), false);
    ASSERT_EQ(test2.size(), 0);
}

TEST(Sequence, assignment_operator) {
    Sequence<int, int> *test = new Sequence<int, int>;
    test->push_front(1, 1);
    test->push_front(1, 2);
    test->push_front(1, 3);

    Sequence<int, int> test2;
    test2 = *test;
    delete test;
    ASSERT_EQ(test2.size(), 3);
    ASSERT_EQ(test2.pop_front(), true);
    ASSERT_EQ(test2.size(), 2);
    ASSERT_EQ(test2.pop_front(), true);
    ASSERT_EQ(test2.size(), 1);
    ASSERT_EQ(test2.pop_front(), true);
    ASSERT_EQ(test2.size(), 0);
    ASSERT_EQ(test2.pop_front(), false);
    ASSERT_EQ(test2.size(), 0);
    ASSERT_EQ(test2.pop_front(), false);
    ASSERT_EQ(test2.size(), 0);
}

TEST(Sequence, get_item) {
    Sequence<int, int> test;
    test.push_front(1, 2);
    test.push_front(3, 4);
    test.push_front(5, 6);

    ASSERT_EQ(test.get_item(1).key, 5);
    ASSERT_EQ(test.get_item(1).info, 6);
    ASSERT_EQ(test.get_item(2).key, 3);
    ASSERT_EQ(test.get_item(2).info, 4);
    ASSERT_EQ(test.get_item(3).key, 1);
    ASSERT_EQ(test.get_item(3).info, 2);

    try {
        test.get_item(0);
        FAIL() << "Expected exception to be thrown for index=0";
    }
    catch(std::out_of_range const & err) {
        EXPECT_EQ(err.what(),std::string("Index out of range"));
    }
    catch(...) {
        FAIL() << "Expected Index out of range exception";
    }

    try {
        test.get_item(-10);
        FAIL() << "Expected exception to be thrown for index=-10";
    }
    catch(std::out_of_range const & err) {
        EXPECT_EQ(err.what(),std::string("Index out of range"));
    }
    catch(...) {
        FAIL() << "Expected Index out of range exception";
    }

    try {
        test.get_item(5);
        FAIL() << "Expected exception to be thrown for index > size";
    }
    catch(std::out_of_range const & err) {
        EXPECT_EQ(err.what(),std::string("Index out of range"));
    }
    catch(...) {
        FAIL() << "Expected Index out of range exception";
    }
}

int sum_int(const int &a, const int &b) {
    return a + b;
}

TEST(Sequence, join) {
    Sequence<string, int> przepis1;
    przepis1.push_front(string("lyzki cukru"), 3);
    przepis1.push_front(string("jajka"), 2);
    przepis1.push_front(string("szklanki mleka"), 2);
    przepis1.push_front(string("lyzki cukru"), 1);

    Sequence<string, int> przepis2;
    przepis2.push_front(string("szklanki mleka"), 3);
    przepis2.push_front(string("lyzki cukru"), 2);
    przepis2.push_front(string("banany"), 2);
    przepis2.push_front(string("szklanki wody"), 2);

    int (*fun_pointer)(const int&, const int&) = &sum_int;
    Sequence<string, int> output = join(przepis1, przepis2, fun_pointer);

    ASSERT_EQ(output.get_item_by_key(string("lyzki cukru")).info, 6);
    ASSERT_EQ(output.get_item_by_key(string("szklanki mleka")).info, 5);
    ASSERT_EQ(output.get_item_by_key(string("jajka")).info, 2);
    ASSERT_EQ(output.get_item_by_key(string("szklanki wody")).info, 2);
    ASSERT_EQ(output.get_item_by_key(string("banany")).info, 2);
}
