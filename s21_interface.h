#ifndef A2_SIMPLE_NAVIGATOR_V1_0_CPP_1_S21_INTERFACE_H_
#define A2_SIMPLE_NAVIGATOR_V1_0_CPP_1_S21_INTERFACE_H_

#include "s21_graph.h"
#include "s21_graph_algorithms.h"

namespace s21 {

enum Type { kBreadth, kDepth };

class Interface {
 public:
  Interface() = default;
  void Run();

 private:
  void Menu();
  void LoadGraphFromFile();
  void PrintGraph(Graph graph);
  void TraverseGraph(Type type);
  void FindShortestPathBetweenTwoVertices();
  void FindShortestPathsBetweenAllVertices();
  void SearchSpanningTree();
  void SolveTravelingSalesmanProblem();
  void SaveGraphToDot();

  int CheckInput();
  bool VertexIsValid(int number);

  Graph graph_ = s21::Graph(1);
  GraphAlgorithms algorithms_;
  bool graph_loaded_ = false;
};
}  // namespace s21

#endif  // A2_SIMPLE_NAVIGATOR_V1_0_CPP_1_S21_INTERFACE_H_