#ifndef PAIR_H
#define PAIR_H

namespace tango
{
    template<typename T1, typename T2>
    class Pair;
}

namespace tango
{
    template<typename T1, typename T2>
    class Pair
    {
        public:
            Pair();
            Pair(T1 t1, T2 t2);
            virtual ~Pair();

        public:
            T1 t1;
            T2 t2;
    };

    template<typename T1, typename T2>
    Pair<T1, T2>::Pair():
        t1(),
        t2()
    {}

    template<typename T1, typename T2>
    Pair<T1, T2>::Pair(T1 t1, T2 t2):
        t1(t1),
        t2(t2)
    {}

    template<typename T1, typename T2>
    Pair<T1, T2>::~Pair()
    {}
}

#endif // PAIR_H
