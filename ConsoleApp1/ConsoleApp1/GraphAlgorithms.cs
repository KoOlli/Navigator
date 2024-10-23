using System;
using S21;

namespace s21
{
    public class GraphAlgorithms
    {
        private Stack<int> stack;
        private Queue<int> queue;

        public int[] DepthFirstSearch(Graph graph, int startVertex)
        {
            startVertex -= 1;
            int vertexCount = graph.GetVertexCount();
            bool[] visited = new bool[vertexCount];
            Stack<int> result = new Stack<int>();

            DepthFirstSearch(graph, startVertex, visited, result);
            return result.ToArray();
        }

        private void DepthFirstSearch(Graph graph, int vertex, bool[] visited, Stack<int> result)
        {
            visited[vertex] = true;
            result.Push(vertex + 1);

            for (int i = 0; i < graph.GetVertexCount(); i++)
            {
                if (graph.GetEdge(vertex, i) != 0 && !visited[i])
                {
                    DepthFirstSearch(graph, i, visited, result);
                }
            }
        }

        public int[] BreadthFirstSearch(Graph graph, int startVertex)
        {
            startVertex -= 1;
            int vertexCount = graph.GetVertexCount();
            bool[] visited = new bool[vertexCount];
            queue = new Queue<int>();
            int[] result = new int[vertexCount];
            int index = 0;

            queue.Push(startVertex);
            visited[startVertex] = true;

            while (!queue.IsEmpty())
            {
                int currentVertex = queue.Front();
                queue.Pop();
                result[index++] = currentVertex + 1;
                for (int i = 0; i < vertexCount; i++)
                {
                    if (graph.GetEdge(currentVertex, i) != 0 && !visited[i])
                    {
                        queue.Push(i);
                        visited[i] = true;
                    }
                }
            }

            Array.Resize(ref result, index);
            return result;
        }

        // Метод для поиска кратчайшего пути между двумя вершинами с помощью алгоритма Дейкстры
        public int GetShortestPathBetweenVertices(Graph graph, int vertex1, int vertex2)
        {
            int vertexCount = graph.GetVertexCount();
            bool[] visited = new bool[vertexCount];
            int[] distances = new int[vertexCount];

            // Инициализация массивов
            for (int i = 0; i < vertexCount; i++)
            {
                distances[i] = (i == vertex1) ? 0 : int.MaxValue; // Расстояние до стартовой вершины 0
            }

            for (int count = 0; count < vertexCount - 1; count++)
            {
                int minDistanceVertex = GetMinimumDistanceVertex(distances, visited);
                visited[minDistanceVertex] = true;

                for (int neighbor = 0; neighbor < vertexCount; neighbor++)
                {
                    int edgeWeight = graph.GetEdge(minDistanceVertex, neighbor);
                    if (!visited[neighbor] && edgeWeight != int.MaxValue &&
                        distances[minDistanceVertex] + edgeWeight < distances[neighbor])
                    {
                        distances[neighbor] = distances[minDistanceVertex] + edgeWeight;
                    }
                }
            }

            return distances[vertex2]; // Возвращаем кратчайшее расстояние до vertex2
        }

        private int GetMinimumDistanceVertex(int[] distances, bool[] visited)
        {
            int minValue = int.MaxValue;
            int minIndex = -1;

            for (int i = 0; i < distances.Length; i++)
            {
                if (!visited[i] && distances[i] <= minValue)
                {
                    minValue = distances[i];
                    minIndex = i;
                }
            }

            return minIndex;
        }

