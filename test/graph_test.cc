#include <gtest/gtest.h>

#include "../s21_graph.h"

TEST(Graph, open_and_read_1) {
  s21::Graph graph(1);
  bool result = graph.LoadGraphFromFile("aboba.txt");
  EXPECT_FALSE(result);
  graph.ClearGraph();
}

TEST(Graph, open_and_read_2) {
  s21::Graph graph(1);
  graph.LoadGraphFromFile("./test/graph1.txt");
  ASSERT_EQ(graph.GetVertexCount(), 11);
  ASSERT_EQ(graph.GetEdge(9, 1), 41);
  ASSERT_EQ(graph.GetEdge(1, 9), 41);
  ASSERT_EQ(graph.GetEdge(8, 6), 101);
  ASSERT_EQ(graph.GetEdge(6, 8), 101);
  ASSERT_EQ(graph.GetEdge(0, 0), 0);
  ASSERT_EQ(graph.GetEdge(10, 10), 0);
  ASSERT_EQ(graph.IsDirected(), false);
  graph.ClearGraph();
}

TEST(Graph, open_and_read_3) {
  s21::Graph graph(1);
  graph.LoadGraphFromFile("./test/graph2.txt");
  ASSERT_EQ(graph.GetVertexCount(), 4);
  ASSERT_EQ(graph.IsDirected(), true);
  graph.ClearGraph();
}

TEST(Graph, open_and_read_4) {
  s21::Graph graph(1);
  graph.LoadGraphFromFile("./test/graph1.txt");
  graph.ExportGraphToDot("./test/graph_to_dot1.dot");
  graph.ClearGraph();
}

TEST(Graph, open_and_read_5) {
  s21::Graph graph(1);
  graph.LoadGraphFromFile("./test/graph2.txt");
  graph.ExportGraphToDot("./test/graph_to_dot2.dot");
  graph.ClearGraph();
}

TEST(Graph, open_and_read_6) {
  s21::Graph graph(1);
  graph.LoadGraphFromFile("./test/graph2.txt");
  bool result = graph.ExportGraphToDot("");
  EXPECT_FALSE(result);
  graph.ClearGraph();
}
