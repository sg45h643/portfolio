#include <assert.h>

#include "../src/Deque.h"
#include "../src/Iterator.h"
#include "../src/ConstIterator.h"

using namespace tango;

int main(int argc, char* argv[])
{
    Deque<int> deque;

    for(int i = 0; i < 107; i++)
        deque.push_back(i);

    Iterator<int> it = deque.begin();
    Iterator<int> it2 = deque.end();

    assert(*it == 0);

    it++;

    assert(*it == 1);

    ++it;

    assert(*it == 2);

    it2 = it;

    --it;

    assert(*it == 1);
    assert(*it2 == 2);

    it--;

    assert(*it == 0);

    it = it2 + 2;

    assert(*it == 4);

    it = 12 + it2;

    assert(*it == 14);

    it = 33 + it2;

    assert(*it == 35);

    it = it - 15;

    assert(*it == 20);

    it2 = deque.finish();
    it2 -= 50;

    assert(*it2 == 56);

    it2 += 10;

    assert(*it2 == 66);

    it2 -= 1;

    assert(*it2 == 65);

    it2 += 41;

    assert(*it2 == 106);

    it = deque.end();
    Deque<int> cdeque;

    for(int i = 0; i < 107; i++)
        cdeque.push_front(i);

    ConstIterator<int> cit = cdeque.cbegin();

    assert(*cit == 106);

    cit += 15;

    assert(*cit == 91);

    return 0;
}
