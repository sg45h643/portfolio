#include "../src/AbstractList.h"
#include "../src/List.h"
#include "../src/Iterator.h"

#include <assert.h>

using namespace tango;

void insertBackTest();
void constructCopyTest();
void iteratorTest();
void constIteratorTest();
void insertBeforeAfterTest();
void swapTest();

AbstractList<int>* al;

int main(int argc, char* argv[])
{
    al = new List<int>;

    insertBackTest();
    constructCopyTest();
    iteratorTest();
    constIteratorTest();
    insertBeforeAfterTest();
    swapTest();

    delete al;

    return 0;
}

void insertBackTest()
{
    assert(al->empty() == true);
    assert(al->size() == 0);

    for(int i = 0; i < 100; i++)
        al->insertBack(i);

    al->insertFront(-3);
    al->insertFront(-2);
    al->insertFront(-1);

    assert(al->empty() == false);
    assert(al->size() == 103);

    assert(al->head() == -1);
    assert(al->tail() == 99);

    al->removeFront();
    al->removeBack();

    assert(al->head() == -2);
    assert(al->tail() == 98);

    al->clear();

    assert(al->size() == 0);

    al->insertBack(23);
    al->insertFront(12);

    al->clear();

    assert(al->size() == 0);
}

void constructCopyTest()
{
    List<char> a;

    for(uint32_t i = 0; i < 250; i++)
        a.insertBack(i);

    a.insertFront(-1);
    List<char> b(a);

    assert(a.size() == b.size());
    assert(b.tail() == a.tail());
}

void iteratorTest()
{
    List<int> l;

    for(uint32_t i = 0; i < 10; i++)
        l.insertFront(i);

    for(uint32_t i = 10; i < 20; i++)
        l.insertBack(i);

    assert(l.size() == 20);

    tango::Iterator<int> it = l.begin();
    it++;
    it++;

    assert(*it == 7);

    it = l.finish();

    assert(*it == 19);

    --it;

    assert(*it == 18);

    --it;

    assert(*it == 17);
    assert(*it == 17);

    ++it;

    assert(*it == 18);

    it++;

    assert(*it == 19);

    --it;

    assert(*it == 18);

    it--;

    assert(*it == 17);

    it = l.begin();
    it += 8;

    assert(*it == 1);

    it -= 5;

    assert(*it == 6);

    it -= 3;

    assert(*it == 9);
}

void constIteratorTest()
{
    List<int> l;

    for(uint32_t i = 0; i < 50; i++)
        l.insertBack(i);

    assert(l.size() == 50);

    const List<int> cl(l);
    ConstIterator<int> it = cl.begin();
    it++;
    it++;
    it = it + 10;

    assert(*it == 12);

    it = it - 10;

    assert(*it == 2);

    --it;

    assert(*it == 1);

    it = it + 9;

    assert(*it == 10);

    it += -5;

    assert(*it == 5);

    it = it + -1;

    assert(*it == 4);
}

void insertBeforeAfterTest()
{
    List<int> l;

    for(uint32_t i = 0; i < 50; i++)
        l.insertBack(i);

    Iterator<int> it = l.begin();
    l.remove(it);

    assert(l.head() == 1);

    it = l.finish();
    l.remove(it);

    assert(l.head() == 1);
    assert(l.tail() == 48);

    it = l.begin();
    l.insertBefore(500, it);
    it = l.finish();
    l.insertAfter(1000, it);

    assert(l.head() == 500);
    assert(l.tail() == 1000);

    it = l.begin();
    l.insertAfter(600, it);
    it++;

    assert(*it == 600);

    it = l.finish();
    l.insertBefore(900, it);
    it--;

    assert(*it == 900);

    it = l.end();
    l.insertBefore(9000, it);

    assert(l.tail() == 9000);

    it = l.end();
    l.insertAfter(9000, it);

    assert(l.tail() == 9000);

    l.clear();

    for(uint32_t i = 0; i < 50; i++)
        l.insertFront(i);

    it = l.begin();
    it += 10;

    l.insertBefore(500, it);

    for(uint32_t i = 0; i < 10; i++)
        l.removeFront();

    assert(l.head() == 500);

    l.removeFront();

    assert(l.head() == 39);

    l.clear();

    for(uint32_t i = 0; i < 16; i++)
        l.insertBack(i);

    it = l.begin();
    it += 3;

    l.insertAfter(700, it);
    l.removeFront();
    l.removeFront();
    l.removeFront();

    assert(l.head() == 3);

    l.removeFront();

    assert(l.head() == 700);
}

void swapTest()
{
    List<int> l;

    for(uint32_t i = 0; i < 10; i++)
        l.insertBack(i);

    Iterator<int> it = l.begin();
    Iterator<int> it_2 = l.finish();

    it++;
    it_2--;
    l.swap(it, it_2);
    l.removeBack();
    l.removeFront();

    assert(l.head() == 8);
    assert(l.tail() == 1);

    it = l.begin();
    it_2 = l.finish();
    l.swap(it_2, it);

    assert(l.head() == 1);
    assert(l.tail() == 8);

    it = l.begin();
    it_2 = l.finish();
    it_2 -= 2;
    l.swap(it, it_2);
    l.removeBack();
    l.removeBack();

    assert(l.head() == 6);
    assert(l.tail() == 1);

    it = l.begin();
    it_2 = l.finish();
    it += 2;
    l.swap(it_2, it);
    l.removeFront();
    l.removeFront();

    assert(l.head() == 1);
    assert(l.tail() == 3);
}
