#include "pch.h"
#include "CppUnitTest.h"
#include "../EquitableChromaticNumber/ColoredGraph.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace EquitableChromaticNumberUnitTests
{
	using namespace ecnGraph;

	TEST_CLASS(ColoredGraphUnitTests)
	{
	public:
		TEST_METHOD(ConstructorAndSize)
		{
			int n = 5;
			ColoredGraph g(n);
			Assert::AreEqual(g.Size(), n);
			Assert::AreEqual((int)g.Colors.size(), n);
			Assert::AreEqual(g.Colors[0], -1);
		}

		TEST_METHOD(AddVertex)
		{
			int n = 5, k = 3;
			ColoredGraph g(n);
			g.AddVertex(k);
			Assert::AreEqual(g.Size(), n + k);
			Assert::AreEqual((int)g.Colors.size(), n + k);
			Assert::AreEqual(g.Colors[0], -1);
			Assert::AreEqual(g.Colors[6], -1);
		}

		TEST_METHOD(ColorCountConsecutive) {
			ColoredGraph g1(5);
			Assert::AreEqual(g1.GetColorCount(), 0);

			g1.Colors[0] = 0;
			Assert::AreEqual(g1.GetColorCount(), 1);

			g1.Colors[3] = 1;
			Assert::AreEqual(g1.GetColorCount(), 2);

			g1.Colors[4] = 0;
			Assert::AreEqual(g1.GetColorCount(), 2);

			g1.Colors[3] = 0;
			Assert::AreEqual(g1.GetColorCount(), 1);
		}

		// The current implementation deliberately forfits this functionality in favour of higher preformence
		/*TEST_METHOD(ColorCountMixed) {
			ColoredGraph g1(5);
			Assert::AreEqual(g1.GetColorCount(), 0);

			g1.Colors[0] = 0;
			Assert::AreEqual(g1.GetColorCount(), 1);

			g1.Colors[3] = 1;
			Assert::AreEqual(g1.GetColorCount(), 2);

			g1.Colors[0] = -1;
			Assert::AreEqual(g1.GetColorCount(), 1);

			g1.Colors[2] = 10;
			Assert::AreEqual(g1.GetColorCount(), 2);
		}*/

		TEST_METHOD(IsFullyColored) {
			ColoredGraph g1(2);
			Assert::AreEqual(g1.IsColoredFully(), false);

			g1.Colors[0] = 0;
			Assert::AreEqual(g1.IsColoredFully(), false);

			g1.Colors[1] = 0;
			Assert::AreEqual(g1.IsColoredFully(), true);

			g1.Colors[0] = 1;
			Assert::AreEqual(g1.IsColoredFully(), true);

			g1.Colors[0] = -1;
			Assert::AreEqual(g1.IsColoredFully(), false);
		}

		TEST_METHOD(IsColoredProperly) {
			ColoredGraph g1(3);
			g1.AddEdge(0, 1);
			g1.AddEdge(0, 2);
			Assert::AreEqual(g1.IsColoredProperly(), true);

			g1.Colors[0] = 0;
			Assert::AreEqual(g1.IsColoredProperly(), true);

			g1.Colors[1] = 1;
			Assert::AreEqual(g1.IsColoredProperly(), true);

			g1.Colors[1] = 0;
			Assert::AreEqual(g1.IsColoredProperly(), false);

			g1.Colors[1] = 1;
			g1.Colors[2] = 1;
			Assert::AreEqual(g1.IsColoredProperly(), true);

			g1.AddEdge(1, 2);
			Assert::AreEqual(g1.IsColoredProperly(), false);

			g1.Colors[1] = 0;
			g1.RemoveEdge(1, 0);
			Assert::AreEqual(g1.IsColoredProperly(), true);
		}

		TEST_METHOD(IsColoredEquitablyConsecutive) {
			ColoredGraph g1(5);
			Assert::AreEqual(g1.IsColoredEquitably(), true);

			g1.Colors[0] = 0;
			Assert::AreEqual(g1.IsColoredEquitably(), true);

			g1.Colors[1] = 0;
			g1.Colors[4] = 0;
			Assert::AreEqual(g1.IsColoredEquitably(), true);

			g1.Colors[2] = 1;
			Assert::AreEqual(g1.IsColoredEquitably(), false);

			g1.Colors[3] = 1;
			Assert::AreEqual(g1.IsColoredEquitably(), true);

			g1.Colors[0] = 2;
			Assert::AreEqual(g1.IsColoredEquitably(), true);

			g1.AddVertex();
			g1.Colors[5] = 0;
			Assert::AreEqual(g1.IsColoredEquitably(), false);
		}

		// The current implementation deliberately forfits this functionality in favour of higher preformence
		/*TEST_METHOD(IsColoredEquitablyMixed) {
			ColoredGraph g1(5);
			Assert::AreEqual(g1.IsColoredEquitably(), true);

			g1.Colors[0] = 3;
			Assert::AreEqual(g1.IsColoredEquitably(), true);

			g1.Colors[1] = 3;
			g1.Colors[4] = 3;
			Assert::AreEqual(g1.IsColoredEquitably(), true);

			g1.Colors[2] = 8;
			Assert::AreEqual(g1.IsColoredEquitably(), false);

			g1.Colors[3] = 8;
			Assert::AreEqual(g1.IsColoredEquitably(), true);

			g1.Colors[0] = 27;
			Assert::AreEqual(g1.IsColoredEquitably(), true);

			g1.AddVertex();
			g1.Colors[5] = 3;
			Assert::AreEqual(g1.IsColoredEquitably(), false);
		}*/
	};
}