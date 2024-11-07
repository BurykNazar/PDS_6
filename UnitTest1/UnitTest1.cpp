#include "pch.h"
#include "CppUnitTest.h"
#include "..\Lab_6\Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(TestReadGraph)
		{
			vector<vector<int>> edges;
			string testFile = "test_graph.txt";
			ofstream file(testFile);
			file << "3 3\n1 2\n2 3\n3 1\n";
			file.close();

			Assert::IsTrue(readGraph(testFile, edges));
			Assert::AreEqual((unsigned int)3, N);
			Assert::AreEqual((unsigned int)3, M);
			Assert::AreEqual(edges[0][0], 0);
			Assert::AreEqual(edges[0][1], 1);
			Assert::AreEqual(edges[1][0], 1);
			Assert::AreEqual(edges[1][1], 2);
			Assert::AreEqual(edges[2][0], 2);
			Assert::AreEqual(edges[2][1], 0);
		}

		TEST_METHOD(TestGetAdjacencyMatrix)
		{
			vector<vector<int>> edges = { {0, 1}, {1, 2}, {2, 0} };
			N = 3;
			vector<vector<int>> matrix;
			getAdjacencyMatrix(edges, matrix);

			Assert::AreEqual((int)matrix[0][1], 1);
			Assert::AreEqual((int)matrix[1][2], 1);
			Assert::AreEqual((int)matrix[2][0], 1);
			Assert::AreEqual((int)matrix[0][0], 0);
		}

		TEST_METHOD(TestGetIncidenceMatrix)
		{
			vector<vector<int>> edges = { {0, 1}, {1, 2}, {2, 0} };
			N = 3;
			M = 3;
			vector<vector<int>> matrix;
			getIncidenceMatrix(edges, matrix);

			Assert::AreEqual((int)matrix[0][0], 1);
			Assert::AreEqual((int)matrix[1][0], -1);
			Assert::AreEqual((int)matrix[2][0], 0);
			Assert::AreEqual((int)matrix[0][1], 0);
			Assert::AreEqual((int)matrix[1][1], 1);
			Assert::AreEqual((int)matrix[2][1], -1);
		}
	};
}
