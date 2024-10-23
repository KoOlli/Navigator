namespace s21
{
    using System.IO;

    public class Graph
    {
        private int[,] adjacencyMatrix;
        private int vertexCount;

        public Graph(int size)
        {
            adjacencyMatrix = new int[size, size];
            vertexCount = size;
        }

        public void LoadGraphFromFile(string filename)
        {
            // Здесь загружаем граф из файла в формате матрицы смежности
            using (var reader = new StreamReader(filename))
            {
                string line;
                int rowIndex = 0;
                if ((line = reader.ReadLine()) != null)
                    vertexCount = int.Parse(line);
                while ((line = reader.ReadLine()) != null)
                {
                    var values = line.Split(' ');

                    for (int colIndex = 0; colIndex < vertexCount; colIndex++)
                    {
                        adjacencyMatrix[rowIndex, colIndex] = int.Parse(values[colIndex]);
                    }

                    rowIndex++;
                }
            }
        }

        public void ExportGraphToDot(string filename)
        {
            bool isDirected = IsDirected();
            
            using (var writer = new StreamWriter(filename))
            {
                // Выводим имя графа
                string graphType = isDirected ? "digraph" : "graph";
                writer.WriteLine($"{graphType} graphname {{");

                // Добавляем вершины
                for (int i = 0; i < vertexCount; i++)
                {
                    writer.WriteLine($"    {i + 1};");
                }

                // Добавляем рёбра в зависимости от типа графа
                for (int i = 0; i < vertexCount; i++)
                {
                    for (int j = 0; j < vertexCount; j++)
                    {
                        if (adjacencyMatrix[i, j] != 0)
                        {
                            if (isDirected)
                            {
                                writer.WriteLine($"    {i + 1} -> {j + 1};");
                            }
                            else
                            {
                                writer.WriteLine($"    {i + 1} -- {j + 1};");
                            }
                        }
                    }
                }

                writer.WriteLine("}");
            }
        }

        private bool IsDirected()
        {
            for (int i = 0; i < vertexCount; i++)
            {
                for (int j = 0; j < vertexCount; j++)
                {
                    // Если есть ребро из i в j, но нет ребра из j в i,
                    // то граф ориентированный.
                    if (adjacencyMatrix[i, j] != 0 && adjacencyMatrix[j, i] == 0)
                    {
                        return true; // Граф ориентированный
                    }
                }
            }
            return false; // Граф неориентированный
        }
        
        public int GetVertexCount()
        {
            return vertexCount;
        }

        public int GetEdge(int src, int dest)
        {
            return adjacencyMatrix[src, dest];
        }
    }
}