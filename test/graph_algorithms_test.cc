#include <gtest/gtest.h>

#include "../s21_graph.h"
#include "../s21_graph_algorithms.h"

TEST(GraphAlgorithms, depth_search_1) {
  s21::Graph graph(1);
  graph.LoadGraphFromFile("./test/graph3.txt");
  s21::GraphAlgorithms algorithms;
  std::vector<int> result = algorithms.DepthFirstSearch(graph, 1);
  std::vector<int> expect{1, 2, 3, 4};
  ASSERT_TRUE(result.size() > 0);
  ASSERT_TRUE(result == expect);
  graph.ClearGraph();
}

TEST(GraphAlgorithms, depth_search_2) {
  s21::Graph graph(1);
  graph.LoadGraphFromFile("./test/graph3.txt");
  s21::GraphAlgorithms algorithms;
  std::vector<int> result = algorithms.DepthFirstSearch(graph, 2);
  std::vector<int> expect{2, 1, 3, 4};
  ASSERT_TRUE(result.size() > 0);
  ASSERT_TRUE(result == expect);
  graph.ClearGraph();
}

TEST(GraphAlgorithms, breath_search_1) {
  s21::Graph graph(1);
  graph.LoadGraphFromFile("./test/graph3.txt");
  s21::GraphAlgorithms algorithms;
  std::vector<int> result = algorithms.BreadthFirstSearch(graph, 1);
  std::vector<int> expect{1, 2, 3, 4};
  ASSERT_TRUE(result.size() > 0);
  ASSERT_TRUE(result == expect);
  graph.ClearGraph();
}

TEST(GraphAlgorithms, breath_search_2) {
  s21::Graph graph(1);
  graph.LoadGraphFromFile("./test/graph3.txt");
  s21::GraphAlgorithms algorithms;
  std::vector<int> result = algorithms.BreadthFirstSearch(graph, 4);
  std::vector<int> expect{4, 1, 2, 3};
  ASSERT_TRUE(result.size() > 0);
  ASSERT_TRUE(result == expect);
  graph.ClearGraph();
}

TEST(GraphAlgorithms, shortest_path_between_vertices_1) {
  s21::Graph graph(1);
  graph.LoadGraphFromFile("./test/graph3.txt");
  s21::GraphAlgorithms algorithms;
  int result = algorithms.GetShortestPathBetweenVertices(graph, 1, 4);
  int expect = 21;
  EXPECT_EQ(result, expect);
  graph.ClearGraph();
}

TEST(GraphAlgorithms, shortest_path_between_vertices_2) {
  s21::Graph graph(1);
  graph.LoadGraphFromFile("./test/graph3.txt");
  s21::GraphAlgorithms algorithms;
  int result = algorithms.GetShortestPathBetweenVertices(graph, 1, 3);
  int expect = 2;
  EXPECT_EQ(result, expect);
  graph.ClearGraph();
}

TEST(GraphAlgorithms, shortest_path_between_vertices_3) {
  s21::Graph graph(1);
  graph.LoadGraphFromFile("./test/graph3.txt");
  s21::GraphAlgorithms algorithms;
  int result = algorithms.GetShortestPathBetweenVertices(graph, 2, 4);
  int expect = 29;
  EXPECT_EQ(result, expect);
  graph.ClearGraph();
}

TEST(GraphAlgorithms, shortest_path_between_all_vertices_1) {
  s21::Graph graph(1);
  graph.LoadGraphFromFile("./test/graph3.txt");
  s21::GraphAlgorithms algorithms;
  std::vector<std::vector<int>> result =
      algorithms.GetShortestPathsBetweenAllVertices(graph);
  std::vector<std::vector<int>> expect{
      {0, 17, 2, 21}, {17, 0, 15, 29}, {2, 15, 0, 21}, {21, 29, 21, 0}};
  EXPECT_EQ(result, expect);
  graph.ClearGraph();
}

TEST(GraphAlgorithms, shortest_path_between_all_vertices_2) {
  s21::Graph graph(1);
  graph.LoadGraphFromFile("./test/graph2.txt");
  s21::GraphAlgorithms algorithms;
  std::vector<std::vector<int>> result =
      algorithms.GetShortestPathsBetweenAllVertices(graph);
  std::vector<std::vector<int>> expect{
      {0, 2, 1, 3}, {1, 0, 1, 1}, {1, 1, 0, 2}, {1, 2, 1, 0}};
  EXPECT_EQ(result, expect);
  graph.ClearGraph();
}

TEST(GraphAlgorithms, spanning_tree_1) {
  s21::Graph graph(1);
  graph.LoadGraphFromFile("./test/graph3.txt");
  s21::GraphAlgorithms algorithms;
  std::vector<std::vector<int>> result = algorithms.GetLeastSpanningTree(graph);
  std::vector<std::vector<int>> expect{
      {0, 0, 2, 21}, {0, 0, 15, 0}, {2, 15, 0, 0}, {21, 0, 0, 0}};
  EXPECT_EQ(result, expect);
  graph.ClearGraph();
}

TEST(GraphAlgorithms, spanning_tree_2) {
  s21::Graph graph(1);
  graph.LoadGraphFromFile("./test/graph1.txt");
  s21::GraphAlgorithms algorithms;
  std::vector<std::vector<int>> result = algorithms.GetLeastSpanningTree(graph);
  double entire_weight = 0;
  for (auto &line : result) {
    for (auto v : line) {
      if (v != 0) entire_weight += v;
    }
  }
  entire_weight /= 2;
  ASSERT_NEAR(entire_weight, 150, 1e-7);
  graph.ClearGraph();
}

TEST(GraphAlgorithms, salesmam_problem_1) {
  s21::Graph graph(1);
  graph.LoadGraphFromFile("./test/graph1.txt");
  s21::GraphAlgorithms algorithms;
  s21::GraphAlgorithms::TsmResult result =
      algorithms.SolveTravelingSalesmanProblem(graph);
  ASSERT_EQ(result.vertices.size(), graph.GetVertexCount());
  ASSERT_NEAR(result.distance, 253, 1);
  graph.ClearGraph();
}

TEST(GraphAlgorithms, salesmam_problem_2) {
  s21::Graph graph(1);
  graph.LoadGraphFromFile("./test/graph2.txt");
  s21::GraphAlgorithms algorithms;
  s21::GraphAlgorithms::TsmResult result =
      algorithms.SolveTravelingSalesmanProblem(graph);
  ASSERT_EQ(result.vertices.size(), graph.GetVertexCount());
  ASSERT_NEAR(result.distance, 4, 1);
  graph.ClearGraph();
}