        // Метод для поиска кратчайших путей между всеми парами вершин с помощью алгоритма Флойда-Уоршелла
        public int[,] GetShortestPathsBetweenAllVertices(Graph graph)
        {
            int vertexCount = graph.GetVertexCount();
            int[,] distanceMatrix = new int[vertexCount, vertexCount];

            // Инициализация матрицы расстояний
            for (int i = 0; i < vertexCount; i++)
            {
                for (int j = 0; j < vertexCount; j++)
                {
                    if (i == j)
                        distanceMatrix[i, j] = 0;
                    else
                        distanceMatrix[i, j] = graph.GetEdge(i, j);
                }
            }

            // Алгоритм Флойда-Уоршелла
            for (int k = 0; k < vertexCount; k++)
            {
                for (int i = 0; i < vertexCount; i++)
                {
                    for (int j = 0; j < vertexCount; j++)
                    {
                        if (distanceMatrix[i, k] != int.MaxValue && distanceMatrix[k, j] != int.MaxValue &&
                            distanceMatrix[i, j] > distanceMatrix[i, k] + distanceMatrix[k, j])
                        {
                            distanceMatrix[i, j] = distanceMatrix[i, k] + distanceMatrix[k, j];
                        }
                    }
                }
            }

            return distanceMatrix; // Возвращаем матрицу кратчайших расстояний
        }


        // Метод для нахождения минимального остовного дерева с использованием алгоритма Прима
        public int[,] GetLeastSpanningTree(Graph graph)
        {
            int vertexCount = graph.GetVertexCount();
            // Матрица для минимального остовного дерева
            int[,] mst = new int[vertexCount, vertexCount];

            // Массив для хранения выбранных вершин
            bool[] visited = new bool[vertexCount];
            // Массив для хранения минимальных весов
            int[] minEdgeWeights = new int[vertexCount];
            // Массив для хранения ребер
            int[] parent = new int[vertexCount];

            // Инициализируем массивы
            for (int i = 0; i < vertexCount; i++)
            {
                minEdgeWeights[i] = int.MaxValue; // Изначально бесконечные веса
                visited[i] = false; // Все вершины непосещенные
                parent[i] = -1; // Начальные родительские вершины
            }

            // Начнем с первой вершины
            minEdgeWeights[0] = 0; // Выбираем первую вершину в качестве начальной

            for (int count = 0; count < vertexCount - 1; count++)
            {
                // Выбор минимального веса ребра из непосещенных вершин
                int u = GetMinimumDistanceVertex(minEdgeWeights, visited);
                visited[u] = true; // Помечаем вершину как посещенную

                // Обновляем веса рёбер
                for (int v = 0; v < vertexCount; v++)
                {
                    // Если есть ребро от u до v и v не посещена
                    if (graph.GetEdge(u, v) != int.MaxValue && !visited[v] &&
                        graph.GetEdge(u, v) < minEdgeWeights[v])
                    {
                        parent[v] = u; // Обновляем родителя
                        minEdgeWeights[v] = graph.GetEdge(u, v); // Обновляем вес
                    }
                }
            }

            // Строим матрицу смежности для минимального остовного дерева
            for (int i = 1; i < vertexCount; i++)
            {
                int u = parent[i];
                int v = i;
                mst[u, v] = graph.GetEdge(u, v); // Добавляем ребро в остовное дерево
                mst[v, u] = graph.GetEdge(u, v); // Так как граф неориентированный
            }

            return mst; // Возвращаем матрицу минимального остовного дерева
        }

