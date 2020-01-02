#include "maze.hpp"

int main()
{
    int row,column;
    std::cout << "Please input the row and column:";
    std::cin >> row >> column;
    Maze *maze = new Maze(row,column);

    maze->init();
    maze->createMaze(1,1,row-2,column-2);
    maze->findPath();
    std::cout << "\n";
    maze->printMaze();
    return 0;
}

