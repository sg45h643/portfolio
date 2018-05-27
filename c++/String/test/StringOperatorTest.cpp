#include <assert.h>
#include <string.h>

#include "AbstractString.h"
#include "String.h"

using namespace tango;

int main(int argc, char* argv[])
{
    AbstractString* test = new String("123789654");
    AbstractString* test2 = new String;

    *test2 = *test;
    *test += *test2;

    assert(test->size() == 18);

    String test3("123789654168254");
    String test4;

    test4 = test3;
    test3 += test4;

    assert(test3.size() == 30);

    String str5 = test3 + test4;

    assert(str5.size() == 45);

    delete test;
    delete test2;

    return 0;
}
