#ifndef S21_SIMPLE_NAVIGATOR_S21_GRATH__H_
#define S21_SIMPLE_NAVIGATOR_S21_GRATH__H_

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

  void LoadGraphFromFile(const std::string& filename);
  void ExportGraphToDot(const std::string& filename);
  bool IsDirected() const;

  int getVertexCount();
  int getEdge(int src, int dest);

 private:
  int** adjacencyMatrix_;
  int vertexCount_;
};
}  // namespace s21

#endif  // S21_SIMPLE_NAVIGATOR_S21_GRATH__H_
