/************************************************************
 * You can use this file to test if your code is working
 * properly by designing your own test case and test code.
 * 
 * We will only be providing test cases for Lab 1.1.
 * 
 * To grade, we will compile your code and run it against 
 * our own test suite. You should design your own tests in 
 * this file to ensure that your code does what you expect.
 ************************************************************/

#include <iostream>
#include <string>

// Comment/Uncomment the .h files when you're ready to start testing
#include "sequential-list.h"
#include "doubly-linked-list.h"

// Once uncommented, you will need to modify the CMakeLists.txt
// to add the .cpp file to be able to compile again.

// Note: This may require you to "rebuild" or "Reload CMake Project"

using namespace std;


#define ASSERT_TRUE(T) \
    if (!(T))          \
        return false;
#define ASSERT_FALSE(T) \
    if ((T))            \
        return false;


string get_status_str(bool status) {
    return status ? "TEST PASSED" : "TEST FAILED";
}


class SequentialListTest {
public:
    bool test1();
    bool test2();
    bool test3();
    bool test4();
    bool test5();
    bool test6();
    bool test7();
    bool test8();
    bool test9();
    bool test10();
    bool test11();
};


class DoublyLinkedListTest{
public:
    bool test1();
    bool test2();
    bool test3();
    bool test4();
    bool test5();
    bool test6();
    bool test7();
    bool test8();
    bool test9();
    bool test10();
};

int main() {

    int grade = 0;
    SequentialListTest seq_test;

    // Some feedback about the tests.
    string seq_test_descriptions[11] = {
        "Test1: New empty list is valid",
        "Test2: insert_front() and insert_back() on zero-element list",
        "Test3: select() and search() work properly",
        "Test4: remove_front() and remove_back() on one-element list",
        "Test5: Inserting too many elements should fail",
        "Test6: insert_front() keeps moving elements forward",
        "Test7: inserting at different positions in the list",
        "Test8: try to remove too many elements, then add a few elements",
        "Test9: lots of inserts and deletes, all of them valid",
        "Test10: lots of inserts and deletes, some of them invalid",
        "Test11: replace() works properly"
    };

    bool seq_test_results[11];
    seq_test_results[0] = seq_test.test1();
    seq_test_results[1] = seq_test.test2();
    seq_test_results[2] = seq_test.test3();
    seq_test_results[3] = seq_test.test4();
    seq_test_results[4] = seq_test.test5();
    seq_test_results[5] = seq_test.test6();
    seq_test_results[6] = seq_test.test7();
    seq_test_results[7] = seq_test.test8();
    seq_test_results[8] = seq_test.test9();
    seq_test_results[9] = seq_test.test10();
    seq_test_results[10] = seq_test.test11();

    cout << "SEQUENTIAL LIST TESTING RESULTS \n";
    cout << "******************************* \n";
    for (int i = 0; i < 11; ++i) {

        cout << seq_test_descriptions[i] << endl
             << get_status_str(seq_test_results[i]) << endl;

        if (seq_test_results[i])
            grade += 4;
    }
    grade += 10;
    cout << endl
         << "Total grade: " << grade << endl << endl;


    //
    // Can put additional tests bellow.
    //

    grade = 0;
    DoublyLinkedListTest linked_test;

    string linked_test_descriptions[10] = {
            "Test1: New empty list is valid",
            "Test2: insert_front() and insert_back() on zero-element list",
            "Test3: select() and search() work properly",
            "Test4: remove_front() and remove_back() on one-element list",
            "Test5: replace() works properly",
            "Test6: insert_front() keeps moving elements forward",
            "Test7: inserting at different positions in the list",
            "Test8: try to remove too many elements, then add a few elements",
            "Test9: lots of inserts and deletes, all of them valid",
            "Test10: lots of inserts and deletes, some of them invalid"
    };

    bool linked_test_results[10];
    linked_test_results[0] = linked_test.test1();
    linked_test_results[1] = linked_test.test2();
    linked_test_results[2] = linked_test.test3();
    linked_test_results[3] = linked_test.test4();
    linked_test_results[4] = linked_test.test5();
    linked_test_results[5] = linked_test.test6();
    linked_test_results[6] = linked_test.test7();
    linked_test_results[7] = linked_test.test8();
    linked_test_results[8] = linked_test.test9();
    linked_test_results[9] = linked_test.test10();

    cout << "DOUBLY LINKED LIST TESTING RESULTS \n";
    cout << "********************************** \n";
    for (int i = 0; i < 10; ++i)
    {
        cout << linked_test_descriptions[i] << endl
             << get_status_str(linked_test_results[i]) << endl;
        if (linked_test_results[i])
            grade += 4;
    }
    grade += 10;
    cout << endl
         << "Total grade: " << grade << endl << endl;


    //
    // Can put additional tests bellow.
    //


    return 0;
}


