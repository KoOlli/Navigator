using System;
using System.ComponentModel;

namespace s21
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Hello");
            Graph grath1 = new Graph(11);
            grath1.LoadGraphFromFile("../../test.txt");

            for (int i = 0; i < grath1.GetVertexCount(); i++)
            {
                for (int j = 0; j < grath1.GetVertexCount(); j++)
                {
                    Console.Write(grath1.GetEdge(i, j) + ",");
                }
                Console.Write("\n");
            }
            grath1.ExportGraphToDot("../../test2.dot");
            
            GraphAlgorithms algorithms = new GraphAlgorithms();
               
            foreach (var elem in algorithms.DepthFirstSearch(grath1, 1))
            {
                Console.Write(elem + " -> ");
            }

            Console.WriteLine("");
            foreach (var elem in algorithms.BreadthFirstSearch(grath1, 1))
            {
                Console.Write(elem + " -> ");
            }
            
            Console.WriteLine("");
            Console.WriteLine(algorithms.GetShortestPathBetweenVertices(grath1, 5, 6));

            int[,] shortestPaths = algorithms.GetShortestPathsBetweenAllVertices(grath1);
            
            for (int i = 0; i < shortestPaths.GetLength(0); i++)
            {
                for (int j = 0; j < shortestPaths.GetLength(1); j++)
                {
                    Console.Write($"{shortestPaths[i, j]}\t");
                }
                Console.WriteLine();
            }
            
            int[,] shortestPaths2 = algorithms.GetLeastSpanningTree(grath1);
            
            for (int i = 0; i < shortestPaths2.GetLength(0); i++)
            {
                for (int j = 0; j < shortestPaths2.GetLength(1); j++)
                {
                    Console.Write($"{shortestPaths2[i, j]}\t");
                }
                Console.WriteLine();
            }

            TsmResult tsm = algorithms.SolveTravelingSalesmanProblem(grath1);
            
            Console.WriteLine("");
            foreach (var elem in tsm.vertices)
            {
                Console.Write(elem + " -> ");
            }
            Console.WriteLine(tsm.distance);
        }
    }
}
