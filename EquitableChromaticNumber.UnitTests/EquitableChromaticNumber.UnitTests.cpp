#include "pch.h"
#include "CppUnitTest.h"
#include "../EquitableChromaticNumber/Graph.h"
#include "../EquitableChromaticNumber/Graph.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace EquitableChromaticNumberUnitTests
{
	TEST_CLASS(EquitableChromaticNumberUnitTests)
	{
	public:

		TEST_METHOD(ConstructorAndSize)
		{
			using namespace ecnGraph;
			int n = 5;
			Graph g(n);
			Assert::AreEqual(g.Size(), n);
		}

		TEST_METHOD(ConstructorAndSize0)
		{
			using namespace ecnGraph;
			int n = 0;
			Graph g(n);
			Assert::AreEqual(g.Size(), n);
		}

		TEST_METHOD(AddVertexTest)
		{
			using namespace ecnGraph;
			int n = 5, k = 3;
			Graph g(n);
			g.AddVertex(k);
			Assert::AreEqual(g.Size(), n+k);
		}

		TEST_METHOD(AddEdgeAndIsEdge)
		{
			using namespace ecnGraph;
			Graph g(3);
			g.AddEdge(0, 1);
			Assert::AreEqual(g.IsEdge(0, 1), true);
			Assert::AreEqual(g.IsEdge(0, 2), false);
		}

		TEST_METHOD(RemoveEdge)
		{
			using namespace ecnGraph;
			Graph g(2);
			Assert::AreEqual(g.IsEdge(0, 1), false);
			g.AddEdge(0, 1);
			Assert::AreEqual(g.IsEdge(0, 1), true);
			g.AddEdge(0, 1);
			Assert::AreEqual(g.IsEdge(0, 1), true);
			g.RemoveEdge(1, 0);
			Assert::AreEqual(g.IsEdge(0, 1), false);
			g.RemoveEdge(1, 0);
			Assert::AreEqual(g.IsEdge(0, 1), false);
		}

		TEST_METHOD(AddVertexPreservesState)
		{
			using namespace ecnGraph;
			Graph g(3);
			g.AddEdge(0, 1);
			Assert::AreEqual(g.IsEdge(0, 1), true);
			g.AddVertex(2);
			Assert::AreEqual(g.IsEdge(0, 1), true);
			Assert::AreEqual(g.IsEdge(0, 4), false);
		}

		TEST_METHOD(DegTest)
		{
			using namespace ecnGraph;
			Graph g(4);
			g.AddEdge(0, 1);
			g.AddEdge(0, 2);
			Assert::AreEqual(g.Deg(0), 2);
			Assert::AreEqual(g.Deg(1), 1);
			Assert::AreEqual(g.Deg(2), 1);
			Assert::AreEqual(g.Deg(3), 0);

			Assert::AreEqual(g.Deg(), 2);
		}
	};
}
