#include "menu.h"

#include <iostream>

void PrintGrath(s21::Graph graph);
void Print();
void CheckInput();

void Print() {
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
  std::cout << "\e[1;36m0. Close program\n\e[0m" << std::endl;
  std::cout << "\e[1;36m_______________________________________________________"
               "__________________________________________________________\e[0m"
            << std::endl;
  std::cout << "\n\e[1;31mSelect menu item: \e[0m";
}

void CheckInput() {
  int menuNumber = 0;
  int startPoint = 0;
  int oneVertex = 0;
  int twoVertex = 0;
  s21::Graph *graph = new s21::Graph(1);
  s21::GraphAlgorithms *algorithms = new s21::GraphAlgorithms();
  bool isMenu = true;
  // std::vector<int> v;
  while (isMenu) {
    Print();
    std::cin >> menuNumber;
    std::cout << "\n";

    switch (menuNumber) {
      case 1:
        graph->LoadGraphFromFile("test.txt");
        PrintGrath(*graph);
        break;
      case 2:
        std::cout << "Enter start point: ";
        std::cin >> startPoint;  // нужно добавить проверку на выход за массив
        std::cout << "\n";
        for (auto elem : algorithms->DepthFirstSearch(*graph, startPoint))
          std::cout << elem << " -> ";
        std::cout << std::endl;
        break;
      case 3:
        std::cout << "Enter start point: ";
        std::cin >> startPoint;  // нужно добавить проверку на выход за массив
        std::cout << "\n";
        for (auto elem : algorithms->BreadthFirstSearch(*graph, startPoint))
          std::cout << elem << " -> ";
        std::cout << std::endl;
        break;
      case 4:
        std::cout << "Enter one vertex: ";
        std::cin >> oneVertex;  // нужно добавить проверку на выход за массив
        std::cout << "Enter two vertex: ";
        std::cin >> twoVertex;  // нужно добавить проверку на выход за массив
        std::cout << algorithms->GetShortestPathBetweenVertices(
                         *graph, oneVertex, twoVertex)
                  << std::endl;
        break;
      // case 5:
      //     s21::
      //     break;
      // case 6:
      //     s21::
      //     break;
      // case 7:
      //     s21::
      //     break;
      case 0:
        isMenu = false;
        std::cout << "Quit" << std::endl;
        break;

      default:
        break;
    }
    // std::cout << menuNumber << std::endl;
  }
}

void PrintGrath(s21::Graph graph) {
  for (int i = 0; i < graph.getVertexCount(); i++) {
    for (int j = 0; j < graph.getVertexCount(); j++) {
      std::cout << graph.getEdge(i, j) << ", ";
    }
    std::cout << std::endl;
  }
}

int main() {
  // Print();
  CheckInput();

  return 0;
}