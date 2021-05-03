#include "ColoredGraph.h"
#include <map>

namespace ecnGraph {
	
	/// O(n) time
	ColoredGraph::ColoredGraph(int n) :Graph(n) {
		Colors.resize(n, -1);
	}

	/// O(n) time
	int ColoredGraph::AddVertex(int n)
	{
		Colors.resize(Colors.size() + n, -1);
		return Graph::AddVertex(n);
	}

	/// <summary>
	/// This implementation is O(|V| * log |V|) and assumes that colors can be arbitrarly numbered
	/// If we assume that colors are numbered consecutivly (1-n) and all appear at least once, a O(|V|) implementation is possible
	/// </summary>
	int ColoredGraph::GetColorCount() const
	{
		std::set<int> ColorSet;
		for (int i = 0; i < Size(); i++) {
			if(Colors[i]!=-1)
				ColorSet.insert(Colors[i]);
		}
		return ColorSet.size();
	}

	/// O(|V|) time
	bool ColoredGraph::IsColoredFully() const
	{
		for (int i = 0; i < Size(); i++) {
			if (Colors[i] == -1)
				return false;
		}
		return true;
	}

	/// O(|V| * deg(G)) time
	bool ColoredGraph::IsColoredProperly() const
	{
		for (int i = 0; i < Size(); i++) {
			for (int neighbour : Vertices[i]) {
				if (IsEdge(i, neighbour) && Colors[i] == Colors[neighbour] && Colors[i] != -1)
					return false;
			}
		}
		return true;
	}

	/// <summary>
	/// This implementation is O(|V| * log |V|) and assumes that colors can be arbitrarly numbered
	/// If we assume that colors are numbered consecutivly (1-n) and all appear at least once, a O(|V|) implementation is possible
	/// </summary>
	bool ColoredGraph::IsColoredEquitably() const
	{
		std::map<int, int> ColorHistogram;
		for (int i = 0; i < Size(); i++) {
			if(Colors[i]!=-1)
				ColorHistogram[Colors[i]] = ColorHistogram.count(Colors[i]) ? ColorHistogram[Colors[i]] + 1 : 1;
		}

		if (ColorHistogram.size() == 0)
			return true;

		int minVal = Size(), maxVal=0;
		for (auto elem : ColorHistogram) {
			minVal = std::min(minVal, elem.second);
			maxVal = std::max(maxVal, elem.second);
		}
		
		return maxVal - minVal <= 1;
	}




}
