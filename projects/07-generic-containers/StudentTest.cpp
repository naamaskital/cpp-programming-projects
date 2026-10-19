#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "Container.hpp"
#include "Stack.hpp"
#include "Queue.hpp"
#include "Algorithms.hpp"

#include <string>
#include <stdexcept>

using namespace containers;

// Container tests

TEST_CASE("Container starts empty") {
    Container<int> c;

    CHECK(c.getCount() == 0);
    CHECK(c.getCount() == 0);
    CHECK(c.isEmpty());
    CHECK(c.isEmpty());
}

TEST_CASE("Container adds one integer") {
    Container<int> c;

    c.add(10);

    CHECK(c.getCount() == 1);
    CHECK(c.get(0) == 10);
}

TEST_CASE("Container adds many integers") {
    Container<int> c;

    for (int i = 0; i < 20; i++) {
        c.add(i);
    }

    CHECK(c.getCount() == 20);
    CHECK(c.get(0) == 0);
    CHECK(c.get(19) == 19);
}

TEST_CASE("Container stores strings") {
    Container<std::string> c;

    c.add("hello");
    c.add("world");

    CHECK(c.getCount() == 2);
    CHECK(c.get(0) == "hello");
    CHECK(c.get(1) == "world");
}

TEST_CASE("Container operator square brackets works") {
    Container<int> c;

    c.add(5);
    c.add(8);

    CHECK(c[0] == 5);
    CHECK(c[1] == 8);
}

TEST_CASE("Container removes item from middle") {
    Container<int> c;

    c.add(1);
    c.add(2);
    c.add(3);

    c.removeAt(1);

    CHECK(c.getCount() == 2);
    CHECK(c.get(0) == 1);
    CHECK(c.get(1) == 3);
}

TEST_CASE("Container removes first item") {
    Container<int> c;

    c.add(1);
    c.add(2);
    c.add(3);

    c.removeAt(0);

    CHECK(c.getCount() == 2);
    CHECK(c.get(0) == 2);
    CHECK(c.get(1) == 3);
}

TEST_CASE("Container removes last item") {
    Container<int> c;

    c.add(1);
    c.add(2);
    c.add(3);

    c.removeAt(2);

    CHECK(c.getCount() == 2);
    CHECK(c.get(0) == 1);
    CHECK(c.get(1) == 2);
}

// Invalid index tests

TEST_CASE("Container invalid positive index throws") {
    Container<int> c;

    c.add(1);

    CHECK_THROWS_WITH_AS(c.get(3), "Index out of range", std::out_of_range);
}

TEST_CASE("Container invalid negative index throws") {
    Container<int> c;

    c.add(1);

    CHECK_THROWS_WITH_AS(c.get(-1), "Index out of range", std::out_of_range);
}

TEST_CASE("Container remove invalid index throws") {
    Container<int> c;

    c.add(1);

    CHECK_THROWS_WITH_AS(c.removeAt(2), "Index out of range", std::out_of_range);
}

TEST_CASE("Container clear makes it empty") {
    Container<int> c;

    c.add(1);
    c.add(2);
    c.clear();

    CHECK(c.getCount() == 0);
    CHECK(c.isEmpty());
}

// Copy behavior tests

TEST_CASE("Container copy constructor creates independent copy") {
    Container<int> first;

    first.add(1);
    first.add(2);

    Container<int> second(first);
    second[0] = 100;

    CHECK(first[0] == 1);
    CHECK(second[0] == 100);
}

TEST_CASE("Container assignment operator creates independent copy") {
    Container<int> first;
    Container<int> second;

    first.add(7);
    first.add(8);

    second = first;
    second[1] = 90;

    CHECK(first[1] == 8);
    CHECK(second[1] == 90);
}

// Iterator tests

TEST_CASE("Iterator works with manual loop") {
    Container<int> c;

    c.add(1);
    c.add(2);
    c.add(3);

    int sum = 0;

    for (Container<int>::Iterator it = c.begin(); it != c.end(); ++it) {
        sum += *it;
    }

    CHECK(sum == 6);
}

TEST_CASE("Iterator works with range based for") {
    Container<int> c;

    c.add(4);
    c.add(5);
    c.add(6);

    int sum = 0;

    for (int value : c) {
        sum += value;
    }

    CHECK(sum == 15);
}

// Stack tests

TEST_CASE("Stack starts empty") {
    Stack<int> s;

    CHECK(s.getCount() == 0);
    CHECK(s.isEmpty());
}

TEST_CASE("Stack push and top") {
    Stack<int> s;

    s.push(10);
    s.push(20);

    CHECK(s.getCount() == 2);
    CHECK(s.top() == 20);
}

TEST_CASE("Stack pop returns last value") {
    Stack<int> s;

    s.push(1);
    s.push(2);
    s.push(3);

    CHECK(s.pop() == 3);
    CHECK(s.pop() == 2);
    CHECK(s.pop() == 1);
    CHECK(s.isEmpty());
}

TEST_CASE("Stack throws when popping empty stack") {
    Stack<int> s;

    CHECK_THROWS_WITH_AS(s.pop(), "Stack is empty", std::runtime_error);
}

TEST_CASE("Stack throws when top on empty stack") {
    Stack<int> s;

    CHECK_THROWS_WITH_AS(s.top(), "Stack is empty", std::runtime_error);
}

TEST_CASE("Stack can store strings") {
    Stack<std::string> s;

    s.push("first");
    s.push("second");

    CHECK(s.pop() == "second");
    CHECK(s.pop() == "first");
}

// Queue tests

