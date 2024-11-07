#ifndef S21_SIMPLE_NAVIGATOR_S21_GRATH_ALGORITHMS_H_
#define S21_SIMPLE_NAVIGATOR_S21_GRATH_ALGORITHMS_H_

#include "Containers/s21_queue.h"
#include "Containers/s21_stack.h"
#include "s21_graph.h"

namespace s21 {

class GraphAlgorithms {
 public:
  std::vector<int> DepthFirstSearch(s21::Graph graph, int startVertex);
  std::vector<int> BreadthFirstSearch(Graph graph, int startVertex);
  int GetShortestPathBetweenVertices(Graph graph, int vertex1, int vertex2);
  std::vector<std::vector<int>> GetShortestPathsBetweenAllVertices(Graph graph);
  std::vector<std::vector<int>> GetLeastSpanningTree(Graph graph);

 private:
  s21::stack<int> stack;
  s21::queue<int> queue;

  void DepthFirstSearch(s21::Graph graph, int vertex, bool* visited,
                        s21::stack<int>* result);
  std::vector<int> StackToArray(s21::stack<int> s);
  int GetMinimumDistanceVertex(int* distances, int vertexCount, bool* visited);
};
}  // namespace s21

#endif  // S21_SIMPLE_NAVIGATOR_S21_GRATH_ALGORITHMS_H_