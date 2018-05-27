#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <string>
#include <stdint.h>
#include <fstream>

namespace tango
{
    class Dijkstra;
}

#include "AbstractDijkstra.h"
#include "Pair.h"

#include "Deque/Deque.h"
#include "Deque/Iterator.h"

#include "Queue/queue.h"

namespace tango
{
    class Dijkstra:
        public AbstractDijkstra
    {
        private:
            typedef struct
            {
                uint32_t node_cnt;
                uint32_t start;
                int64_t end;

                Deque<Pair<uint32_t, uint32_t> >* neighbor; // node, price
            } Parcel;

        public:
            Dijkstra();
            virtual ~Dijkstra();

            void addGraph(const char* graph_path);
            void removeGraph(uint32_t nr);
            void convertAll();
            String getResult(uint32_t nr);

            size_t amountGraph() const;

            void clear();

        private:
            bool prepareGraph(const uint32_t& nr, Parcel* parcel);
            void doAlghoritm(const uint32_t nr);
            void selectionSort(Deque<Pair<uint32_t, uint32_t> >* const node);

        private:
            Deque<Pair<const char*, String> > graph; // file path, result
    };
}

#endif // DIJKSTRA_H
