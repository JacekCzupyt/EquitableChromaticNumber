#include "GreedyAlgorithm.h"
#include "JfkAlgorithm.h"
#include "Graph.h"
#include<vector>
#include<set>
#include "ColoredGraph.h"
#include "AbstractColoringAlgorithm.h"
#include <map>
#include <algorithm>

namespace ecnGraph {
	int GreedyAlgorithm::Color(ColoredGraph& Graph)
	{
		bool notValid = false;
		std::vector<int> indexes;

		for (int j = 0; j < Graph.Colors.size();j++)
		{
			indexes.push_back(j);
		}

		bool equi = Graph.IsColoredEquitably();
		bool prop = Graph.IsColoredProperly();

		do{
		    notValid = false;
			std::random_shuffle(indexes.begin(), indexes.end());
			for (int i = 0; i < Graph.Size(); i++) {

				int colorpick = -1;
				for (int color = 0; color < Graph.Size();color++)
				{
					bool possibletocolor = true;

					for (int neighbour : Graph.Vertices[i])
					{
						if (Graph.Colors[neighbour] == color && Graph.Colors[neighbour] != -1)
						{
							possibletocolor = false;
						}
					}

					if (possibletocolor)
					{
						colorpick = color;

					}

					int tempcolor = Graph.Colors[indexes[i]];
					Graph.Colors[indexes[i]] = colorpick;


					if (Graph.IsColoredEquitably() && possibletocolor)
					{
						break;
					}

					if (!Graph.IsColoredEquitably())
					{
						Graph.Colors[indexes[i]] = tempcolor;
					}
				}

				for (int k = 0;k < Graph.Colors.size();k++)
				{
					if (Graph.Colors[k] == -1)
						notValid = true;
				}
			}		
		} while (!Graph.IsColoredEquitably() || !Graph.IsColoredProperly() || notValid == true );
		

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