
#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <map>
#include <iostream>

#include <vector>
//#include "../../util/checkvec.hpp"

namespace br_stl {

template<typename VertexType, typename EdgeType>
class Graph
{
public:
	// public type interface
	typedef std::map<int, EdgeType> Successor;
	typedef std::pair<VertexType, Successor> vertex;
//	typedef br_stl::checkedVector<vertex> GraphType;
	typedef std::vector<vertex> GraphType;
	typedef typename GraphType::iterator iterator;
	typedef typename GraphType::const_iterator const_iterator;

private:
	bool directed;
	GraphType C;	// actual container
	std::ostream* pOut;

public:
	/*The following constructor initializes the output channel with cerr. A parameter
	must be specified as to whether the graph is directed or undirected, because this is
	an essential property of a graph.
	*/
	Graph(bool g, std::ostream& os = std::cerr)
		: directed(g), pOut(&os) {
	}

	bool isDirected() const { return directed;}
	/*A graph is a special kind of container to which something can be added and whose
	elements can be accessed. Therefore, in the following typical container methods,
	their extents are limited to those needed for the examples. Thus, there is no method
	for explicit removal of a vertex or an edge from the graph.
	*/
	size_t size() const { return C.size();}
	iterator begin() { return C.begin();}
	iterator end() { return C.end();}
	
	// access to vertex i
	vertex& operator[](int i) {
		// the access is safe, because C is a checkedVector
		return C[i];
	}
	
	// addition of a vertex
	int insert(const VertexType& e);
	
	// addition of an edge between e1 and e2
	void insert(const VertexType& e1, const VertexType& e2,
		const EdgeType& Value);
	
	// addition of an edge between vertices no. i and j
	void connectVertices(int i,int j,const EdgeType& Value);
	
	/*The following methods are useful tools for displaying information on a graph and
	checking its structure. These methods are described in detail in the next sections.
	*/
	// checking of a read data model
	// output on the channel passed to check()
	void check(std::ostream& = std::cout);

	// determine the number of edges
	size_t CountEdges();

	// determine whether the graph contains cycles
	// and in which way it is connected
	void CyclesAndConnectivity(std::ostream& = std::cout);
}; // Graph

} // end namespace br_stl

// Display of vertices and edges
// The output operator is used to display the vertices and edges of a graph. The output
// format corresponds to the format assumed by the routines of the next section.
template<class VertexType, class EdgeType>
std::ostream& operator<<(std::ostream& os, br_stl::Graph<VertexType, EdgeType>& G)
{
		// display of vertices with successors
		for(size_t i = 0; i < G.size(); ++i) {
			os << G[i].first << " <";
			typename br_stl::Graph<VertexType,EdgeType>::Successor::const_iterator
				startN = G[i].second.begin(),
				endN = G[i].second.end();
			while(startN != endN) {
				os << G[(*startN).first].first << ' ' // vertex
					<< (*startN).second << ' '; // edge value
				++startN;
			}
			os << ">" << std::endl;
		}
		return os;
}




#endif
