// #include "menu.h"
#include <iostream>

void Print() {
    std::cout << "\e[1;36m_________________________________________________________________________________________________________________\n\e[0m" << std::endl;
    std::cout << "\e[1;36m1. Load the original graph from a file\e[0m" << std::endl;
    std::cout << "\e[1;36m2. Traverse the graph in breadth and print the result to the console\e[0m" << std::endl;
    std::cout << "\e[1;36m3. Traverse the graph in depth and print the result to the console\e[0m" << std::endl;
    std::cout << "\e[1;36m4. Find the shortest path between any two vertices and print the result to the console\e[0m" << std::endl;
    std::cout << "\e[1;36m5. Find the shortest paths between all pairs of vertices in the graph and print the result matrix to the console\e[0m" << std::endl;
    std::cout << "\e[1;36m6. Search for the minimum spanning tree in the graph and print the resulting adjacency matrix to the console\e[0m" << std::endl;
    std::cout << "\e[1;36m7. Solve the Salesman problem, with output of the resulting route and its length to the console\e[0m" << std::endl;
    std::cout << "\e[1;36m0. Close program\n\e[0m" << std::endl;
    std::cout << "\e[1;36m_________________________________________________________________________________________________________________\e[0m" << std::endl;
    std::cout << "\n\e[1;31mSelect menu item: \e[0m";
}

void CheckInput() {
    int menuNumber;
    std::cin >> menuNumber;
    std::cout << "\n";

    // switch (menuNumber)
    // {
    // case 1:
    //     s21::
    //     break;
    // case 2:
    //     s21::
    //     break;
    // case 3:
    //     s21::
    //     break;
    // case 4:
    //     s21::
    //     break;
    // case 5:
    //     s21::
    //     break;
    // case 6:
    //     s21::
    //     break;
    // case 7:
    //     s21::
    //     break;
    // case 0:
    //     s21::
    //     break;

    // default:

    //     break;
    // }
    std::cout << menuNumber<< std::endl;

}


int main() {
    Print();
    CheckInput();

    return 0;
}