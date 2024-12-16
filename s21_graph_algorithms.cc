#include "s21_graph_algorithms.h"

std::vector<int> s21::GraphAlgorithms::DepthFirstSearch(Graph graph,
                                                        int start_vertex) {
  start_vertex--;
  int vertex_count = graph.GetVertexCount();
  bool* visited = new bool[vertex_count];
  for (int i = 0; i < vertex_count; ++i) {
    visited[i] = false;
  }
  s21::stack<int> result = s21::stack<int>();

  DepthFirstSearch(graph, start_vertex, visited, &result);
  delete[] visited;
  return StackToArray(result);
}

void s21::GraphAlgorithms::DepthFirstSearch(Graph graph, int vertex,
                                            bool* visited,
                                            s21::stack<int>* result) {
  visited[vertex] = true;
  result->push(vertex + 1);

  for (int i = 0; i < graph.GetVertexCount(); ++i) {
    if (graph.GetEdge(vertex, i) != 0 && !visited[i]) {
      DepthFirstSearch(graph, i, visited, result);
    }
  }
}

std::vector<int> s21::GraphAlgorithms::StackToArray(s21::stack<int> stack) {
  std::vector<int> vector;
  while (!stack.empty()) {
    vector.push_back(stack.top());
    stack.pop();
  }
  std::reverse(vector.begin(), vector.end());
  return vector;
}

std::vector<int> s21::GraphAlgorithms::BreadthFirstSearch(Graph graph,
                                                          int start_vertex) {
  start_vertex--;
  int vertex_count = graph.GetVertexCount();
  bool* visited = new bool[vertex_count]();
  s21::queue<int> queue = s21::queue<int>();
  std::vector<int> result;

  visited[start_vertex] = true;
  queue.push(start_vertex);

  while (!queue.empty()) {
    int current_vertex = queue.front();
    queue.pop();
    result.push_back(current_vertex + 1);
    for (int i = 0; i < vertex_count; ++i) {
      if (graph.GetEdge(current_vertex, i) != 0 && !visited[i]) {
        queue.push(i);
        visited[i] = true;
      }
    }
  }
  delete[] visited;
  return result;
}

int s21::GraphAlgorithms::GetShortestPathBetweenVertices(Graph graph,
                                                         int vertex1,
                                                         int vertex2) {
  vertex1--;
  vertex2--;
  int vertex_count = graph.GetVertexCount();
  bool* visited = new bool[vertex_count];
  int* distances = new int[vertex_count];

  for (int i = 0; i < vertex_count; ++i) {
    visited[i] = false;
    distances[i] = (i == vertex1) ? 0 : 2147483647;
  }

  for (int count = 0; count < vertex_count - 1; ++count) {
    int min_distance_vertex =
        GetMinimumDistanceVertex(distances, vertex_count, visited);
    visited[min_distance_vertex] = true;

    for (int neighbor = 0; neighbor < vertex_count; ++neighbor) {
      int edge_weight = graph.GetEdge(min_distance_vertex, neighbor);
      if (!visited[neighbor] && edge_weight != 2147483647 &&
          distances[min_distance_vertex] + edge_weight < distances[neighbor]) {
        distances[neighbor] = distances[min_distance_vertex] + edge_weight;
      }
    }
  }
  int result = distances[vertex2];
  delete[] visited;
  delete[] distances;
  return result;
}

int s21::GraphAlgorithms::GetMinimumDistanceVertex(int* distances,
                                                   int vertex_count,
                                                   bool* visited) {
  int min_value = 2147483647;
  int min_index = -1;

  for (int i = 0; i < vertex_count; ++i) {
    if (!visited[i] && distances[i] <= min_value) {
      min_value = distances[i];
      min_index = i;
    }
  }

  return min_index;
}

std::vector<std::vector<int>>
s21::GraphAlgorithms::GetShortestPathsBetweenAllVertices(Graph graph) {
  int vertex_count = graph.GetVertexCount();
  std::vector<std::vector<int>> distance_matrix(
      vertex_count,
      std::vector<int>(vertex_count, std::numeric_limits<int>::max()));

  for (int i = 0; i < vertex_count; ++i) {
    for (int j = 0; j < vertex_count; ++j) {
      if (i == j) {
        distance_matrix[i][j] = 0;
      } else {
        int edge = graph.GetEdge(i, j);
        if (edge != 0) {
          distance_matrix[i][j] = edge;
        }
      }
    }
  }

  for (int k = 0; k < vertex_count; ++k) {
    for (int i = 0; i < vertex_count; ++i) {
      for (int j = 0; j < vertex_count; ++j) {
        if (distance_matrix[i][k] != std::numeric_limits<int>::max() &&
            distance_matrix[k][j] != std::numeric_limits<int>::max() &&
            distance_matrix[i][j] >
                distance_matrix[i][k] + distance_matrix[k][j]) {
          distance_matrix[i][j] = distance_matrix[i][k] + distance_matrix[k][j];
        }
      }
    }
  }

  return distance_matrix;
}

