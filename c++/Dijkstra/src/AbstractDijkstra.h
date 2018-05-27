#ifndef ABSTRACT_DIJKSTRA_H
#define ABSTRACT_DIJKSTRA_H

#include <stdint.h>

namespace tango
{
    class AbstractDijkstra;
}

#include "String/String.h"

namespace tango
{
    class AbstractDijkstra
    {
        public:
            virtual ~AbstractDijkstra() {}

            virtual void addGraph(const char* graph_path) = 0;
            virtual void convertAll() = 0;
            virtual String getResult(const uint32_t nr) = 0;

            virtual size_t amountGraph() const = 0;

            virtual void clear() = 0;
    };
}

#endif // ABSTRACT_DIJKSTRA_H
