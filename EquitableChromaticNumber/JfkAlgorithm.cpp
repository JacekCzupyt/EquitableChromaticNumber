#include "JfkAlgorithm.h"
#include "Graph.h"
#include<vector>
#include<set>
#include "ColoredGraph.h"
#include "AbstractColoringAlgorithm.h"
#include <map>
#include <algorithm>
#include <stdlib.h>


namespace ecnGraph {

	int JfkAlgorithm::Color(ColoredGraph& Graph)
	{
		srand(0);

		for (int i = 0; i < Graph.Colors.size();i++)
		{
			

			//Graph.Colors[i] = (rand() % Graph.Colors.size()) + 1;
			Graph.Colors[i] = 1;
		}

		std::vector<int> mostfrequents;

		//main loop
		while (!Graph.IsColoredEquitably() || !Graph.IsColoredProperly())
		{
			//creating dictionary with colors and their frequency
			std::map<int, int> ColorHistogram;
			for (int i = 0; i < Graph.Size(); i++) {
				if (Graph.Colors[i] != -1)
					ColorHistogram[Graph.Colors[i]] = ColorHistogram.count(Graph.Colors[i]) ? ColorHistogram[Graph.Colors[i]] + 1 : 1;
			}
			mostfrequents.clear();

			int mostfrequent = -1;
			int mostfrequentvalue = 0;


			//find most frequent color
			for (int i = 0; i < ColorHistogram.size(); i++) {
				if (ColorHistogram[i] >= mostfrequentvalue)
				{
					mostfrequent = i;
					mostfrequentvalue = ColorHistogram[i];
				}
			}

			int leastfrequent = mostfrequent;
			int leastfrequentvalue = mostfrequentvalue;

			//find least frequent color
			for (int i = 0; i < ColorHistogram.size(); i++) {
				if (ColorHistogram[i] <= leastfrequentvalue)
				{
					leastfrequent = i;
					leastfrequentvalue = ColorHistogram[i];
				}
			}

			int frequentcounter = 0;

			for (int i = 0; i < ColorHistogram.size(); i++) {

				if (ColorHistogram[i] == mostfrequentvalue)
				{
					frequentcounter++;
					mostfrequents.push_back(i);
				}
				
			}

			int chosenmax;
			if (frequentcounter >= 2)
			{
				chosenmax = rand() % frequentcounter;
				mostfrequent = mostfrequents[chosenmax];
				mostfrequentvalue = ColorHistogram[mostfrequent];
			}

			if (leastfrequent == mostfrequent)
			{
				leastfrequent = 0;
				mostfrequent = 1;
			}

			bool changed = false;
			for (int i = 0; i < Graph.Size(); i++) {
				if (Graph.Colors[i] == mostfrequent)
				{
					bool toChange = true;
					for (int neighbour : Graph.Vertices[i])
					{
						if (leastfrequent == Graph.Colors[neighbour] || Graph.Colors[neighbour] == -1 || leastfrequent == -1)
						{
							toChange = false;
						}
					}

					if (toChange)
					{
						Graph.Colors[i] = leastfrequent;
						changed = true;
						break;
					}
				}
			}

			if (!changed)
			{
				for (int i = 0; i < Graph.Size(); i++) {
					if (Graph.Colors[i] == mostfrequent)
					{
						int it = *max_element(std::begin(Graph.Colors), std::end(Graph.Colors));
						Graph.Colors[i] = it + 1;
						break;
					}
				}
			}

		}

		int res = 1;
		int n = Graph.Colors.size();


		// Pick all elements one by one
		for (int i = 1; i < n; i++) {
			int j = 0;
			for (j = 0; j < i; j++)
				if (Graph.Colors[i] == Graph.Colors[j])
					break;

			// If not printed earlier, then print it
			if (i == j)
				res++;
		}
		return res;
	}
}

	

	