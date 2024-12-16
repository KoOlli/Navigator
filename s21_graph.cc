#include "s21_graph.h"

s21::Graph::Graph(int size) : vertex_count_(size) {
  adjacency_matrix_ = new int*[vertex_count_];
  for (int i = 0; i < vertex_count_; ++i) {
    adjacency_matrix_[i] = new int[vertex_count_];
    std::fill(adjacency_matrix_[i], adjacency_matrix_[i] + vertex_count_, 0);
  }
}

bool s21::Graph::LoadGraphFromFile(const std::string& filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Could not open the file: " << filename << std::endl;
    return false;
  }
  ClearGraph();
  std::string line;
  if (std::getline(file, line)) {
    vertex_count_ = std::stoi(line);

    adjacency_matrix_ = new int*[vertex_count_];
    for (int i = 0; i < vertex_count_; ++i) {
      adjacency_matrix_[i] = new int[vertex_count_]();
    }
  }

  int row = 0;
  while (std::getline(file, line) && row < vertex_count_) {
    std::istringstream ss(line);
    for (int col = 0; col < vertex_count_; ++col) {
      ss >> adjacency_matrix_[row][col];
    }
    row++;
  }

  file.close();
  return true;
}

bool s21::Graph::ExportGraphToDot(const std::string& filename) {
  bool is_directed = IsDirected();
  std::ofstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Could not open the file: " << filename << std::endl;
    return false;
  }

  std::string graph_type = is_directed ? "digraph" : "graph";
  file << graph_type << " graphname {\n";

  for (int i = 0; i < vertex_count_; ++i) {
    file << "    " << (i + 1) << ";\n";
  }

  for (int i = 0; i < vertex_count_; ++i) {
    for (int j = 0; j < vertex_count_; ++j) {
      if (adjacency_matrix_[i][j] != 0) {
        if (is_directed) {
          file << "    " << (i + 1) << " -> " << (j + 1) << ";\n";
        } else {
          file << "    " << (i + 1) << " -- " << (j + 1) << ";\n";
        }
      }
    }
  }

  file << "}\n";
  file.close();
  return true;
}

bool s21::Graph::IsDirected() const {
  for (int i = 0; i < vertex_count_; ++i) {
    for (int j = 0; j < vertex_count_; ++j) {
      if (adjacency_matrix_[i][j] != adjacency_matrix_[j][i]) {
        return true;
      }
    }
  }
  return false;
}

int s21::Graph::GetVertexCount() { return vertex_count_; }

int s21::Graph::GetEdge(int row, int col) {
  return adjacency_matrix_[row][col];
}

void s21::Graph::ClearGraph() {
  if (adjacency_matrix_) {
    for (int i = 0; i < vertex_count_; ++i) {
      delete[] adjacency_matrix_[i];
    }
    delete[] adjacency_matrix_;
  }
  adjacency_matrix_ = nullptr;
  vertex_count_ = 0;
}
