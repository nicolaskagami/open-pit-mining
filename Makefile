
GENERATION=./Generation
VERIFICATION=./Verification
ALGORITHMS=./MaxFlow
OPM=./OPM
FSGRAPH=./FSgraph
NHEAP=./NHeap

all: $(ALGORITHMS)/EdmondsKarp $(OPM)/OPM

$(ALGORITHMS)/EdmondsKarp: $(ALGORITHMS)/EdmondsKarp.cpp $(ALGORITHMS)/EdmondsKarp.h
	g++ $(ALGORITHMS)/EdmondsKarp.cpp $(NHEAP)/NHeap.cpp $(FSGRAPH)/FSgraph.cpp -o $(ALGORITHMS)/EdmondsKarp

$(OPM)/OPM: $(OPM)/opm.cpp
	g++ $(OPM)/opm.cpp -std=c++0x -lboost_program_options -o $(OPM)/OPM


clean:
	rm -rf $(ALGORITHMS)/EdmondsKarp
