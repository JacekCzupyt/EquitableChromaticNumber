#include "pch.h"
#include "CppUnitTest.h"
#include "../EquitableChromaticNumber/ColFileReader.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace EquitableChromaticNumberUnitTests {
	using namespace ecnGraph;

	TEST_CLASS(ColFileReader_UnitTests) {

	public:
		TEST_METHOD(myciel7) {
			ColoredGraph graph = ReadColFile("../TestCases/myciel7.col");
			Assert::AreEqual(191, graph.Size());
			Assert::IsTrue(graph.IsEdge(0, 1));
			Assert::IsFalse(graph.IsEdge(0, 2));
			Assert::IsTrue(graph.IsEdge(4, 108));
			Assert::IsFalse(graph.IsEdge(107, 4));
			int sum = 0;
			for (int v = 0; v < graph.Size(); v++) {
				sum += graph.Deg(v);
			}
			Assert::AreEqual(2360 * 2, sum);
		}
		
	};
}