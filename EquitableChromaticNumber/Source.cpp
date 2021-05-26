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

int main() {

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

	ColoredGraph gk(12);
	gk.AddEdge(0, 1);
	gk.AddEdge(0, 2);
	gk.AddEdge(0, 10);
	gk.AddEdge(0, 11);
	gk.AddEdge(0, 9);
	gk.AddEdge(3, 10);
	gk.AddEdge(4, 10);
	gk.AddEdge(5, 10);
	gk.AddEdge(11, 6);
	gk.AddEdge(11, 7);
	gk.AddEdge(11, 8);

	ColoredGraph gk2(12);
	gk2.AddEdge(0, 1);
	gk2.AddEdge(0, 2);
	gk2.AddEdge(0, 10);
	gk2.AddEdge(0, 11);
	gk2.AddEdge(0, 9);
	gk2.AddEdge(3, 10);
	gk2.AddEdge(4, 10);
	gk2.AddEdge(5, 10);
	gk2.AddEdge(11, 6);
	gk2.AddEdge(11, 7);
	gk2.AddEdge(11, 8);

	JfkAlgorithm jfk;
	GreedyAlgorithm grd;
	BitsColoringAlgorithm bits1(0.2f);

	int chromaticNumber1 = jfk.Color(gz);
	int chromaticNumber2 = grd.Color(gk);
	int chromaticNumber3 = bits1.Color(gk2);

	std::cout << "jfk: Chromatic number equals " << chromaticNumber1 << ".\n";;
	std::cout << "greedy: Chromatic number equals " << chromaticNumber2 << ".\n";;
	std::cout << "Bits: Chromatic number equals " << chromaticNumber3 << ".\n";;
}