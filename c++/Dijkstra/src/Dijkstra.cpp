#include "Dijkstra.h"

namespace tango
{
    Dijkstra::Dijkstra()
    {}

    Dijkstra::~Dijkstra()
    {
        clear();
    }

    void Dijkstra::addGraph(const char* graph_path)
    {
        Pair<const char*, String> pair(graph_path, "no result");

        graph.push_back(pair);
    }
    
    void Dijkstra::removeGraph(uint32_t nr)
    {
		Iterator<Pair<const char*, String> > it = graph.begin();
		it += nr;
		graph.erase(it);
    }

    void Dijkstra::convertAll()
    {
        for(uint32_t i = 0; i < graph.size(); i++)
            if(graph[i].t2 == "no result")
                doAlghoritm(i);
    }

    String Dijkstra::getResult(uint32_t nr)
    {
        if(nr < graph.size())
        {
            if(graph[nr].t2 == "no result")
                doAlghoritm(nr);

            return graph[nr].t2;
        }

        return String();
    }

    size_t Dijkstra::amountGraph() const
    {
        return graph.size();
    }

    void Dijkstra::clear()
    {
        graph.clear();
    }

    bool Dijkstra::prepareGraph(const uint32_t& nr, Parcel* parcel)
    {
        std::fstream graph_file;
        graph_file.open(graph[nr].t1, std::ios::in);

        if(!graph_file.is_open() && !graph_file.good())
        {
            graph[nr].t2.write("Not find graph file");
            return false;
        }

        char type;
        int32_t node, edges;
        int32_t n1, w, n2; // n - node, w - weight
        int32_t sp, ep; // sp - start position, ep - end position

        graph_file >> type;
        graph_file >> node >> edges;
        graph_file >> sp >> ep;

        if((type != 'd' && type != 'u') || node <= 0 || edges <= 0 || sp < 0)
        {
            graph[nr].t2.write("Error context in graph");
            return false;
        }

        parcel->node_cnt = node;
        parcel->start = sp;
        parcel->end = ep;
        parcel->neighbor = new Deque<Pair<uint32_t, uint32_t> >[node];

        graph_file >> n1 >> w >> n2;

        if(w <= 0)
        {
            graph[nr].t2.write("Edges weight is less than zero or zero");
            return false;
        }

        int32_t y = n1;
        Pair<uint32_t, uint32_t> pair(n2, w);

        switch(type)
        {
            case 'd':
                parcel->neighbor[y].push_back(pair);

                for(uint32_t i = 1; i < edges; i++)
                {
                    graph_file >> n1 >> w >> n2;

                    if(w <= 0)
                    {
                        graph[nr].t2.write("Edges weight is less than zero or zero");
                        return false;
                    }

                    if(n1 != y)
                    {
                        selectionSort(&parcel->neighbor[y]);

                        y = n1;
                    }

                    pair.t1 = n2;
                    pair.t2 = w;
                    parcel->neighbor[y].push_back(pair);
                }

                break;

            case 'u':
                parcel->neighbor[y].push_back(pair);
                pair.t1 = n1;
                pair.t2 = w;
                parcel->neighbor[n2].push_back(pair);

                for(uint32_t i = 1; i < edges; i++)
                {
                    graph_file >> n1 >> w >> n2;

                    if(w <= 0)
                    {
                        graph[nr].t2.write("Edges weight is less than zero or zero");
                        return false;
                    }

                    if(n1 != y)
                    {
                        selectionSort(&parcel->neighbor[y]);

                        y = n1;
                    }

                    pair.t1 = n2;
                    pair.t2 = w;
                    parcel->neighbor[y].push_back(pair);
                    pair.t1 = n1;
                    pair.t2 = w;
                    parcel->neighbor[n2].push_back(pair);
                }

                break;

            default:
                graph[nr].t2.write("Undefined error");
                return false;
                break;
        }


        selectionSort(&parcel->neighbor[y]);

        graph_file.close();

        return true;
    }

    void Dijkstra::doAlghoritm(const uint32_t nr)
    {
        Parcel parcel;

        if(!prepareGraph(nr, &parcel))
            return;

        int32_t d[parcel.node_cnt];
        int32_t p[parcel.node_cnt];

        bool Q[parcel.node_cnt];

        for(uint32_t i = 0; i < parcel.node_cnt; i++)
        {
            d[i] = 2147483647;
            p[i] = -1;
            Q[i] = true;
        }

        d[parcel.start] = 0;

        uint32_t y = 0;
        uint32_t x = 0;

        Queue<int32_t> queue;
        queue.insert(parcel.start);

REPEAT:

        while(!queue.empty())
        {
            y = queue.head();
            queue.remove();

            if(Q[y])
                Q[y] = false;
            else
                goto REPEAT;

            while(x < parcel.neighbor[y].size())
            {
                if(Q[parcel.neighbor[y][x].t1])
                    if(d[parcel.neighbor[y][x].t1] > d[y] + parcel.neighbor[y][x].t2)
                    {
                        d[parcel.neighbor[y][x].t1] = d[y] + parcel.neighbor[y][x].t2;
                        p[parcel.neighbor[y][x].t1] = y;

                        queue.insert(parcel.neighbor[y][x].t1);
                    }

                x++;
            }

            x = 0;
        }

        char str[300];

        if(0 <= parcel.end)
        {
            sprintf(str, "%d", d[parcel.end]);
            graph[nr].t2 = str;
        }
        else
        {
            graph[nr].t2.clear();

            for(uint32_t i = 0; i < parcel.node_cnt; i++)
            {
                sprintf(str, "%d", i);
                graph[nr].t2.append(str);
                graph[nr].t2.append(": ");
                sprintf(str, "%d", d[i]);
                graph[nr].t2.append(str);
                graph[nr].t2.append(", ");
            }
        }

        delete[] parcel.neighbor;
    }

    void Dijkstra::selectionSort(Deque<Pair<uint32_t, uint32_t> >* const node)
    {
        if(1 < node->size())
            for(uint32_t i = 0; i < node->size() - 1; i++)
                for(uint32_t j = i + 1; j < node->size(); j++)
                    if(node->at(j).t2 < node->at(i).t2)
                    {
                        std::swap(node->at(j).t1, node->at(i).t1);
                        std::swap(node->at(j).t2, node->at(i).t2);
                    }
    }
}
