
#include "../MaxFlow/FordFulkerson.h"
int main(int argc, char ** argv)
{
    FSgraph gr(std::cin);
    FordFulkerson FF(&gr);
    gr.printOPM();
    return 0;
}
