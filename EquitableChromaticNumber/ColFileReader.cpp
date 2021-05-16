#include "ColoredGraph.h"
#include <string>
#include <iostream>
#include <fstream>

namespace ecnGraph {
	ColoredGraph ReadColFile(std::string fileName) {
		std::ifstream file(fileName);
		if (file.is_open()) {
			std::string line;
			ColoredGraph graph(0);
			while (getline(file, line)) {
				switch (line[0])
				{
				case 'c':
					break;
				case 'p':
					int n;
					if(sscanf_s(line.c_str(), "p edge %d %*d", &n)!=1) throw 500;
					graph = ColoredGraph(n);
					break;
				case 'e':
					int a, b;
					if(sscanf_s(line.c_str(), "e %d %d", &a, &b)!=2) throw 500;
					graph.AddEdge(a-1, b-1);
					break;
				default:
					break;
				}
			}
			return graph;
		}
		throw 404;
	}
}