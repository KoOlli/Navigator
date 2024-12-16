#ifndef A2_SIMPLE_NAVIGATOR_V1_0_CPP_1_S21_GRAPH_ALGORITHMS_H_
#define A2_SIMPLE_NAVIGATOR_V1_0_CPP_1_S21_GRAPH_ALGORITHMS_H_

#include <cmath>
#include <limits>

#include "containers/s21_queue.h"
#include "containers/s21_stack.h"
#include "s21_graph.h"

namespace s21 {

constexpr double kInf = INFINITY;

class GraphAlgorithms {
 public:
  struct TsmResult {
    std::vector<int> vertices;
    double distance;
  };

  std::vector<int> DepthFirstSearch(Graph graph, int start_vertex);
  std::vector<int> BreadthFirstSearch(Graph graph, int start_vertex);
  int GetShortestPathBetweenVertices(Graph graph, int vertex1, int vertex2);
  std::vector<std::vector<int>> GetShortestPathsBetweenAllVertices(Graph graph);
  std::vector<std::vector<int>> GetLeastSpanningTree(Graph graph);
  TsmResult SolveTravelingSalesmanProblem(Graph& graph);

 private:
  void DepthFirstSearch(Graph graph, int vertex, bool* visited,
                        s21::stack<int>* result);
  std::vector<int> StackToArray(s21::stack<int> stack);
  int GetMinimumDistanceVertex(int* distances, int vertex_count, bool* visited);
  int SelectNextCity(const std::vector<std::vector<double>>& pheromones,
                     Graph& graph, const std::vector<bool>& visited,
                     int current_city, double alpha, double beta);
  void UpdatePheromones(std::vector<std::vector<double>>& pheromones,
                        const std::vector<int>& ant_tour, double distance,
                        double evaporation_rate);
};
}  // namespace s21

#endif  // A2_SIMPLE_NAVIGATOR_V1_0_CPP_1_S21_GRAPH_ALGORITHMS_H_