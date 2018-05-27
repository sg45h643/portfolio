#include "../src/AbstractDijkstra.h"
#include "../src/Dijkstra.h"

#include <assert.h>
#include <iostream>

using namespace tango;

int main(int argc, char* argv[])
{
    Dijkstra d;
    d.addGraph("../../test/graph/www_example_directed");
    d.addGraph("../../test/graph/d_one.txt");
    d.addGraph("../../test/graph/www_example_undirected");
    assert(d.getResult(0) == "6");
    assert(d.getResult(1) == "5");

    d.convertAll();

    assert(d.getResult(2) == "20");

    d.removeGraph(1);
    assert(d.getResult(1) == "20");

    return 0;
}
