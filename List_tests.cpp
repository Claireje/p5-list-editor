#include "List.hpp"
#include "unit_test_framework.hpp"

using namespace std;

//empty/size

TEST(test_empty_default) {
    List<int> l;
    ASSERT_TRUE(l.empty());
    ASSERT_EQUAL(l.size(), 0);
}

TEST(test_empty_false_after_push) {
    List<int> l;
    l.push_back(1);
    ASSERT_FALSE(l.empty());
    ASSERT_EQUAL(l.size(), 1);
}

//push_front/push_back/front/back

TEST(test_push_back_1) {
    List<int> l;
    l.push_back(42);
    ASSERT_EQUAL(l.front(), 42);
    ASSERT_EQUAL(l.back(), 42);
}

TEST(test_push_front_1) {
    List<int> l;
    l.push_front(7);
    ASSERT_EQUAL(l.front(), 7);
    ASSERT_EQUAL(l.back(), 7);
}

TEST(test_push_back_multiple) {
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    ASSERT_EQUAL(l.front(), 1);
    ASSERT_EQUAL(l.back(), 3);
    ASSERT_EQUAL(l.size(), 3);
}

TEST(test_push_front_multiple) {
    List<int> l;
    l.push_front(3);
    l.push_front(2);
    l.push_front(1);
    ASSERT_EQUAL(l.front(), 1);
    ASSERT_EQUAL(l.back(), 3);
    ASSERT_EQUAL(l.size(), 3);
}

TEST(test_push_front_back) {
    List<int> l;
    l.push_back(2);
    l.push_front(1);
    l.push_back(3);
    ASSERT_EQUAL(l.front(), 1);
    ASSERT_EQUAL(l.back(), 3);
    ASSERT_EQUAL(l.size(), 3);
}

//pop_front/pop_back

TEST(test_pop_front) {
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.pop_front();
    ASSERT_EQUAL(l.front(), 2);
    ASSERT_EQUAL(l.size(), 2);
}

TEST(test_pop_back) {
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.pop_back();
    ASSERT_EQUAL(l.back(), 2);
    ASSERT_EQUAL(l.size(), 2);
}

TEST(test_pop_front_empty) {
    List<int> l;
    l.push_back(5);
    l.push_back(10);
    l.pop_front();
    l.pop_front();
    ASSERT_TRUE(l.empty());
    ASSERT_EQUAL(l.size(), 0);
}

TEST(test_pop_back_empty) {
    List<int> l;
    l.push_back(10);
    l.push_back(5);
    l.pop_back();
    l.pop_back();
    ASSERT_TRUE(l.empty());
    ASSERT_EQUAL(l.size(), 0);
}

TEST(test_pop_single) {
    List<int> l;
    l.push_back(5);
    l.pop_front();
    ASSERT_TRUE(l.empty());
}

//clear

TEST(test_clear) {
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.clear();
    ASSERT_TRUE(l.empty());
    ASSERT_EQUAL(l.size(), 0);
}

TEST(test_clear_push) {
    List<int> l;
    l.push_back(1);
    l.clear();
    l.push_back(28);
    ASSERT_EQUAL(l.front(), 28);
    ASSERT_EQUAL(l.size(), 1);
}

//copy constructor/assignment operator

TEST(test_copy_constructor) {
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    List<int> copy(l);
    ASSERT_EQUAL(copy.size(), 3);
    ASSERT_EQUAL(copy.front(), 1);
    ASSERT_EQUAL(copy.back(), 3);
}

TEST(test_copy_constructor_independence) {
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    List<int> copy(l);
    copy.push_back(3);
    ASSERT_EQUAL(l.size(), 2);
    ASSERT_EQUAL(copy.size(), 3);
}

TEST(test_assignment_operator) {
    List<int> l;
    l.push_back(10);
    l.push_back(20);
    List<int> other;
    other.push_back(99);
    other = l;
    ASSERT_EQUAL(other.size(), 2);
    ASSERT_EQUAL(other.front(), 10);
    ASSERT_EQUAL(other.back(), 20);
}

TEST(test_assignment_self) {
    List<int> l;
    l.push_back(5);
    List<int> &ref = l;
    l = ref;
    ASSERT_EQUAL(l.size(), 1);
    ASSERT_EQUAL(l.front(), 5);
}

TEST(test_copy_empty) {
    List<int> l;
    List<int> copy(l);
    ASSERT_TRUE(copy.empty());
}

