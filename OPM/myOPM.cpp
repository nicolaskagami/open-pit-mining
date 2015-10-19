
#include "../MaxFlow/EdmondsKarp.h"
int main(int argc, char ** argv)
{
    FSgraph gr(std::cin);
    EdmondsKarp EK(&gr);
    gr.printOPM();
    return 0;
}
