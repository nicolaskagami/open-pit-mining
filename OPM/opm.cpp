#include "../MaxFlow/FordFulkerson.h"
//#include "../MaxFlow/EdmondsKarp.h"
#include<iostream>
int main(int argc, char ** argv)
{
    FSgraph gr(std::cin);
    FordFulkerson FF(&gr);
    //EdmondsKarp EE(&gr);
    gr.printOPM();
    return 0;
}
