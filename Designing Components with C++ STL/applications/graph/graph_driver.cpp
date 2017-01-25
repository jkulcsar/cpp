
#include "Graph.hpp"
#include "ReadGraph.hpp"
#include "Empty.hpp"

int main(int argc, char** argv)
{
	// no edge weighting, therefore type Empty:
	br_stl::Graph<std::string, br_stl::Empty> V(true);
	
	// true means directed
	br_stl::ReadGraph(V, "graph1.dat");
	
	V.check(); // display properties
	std::cout << V; // display of vertices with successors

	return 0;
}
