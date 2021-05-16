#include "ColoredGraph.h"
#include <string>
#include <iostream>
#include <fstream>

namespace ecnGraph {
	ColoredGraph ReadColFile(std::string fileName) {
		std::ifstream file(fileName);
		if (file.is_open()) {
			std::string line;
			ColoredGraph* graph = nullptr;
			while (getline(file, line)) {
				switch (line[0])
				{
				case 'c':
					break;
				case 'p':
					int n;
					scanf("p edge %d %d", &n, nullptr);
					graph = &ColoredGraph(n);
					break;
				case 'e':
					int a, b;
					scanf("e %d %d", &a, &b);
					graph->AddEdge(a-1, b-1);
					break;
				default:
					break;
				}
			}
			return *graph;
		}
		throw 404;
	}
}