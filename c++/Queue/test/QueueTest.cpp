#include "../src/abstract_queue.h"
#include "../src/queue.h"

#include <assert.h>

using namespace tango;

void test()
{
    AbstractQueue<int>* q = new Queue<int>;

    for(int i = 0; i < 601; i++)
        q->insert(i);

    assert(q->head() == 0);
    assert(q->tail() == 600);
    assert(q->size() == 601);

    q->clear();
    q->clear();
    q->clear();

    for(int i = 0; i < 601; i++)
        q->insert(i);

    assert(q->head() == 0);
    assert(q->tail() == 600);
    assert(q->size() == 601);

    q->remove();
    q->remove();
    q->remove();

    assert(q->size() == 598);
    assert(q->head() == 3);

    delete q;
}

int main(int argc, char* argv[])
{
    test();

    return 0;
}
