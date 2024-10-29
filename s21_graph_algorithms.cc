#include "s21_graph_algorithms.h"

std::vector<int> s21::GraphAlgorithms::DepthFirstSearch(s21::Graph graph,
                                                        int startVertex) {
  startVertex--;
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
  startVertex--;
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
  vertex1--;
  vertex2--;
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

std::vector<std::vector<int>>
s21::GraphAlgorithms::GetShortestPathsBetweenAllVertices(Graph graph) {
  int vertexCount = graph.getVertexCount();
  std::vector<std::vector<int>> distanceMatrix = std::vector<std::vector<int>>(
      vertexCount, std::vector<int>(vertexCount, 0));

  // Инициализация матрицы расстояний
  for (int i = 0; i < vertexCount; i++) {
    for (int j = 0; j < vertexCount; j++) {
      if (i == j)
        distanceMatrix[i][j] = 0;
      else
        distanceMatrix[i][j] = graph.getEdge(i, j);
    }
  }

  // Алгоритм Флойда-Уоршелла
  for (int k = 0; k < vertexCount; k++) {
    for (int i = 0; i < vertexCount; i++) {
      for (int j = 0; j < vertexCount; j++) {
        if (distanceMatrix[i][k] != 2147483647 &&
            distanceMatrix[k][j] != 2147483647 &&
            distanceMatrix[i][j] >
                distanceMatrix[i][k] + distanceMatrix[k][j]) {
          distanceMatrix[i][j] = distanceMatrix[i][k] + distanceMatrix[k][j];
        }
      }
    }
  }

  return distanceMatrix;  // Возвращаем матрицу кратчайших расстояний
}

// Метод для нахождения минимального остовного дерева с использованием алгоритма
// Прима
std::vector<std::vector<int>> s21::GraphAlgorithms::GetLeastSpanningTree(
    Graph graph) {
  int vertexCount = graph.getVertexCount();
  // Матрица для минимального остовного дерева
  std::vector<std::vector<int>> mst = std::vector<std::vector<int>>(
      vertexCount, std::vector<int>(vertexCount, 0));

  // Массив для хранения выбранных вершин
  bool* visited = new bool[vertexCount];
  // Массив для хранения минимальных весов
  int* minEdgeWeights = new int[vertexCount];
  // Массив для хранения ребер
  int* parent = new int[vertexCount];

  // Инициализируем массивы
  for (int i = 0; i < vertexCount; i++) {
    minEdgeWeights[i] = 2147483647;  // Изначально бесконечные веса
    visited[i] = false;  // Все вершины непосещенные
    parent[i] = -1;  // Начальные родительские вершины
  }

  // Начнем с первой вершины
  minEdgeWeights[0] = 0;  // Выбираем первую вершину в качестве начальной

  for (int count = 0; count < vertexCount - 1; count++) {
    // Выбор минимального веса ребра из непосещенных вершин
    int u = GetMinimumDistanceVertex(minEdgeWeights, vertexCount, visited);
    visited[u] = true;  // Помечаем вершину как посещенную

    // Обновляем веса рёбер
    for (int v = 0; v < vertexCount; v++) {
      // Если есть ребро от u до v и v не посещена
      if (graph.getEdge(u, v) != 2147483647 && !visited[v] &&
          graph.getEdge(u, v) < minEdgeWeights[v]) {
        parent[v] = u;  // Обновляем родителя
        minEdgeWeights[v] = graph.getEdge(u, v);  // Обновляем вес
      }
    }
  }

  // Строим матрицу смежности для минимального остовного дерева
  for (int i = 1; i < vertexCount; i++) {
    int u = parent[i];
    int v = i;
    mst[u][v] = graph.getEdge(u, v);  // Добавляем ребро в остовное дерево
    mst[v][u] = graph.getEdge(u, v);  // Так как граф неориентированный
  }

  return mst;  // Возвращаем матрицу минимального остовного дерева
}