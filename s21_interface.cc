#include "s21_interface.h"

#include <iostream>
#include <limits>

void s21::Interface::Run() {
  bool is_menu = true;
  while (is_menu) {
    Menu();
    int menu_number = CheckInput();
    if (menu_number < 0 || menu_number > 8) {
      std::cout << "Invalid input. Use numbers from 0 to 8" << std::endl;
    } else {
      switch (menu_number) {
        case 1:
          LoadGraphFromFile();
          break;
        case 2:
          TraverseGraph(kBreadth);
          break;
        case 3:
          TraverseGraph(kDepth);
          break;
        case 4:
          FindShortestPathBetweenTwoVertices();
          break;
        case 5:
          FindShortestPathsBetweenAllVertices();
          break;
        case 6:
          SearchSpanningTree();
          break;
        case 7:
          SolveTravelingSalesmanProblem();
          break;
        case 8:
          SaveGraphToDot();
          break;
        case 0:
          is_menu = false;
          std::cout << "Quit" << std::endl;
          break;
        default:
          break;
      }
    }
  }
}

void s21::Interface::Menu() {
  std::cout
      << "\e[1;36m_____________________________________________________________"
         "____________________________________________________\n\e[0m"
      << std::endl;
  std::cout << "\e[1;36m1. Load the original graph from a file\e[0m"
            << std::endl;
  std::cout << "\e[1;36m2. Traverse the graph in breadth and print the result "
               "to the console\e[0m"
            << std::endl;
  std::cout << "\e[1;36m3. Traverse the graph in depth and print the result to "
               "the console\e[0m"
            << std::endl;
  std::cout << "\e[1;36m4. Find the shortest path between any two vertices and "
               "print the result to the console\e[0m"
            << std::endl;
  std::cout
      << "\e[1;36m5. Find the shortest paths between all pairs of vertices in "
         "the graph and print the result matrix to the console\e[0m"
      << std::endl;
  std::cout << "\e[1;36m6. Search for the minimum spanning tree in the graph "
               "and print the resulting adjacency matrix to the console\e[0m"
            << std::endl;
  std::cout << "\e[1;36m7. Solve the Salesman problem, with output of the "
               "resulting route and its length to the console\e[0m"
            << std::endl;
  std::cout << "\e[1;36m8. Exporting a graph to a dot file\e[0m" << std::endl;
  std::cout << "\e[1;36m0. Close program\n\e[0m" << std::endl;
  std::cout << "\e[1;36m_______________________________________________________"
               "__________________________________________________________\e[0m"
            << std::endl;
  std::cout << "\n\e[1;31mSelect menu item: \e[0m";
}

void s21::Interface::LoadGraphFromFile() {
  graph_.ClearGraph();
  std::cout << "Enter the path to the file: ";
  std::string file_path;
  std::cin >> file_path;
  if (graph_.LoadGraphFromFile(file_path)) {
    std::cout << "Graph loaded successfully." << std::endl;
    graph_loaded_ = true;
    PrintGraph(graph_);
  } else {
    std::cout << "Error: Graph not loaded. Please check the file path."
              << std::endl;
  }
}

void s21::Interface::TraverseGraph(Type type) {
  if (!graph_loaded_) {
    std::cout << "Graph not loaded, use 1 first" << std::endl;
  } else {
    std::vector<int> result;
    std::cout << "Enter start point: ";
    int start_point = CheckInput();
    std::cout << "\n";
    if (VertexIsValid(start_point)) {
      if (type == kBreadth) {
        result = algorithms_.BreadthFirstSearch(graph_, start_point);
      } else if (type == kDepth) {
        result = algorithms_.DepthFirstSearch(graph_, start_point);
      }
      for (size_t i = 0; i < result.size(); ++i) {
        if (i != result.size() - 1) {
          std::cout << result[i] << " -> ";
        } else {
          std::cout << result[i];
        }
      }
      std::cout << std::endl;
    } else {
      std::cout << "Incorrect vertex" << std::endl;
    }
  }
}

