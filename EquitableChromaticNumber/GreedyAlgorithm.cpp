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

		return 0;

	}
}