// New empty list is valid
bool SequentialListTest::test1() {

    unsigned int capacity = 5;
    SequentialList list(capacity);

    ASSERT_TRUE(list.size() == 0)
    ASSERT_TRUE(list.capacity() == capacity)
    ASSERT_TRUE(list.empty() == true)
    ASSERT_TRUE(list.full() == false)

    return true;
}


// insert_front() and insert_back() on zero-element list
bool SequentialListTest::test2() {

    unsigned int capacity = 5;
    SequentialList list1(capacity);
    SequentialList list2(capacity);

    ASSERT_TRUE(list1.insert_front(100))
    ASSERT_TRUE(list2.insert_back(100))

    ASSERT_TRUE(list1.size() == list2.size() && list1.size() == 1)
    ASSERT_TRUE(list1.data_ != NULL)
    ASSERT_TRUE(list2.data_ != NULL)
    ASSERT_TRUE(list1.select(0) == list2.select(0) && list1.select(0) == 100)

    return true;
}


// select() and search() work properly
bool SequentialListTest::test3() {

    unsigned int capacity = 5;
    SequentialList list(capacity);

    for (unsigned int i = 0; i < capacity; i++) {
        ASSERT_TRUE(list.insert_back(i * 100))
    }

    unsigned int idx = 3;
    ASSERT_TRUE(list.search(list.select(idx)) == idx)
    ASSERT_TRUE(list.select(capacity + 1) == list.select(capacity))
    ASSERT_TRUE(list.search(1000) == list.size())

    for (unsigned int i = 0; i < capacity; i++) {
        ASSERT_TRUE(list.select(i) == i * 100 && list.data_[i] == i * 100)
    }

    return true;
}


// remove_front() and remove_back() on one-element list
bool SequentialListTest::test4() {

    unsigned int capacity = 5;
    SequentialList list1(capacity);
    SequentialList list2(capacity);

    ASSERT_TRUE(list1.insert_front(100))
    ASSERT_TRUE(list2.insert_front(100))
    ASSERT_TRUE(list1.remove_front())
    ASSERT_TRUE(list2.remove_back())

    ASSERT_TRUE(list1.size_ == list2.size_ && list1.size_ == 0)
    ASSERT_TRUE(list1.empty() == true && list2.empty() == true)

    return true;
}


// Inserting too many elements should fail
bool SequentialListTest::test5() {

    unsigned int capacity = 5;
    SequentialList list(capacity);

    // Fill up the list.
    for (unsigned int i = 0; i < capacity; i++) {
        ASSERT_TRUE(list.insert_back(i))
    }

    // Try overfilling (they should all return false with no modifications).
    int val_not_inserted = 100;
    ASSERT_FALSE(list.insert_back(val_not_inserted))
    ASSERT_FALSE(list.insert_front(val_not_inserted))
    ASSERT_FALSE(list.insert(val_not_inserted, 3))

    // Check size is correct.
    ASSERT_TRUE(list.full() == true && list.empty() == false)
    ASSERT_TRUE(list.size_ == list.capacity_ && list.capacity_ == capacity)

    return true;
}


