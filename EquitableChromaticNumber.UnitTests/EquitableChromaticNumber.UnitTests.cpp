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
	};
}
