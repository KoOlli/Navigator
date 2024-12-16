#ifndef A2_SIMPLE_NAVIGATOR_V1_0_CPP_1_S21_GRAPH_H_
#define A2_SIMPLE_NAVIGATOR_V1_0_CPP_1_S21_GRAPH_H_

#include <fstream>
#include <sstream>
#include <vector>

#include "algorithm"
#include "iostream"
#include "stdlib.h"

namespace s21 {

class Graph {
 public:
  Graph(int size);

  bool LoadGraphFromFile(const std::string& filename);
  bool ExportGraphToDot(const std::string& filename);
  bool IsDirected() const;

  int GetVertexCount();
  int GetEdge(int row, int col);
  void ClearGraph();

 private:
  int** adjacency_matrix_;
  int vertex_count_;
};
}  // namespace s21

#endif  // A2_SIMPLE_NAVIGATOR_V1_0_CPP_1_S21_GRAPH_H_
