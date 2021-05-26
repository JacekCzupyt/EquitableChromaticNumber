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
#include "BitsColoringAlgorithm.h"


using namespace ecnGraph;

ColoredGraph getGz() {
	ColoredGraph gz(12);
	gz.AddEdge(0, 1);
	gz.AddEdge(0, 2);
	gz.AddEdge(0, 10);
	gz.AddEdge(0, 11);
	gz.AddEdge(0, 9);
	gz.AddEdge(3, 10);
	gz.AddEdge(4, 10);
	gz.AddEdge(5, 10);
	gz.AddEdge(11, 6);
	gz.AddEdge(11, 7);
	gz.AddEdge(11, 8);
	return gz;
}


int main() {

	JfkAlgorithm jfk;
	GreedyAlgorithm grd;
	BitsColoringAlgorithm bits1(0.2f);

	ColoredGraph g1 = getGz(), g2 = getGz(), g3 = getGz();

	int chromaticNumber1 = jfk.Color(g1);
	int chromaticNumber2 = grd.Color(g2);
	int chromaticNumber3 = bits1.Color(g3);

	std::cout << "jfk: Chromatic number equals " << chromaticNumber1 << ".\n";;
	std::cout << "greedy: Chromatic number equals " << chromaticNumber2 << ".\n";;
	std::cout << "Bits: Chromatic number equals " << chromaticNumber3 << ".\n";;
}