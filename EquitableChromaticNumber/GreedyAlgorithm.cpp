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

				Graph.Colors[i] = colorpick;

				if (Graph.IsColoredEquitably() && possibletocolor)
				{
					break;
				}

			}
		}

		int res = 1;
		int n = sizeof(Graph.Colors) / sizeof(Graph.Colors[0]);


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