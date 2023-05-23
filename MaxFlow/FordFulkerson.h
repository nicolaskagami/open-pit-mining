
#include "../FSgraph/FSgraph.h"
#include<iostream>
#include<stack>


class FordFulkerson
{
    public:
        unsigned src;
        unsigned tgt;
        FSgraph * graph;
        unsigned * parent;
        unsigned flow;
        bool * visited;

        unsigned expandedVerts;
        unsigned pathsSearched;

        bool findPath();
        void printPath();
        FordFulkerson(FSgraph * g);
        unsigned getResidual(unsigned u, unsigned v);
        void subResidual(unsigned u, unsigned v,unsigned subtraction);
        void addResidual(unsigned u, unsigned v,unsigned addition);
        ~FordFulkerson();

};
