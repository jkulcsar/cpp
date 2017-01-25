
#include "Graph.hpp"

namespace br_stl
{

// To avoid ambiguities, a vertex is entered only if it did not previously exist. The
// sequential search is not particularly fast; however, this process is needed only once
// during the construction of the graph.
template<class VertexType, class EdgeType>
int Graph<VertexType,EdgeType>::insert(const VertexType& e)
{
		for(int i = 0; i < size(); ++i)
			if(e == C[i].first)
				return i;
		// if not found, insert:
		C.push_back(vertex(e, Successor()));
		return size()-1;
}

// An edge is inserted by first inserting the vertices, if they are needed, and by
// determining their positions. The edge construction itself is carried out by the function
// connectVertices(). It is passed the vertex numbers and, because there is no
// search procedure, it is very fast.
template<class VertexType, class EdgeType>
void Graph<VertexType,EdgeType>::insert(
	const VertexType& e1,
	const VertexType& e2,
	const EdgeType& Value)
{
		int pos1 = insert(e1);
		int pos2 = insert(e2);
		connectVertices(pos1, pos2, Value);
}

template<class VertexType, class EdgeType>
void Graph<VertexType,EdgeType>::connectVertices(
	int pos1, int pos2, const EdgeType& Value)
{
		(C[pos1].second)[pos2] = Value;
		if(!directed) // automatically insert opposite direction too
			(C[pos2].second)[pos1] = Value;
}

// The method check() sets the output channel and calls all other checking methods.
template<class VertexType, class EdgeType>
void Graph<VertexType,EdgeType>::check(std::ostream& os)
{
	os << "The graph is ";
	if(!isDirected())
		os << "un";
	os << "directed and has "
		<< size() << " vertices and "
		<< CountEdges()
		<< " edges\n";
	CyclesAndConnectivity(os);
}

// Determining the number of edges
// Determining the number of edges of a given graph is simple: all that is required is
// to add the lengths of all adjacency lists. Undirected graphs are represented by two
// opposed edges for each connected pair of vertices; thus, in this case, the sum is
// halved.
template<class VertexType, class EdgeType>
size_t Graph<VertexType,EdgeType>::CountEdges() {
	size_t edges = 0;
	iterator temp = begin();
	while(temp != end())
		edges += (*temp++).second.size();
	if(!directed)
		edges /= 2;
	return edges;
}

template<class VertexType, class EdgeType>
void Graph<VertexType, EdgeType>::CyclesAndConnectivity(std::ostream& os)
{
	int Cycles = 0;
	int ComponentNumber = 0;
	std::stack<int, std::vector<int> >
		verticesStack; // vertices to be visited
	/*To prevent multiple visits to vertices in possible cycles, which entails the risk of
	infinite loops, the vertices are earmarked as having been visited or as finished
	being processed. This is executed by the vector VertexState.
	*/
	// assign all vertices the state ‘not visited’
	enum VertStatus {notVisited, visited, processed};
	std::vector<VertStatus> VertexState(size(), notVisited);
	/*If, starting from one vertex, an attempt is made to reach all other vertices, success
	is not guaranteed in weakly or non-connected graphs. Therefore, each vertex is
	visited. If it is found that a vertex has already been visited, it does not need to be
	processed any further.
	*/
	// visit all vertices
	for(size_t i = 0; i < size(); ++i) {
		if(VertexState[i] == notVisited) {
			ComponentNumber++;
			// store on stack for further processing
			verticesStack.push(i);
			// process stack
			while(!verticesStack.empty()) {
				int theVertex = verticesStack.top();
				verticesStack.pop();
				if(VertexState[theVertex] == visited)
					VertexState[theVertex] = processed;
				else
					if(VertexState[theVertex] == notVisited) {
						VertexState[theVertex] = visited;
						// new vertex, earmark for processed mark
						verticesStack.push(theVertex);
						/*If one of the successors of a newly found vertex bears the
						visited mark, the algorithm has already passed this point
						once, and there is a cycle.
						*/
						// earmark successors:
						typename Successor::const_iterator start =
							operator[](theVertex).second.begin();
						typename Successor::const_iterator end =
							operator[](theVertex).second.end();
						while(start != end) {
							int Succ = (*start).first;
							if(VertexState[Succ] == visited) {
								// someone’s been here already!
								++Cycles;
								(*pOut) << "at least vertex "
									<< operator[](Succ).first
									<< " lies in a cycle\n";
							}
							/*Otherwise, the vertex has already been processed and
							therefore should not be considered again, or it has not yet
							been visited and is earmarked on the stack.
							*/
							if(VertexState[Succ] == notVisited)
								verticesStack.push(Succ);
							++start;
						}
					}
			} // stack empty?
		} // if(VertexState...
	} // for() ...
	/*Now we only need the output. In case of directed, weakly connected graphs, the
	algorithm counts several components. To make the output conform to the above
	definitions, although with a lesser information content, a distinction is made as to
	whether the graph is directed or not.
	*/
	if(directed) {
		if(ComponentNumber == 1)
			os << "The graph is strongly connected.\n";
		else
			os << "The graph is not or weakly connected.\n";
	}
	else
		os << "The graph has "
		<< ComponentNumber
		<< " component(s)." << std::endl;
	os << "The graph has ";
	if(Cycles == 0)
		os << "no ";
	os << "cycles." << std::endl;
}

} // end br_stl namespace
