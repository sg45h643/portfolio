#include <assert.h>

#include "../src/AbstractDeque.h"
#include "../src/Deque.h"
#include "../src/Iterator.h"
#include "../src/ConstIterator.h"

void atTest();
void push_backTest();
void front_back_Test();
void push_frontTest();
void pop_frontTest();
void insert_eraseTest();
void insertBack();
void swapTest();

using namespace tango;

int main(int argc, char* argv[])
{
    atTest();
    push_backTest();
    front_back_Test();
    push_frontTest();
    pop_frontTest();
    insert_eraseTest();
    swapTest();

    return 0;
}

void atTest()
{
    Deque<int> at;
    Deque<int> at2;

    for(int i = 0; i < 10; i++)
        at.push_back(i);

    assert(at[0] == 0);
    assert(at[6] == 6);
    assert(at[9] == 9);

    for(int i = 0; i < 10; i++)
        at2.push_front(i);

    at2.pop_front();
    at2.pop_front();
    at2.pop_front();
    at2.pop_front();

    assert(at2[0] == 5);

    at.clear();
    at2.clear();

    for(int i = 0; i < 1000; i++)
        at.push_back(i);

    assert(at.at(0) == 0);
    assert(at.at(555) == 555);
    assert(at.at(816) == 816);
    assert(at.at(999) == 999);

    for(int i = 0; i < 1000; i++)
        at2.push_front(i);

    for(int i = 0; i < at2.size(); i++)
        assert(999 - i == at2[i]);

    for(int i = 0; i < 500; i++)
        at2.push_back(i);

    for(int i = 0; i < 1000; i++)
        assert(999 - i == at2[i]);

    for(int i = 0; i < 500; i++)
        assert(i == at2[i + 1000]);
}

void push_backTest()
{
    Deque<int>* d_test = new Deque<int>;

    int limit = 500;

    for(int i = 0; i < limit; i++)
        d_test->push_back(i);

    for(int i = 0; i < limit; i++)
        assert(d_test->at(i) == i);

    for(int i = 0; i < limit; i++)
        d_test->pop_back();

    assert(d_test->size() == 0);

    for(int i = 0; i < limit; i++)
        d_test->push_back(i);

    for(int i = 0; i < 15; i++)
        d_test->pop_back();

    assert(d_test->at(484) == 484);

    for(int i = 0; i < 100; i++)
        d_test->pop_back();

    d_test->shrink_to_fit();

    assert(d_test->at(384) == 384);

    d_test->push_back(1000);

    assert(d_test->at(385) == 1000);

    d_test->clear();
	delete d_test;
}

void front_back_Test()
{
    Deque<int> test_one;
    test_one.push_back(5);

    assert(test_one.front() == 5);

    test_one.push_back(4);
    assert(test_one.front() == 5);
    assert(test_one.back() == 4);

    for(int i = 0; i < 219; i++)
        test_one.push_back(i);

    assert(test_one.front() == 5);
    assert(test_one.back() == 218);

    test_one.clear();

    test_one.push_back(600);

    assert(test_one.front() == 600);
    assert(test_one.back() == 600);

    test_one.push_front(9524);

    assert(test_one.front() == 9524);
    assert(test_one.back() == 600);

    test_one.clear();

    test_one.push_front(5);

    assert(test_one.front() == 5);
    assert(test_one.back() == 5);

    test_one.clear();
    test_one.push_back(10);

    assert(test_one.front() == 10);
    assert(test_one.back() == 10);

    test_one.push_back(11);
    assert(test_one.front() == 10);
    assert(test_one.back() == 11);

    test_one.push_back(12);
    test_one.pop_front();
    test_one.pop_front();

    assert(test_one.front() == 12);
    assert(test_one.back() == 12);

    Deque<int> a(9, 4);
    Deque<int> b;
    b = a;

    assert(b.size() == 9);
}

void push_frontTest()
{
    Deque<int> test_two;

    for(uint32_t i = 0; i < 10; i++)
        test_two.push_front(i);

    for(uint32_t i = 0; i < 20; i++)
        test_two.push_back(i);

    assert(test_two.at(0) == 9);
    assert(test_two.at(9) == 0);
    assert(test_two.at(10) == 0);
    assert(test_two.at(20) == 10);

    assert(test_two.front() == 9);
    assert(test_two.back() == 19);

    test_two.push_back(878);
    assert(test_two.back() == 878);

    for(uint32_t i = 0; i < 230; i++)
        test_two.push_back(i);


    assert(test_two.front() == 9);
    assert(test_two.back() == 229);

    for(uint32_t i = 0; i < 50; i++)
        test_two.push_front(i);

    assert(test_two.front() == 49);
    assert(test_two.back() == 229);

    test_two.clear();

    assert(test_two.size() == 0);

    for(uint32_t i = 0; i < 49; i++)
        test_two.push_front(i);

    for(uint32_t i = 0; i < 52; i++)
        test_two.push_back(i);

    assert(test_two.front() == 48);
    assert(test_two.back() == 51);
    assert(test_two.at(18) == 30);

    test_two.resize(10);

    assert(test_two.size() == 10);

    test_two.resize(0);

    assert(test_two.size() == 0);

    test_two.clear();
}

void pop_frontTest()
{
    Deque<int> some_test;

    for(uint32_t i = 0; i < 49; i++)
        some_test.push_front(i);

    Deque<int> test_three(some_test);

    assert(test_three.size() == 49);

    for(uint32_t i = 0; i < 9; i++)
        test_three.pop_front();

    assert(test_three[0] == 39);

    AbstractDeque<int>* d_test = new Deque<int>;

    d_test->clear();
    d_test->clear();
    d_test->shrink_to_fit();

    delete d_test;
}

void insert_eraseTest()
{
    Deque<char> test;

    for(char i = 'A'; i < 'Z'; i++)
        test.push_back(i);

    Iterator<char> it = test.begin();
    it += 10;

    test.insert(it, '^');

    assert(test.at(10) == '^');
    assert(test.at(11) == 'K');
    assert(test.at(12) == 'L');

    it = test.begin();

    test.insert(it, '>');

    assert(test.at(0) == '>');

    it = test.finish();
    test.insert(it, '@');

    assert(test.at(26) == '@');
    assert(test.at(27) == 'Y');

    it = test.end();
    test.insert(it, '/');

    assert(test.at(28) == '/');
    assert(test.size() == 29);

    Deque<float> test2;

    for(float i = 0.5; i < 800.5; i += 1.0)
        test2.push_front(i);

    for(float i = 0.5; i < 800.5; i += 1.0)
        test2.push_back(i);

    Iterator<float> it2 = test2.begin();
    test2.erase(it2);
    assert(test2.at(0) == 798.5);

    test2.clear();

    for(float i = 0.0; i < 60.0; i += 1.0)
        test2.push_back(i);

    it2 = test2.finish();
    test2.erase(it2);
    assert(test2.at(58) == 58);
    assert(test2.size() == 59);

    it2 = test2.begin();
    it2 += 9;

    test2.erase(it2);

    assert(test2.at(9) = 9.0);
    assert(test2.at(10) == 11.0);
    assert(test2.at(11) == 12.0);
}

void swapTest()
{
    Deque<int> one;
    Deque<int> two;

    for(int i = 0; i < 899; i++)
        one.push_front(i);

    two.push_back(4);

    one.swap(two);

    assert(one.size() == 1);
    assert(two.size() == 899);

    assert(one.at(0) == 4);
    assert(two.at(0) == 898);
    assert(two.at(898) == 0);
}
