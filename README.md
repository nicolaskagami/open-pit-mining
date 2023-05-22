# Open Pit Mining
Given a matrix M of profits and costs P = (pij) of width w and height h, each entry (i, j) of the matrix represents an underground area that can be mined with a cost pij. 
If pij > 0, mining generates a profit; if pij < 0, it generates a cost of -pij. 
In order to mine a cell (i, j), we need to mine the cells above (i-1, j-1), (i-1, j), and (i-1, j+1) beforehand.

## Prerequisites
* [ImageMagick](https://github.com/ImageMagick/ImageMagick) - to convert image files
* [Boost](https://github.com/boostorg/boost) - C++ utilities

## Implementation
The problem of OPM is solved by representing the matrix of profits and costs as a graph and solving the associated maximum flow problem.

### Forward Star
The Forward Star data structure was employed with a dedicated constructor to parse the OPM format. 
For this purpose, source and target points are created. 
Nodes with positive values receive a connection from the source: source -> node, with a capacity equal to their value. 
Nodes with negative values are connected to the target: node -> target, with a capacity equal to the magnitude of their value. 
For each dependency (A, B), a connection A -> B is created with a capacity equal to the sum of the capacities linked to the source and target. 
These dependency connections differentiate Open Pit Mining from a generic process scheduling problem since each node depends on those directly above it (in this case, 3 nodes above). 
A function has been added to determine the chosen nodes and print the total profit value.

### Ford-Fulkerson vs Edmonds-Karp
Both Ford-Fulkerson and Edmonds-Karp have been implemented to solve this maximum flow problem.
In this case the Ford-Fulkerson implementation was considerably faster, which is in line with the theoretical complexity of Ford-Fulkerson as O(E * maxFlow) and Edmonds-Karp as O(V * E^2). 
The Open Pit Mining problem generates 7 edges for most nodes (3 dependencies + 3 mirrored + 1 for source or target for non-margin nodes).
