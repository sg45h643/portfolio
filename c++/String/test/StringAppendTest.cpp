#include <assert.h>
#include <string.h>

#include "AbstractString.h"
#include "String.h"

using namespace tango;

int main(int argc, char* argv[])
{
    String test;

    assert(test.empty() == true);

    test.append("abcdefghij", 10);

    assert(test.empty() == false);
    assert(test.size() == 10);

    test.append("012345678910111213", 18);

    assert(test.size() == 28);

    test.append(" Ala ma kota", 12);

    String str = test.substr(33, 7);

    assert(test.size() == 40);

    test.clear();

    assert(test.size() == 0);

    test.append("qwertyuiop", 10);
    AbstractString* test2 = new String;
    test2->append(test);

    assert(test2->size() == 10);

    test2->clear();

    assert(test2->size() == 0);

    test2->append(",./;'\\[]");

    assert(test2->size() == 8);

    AbstractString* test3 = new String;
    test3->append(*test2);

    assert(test3->size() == 8);

    test3->clear();
    test3->append(str);

    assert(test3->size() == 7);

    *test2 = *test3;

    assert(test2->size() == 7);

    delete test2;
    delete test3;

    test.clear();
    test.append("-+[][][][]>", 11);
    String test4(test);

    assert(test4.size() == 11);

    test4 = test;

    assert(test4.size() == 11);

    test.clear();
    test.append("Gregory work in petrol station", 30);
    test4 = test.substr(8, 7);

    assert(test4.size() == 7);

    return 0;
}