// insert_front() keeps moving elements forward
bool SequentialListTest::test6() {

    unsigned int capacity = 5;
    SequentialList list(capacity);

    for (unsigned int i = 0; i < capacity; i++) {

        ASSERT_TRUE(list.insert_front(i))
        ASSERT_TRUE(list.size_ == (i + 1))

        for (int j = 0; j <= i; j++) {
            SequentialList::DataType expected_value = i - j;
            ASSERT_TRUE(list.data_[j] == expected_value)
        }
    }
    return true;
}


// inserting at different positions in the list succeeds
bool SequentialListTest::test7() {

    unsigned int capacity = 10;
    SequentialList list(capacity);

    for (int i = 0; i < 4; i++) {
        ASSERT_TRUE(list.insert_back(i))
    }

    ASSERT_TRUE(list.insert(4, 1))
    ASSERT_TRUE(list.insert(5, 1))
    ASSERT_TRUE(list.insert(6, 5))
    ASSERT_TRUE(list.insert(7, 7))

    // Check that the list has the right values.
    int expected_values[] = {0, 5, 4, 1, 2, 6, 3, 7};
    ASSERT_TRUE(list.size_ == 8)
    for (int i = 0; i < list.size_; i++) {
        ASSERT_TRUE(list.data_[i] == expected_values[i])
    }

    return true;
}


// try to remove too many elements, then add a few elements
bool SequentialListTest::test8() {

    unsigned int capacity = 5;
    const int num_elems = 4;
    SequentialList list(capacity);

    for (int i = 0; i < num_elems; i++) {
        ASSERT_TRUE(list.insert_back(i))
    }

    for (int i = 0; i < num_elems; i++) {
        ASSERT_TRUE(list.remove_back())
    }

    // Try a bunch of invalid commands.
    ASSERT_FALSE(list.remove_front())
    ASSERT_FALSE(list.remove_front())
    ASSERT_FALSE(list.remove(0))
    ASSERT_TRUE(list.empty() && list.size_ == 0)

    int expected_value = 1234;
    ASSERT_TRUE(list.insert(expected_value, 0))
    ASSERT_TRUE(list.data_[0] == expected_value)

    return true;
}


// lots of inserts and deletes, all of them valid
bool SequentialListTest::test9() {

    unsigned int capacity = 5;
    SequentialList list(capacity);

    ASSERT_TRUE(list.insert_back(32))
    ASSERT_TRUE(list.insert_front(44))
    ASSERT_TRUE(list.insert(12, 2))
    ASSERT_TRUE(list.remove_back())
    ASSERT_TRUE(list.remove_front())
    ASSERT_TRUE(list.insert_back(88))
    ASSERT_TRUE(list.remove(1))
    ASSERT_TRUE(list.insert(99, 0))

    // Check that the list has the right values
    ASSERT_TRUE(list.select(0) == 99 && list.data_[0] == 99)
    ASSERT_TRUE(list.select(1) == 32 && list.data_[1] == 32)

    return true;
}


// lots of inserts and deletes, some of them invalid
bool SequentialListTest::test10() {

    unsigned int capacity = 5;
    SequentialList list(capacity);

    ASSERT_FALSE(list.remove(0))
    ASSERT_TRUE(list.insert_back(32))
    ASSERT_TRUE(list.insert_front(44))
    ASSERT_FALSE(list.insert(12, 3))
    ASSERT_TRUE(list.insert(12, 2))
    ASSERT_TRUE(list.remove_back())
    ASSERT_FALSE(list.remove(5))
    ASSERT_TRUE(list.remove_front())
    ASSERT_TRUE(list.insert_back(88))
    ASSERT_FALSE(list.insert(12345, 6))
    ASSERT_TRUE(list.remove(1))
    ASSERT_TRUE(list.insert(99, 0))

    // Check that the list has the right values
    ASSERT_TRUE(list.select(0) == 99 && list.data_[0] == 99)
    ASSERT_TRUE(list.select(1) == 32 && list.data_[1] == 32)

    return true;
}