        public TsmResult SolveTravelingSalesmanProblem(Graph graph)
        {
            int vertexCount = graph.GetVertexCount();
            double[,] pheromone = new double[vertexCount, vertexCount];
            double[,] distance = new double[vertexCount, vertexCount];
            Random random = new Random();

            // Инициализация расстояний и феромонов
            for (int i = 0; i < vertexCount; i++)
            {
                for (int j = 0; j < vertexCount; j++)
                {
                    if (i != j)
                    {
                        distance[i, j] = graph.GetEdge(i, j);
                        pheromone[i, j] = 1.0; // Начальное значение феромонов
                    }
                    else
                    {
                        distance[i, j] = double.MaxValue; // Нет самосоединений
                    }
                }
            }

            // Параметры алгоритма
            // int maxIterations = vertexCount * vertexCount;
            // int antCount = vertexCount;
            // double alpha = 1.0; // Влияние феромонов
            // double beta = 2.0; // Влияние расстояний
            // double evaporationRate = 0.5;
            
            int maxIterations = 200; // Увеличено для повышения надежности
            int antCount = 20; // Увеличено для улучшения поиска
            double alpha = 1.5; // Увеличено, чтобы феромоны оказали больше влияния
            double beta = 2.5; // Увеличено, чтобы расстояния имели заметное влияние
            double evaporationRate = 0.3;

            int[] bestRoute = new int[vertexCount];
            double bestDistance = double.MaxValue;

            // Основной цикл алгоритма
            for (int iteration = 0; iteration < maxIterations; iteration++)
            {
                for (int ant = 0; ant < antCount; ant++)
                {
                    // Стартуем с случайной вершины
                    bool[] visited = new bool[vertexCount];
                    List<int> route = new List<int>();
                    int currentVertex = random.Next(vertexCount);
                    visited[currentVertex] = true;
                    route.PushBack(currentVertex);

                    // Построение маршрута
                    for (int step = 1; step < vertexCount; step++)
                    {
                        currentVertex = SelectNextVertex(currentVertex, visited, pheromone, distance, alpha, beta,
                            random);
                        visited[currentVertex] = true;
                        route.PushBack(currentVertex);
                    }

                    // Возврат к стартовой вершине
                    route.PushBack(route.Front());
                    double routeDistance = CalculateRouteDistance(route.ToArray(), distance);

                    // Обновление лучшего маршрута
                    if (routeDistance < bestDistance)
                    {
                        bestDistance = routeDistance;
                        bestRoute = route.ToArray();
                    }

                    // Обновление феромонов
                    UpdatePheromones(pheromone, routeDistance, route.ToArray(), evaporationRate);
                }
            }

            // Console.WriteLine("");
            // foreach (var elem in bestRoute)
            // {
            //     Console.Write(elem + " -> ");
            // }
            // Console.WriteLine(bestDistance);
            
            // Возвращаем результат
            return new TsmResult { vertices = bestRoute, distance = bestDistance };
        }

        // Метод для выбора следующей вершины на основе феромонов и расстояний
        private int SelectNextVertex(int currentVertex, bool[] visited, double[,] pheromone, double[,] distance,
            double alpha, double beta, Random random)
        {
            double[] probabilities = new double[pheromone.GetLength(0)];
            double sum = 0.0;

            for (int i = 0; i < pheromone.GetLength(0); i++)
            {
                if (!visited[i] && distance[currentVertex, i] != double.MaxValue)
                {
                    probabilities[i] = Math.Pow(pheromone[currentVertex, i], alpha) *
                                       Math.Pow(1.0 / distance[currentVertex, i], beta);
                    sum += probabilities[i];
                }
            }

            // Нормализация вероятностей
            for (int i = 0; i < probabilities.Length; i++)
            {
                probabilities[i] = (sum > 0) ? probabilities[i] / sum : 0;
            }

            // Выбор следующей вершины
            double cumulative = 0.0;
            double rand = random.NextDouble();
            for (int i = 0; i < probabilities.Length; i++)
            {
                cumulative += probabilities[i];
                if (rand < cumulative)
                {
                    return i;
                }
            }

            return -1; // Ничего не выбрано (должно произойти никогда)
        }

        // Метод для расчета длины маршрута
        private double CalculateRouteDistance(int[] route, double[,] distance)
        {
            double totalDistance = 0.0;

            for (int i = 0; i < route.Length - 1; i++)
            {
                totalDistance += distance[route[i], route[i + 1]];
            }

            return totalDistance;
        }

        // Метод для обновления феромонов на основе пройденного маршрута
        private void UpdatePheromones(double[,] pheromone, double routeDistance, int[] route, double evaporationRate)
        {
            for (int i = 0; i < pheromone.GetLength(0); i++)
            {
                for (int j = 0; j < pheromone.GetLength(1); j++)
                {
                    pheromone[i, j] *= (1 - evaporationRate); // Испарение феромона
                }
            }

            double pheromoneIncrement = 1.0 / routeDistance;

            // Обновление феромонов на рёбрах маршрута
            for (int i = 0; i < route.Length - 1; i++)
            {
                int from = route[i];
                int to = route[i + 1];
                pheromone[from, to] += pheromoneIncrement;
                pheromone[to, from] += pheromoneIncrement; // Так как граф неориентированный
            }
        }
    }
}