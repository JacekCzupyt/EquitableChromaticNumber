#include<iostream>
#include "Graph.h"
#include "Graph.h"
#include<vector>
#include<set>
#include "ColoredGraph.h"
#include "AbstractColoringAlgorithm.h"
#include <map>
#include <algorithm>
#include "GreedyAlgorithm.h"
#include "JfkAlgorithm.h"


using namespace ecnGraph;

int main() {

	ColoredGraph gz(5);
	gz.AddEdge(0, 1);
	gz.AddEdge(0, 2);
	gz.AddEdge(0, 3);
	gz.AddEdge(0, 4);

	gz.Colors[0] = 0;
	gz.Colors[1] = 1;
	gz.Colors[2] = 0;
	gz.Colors[3] = 1;
	gz.Colors[4] = 0;

	ColoredGraph g(5);
	g.AddEdge(0, 1);
	g.AddEdge(0, 2);
	g.AddEdge(0, 3);
	g.AddEdge(0, 4);

	JfkAlgorithm jfk;
	GreedyAlgorithm grd;
	int chromaticNumber1 = jfk.Color(gz);
	int chromaticNumber2 = grd.Color(g);

	std::cout << "jfk: Chromatic number equals " << chromaticNumber1 << ".\n";;
	std::cout << "greedy: Chromatic number equals " << chromaticNumber2 << ".\n";;
}