// replace() works properly
bool SequentialListTest::test11() {
    unsigned int capacity = 5;
    SequentialList list(capacity);

    ASSERT_FALSE(list.replace(0, 10))

    for (int i = 0; i < capacity; i++)
    {
        ASSERT_TRUE(list.insert_back(i * 100))
    }

    ASSERT_TRUE(list.replace(3, 30))
    ASSERT_FALSE(list.replace(5, 50))
    ASSERT_TRUE(list.replace(0, 10))
    ASSERT_TRUE(list.replace(4, 40))

    ASSERT_TRUE(list.select(3) == 30)
    ASSERT_TRUE(list.select(0) == 10)
    ASSERT_TRUE(list.select(4) == 40)

    return true;
}

//############# DoublyLinkedListTest function definitions ###########

// New empty list is valid
bool DoublyLinkedListTest::test1()
{
    DoublyLinkedList list;
    ASSERT_TRUE(list.size() == 0)
    ASSERT_TRUE(list.empty() == true)
    ASSERT_TRUE(list.full() == false)
    ASSERT_TRUE(list.head_ == NULL)
    ASSERT_TRUE(list.tail_ == NULL)
    return true;
}

// insert_front() and insert_back() on zero-element list
bool DoublyLinkedListTest::test2()
{
    DoublyLinkedList list1, list2;
    list1.insert_front(100);
    list2.insert_back(100);

    ASSERT_TRUE(list1.size() == list2.size() && list1.size() == 1)
    ASSERT_TRUE(list1.head_ != NULL && list1.head_ == list1.tail_)
    ASSERT_TRUE(list2.head_ != NULL && list2.head_ == list2.tail_)
    ASSERT_TRUE(list1.head_->prev == NULL && list1.tail_->next == NULL)
    ASSERT_TRUE(list2.head_->prev == NULL && list2.tail_->next == NULL)
    ASSERT_TRUE(list1.select(0) == list2.select(0) && list1.select(0) == 100)
    return true;
}


// select() and search() work properly
bool DoublyLinkedListTest::test3()
{
    DoublyLinkedList list;
    const int num_elems = 5;
    for (int i = 0; i < num_elems; i++)
    {
        ASSERT_TRUE(list.insert_back(i * 100))
    }

    unsigned int idx = 3;
    ASSERT_TRUE(list.search(list.select(idx)) == idx)
    ASSERT_TRUE(list.select(num_elems + 1) == 400)
    ASSERT_TRUE(list.search(1000) == list.size())

    for (int i = 0; i < num_elems; i++)
    {
        ASSERT_TRUE(list.select(i) == i * 100)
    }

    ASSERT_TRUE(list.head_->prev == NULL && list.tail_->next == NULL)

    return true;
}

bool DoublyLinkedListTest::test4() {
    DoublyLinkedList list1;
    DoublyLinkedList list2;

    ASSERT_TRUE(list1.insert_front(100))
    ASSERT_TRUE(list2.insert_front(100))
    ASSERT_TRUE(list1.remove_front())
    ASSERT_TRUE(list2.remove_back())

    ASSERT_TRUE(list1.size_ == list2.size_ && list1.size_ == 0)
    ASSERT_TRUE(list1.empty() == true && list2.empty() == true)

    return true;
}

bool DoublyLinkedListTest::test5() {
    DoublyLinkedList list;

    ASSERT_FALSE(list.replace(0, 10))

    const int num_elems = 5;
    for (int i = 0; i < num_elems; i++)
    {
        ASSERT_TRUE(list.insert_back(i * 100))
    }

    ASSERT_TRUE(list.replace(3, 30))
    ASSERT_FALSE(list.replace(5, 50))
    ASSERT_TRUE(list.replace(0, 10))
    ASSERT_TRUE(list.replace(4, 40))

    ASSERT_TRUE(list.select(3) == 30)
    ASSERT_TRUE(list.select(0) == 10)
    ASSERT_TRUE(list.select(4) == 40)

    return true;
}

