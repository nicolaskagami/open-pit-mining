
GENERATION=./Generation
VERIFICATION=./Verification
ALGORITHMS=./MaxFlow
OPM=./OPM
FSGRAPH=./FSgraph
NHEAP=./NHeap

all: clean $(OPM)/myOPM $(OPM)/OPM 

$(OPM)/myOPM: $(ALGORITHMS)/FordFulkerson.cpp $(ALGORITHMS)/FordFulkerson.h
	g++ -Ofast -march=native -funroll-loops $(OPM)/myOPM.cpp $(ALGORITHMS)/FordFulkerson.cpp $(NHEAP)/NHeap.cpp $(FSGRAPH)/FSgraph.cpp -o $(OPM)/myOPM

$(OPM)/OPM: $(OPM)/opm.cpp
	g++ $(OPM)/opm.cpp -std=c++0x -lboost_program_options -o $(OPM)/OPM


clean:
	rm -rf $(OPM)/myOPM
