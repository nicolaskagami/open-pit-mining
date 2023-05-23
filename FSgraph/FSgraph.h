//Author: Nicolas Silveira Kagami
//Modified to hold local residual and global source and target
//Modified to calculate Open Pit Mining 
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<iostream>
#include<fstream>
#include<sstream>
#include<stack>

typedef struct FSedge
{
    unsigned target;
    unsigned weight;
    unsigned residual;
} EDGE;

typedef struct FSvert
{
    unsigned index;
    unsigned edgeNum;
} VERT;

class FSgraph
{
    public:
        EDGE * edges;
        VERT * vertices;//indexed by i-1
        unsigned currentEdge;
        unsigned currentVert;
        unsigned numEdges;
        unsigned numVerts;

        FSgraph(unsigned vertNum, unsigned edgeNum);
        FSgraph(std::istream& in);
        void preallocate(unsigned vert, unsigned tgt);
        void indexify();
        ~FSgraph();
        void addEdge(unsigned vert, unsigned tgt, unsigned wht);
        void print();

        void proposeEdge(unsigned vert, unsigned tgt, unsigned wht);
        int findEdge(unsigned u, unsigned v);
        unsigned source;
        unsigned target;
        unsigned maxCapacity;

        unsigned width, height;
        void printOPM();
        bool * opm;
        
};