bool DoublyLinkedListTest::test6() {
    DoublyLinkedList list;    // Fill up the list.

    const int num_elems = 5;
    for (unsigned int i = 0; i < num_elems; i++) {

        ASSERT_TRUE(list.insert_front(i))
        ASSERT_TRUE(list.size_ == (i + 1))

        for (int j = 0; j <= i; j++) {
            DoublyLinkedList::DataType expected_value = i - j;
            ASSERT_TRUE(list.select(j) == expected_value)
        }
    }
    return true;
}

bool DoublyLinkedListTest::test7() {
    DoublyLinkedList list;

    for (int i = 0; i < 4; i++) {
        ASSERT_TRUE(list.insert_back(i))
    }

    ASSERT_TRUE(list.insert(4, 1))
    ASSERT_TRUE(list.insert(5, 1))
    ASSERT_TRUE(list.insert(6, 5))
    ASSERT_TRUE(list.insert(7, 7))

    // Check that the list has the right values.
    int expected_values[] = {0, 5, 4, 1, 2, 6, 3, 7};
    ASSERT_TRUE(list.size_ == 8)
    for (int i = 0; i < list.size_; i++) {
        ASSERT_TRUE(list.select(i) == expected_values[i])
    }

    return true;
}

bool DoublyLinkedListTest::test8() {
    const int num_elems = 4;
    DoublyLinkedList list;

    for (int i = 0; i < num_elems; i++) {
        ASSERT_TRUE(list.insert_back(i))
    }

    for (int i = 0; i < num_elems; i++) {
        ASSERT_TRUE(list.remove_back())
    }

    // Try a bunch of invalid commands.
    ASSERT_FALSE(list.remove_front())
    ASSERT_FALSE(list.remove_front())
    ASSERT_FALSE(list.remove(0))
    ASSERT_TRUE(list.empty() && list.size_ == 0)

    int expected_value = 1234;
    ASSERT_TRUE(list.insert(expected_value, 0))
    ASSERT_TRUE(list.select(0) == expected_value)

    return true;
}

bool DoublyLinkedListTest::test9() {
    DoublyLinkedList list;

    ASSERT_TRUE(list.insert_back(32))
    ASSERT_TRUE(list.insert_front(44))
    ASSERT_TRUE(list.insert(12, 2))
    ASSERT_TRUE(list.remove_back())
    ASSERT_TRUE(list.remove_front())
    ASSERT_TRUE(list.insert_back(88))
    ASSERT_TRUE(list.remove(1))
    ASSERT_TRUE(list.insert(99, 0))

    // Check that the list has the right values
    ASSERT_TRUE(list.select(0) == 99)
    ASSERT_TRUE(list.select(1) == 32)

    return true;
}

bool DoublyLinkedListTest::test10() {
    DoublyLinkedList list;

    ASSERT_FALSE(list.remove(0))
    ASSERT_TRUE(list.insert_back(32))
    ASSERT_TRUE(list.insert_front(44))
    ASSERT_FALSE(list.insert(12, 3))
    ASSERT_TRUE(list.insert(12, 2))
    ASSERT_TRUE(list.remove_back())
    ASSERT_FALSE(list.remove(5))
    ASSERT_TRUE(list.remove_front())
    ASSERT_TRUE(list.insert_back(88))
    ASSERT_FALSE(list.insert(12345, 6))
    ASSERT_TRUE(list.remove(1))
    ASSERT_TRUE(list.insert(99, 0))

    // Check that the list has the right values
    ASSERT_TRUE(list.select(0) == 99)
    ASSERT_TRUE(list.select(1) == 32)

    return true;
}
