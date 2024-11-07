#include "s21_graph.h"

s21::Graph::Graph(int size) {
  vertexCount_ = size;
  adjacencyMatrix_ = new int*[vertexCount_];
  for (int i = 0; i < vertexCount_; ++i) {
    adjacencyMatrix_[i] =
        new int[vertexCount_];  // или инициализация значениями, например, 0
    std::fill(adjacencyMatrix_[i], adjacencyMatrix_[i] + vertexCount_,
              0);  // Инициализация нулями
  }
}

void s21::Graph::LoadGraphFromFile(const std::string& filename) {
  std::ifstream inFile(filename);
  if (!inFile.is_open()) {
    std::cerr << "Could not open the file: " << filename << std::endl;
    return;
  }

  std::string line;
  if (std::getline(inFile, line)) {
    vertexCount_ = std::stoi(line);
    // Инициализация матрицы смежности
    adjacencyMatrix_ = new int*[vertexCount_];
    for (int i = 0; i < vertexCount_; ++i) {
      adjacencyMatrix_[i] = new int[vertexCount_]();
    }
  }

  int rowIndex = 0;
  while (std::getline(inFile, line) && rowIndex < vertexCount_) {
    std::istringstream ss(line);
    for (int colIndex = 0; colIndex < vertexCount_; ++colIndex) {
      ss >> adjacencyMatrix_[rowIndex][colIndex];
    }
    rowIndex++;
  }

  inFile.close();
}

void s21::Graph::ExportGraphToDot(const std::string& filename) {
  bool isDirected = IsDirected();
  std::ofstream outFile(filename);
  if (!outFile.is_open()) {
    std::cerr << "Could not open the file: " << filename << std::endl;
    return;
  }

  // Выводим имя графа
  std::string graphType = isDirected ? "digraph" : "graph";
  outFile << graphType << " graphname {\n";

  // Добавляем вершины
  for (int i = 0; i < vertexCount_; i++) {
    outFile << "    " << (i + 1) << ";\n";
  }

  // Добавляем рёбра
  for (int i = 0; i < vertexCount_; i++) {
    for (int j = 0; j < vertexCount_; j++) {
      if (adjacencyMatrix_[i][j] != 0) {
        if (isDirected) {
          outFile << "    " << (i + 1) << " -> " << (j + 1) << ";\n";
        } else {
          outFile << "    " << (i + 1) << " -- " << (j + 1) << ";\n";
        }
      }
    }
  }

  outFile << "}\n";
  outFile.close();
}

bool s21::Graph::IsDirected() const {
  // Реализуйте метод, который определяет, является ли граф направленным или
  // нет.
  return false;  // Например, по умолчанию определим как ненаправленный.
}

int s21::Graph::getVertexCount() { return vertexCount_; }

int s21::Graph::getEdge(int src, int dest) {
  return adjacencyMatrix_[src][dest];
}