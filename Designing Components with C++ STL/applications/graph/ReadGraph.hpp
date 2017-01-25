
#ifndef GR_INPUT_H
#define GR_INPUT_H

#include <string>
#include <cctype>
#include <fstream>
#include <iostream>

#include "Graph.hpp"

namespace br_stl {
	template<class EdgeParamType>
	void ReadGraph(Graph<std::string,EdgeParamType>& G,
		const char *Filename) {
			std::ifstream Source;
			Source.open(Filename);
			if (!Source) { // error check
				std::cerr << "Cannot open "
					<< Filename << "!\n";
				exit(-1);
			}
			while(Source) {
				char c;
				std::string vertex, VertexSuccessor;
				Source.get(c);
				if(isalnum(c)) {
					Source.putback(c);
					Source >> vertex;
					G.insert(vertex);
					// collect successor now, if present
					bool SuccessorExists = false;
					Source >> c;
					if(c == '<')
						SuccessorExists = true;
					else
						Source.putback(c);
					while(SuccessorExists) {
						Source >> VertexSuccessor;
						if(!isalnum(VertexSuccessor[0]))
							break; // illegal character
						EdgeParamType Par;
						Source >> Par; // read parameters
						G.insert(vertex, VertexSuccessor, Par);
					}
				}
				else // skip line
					while(Source && c != '\n') Source.get(c);
			}
	}
} // namespace br_stl
#endif
