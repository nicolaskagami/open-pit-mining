
GENERATION=./Generation
VERIFICATION=./Verification
ALGORITHMS=./MaxFlow
OPM=./OPM
FSGRAPH=./FSgraph
NHEAP=./NHeap

all: clean $(OPM)/OPM $(OPM)/standardOPM 

$(OPM)/OPM: $(OPM)/opm.cpp $(ALGORITHMS)/EdmondsKarp.cpp $(ALGORITHMS)/EdmondsKarp.h $(ALGORITHMS)/FordFulkerson.cpp $(ALGORITHMS)/FordFulkerson.h
	g++ $(OPM)/opm.cpp $(ALGORITHMS)/EdmondsKarp.cpp $(ALGORITHMS)/FordFulkerson.cpp $(NHEAP)/NHeap.cpp $(FSGRAPH)/FSgraph.cpp -o $(OPM)/OPM

$(OPM)/standardOPM: $(OPM)/standardOpm.cpp
	g++ $(OPM)/standardOpm.cpp -std=c++0x -lboost_program_options -o $(OPM)/standardOPM

clean:
	rm -rf $(OPM)/OPM
	rm -rf $(OPM)/standardOPM