TEST_CASE("Queue starts empty") {
    Queue<int> q;

    CHECK(q.getCount() == 0);
    CHECK(q.isEmpty());
}

TEST_CASE("Queue enqueue and front") {
    Queue<int> q;

    q.enqueue(10);
    q.enqueue(20);

    CHECK(q.getCount() == 2);
    CHECK(q.front() == 10);
}

TEST_CASE("Queue dequeue returns first value") {
    Queue<int> q;

    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);

    CHECK(q.dequeue() == 1);
    CHECK(q.dequeue() == 2);
    CHECK(q.dequeue() == 3);
    CHECK(q.isEmpty());
}

TEST_CASE("Queue throws when dequeue on empty queue") {
    Queue<int> q;

    CHECK_THROWS_WITH_AS(q.dequeue(), "Queue is empty", std::runtime_error);
}

TEST_CASE("Queue throws when front on empty queue") {
    Queue<int> q;

    CHECK_THROWS_WITH_AS(q.front(), "Queue is empty", std::runtime_error);
}

TEST_CASE("Queue can store strings") {
    Queue<std::string> q;

    q.enqueue("first");
    q.enqueue("second");

    CHECK(q.dequeue() == "first");
    CHECK(q.dequeue() == "second");
}

// Algorithm tests

TEST_CASE("Algorithm count works") {
    Container<int> c;

    c.add(1);
    c.add(2);
    c.add(2);
    c.add(3);

    CHECK(count(c.begin(), c.end(), 2) == 2);
    CHECK(count(c, 2) == 2);
}

TEST_CASE("Algorithm find works when value exists") {
    Container<int> c;

    c.add(5);
    c.add(10);
    c.add(15);

    Container<int>::Iterator it = find(c.begin(), c.end(), 10);

    CHECK(it != c.end());
    CHECK(*it == 10);
}

TEST_CASE("Algorithm find returns end when value does not exist") {
    Container<int> c;

    c.add(5);
    c.add(10);

    Container<int>::Iterator it = find(c.begin(), c.end(), 100);

    CHECK(it == c.end());
}

TEST_CASE("Algorithm contains works") {
    Container<int> c;

    c.add(1);
    c.add(2);

    CHECK(contains(c.begin(), c.end(), 1));
    CHECK_FALSE(contains(c.begin(), c.end(), 9));
}

TEST_CASE("Algorithm transform changes values") {
    Container<int> c;

    c.add(1);
    c.add(2);
    c.add(3);

    transform(c.begin(), c.end(), [](int& value) {
        value *= 2;
    });

    CHECK(c.get(0) == 2);
    CHECK(c.get(1) == 4);
    CHECK(c.get(2) == 6);
}

TEST_CASE("Algorithm replace changes matching values") {
    Container<int> c;

    c.add(1);
    c.add(2);
    c.add(2);
    c.add(3);

    replace(c.begin(), c.end(), 2, 9);

    CHECK(c.get(0) == 1);
    CHECK(c.get(1) == 9);
    CHECK(c.get(2) == 9);
    CHECK(c.get(3) == 3);
}

TEST_CASE("Algorithm swapValues works") {
    int a = 3;
    int b = 8;

    swapValues(a, b);

    CHECK(a == 8);
    CHECK(b == 3);
}

// Extra container behavior tests

TEST_CASE("Container constructor with capacity") {
    Container<int> c(8);

    CHECK(c.getCount() == 0);
    CHECK(c.getCapacity() == 8);
}

TEST_CASE("Container invalid capacity throws") {
    CHECK_THROWS_AS(Container<int>(0), std::invalid_argument);
    CHECK_THROWS_AS(Container<int>(-5), std::invalid_argument);
}

TEST_CASE("Find returns index") {
    Container<int> c;

    c.add(10);
    c.add(20);
    c.add(30);

    CHECK(find(c, 10) == 0);
    CHECK(find(c, 30) == 2);
    CHECK(find(c, 99) == -1);
}

TEST_CASE("Queue back works") {
    Queue<int> q;

    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);

    CHECK(q.back() == 30);
}

TEST_CASE("Queue back throws when empty") {
    Queue<int> q;

    CHECK_THROWS_AS(q.back(), std::underflow_error);
}

// Utility algorithm tests

TEST_CASE("toString works") {
    Container<int> c;

    c.add(1);
    c.add(2);
    c.add(3);

    CHECK(toString(c) == "[1, 2, 3]");
}

TEST_CASE("reverse works") {
    Container<int> c;

    c.add(1);
    c.add(2);
    c.add(3);

    reverse(c);

    CHECK(toString(c) == "[3, 2, 1]");
}

TEST_CASE("filter works") {
    Container<int> c;

    c.add(1);
    c.add(2);
    c.add(3);
    c.add(4);

    Container<int> result = filter(c, [](const int& x) {
        return x % 2 == 0;
    });

    CHECK(toString(result) == "[2, 4]");
}

TEST_CASE("min and max throw on empty container") {
    Container<int> c;

    CHECK_THROWS_AS(min(c), std::underflow_error);
    CHECK_THROWS_AS(max(c), std::underflow_error);
}

TEST_CASE("print stack and queue format") {
    Stack<int> s;
    s.push(1);
    s.push(2);

    Queue<int> q;
    q.enqueue(10);
    q.enqueue(20);

    std::ostringstream stackOut;
    std::ostringstream queueOut;

    print(s, stackOut);
    print(q, queueOut);

    CHECK(stackOut.str() == "Stack(bottom -> top): [1, 2]");
    CHECK(queueOut.str() == "Queue(front -> back): [10, 20]");
}