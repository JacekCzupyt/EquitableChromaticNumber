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

	//ColoredGraph g(5);
	//g.AddEdge(0, 1);
	//g.AddEdge(0, 2);
	//g.AddEdge(0, 3);
	//g.AddEdge(0, 4);

	//GreedyAlgorithm algo;
	//algo.Color(g);

	//ColoredGraph gz(6);
	//gz.AddEdge(0, 1);
	//gz.AddEdge(1, 2);
	//gz.AddEdge(2, 3);
	//gz.AddEdge(3, 4);
	//gz.AddEdge(4, 5);

	//gz.Colors[0] = 0;
	//gz.Colors[1] = 0;
	//gz.Colors[2] = 0;
	//gz.Colors[3] = 2;
	//gz.Colors[4] = 1;
	//gz.Colors[5] = 1;

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


	JfkAlgorithm jfk;
	jfk.Color(gz);
	int x = 0;
	std::cout << "Hello World";


}