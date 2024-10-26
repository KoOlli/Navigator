
#include "s21_graph_algorithms.h"

std::vector<int> s21::GraphAlgorithms::DepthFirstSearch(s21::Graph graph,
                                                        int startVertex) {
  startVertex -= 1;
  int vertexCount = graph.getVertexCount();
  bool* visited = new bool[vertexCount];
  s21::stack<int> result = s21::stack<int>();

  DepthFirstSearch(graph, startVertex, visited, &result);
  return StackToArray(result);
}

void s21::GraphAlgorithms::DepthFirstSearch(s21::Graph graph, int vertex,
                                            bool* visited,
                                            s21::stack<int>* result) {
  visited[vertex] = true;
  result->push(vertex + 1);

  for (int i = 0; i < graph.getVertexCount(); i++) {
    if (graph.getEdge(vertex, i) != 0 && !visited[i]) {
      DepthFirstSearch(graph, i, visited, result);
    }
  }
}

std::vector<int> s21::GraphAlgorithms::StackToArray(s21::stack<int> s) {
  std::vector<int> v;
  while (!s.empty()) {
    v.push_back(s.top());
    s.pop();
  }
  std::reverse(v.begin(), v.end());
  return v;
}

std::vector<int> s21::GraphAlgorithms::BreadthFirstSearch(s21::Graph graph,
                                                          int startVertex) {
  startVertex -= 1;
  int vertexCount = graph.getVertexCount();
  bool* visited = new bool[vertexCount];
  queue = s21::queue<int>();
  std::vector<int> result;
  int index = 0;

  queue.push(startVertex);
  visited[startVertex] = true;

  while (!queue.empty()) {
    int currentVertex = queue.front();
    queue.pop();
    result.push_back(currentVertex + 1);
    for (int i = 0; i < vertexCount; i++) {
      if (graph.getEdge(currentVertex, i) != 0 && !visited[i]) {
        queue.push(i);
        visited[i] = true;
      }
    }
  }

  return result;
}

int s21::GraphAlgorithms::GetShortestPathBetweenVertices(Graph graph,
                                                         int vertex1,
                                                         int vertex2) {
  int vertexCount = graph.getVertexCount();
  bool* visited = new bool[vertexCount];
  int* distances = new int[vertexCount];

  // Инициализация массивов
  for (int i = 0; i < vertexCount; i++) {
    distances[i] =
        (i == vertex1) ? 0 : 2147483647;  // Расстояние до стартовой вершины 0
  }

  for (int count = 0; count < vertexCount - 1; count++) {
    int minDistanceVertex =
        GetMinimumDistanceVertex(distances, vertexCount, visited);
    visited[minDistanceVertex] = true;

    for (int neighbor = 0; neighbor < vertexCount; neighbor++) {
      int edgeWeight = graph.getEdge(minDistanceVertex, neighbor);
      if (!visited[neighbor] && edgeWeight != 2147483647 &&
          distances[minDistanceVertex] + edgeWeight < distances[neighbor]) {
        distances[neighbor] = distances[minDistanceVertex] + edgeWeight;
      }
    }
  }

  return distances[vertex2];  // Возвращаем кратчайшее расстояние до vertex2
}

int s21::GraphAlgorithms::GetMinimumDistanceVertex(int* distances,
                                                   int vertexCount,
                                                   bool* visited) {
  int minValue = 2147483647;
  int minIndex = -1;

  for (int i = 0; i < vertexCount; i++) {
    if (!visited[i] && distances[i] <= minValue) {
      minValue = distances[i];
      minIndex = i;
    }
  }

  return minIndex;
}