//iterators: begin / end / ++ / * / ==/ !=

TEST(test_iterator_begin_end_empty) {
    List<int> l;
    ASSERT_TRUE(l.begin() == l.end());
}

TEST(test_iterator_deref) {
    List<int> l;
    l.push_back(42);
    ASSERT_EQUAL(*l.begin(), 42);
}

TEST(test_iterator_traverse) {
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    int expected = 1;
    for (auto it = l.begin(); it != l.end(); ++it) {
        ASSERT_EQUAL(*it, expected++);
    }
    ASSERT_EQUAL(expected, 4);
}

TEST(test_iterator_postfix_increment) {
    List<int> l;
    l.push_back(10);
    l.push_back(20);
    auto it = l.begin();
    auto old = it++;
    ASSERT_EQUAL(*old, 10);
    ASSERT_EQUAL(*it, 20);
}

TEST(test_iterator_decrement_from_end) {
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    auto it = l.end();
    --it;
    ASSERT_EQUAL(*it, 3);
}

TEST(test_iterator_decrement_traverse) {
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    auto it = l.end();
    --it; 
    ASSERT_EQUAL(*it, 3);
    --it; 
    ASSERT_EQUAL(*it, 2);
    --it; 
    ASSERT_EQUAL(*it, 1);
    ASSERT_TRUE(it == l.begin());
}

TEST(test_default_iterator_equality) {
    List<int>::Iterator a;
    List<int>::Iterator b;
    ASSERT_TRUE(a == b);
}

TEST(test_default_iterator_not_equal_to_list_end) {
    List<int> l;
    List<int>::Iterator def;
    ASSERT_TRUE(def != l.end());
}

//insert/erase

TEST(test_insert_end) {
    List<int> l;
    l.push_back(1);
    l.push_back(3);
    auto it = l.end();
    l.insert(it, 4);
    ASSERT_EQUAL(l.back(), 4);
    ASSERT_EQUAL(l.size(), 3);
}

TEST(test_insert_start) {
    List<int> l;
    l.push_back(2);
    l.push_back(3);
    l.insert(l.begin(), 1);
    ASSERT_EQUAL(l.front(), 1);
    ASSERT_EQUAL(l.size(), 3);
}

TEST(test_insert_middle) {
    List<int> l;
    l.push_back(1);
    l.push_back(3);
    auto it = l.begin();
    ++it; // points to 3
    l.insert(it, 2);
    it = l.begin();
    ASSERT_EQUAL(*it, 1); 
    ++it;
    ASSERT_EQUAL(*it, 2); 
    ++it;
    ASSERT_EQUAL(*it, 3);
    ASSERT_EQUAL(l.size(), 3);
}

TEST(test_insert_returns_correct_iterator) {
    List<int> l;
    l.push_back(1);
    l.push_back(3);
    auto it = l.begin(); 
    ++it;
    auto inserted = l.insert(it, 2);
    ASSERT_EQUAL(*inserted, 2);
}

TEST(test_erase_front) {
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    auto it = l.erase(l.begin());
    ASSERT_EQUAL(l.front(), 2);
    ASSERT_EQUAL(*it, 2);
    ASSERT_EQUAL(l.size(), 2);
}

TEST(test_erase_back) {
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    auto it = l.end(); 
    --it;
    it = l.erase(it);
    ASSERT_TRUE(it == l.end());
    ASSERT_EQUAL(l.back(), 2);
    ASSERT_EQUAL(l.size(), 2);
}

TEST(test_erase_middle) {
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    auto it = l.begin(); 
    ++it; // points to 2
    it = l.erase(it);
    ASSERT_EQUAL(*it, 3);
    ASSERT_EQUAL(l.size(), 2);
    ASSERT_EQUAL(l.front(), 1);
    ASSERT_EQUAL(l.back(), 3);
}

TEST(test_erase_single) {
    List<int> l;
    l.push_back(42);
    l.erase(l.begin());
    ASSERT_TRUE(l.empty());
}

//size tracking

TEST(test_size_tracking) {
    List<int> l;
    ASSERT_EQUAL(l.size(), 0);
    l.push_back(1); ASSERT_EQUAL(l.size(), 1);
    l.push_front(0); ASSERT_EQUAL(l.size(), 2);
    l.pop_back(); ASSERT_EQUAL(l.size(), 1);
    l.pop_front(); ASSERT_EQUAL(l.size(), 0);
    ASSERT_TRUE(l.empty());
}

TEST_MAIN()
