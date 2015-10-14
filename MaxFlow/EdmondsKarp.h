
#include "../FSgraph/FSgraph.h"
#include "../NHeap/NHeap.h"


class EdmondsKarp
{
    public:
        unsigned src;
        unsigned tgt;
        FSgraph * graph;
        unsigned * parent;
        unsigned flow;

        bool * visited;
        unsigned * distances;
        unsigned expanded_verts;
        unsigned paths_searched;

        bool findPath();
        void printPath();
        EdmondsKarp(FSgraph * g);
        unsigned getResidual(unsigned u, unsigned v);
        void subResidual(unsigned u, unsigned v,unsigned subtraction);
        void addResidual(unsigned u, unsigned v,unsigned addition);
        ~EdmondsKarp();

};