void s21::Interface::FindShortestPathBetweenTwoVertices() {
  if (!graph_loaded_) {
    std::cout << "Graph not loaded, use 1 first" << std::endl;
  } else {
    std::cout << "Enter one vertex: ";
    int one_vertex = CheckInput();
    if (!VertexIsValid(one_vertex)) {
      std::cout << "Incorrect vertex" << std::endl;
      return;
    } else {
      std::cout << "Enter two vertex: ";
      int two_vertex = CheckInput();
      if (VertexIsValid(two_vertex)) {
        int result = algorithms_.GetShortestPathBetweenVertices(
            graph_, one_vertex, two_vertex);
        std::cout << "\n";
        std::cout << result << std::endl;
      } else
        std::cout << "Incorrect vertex" << std::endl;
    }
  }
}

void s21::Interface::FindShortestPathsBetweenAllVertices() {
  if (!graph_loaded_) {
    std::cout << "Graph not loaded, use 1 first" << std::endl;
  } else {
    try {
      std::vector<std::vector<int>> shortest_paths;
      shortest_paths = algorithms_.GetShortestPathsBetweenAllVertices(graph_);
      for (int i = 0; i < graph_.GetVertexCount(); i++) {
        for (int j = 0; j < graph_.GetVertexCount(); j++) {
          std::cout << shortest_paths[i][j] << "\t";
        }
        std::cout << std::endl;
      }
    } catch (...) {
      std::cout << "Invalid input" << std::endl;
    }
  }
}

void s21::Interface::SearchSpanningTree() {
  if (!graph_loaded_) {
    std::cout << "Graph not loaded, use 1 first" << std::endl;
  } else {
    try {
      std::vector<std::vector<int>> least_spanning_tree;
      least_spanning_tree = algorithms_.GetLeastSpanningTree(graph_);
      for (int i = 0; i < graph_.GetVertexCount(); i++) {
        for (int j = 0; j < graph_.GetVertexCount(); j++) {
          std::cout << least_spanning_tree[i][j] << "\t";
        }
        std::cout << std::endl;
      }
    } catch (...) {
      std::cout << "Invalid input" << std::endl;
    }
  }
}

void s21::Interface::SolveTravelingSalesmanProblem() {
  if (!graph_loaded_) {
    std::cout << "Graph not loaded, use 1 first" << std::endl;
  } else {
    s21::GraphAlgorithms::TsmResult result;
    result = algorithms_.SolveTravelingSalesmanProblem(graph_);

    std::cout << "Visited cities: ";
    for (int vertex : result.vertices) {
      std::cout << vertex << " ";
    }
    std::cout << "\nLength of this route: " << result.distance << std::endl;
  }
}

void s21::Interface::SaveGraphToDot() {
  if (!graph_loaded_) {
    std::cout << "Graph not loaded, use 1 first" << std::endl;
  } else {
    std::cout << "Enter the path to the file: ";
    std::string file_path;
    std::cin >> file_path;
    if (graph_.ExportGraphToDot(file_path)) {
      std::cout << "Graph was exported successfully" << std::endl;
    } else {
      std::cout << "Error: Graph was not exported." << std::endl;
    }
  }
}

void s21::Interface::PrintGraph(Graph graph) {
  for (int i = 0; i < graph.GetVertexCount(); i++) {
    for (int j = 0; j < graph.GetVertexCount(); j++) {
      std::cout << graph.GetEdge(i, j) << "\t";
    }
    std::cout << std::endl;
  }
}

int s21::Interface::CheckInput() {
  int number;
  while (!(std::cin >> number)) {
    std::cout << "Invalid input. Try again" << std::endl;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  return number;
}

bool s21::Interface::VertexIsValid(int number) {
  if (number < 1 || number > graph_.GetVertexCount()) {
    return false;
  }
  return true;
}