std::vector<std::vector<int>> s21::GraphAlgorithms::GetLeastSpanningTree(
    Graph graph) {
  int vertex_count = graph.GetVertexCount();
  std::vector<std::vector<int>> mst = std::vector<std::vector<int>>(
      vertex_count, std::vector<int>(vertex_count, 0));

  bool* visited = new bool[vertex_count];
  int* min_edge_weights = new int[vertex_count];
  int* parent = new int[vertex_count];

  for (int i = 0; i < vertex_count; ++i) {
    min_edge_weights[i] = 2147483647;
    visited[i] = false;
    parent[i] = -1;
  }

  min_edge_weights[0] = 0;

  for (int count = 0; count < vertex_count - 1; ++count) {
    int row = GetMinimumDistanceVertex(min_edge_weights, vertex_count, visited);
    visited[row] = true;

    for (int col = 0; col < vertex_count; col++) {
      if (graph.GetEdge(row, col) != 2147483647 && !visited[col] &&
          graph.GetEdge(row, col) < min_edge_weights[col]) {
        parent[col] = row;
        min_edge_weights[col] = graph.GetEdge(row, col);
      }
    }
  }

  for (int i = 1; i < vertex_count; ++i) {
    int row = parent[i];
    int col = i;
    mst[row][col] = graph.GetEdge(row, col);
    mst[col][row] = graph.GetEdge(row, col);
  }
  delete[] visited;
  delete[] min_edge_weights;
  delete[] parent;
  return mst;
}

s21::GraphAlgorithms::TsmResult
s21::GraphAlgorithms::SolveTravelingSalesmanProblem(Graph& graph) {
  TsmResult result{std::vector<int>(), kInf};
  size_t num_cities = graph.GetVertexCount();
  std::vector<std::vector<double>> pheromones(
      num_cities, std::vector<double>(num_cities, 1.0));
  double best_distance = std::numeric_limits<double>::max();
  std::vector<int> best_path;

  const int MAX_ITERATIONS = 2000;
  const double ALPHA = 1.0;
  const double BETA = 2.0;
  const double EVAPORATION_RATE = 0.1;

  for (int iteration = 0; iteration < MAX_ITERATIONS; ++iteration) {
    std::vector<int> current_path;
    std::vector<bool> visited(num_cities, false);
    int current_city = rand() % num_cities;
    visited[current_city] = true;
    current_path.push_back(current_city);
    double current_distance = 0.0;

    for (size_t step = 1; step < num_cities; ++step) {
      current_city = SelectNextCity(pheromones, graph, visited,
                                    current_path.back(), ALPHA, BETA);
      if (current_city == -1) {
        break;
      }
      current_path.push_back(current_city);
      visited[current_city] = true;
      current_distance += graph.GetEdge(current_path[step - 1], current_city);
    }
    // Вернуться в стартовый город, если текущий путь успешно завершен
    if (current_path.size() == num_cities) {
      current_distance += graph.GetEdge(current_path.back(), current_path[0]);

      if (current_distance < best_distance) {
        best_distance = current_distance;
        best_path = current_path;
      }
    }

    UpdatePheromones(pheromones, current_path, current_distance,
                     EVAPORATION_RATE);
  }

  result.vertices = best_path;
  result.distance = best_distance;

  return result;
}

int s21::GraphAlgorithms::SelectNextCity(
    const std::vector<std::vector<double>>& pheromones, Graph& graph,
    const std::vector<bool>& visited, int current_city, double alpha,
    double beta) {
  int num_cities = pheromones.size();
  double total = 0.0;
  std::vector<double> probabilities(num_cities, 0.0);

  for (int i = 0; i < num_cities; ++i) {
    if (!visited[i]) {
      double pheromone = pheromones[current_city][i];
      double edge_length = graph.GetEdge(current_city, i);
      double heuristic = edge_length > 0 ? 1.0 / edge_length : 0;
      probabilities[i] = pow(pheromone, alpha) * pow(heuristic, beta);
      total += probabilities[i];
    }
  }

  if (total == 0.0) return -1;

  double rand_val = static_cast<double>(rand()) / RAND_MAX * total;
  for (int i = 0; i < num_cities; ++i) {
    if (!visited[i]) {
      rand_val -= probabilities[i];
      if (rand_val <= 0.0) {
        return i;
      }
    }
  }
  return 0;
}

void s21::GraphAlgorithms::UpdatePheromones(
    std::vector<std::vector<double>>& pheromones,
    const std::vector<int>& ant_tour, double distance,
    double evaporation_rate) {
  int num_cities = pheromones.size();
  for (int i = 0; i < num_cities; ++i) {
    for (int j = 0; j < num_cities; ++j) {
      pheromones[i][j] *= (1.0 - evaporation_rate);
    }
  }

  for (size_t i = 0; i < ant_tour.size(); ++i) {
    int from = ant_tour[i];
    int to = ant_tour[(i + 1) % ant_tour.size()];
    pheromones[from][to] += 1.0 / distance;
    pheromones[to][from] += 1.0 / distance;
  }
}
