/*======================================================================
** You can use this file to test if your code is working
** properly by designing your own test case and test code.
** 
** You are allowed to modify this file as much as you would like.
** For grading, we will use our own filled version.
**======================================================================*/

#include <iostream>
#include <string>

#include "circular-queue.h"
#include "dynamic-stack.h"

using namespace std;

// Assert Macros for test cases.
#define ASSERT_TRUE(T) \
    if (!(T))          \
        return false;
#define ASSERT_FALSE(T) \
    if ((T))            \
        return false;

string get_status_str(bool status) {
    return status ? "PASSED" : "FAILED";
}

// Define the test suites (implementation below).
class DynamicStackTest {
private:
    bool test_result[10] = {0,0,0,0,0,0,0,0,0,0};
    string test_description[10] = {
        "Test1: new empty stack is valid",
        "Test2: push() an element on zero-element stacks",
        "Test3: peek() and pop() on one-element stack",
        "Test4: peek(), push(), and pop() work properly together",
        "Test5: push() too many elements should increase capacity",
        "Test6: push() keeps changing size and capacity",
        "Test7: pop() keeps changing size and capacity",
        "Test8: try to pop() too many elements, then push() a few elements",
        "Test9: lots of push() and pop(), all of them valid",
        "Test10: lots of push() and pop(), some of them invalid"
    };
    
public:
    string getTestDescription(int test_num);
    void runAllTests();
    void printReport();

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

class CircularQueueTest {
private:
    bool test_result[10] = {0,0,0,0,0,0,0,0,0,0};
    string test_description[10] = {
        "Test1: new empty queue is valid",
        "Test2: enqueue() an element on zero-element queues",
        "Test3: peek() and dequeue() on one-element queue",
        "Test4: peek(), enqueue(), and dequeue() work properly together",
        "Test5: enqueue() too many elements should fail",
        "Test6: enqueue() keeps changing tail",
        "Test7: dequeue() keeps changing head",
        "Test8: try to dequeue() too many elements, then enqueue() a few elements",
        "Test9: lots of enqueue() and dequeue(), all of them valid",
        "Test10: lots of enqueue() and dequeue(), some of them invalid"
    };

public:
    string getTestDescription(int test_num);
    void runAllTests();
    void printReport();

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


//======================================================================
//================================ MAIN ================================
//======================================================================
int main() {

    // The test suite has some tests implemented for you,
    // and place holders for where you can put your own.
    DynamicStackTest ds_test;

    // You can check the description for each test to see 
    // what we will be testing for with the following method.
    // Alternatively, you can also navigate to the line above 
    // where the test description is stored to read it.
    cout << ds_test.getTestDescription(1) << endl;

    // Tests can be run one at a time to get their result
    bool result = ds_test.test1();
    cout << "Test1: " << get_status_str(result) << endl << endl;

    // Or you can run all of the tests at once and generate a report.
    ds_test.runAllTests();
    ds_test.printReport();

    // Uncomment and use this for lab 2.2 when it is released.
    CircularQueueTest cq_test;
    cq_test.runAllTests();
    cq_test.printReport();

    return 0;
}


//======================================================================
//========================= Dynamic Stack Test =========================
//======================================================================
string DynamicStackTest::getTestDescription(int test_num) {
    if (test_num < 1 || test_num > 10) { // check range.
        return "";
    }
    return test_description[test_num-1];
}

void DynamicStackTest::runAllTests() {
    test_result[0] = test1();
    test_result[1] = test2();
    test_result[2] = test3();
    test_result[3] = test4();
    test_result[4] = test5();
    test_result[5] = test6();
    test_result[6] = test7();
    test_result[7] = test8();
    test_result[8] = test9();
    test_result[9] = test10();
}

void DynamicStackTest::printReport() {
    cout << "  DYNAMIC STACK TEST RESULTS  \n"
         << " ^^^^^^^^^^^^^^^^^^^^^^^^^^^^ \n";
    for (int idx = 0; idx < 10; ++idx) {
        cout << test_description[idx] << "\n  " << get_status_str(test_result[idx]) << endl << endl;
    }
    cout << endl;
}

// Test 1: new empty stack is valid
bool DynamicStackTest::test1() {

    // Test set up.
    unsigned int capacity = 5;
    DynamicStack stack(capacity);

    // Check that the internal state is set correctly.
    ASSERT_TRUE(stack.size() == 0)
    ASSERT_TRUE(stack.empty())
    ASSERT_TRUE(stack.capacity_ == capacity)
    ASSERT_TRUE(stack.init_capacity_ == capacity)
    ASSERT_FALSE(stack.items_ == nullptr) 

    // Test the default constructor for the stack.
    DynamicStack default_stack;

    // Check that the internal state is set correctly.
    ASSERT_TRUE(default_stack.size() == 0)
    ASSERT_TRUE(default_stack.empty())
    ASSERT_TRUE(default_stack.capacity_ == 16)
    ASSERT_TRUE(default_stack.init_capacity_ == 16)
    ASSERT_FALSE(default_stack.items_ == nullptr)

    // Return true to signal all tests passed.
    return true;
}

// Test 2: push() an element on zero-element stacks
bool DynamicStackTest::test2() {

    // Test set up.
    unsigned int capacity = 5;
    DynamicStack stack(capacity);

    // Try to add data to the stack (returns void so no assert check for success).
    stack.push(100);

    // Check that the internal state is correct.
    ASSERT_TRUE(stack.size() == 1)
    ASSERT_TRUE(stack.capacity_ == capacity)
    ASSERT_TRUE(stack.init_capacity_ == capacity)
    ASSERT_FALSE(stack.items_ == nullptr)
    ASSERT_TRUE(stack.items_[0] == 100)

    // Return true to signal all tests passed.
    return true;
}

// Test 3: peek() and pop() on one-element stack
bool DynamicStackTest::test3() {

    // Test set up.
    unsigned int capacity = 5;
    DynamicStack stack1(capacity);
    DynamicStack stack2(capacity);

    // Check peek on an empty stack.
    ASSERT_TRUE(stack1.peek() == DynamicStack::EMPTY_STACK)

    // Try to add data to the stacks (returns void so no assert check for success).
    stack1.push(100);
    stack2.push(200);

    // Check the state of the capacities before popping.
    ASSERT_TRUE(stack1.init_capacity_ == 5 && stack1.capacity_ == 5 && !stack1.empty() && stack1.size_ == 1)
    ASSERT_TRUE(stack2.init_capacity_ == 5 && stack2.capacity_ == 5 && !stack2.empty() && stack2.size_ == 1)

    // Peek at the top element, then remove it.
    ASSERT_TRUE(stack1.peek() == 100 && stack1.pop() == 100)
    ASSERT_TRUE(stack2.peek() == 200 && stack2.pop() == 200)

    // Check the state of the capacities after popping.
    ASSERT_TRUE(stack1.init_capacity_ == 5 && stack1.capacity_ == 5 && stack1.empty() && stack1.size_ == 0)
    ASSERT_TRUE(stack2.init_capacity_ == 5 && stack2.capacity_ == 5 && stack2.empty() && stack2.size_ == 0)

    // Check that the peek on an empty stack still gives expected value.
    ASSERT_TRUE(stack2.peek() == DynamicStack::EMPTY_STACK)

    // Return true to signal all tests passed.
    return true;
}

// Test 4: peek(), push(), and pop() work properly together
bool DynamicStackTest::test4() {
    unsigned int capacity = 5;
    DynamicStack stack(capacity);

    stack.push(10);
    ASSERT_TRUE(stack.peek() == 10 && stack.size_ == 1 && stack.capacity_ == 5 && !stack.empty());

    stack.pop();
    ASSERT_TRUE(stack.peek() == DynamicStack::EMPTY_STACK && stack.size_ == 0 && stack.capacity_ == 5 && stack.empty())

    stack.push(100);
    stack.push(200);
    ASSERT_TRUE(stack.peek() == 200 && stack.size_ == 2 && stack.capacity_ == 5 && !stack.empty());
    stack.push(300);
    ASSERT_TRUE(stack.peek() == 300 && stack.size_ == 3 && stack.capacity_ == 5 && !stack.empty());
    stack.pop();
    ASSERT_TRUE(stack.peek() == 200 && stack.size_ == 2 && stack.capacity_ == 5 && !stack.empty());
    stack.pop();
    ASSERT_TRUE(stack.peek() == 100 && stack.size_ == 1 && stack.capacity_ == 5 && !stack.empty());
    stack.pop();
    ASSERT_TRUE(stack.peek() == DynamicStack::EMPTY_STACK && stack.size_ == 0 && stack.capacity_ == 5 && stack.empty())

    return true;
}

// Test 5: push() too many elements should increase capacity
bool DynamicStackTest::test5() {
    unsigned int capacity = 5;
    DynamicStack stack(capacity);

    for (int i = 1;  i <= stack.capacity_; i++) {
        stack.push(i * 100);
    }
    ASSERT_TRUE(stack.peek() == 500 && stack.size_ == 5 && stack.capacity_ == 5 && !stack.empty())

    stack.push(600);
    ASSERT_TRUE(stack.peek() == 600 && stack.size_ == 6 && stack.capacity_ == 10 && !stack.empty())

    return true;
}

// Test 6: push() keeps changing size and capacity
bool DynamicStackTest::test6() {
    unsigned int capacity = 5;
    DynamicStack stack(capacity);

    for (int i = 1;  i <= 10; i++) {
        stack.push(i * 100);
    }
    ASSERT_TRUE(stack.peek() == 1000 && stack.size_ == 10 && stack.capacity_ == 10 && !stack.empty())

    stack.push(1100);
    ASSERT_TRUE(stack.peek() == 1100 && stack.size_ == 11 && stack.capacity_ == 20 && !stack.empty())

    for (int i = 12;  i <= stack.capacity_; i++) {
        stack.push(i * 100);
    }
    ASSERT_TRUE(stack.peek() == 2000 && stack.size_ == 20 && stack.capacity_ == 20 && !stack.empty())

    stack.push(2100);
    ASSERT_TRUE(stack.peek() == 2100 && stack.size_ == 21 && stack.capacity_ == 40 && !stack.empty())

    return true;
}

// Test 7: pop() keeps changing size and capacity
bool DynamicStackTest::test7() {
    unsigned int capacity = 4;
    DynamicStack stack(capacity);

    for (int i = 1;  i <= 5; i++) {
        stack.push(i * 100);
    }
    ASSERT_TRUE(stack.peek() == 500 && stack.size_ == 5 && stack.capacity_ == 8 && !stack.empty())
    stack.pop();
    ASSERT_TRUE(stack.peek() == 400 && stack.size_ == 4 && stack.capacity_ == 8 && !stack.empty())
    stack.pop();
    ASSERT_TRUE(stack.peek() == 300 && stack.size_ == 3 && stack.capacity_ == 8 && !stack.empty())
    stack.pop();
    ASSERT_TRUE(stack.peek() == 200 && stack.size_ == 2 && stack.capacity_ == 4 && !stack.empty())
    stack.pop();
    ASSERT_TRUE(stack.peek() == 100 && stack.size_ == 1 && stack.capacity_ == 4 && !stack.empty())

    return true;
}

// Test 8: try to pop() too many elements, then push() a few elements
bool DynamicStackTest::test8() {
    unsigned int capacity = 4;
    DynamicStack stack(capacity);

    for (int i = 1;  i <= 4; i++) {
        stack.push(i * 100);
    }

    for (int i = 1;  i <= 3; i++) {
        stack.pop();
    }
    ASSERT_TRUE(stack.peek() == 100 && stack.size_ == 1 && stack.capacity_ == 4 && !stack.empty())

    stack.pop();
    ASSERT_TRUE(stack.peek() == DynamicStack::EMPTY_STACK && stack.size_ == 0 && stack.capacity_ == 4 &&stack.empty())
    stack.pop();
    ASSERT_TRUE(stack.peek() == DynamicStack::EMPTY_STACK && stack.size_ == 0 && stack.capacity_ == 4 &&stack.empty())

    return true;
}

// Test 9: lots of push() and pop(), all of them valid
bool DynamicStackTest::test9() {
    unsigned int capacity = 5;
    DynamicStack stack(capacity);

    for (int i = 1; i <= 6; i++) {
        stack.push(i * 100);
    }
    ASSERT_TRUE(stack.peek() == 600 && stack.size_ == 6 && stack.capacity_ == 10 && !stack.empty())

    stack.pop();
    stack.pop();
    ASSERT_TRUE(stack.peek() == 400 && stack.size_ == 4 && stack.capacity_ == 10 && !stack.empty())
    stack.pop();
    stack.pop();
    ASSERT_TRUE(stack.peek() == 200 && stack.size_ == 2 && stack.capacity_ == 5 && !stack.empty())

    for (int i = 3; i <= 11; i++) {
        stack.push(i * 100);
    }
    ASSERT_TRUE(stack.peek() == 1100 && stack.size_ == 11 && stack.capacity_ == 20 && !stack.empty())

    for (int i = 1; i <= 6; i++) {
        stack.pop();
    }
    ASSERT_TRUE(stack.peek() == 500 && stack.size_ == 5 && stack.capacity_ == 10 && !stack.empty())


    return true;
}

// Test 10: lots of push() and pop(), some of them invalid
bool DynamicStackTest::test10() {
    unsigned int capacity = 3;
    DynamicStack stack(capacity);

    for (int i = 1; i <= 4; i++) {
        stack.push(i * 100);
    }
    ASSERT_TRUE(stack.peek() == 400 && stack.size_ == 4 && stack.capacity_ == 6 && !stack.empty())

    for (int i = 1; i <= 3; i++) {
        stack.pop();
    }
    ASSERT_TRUE(stack.peek() == 100 && stack.size_ == 1 && stack.capacity_ == 3 && !stack.empty())

    stack.pop();
    ASSERT_TRUE(stack.peek() == DynamicStack::EMPTY_STACK && stack.size_ == 0 && stack.capacity_ == 3 && stack.empty())
    stack.push(100);
    ASSERT_TRUE(stack.peek() == 100 && stack.size_ == 1 && stack.capacity_ == 3 && !stack.empty())
    stack.pop();
    ASSERT_TRUE(stack.peek() == DynamicStack::EMPTY_STACK && stack.size_ == 0 && stack.capacity_ == 3 && stack.empty())

    return true;
}


//======================================================================
//======================== Circular Queue Test =========================
//======================================================================
string CircularQueueTest::getTestDescription(int test_num) {
    if (test_num < 1 || test_num > 10) { // check range.
        return "";
    }
    return test_description[test_num-1];
}

void CircularQueueTest::runAllTests() {
    test_result[0] = test1();
    test_result[1] = test2();
    test_result[2] = test3();
    test_result[3] = test4();
    test_result[4] = test5();
    test_result[5] = test6();
    test_result[6] = test7();
    test_result[7] = test8();
    test_result[8] = test9();
    test_result[9] = test10();
}

void CircularQueueTest::printReport() {
    cout << "  CIRCULAR QUEUE TEST RESULTS  \n"
         << " ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ \n";
    for (int idx = 0; idx < 10; ++idx) {
        cout << test_description[idx] << "\n  " << get_status_str(test_result[idx]) << endl << endl;
    }
    cout << endl;
}

// Test 1: new empty queue is valid
bool CircularQueueTest::test1() {

    // Test set up.
    unsigned int capacity = 5;
    CircularQueue queue(capacity);

    // Check that the internal state is set correctly.
    ASSERT_TRUE(queue.size() == 0)
    ASSERT_TRUE(queue.empty())
    ASSERT_FALSE(queue.full())
    ASSERT_TRUE(queue.capacity_ == capacity)
    ASSERT_FALSE(queue.items_ == nullptr)
    ASSERT_TRUE(queue.head_ == 0 && queue.tail_ == 0)

    // Test the default constructor for the queue.
    CircularQueue default_queue;

    // Check that the internal state is set correctly.
    ASSERT_TRUE(default_queue.size() == 0)
    ASSERT_TRUE(default_queue.empty())
    ASSERT_FALSE(default_queue.full())
    ASSERT_TRUE(default_queue.capacity_ == 16)
    ASSERT_FALSE(default_queue.items_ == nullptr)
    ASSERT_TRUE(default_queue.head_ == 0 && default_queue.tail_ == 0)

    // Return true to signal all tests passed.
    return true;
}

// Test 2: enqueue() an element on zero-element queues
bool CircularQueueTest::test2() {
    
    // Test set up.
    unsigned int capacity = 5;
    CircularQueue queue1(capacity);
    CircularQueue queue2(capacity);

    // Try to enqueue data to the queues.
    ASSERT_TRUE(queue1.enqueue(100))
    ASSERT_TRUE(queue2.enqueue(100))

    // Check that the internal state is correct.
    ASSERT_TRUE(queue1.size() == queue2.size() && queue1.size() == 1)
    ASSERT_FALSE(queue1.items_ == nullptr)
    ASSERT_FALSE(queue2.items_ == nullptr)
    ASSERT_TRUE(queue1.items_[queue1.head_] == 100)
    ASSERT_TRUE(queue2.items_[queue2.head_] == 100)
    ASSERT_TRUE(queue1.head_ == 0 && queue1.tail_ == 1)
    ASSERT_TRUE(queue2.head_ == 0 && queue2.tail_ == 1)

    // Return true to signal all tests passed.
    return true;
}

// Test 3: peek() and dequeue() on one-element queue
bool CircularQueueTest::test3() {

    // Test set up.
    unsigned int capacity = 5;
    CircularQueue queue1(capacity);
    CircularQueue queue2(capacity);

    // Check peek on an empty queue.
    ASSERT_TRUE(queue1.peek() == CircularQueue::EMPTY_QUEUE)

    // Add data to the queues.
    ASSERT_TRUE(queue1.enqueue(100))
    ASSERT_TRUE(queue2.enqueue(200))

    // Peek at the top element, then remove it.
    ASSERT_TRUE(queue1.peek() == 100 && queue1.dequeue() == 100)
    ASSERT_TRUE(queue2.peek() == 200 && queue2.dequeue() == 200)

    // Check the resulting sizes of the queues.
    ASSERT_TRUE(queue1.size_ == queue2.size_ && queue1.size_ == 0)
    ASSERT_TRUE(queue1.empty() && queue2.empty())

    // Check that the peek on an empty queue still gives expected value.
    ASSERT_TRUE(queue2.peek() == CircularQueue::EMPTY_QUEUE)

    // Return true to signal all tests passed.
    return true;
}

// Test 4: peek(), enqueue(), and dequeue() work properly together
bool CircularQueueTest::test4() {
    unsigned int capacity = 5;
    CircularQueue queue(capacity);

    queue.enqueue(10);
    ASSERT_TRUE(queue.peek() == 10 && queue.size_ == 1 && queue.capacity_ == 5 && !queue.empty() && !queue.full() && queue.head_ == 0 && queue.tail_ == 1);
    queue.dequeue();
    ASSERT_TRUE(queue.peek() == CircularQueue::EMPTY_QUEUE && queue.size_ == 0 && queue.capacity_ == 5 && queue.empty() && !queue.full() && queue.head_ == 1 && queue.tail_ == 1);

    queue.enqueue(100);
    queue.enqueue(200);
    ASSERT_TRUE(queue.peek() == 100 && queue.size_ == 2 && queue.capacity_ == 5 && !queue.empty() && !queue.full() && queue.head_ == 1 && queue.tail_ == 3);
    queue.enqueue(300);
    ASSERT_TRUE(queue.peek() == 100 && queue.size_ == 3 && queue.capacity_ == 5 && !queue.empty() && !queue.full() && queue.head_ == 1 && queue.tail_ == 4);
    queue.dequeue();
    ASSERT_TRUE(queue.peek() == 200 && queue.size_ == 2 && queue.capacity_ == 5 && !queue.empty() && !queue.full() && queue.head_ == 2 && queue.tail_ == 4);
    queue.dequeue();
    ASSERT_TRUE(queue.peek() == 300 && queue.size_ == 1 && queue.capacity_ == 5 && !queue.empty() && !queue.full() && queue.head_ == 3 && queue.tail_ == 4);
    queue.dequeue();
    ASSERT_TRUE(queue.peek() == CircularQueue::EMPTY_QUEUE && queue.size_ == 0 && queue.capacity_ == 5 && queue.empty() && !queue.full() && queue.head_ == 4 && queue.tail_ == 4);

    return true;
}

// Test 5: enqueue() too many elements should fail
bool CircularQueueTest::test5() {
    unsigned int capacity = 5;
    CircularQueue queue(capacity);

    for (int i = 1;  i <= queue.capacity_; i++) {
        queue.enqueue(i * 100);
    }
    ASSERT_TRUE(queue.peek() == 100 && queue.size_ == 5 && queue.capacity_ == 5 && !queue.empty() && queue.full() && queue.head_ == 0 && queue.tail_ == 0)

    queue.enqueue(600);
    ASSERT_FALSE(queue.enqueue(600))

    return true;
}

// Test 6: enqueue() keeps changing tail
bool CircularQueueTest::test6() {
    unsigned int capacity = 5;
    CircularQueue queue(capacity);

    for (int i = 1;  i <= 4 ; i++) {
        queue.enqueue(i * 100);
    }
    ASSERT_TRUE(queue.peek() == 100 && queue.size_ == 4 && queue.capacity_ == 5 && !queue.empty() && !queue.full() && queue.head_ == 0 && queue.tail_ == 4);

    queue.enqueue(500);
    ASSERT_TRUE(queue.peek() == 100 && queue.size_ == 5 && queue.capacity_ == 5 && !queue.empty() && queue.full() && queue.head_ == 0 && queue.tail_ == 0);

    queue.dequeue();
    ASSERT_TRUE(queue.peek() == 200 && queue.size_ == 4 && queue.capacity_ == 5 && !queue.empty() && !queue.full() && queue.head_ == 1 && queue.tail_ == 0);

    queue.enqueue(600);
    ASSERT_TRUE(queue.peek() == 200 && queue.size_ == 5 && queue.capacity_ == 5 && !queue.empty() && queue.full() && queue.head_ == 1 && queue.tail_ == 1);

    return true;
}

// Test 7: dequeue() keeps changing head
bool CircularQueueTest::test7() {
    unsigned int capacity = 4;
    CircularQueue queue(capacity);

    for (int i = 1;  i <= 4; i++) {
        queue.enqueue(i * 100);
    }
    ASSERT_TRUE(queue.peek() == 100 && queue.size_ == 4 && queue.capacity_ == 4 && !queue.empty() && queue.full() && queue.head_ == 0 && queue.tail_ == 0);
    queue.dequeue();
    ASSERT_TRUE(queue.peek() == 200 && queue.size_ == 3 && queue.capacity_ == 4 && !queue.empty() && !queue.full() && queue.head_ == 1 && queue.tail_ == 0);
    queue.dequeue();
    ASSERT_TRUE(queue.peek() == 300 && queue.size_ == 2 && queue.capacity_ == 4 && !queue.empty() && !queue.full() && queue.head_ == 2 && queue.tail_ == 0);
    queue.enqueue(500);
    ASSERT_TRUE(queue.peek() == 300 && queue.size_ == 3 && queue.capacity_ == 4 && !queue.empty() && !queue.full() && queue.head_ == 2 && queue.tail_ == 1);
    queue.dequeue();
    ASSERT_TRUE(queue.peek() == 400 && queue.size_ == 2 && queue.capacity_ == 4 && !queue.empty() && !queue.full() && queue.head_ == 3 && queue.tail_ == 1);
    queue.dequeue();
    ASSERT_TRUE(queue.peek() == 500 && queue.size_ == 1 && queue.capacity_ == 4 && !queue.empty() && !queue.full() && queue.head_ == 0 && queue.tail_ == 1);
    queue.dequeue();
    ASSERT_TRUE(queue.peek() == CircularQueue::EMPTY_QUEUE && queue.size_ == 0 && queue.capacity_ == 4 && queue.empty() && !queue.full() && queue.head_ == 1 && queue.tail_ == 1);

    return true;
}

// Test 8: try to dequeue() too many elements, then enqueue() a few elements
bool CircularQueueTest::test8() {
    unsigned int capacity = 4;
    CircularQueue queue(capacity);

    ASSERT_TRUE(queue.peek() == CircularQueue::EMPTY_QUEUE && queue.size_ == 0 && queue.capacity_ == 4 && queue.empty() && !queue.full() && queue.head_ == 0 && queue.tail_ == 0);
    ASSERT_TRUE(queue.dequeue() == CircularQueue::EMPTY_QUEUE)
    queue.enqueue(100);
    ASSERT_TRUE(queue.peek() == 100 && queue.size_ == 1 && queue.capacity_ == 4 && !queue.empty() && !queue.full() && queue.head_ == 0 && queue.tail_ == 1);
    queue.enqueue(200);
    ASSERT_TRUE(queue.peek() == 100 && queue.size_ == 2 && queue.capacity_ == 4 && !queue.empty() && !queue.full() && queue.head_ == 0 && queue.tail_ == 2);
    queue.dequeue();
    ASSERT_TRUE(queue.peek() == 200 && queue.size_ == 1 && queue.capacity_ == 4 && !queue.empty() && !queue.full() && queue.head_ == 1 && queue.tail_ == 2);
    queue.dequeue();
    ASSERT_TRUE(queue.peek() == CircularQueue::EMPTY_QUEUE && queue.size_ == 0 && queue.capacity_ == 4 && queue.empty() && !queue.full() && queue.head_ == 2 && queue.tail_ == 2);
    ASSERT_TRUE(queue.dequeue() == CircularQueue::EMPTY_QUEUE)
    queue.enqueue(100);
    ASSERT_TRUE(queue.peek() == 100 && queue.size_ == 1 && queue.capacity_ == 4 && !queue.empty() && !queue.full() && queue.head_ == 2 && queue.tail_ == 3);
    queue.enqueue(200);
    ASSERT_TRUE(queue.peek() == 100 && queue.size_ == 2 && queue.capacity_ == 4 && !queue.empty() && !queue.full() && queue.head_ == 2 && queue.tail_ == 0);

    return true;
}

// Test 9: lots of enqueue() and dequeue(), all of them valid
bool CircularQueueTest::test9() {
    unsigned int capacity = 5;
    CircularQueue queue(capacity);

    for (int i = 1; i <= 5; i++) {
        queue.enqueue(i * 100);
    }
    ASSERT_TRUE(queue.peek() == 100 && queue.size_ == 5 && queue.capacity_ == 5 && !queue.empty() && queue.full() && queue.head_ == 0 && queue.tail_ == 0);

    queue.dequeue();
    queue.dequeue();
    ASSERT_TRUE(queue.peek() == 300 && queue.size_ == 3 && queue.capacity_ == 5 && !queue.empty() && !queue.full() && queue.head_ == 2 && queue.tail_ == 0);
    queue.dequeue();
    queue.dequeue();
    ASSERT_TRUE(queue.peek() == 500 && queue.size_ == 1 && queue.capacity_ == 5 && !queue.empty() && !queue.full() && queue.head_ == 4 && queue.tail_ == 0);

    for (int i = 6; i <= 9; i++) {
        queue.enqueue(i * 100);
    }
    ASSERT_TRUE(queue.peek() == 500 && queue.size_ == 5 && queue.capacity_ == 5 && !queue.empty() && queue.full() && queue.head_ == 4 && queue.tail_ == 4);

    for (int i = 1; i <= 4; i++) {
        queue.dequeue();
    }
    ASSERT_TRUE(queue.peek() == 900 && queue.size_ == 1 && queue.capacity_ == 5 && !queue.empty() && !queue.full() && queue.head_ == 3 && queue.tail_ == 4);

    return true;
}

// Test 10: lots of enqueue() and dequeue(), some of them invalid
bool CircularQueueTest::test10() {
    unsigned int capacity = 3;
    CircularQueue queue(capacity);

    for (int i = 1; i <= 3; i++) {
        queue.enqueue(i * 100);
    }
    ASSERT_TRUE(queue.peek() == 100 && queue.size_ == 3 && queue.capacity_ == 3 && !queue.empty() && queue.full() && queue.head_ == 0 && queue.tail_ == 0);
    ASSERT_FALSE(queue.enqueue(400))
    ASSERT_FALSE(queue.enqueue(500))

    for (int i = 1; i <= 2; i++) {
        queue.dequeue();
    }
    ASSERT_TRUE(queue.peek() == 300 && queue.size_ == 1 && queue.capacity_ == 3 && !queue.empty() && !queue.full() && queue.head_ == 2 && queue.tail_ == 0);
    queue.dequeue();
    ASSERT_TRUE(queue.peek() == CircularQueue::EMPTY_QUEUE && queue.size_ == 0 && queue.capacity_ == 3 && queue.empty() && !queue.full() && queue.head_ == 0 && queue.tail_ == 0);
    queue.dequeue();
    ASSERT_TRUE(queue.peek() == CircularQueue::EMPTY_QUEUE && queue.size_ == 0 && queue.capacity_ == 3 && queue.empty() && !queue.full() && queue.head_ == 0 && queue.tail_ == 0);

    queue.enqueue(100);
    ASSERT_TRUE(queue.peek() == 100 && queue.size_ == 1 && queue.capacity_ == 3 && !queue.empty() && !queue.full() && queue.head_ == 0 && queue.tail_ == 1);
    queue.dequeue();
    ASSERT_TRUE(queue.peek() == CircularQueue::EMPTY_QUEUE && queue.size_ == 0 && queue.capacity_ == 3 && queue.empty() && !queue.full() && queue.head_ == 1 && queue.tail_ == 1);

    return true;
}
