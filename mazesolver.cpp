/*
   MAZE SOLVER

*/
#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <algorithm>
using namespace std;
int traverse(char **maze, int x, int y)
{

    if (maze[x][y] == '1' || maze[x][y] == 'v')
        return 0;
    if (maze[x][y] == 'B')
        return 1;
    maze[x][y] = 'v';
    if (traverse(maze, x, y - 1)) // north
    {
        maze[x][y - 1] = '#';
        return 1;
    }
    if (traverse(maze, x + 1, y)) // south
    {
        maze[x + 1][y] = '#';
        return 1;
    }
    if (traverse(maze, x, y + 1)) // east
    {
        maze[x][y + 1] = '#';
        return 1;
    }
    if (traverse(maze, x - 1, y)) // west
    {
        maze[x - 1][y] = '#';
        return 1;
    }
    return 0;
}

int main()
{
    cout << "\n****************************************************************************************\n"
            "**********************************MAZE SOLVER******************************************\n\n";

    ifstream readMaze("mazeoutput.txt");
    if (!readMaze)
    {
        cerr << "Cannot open the File" << endl; // report error
        exit(0);
    }

    string str;
    int size, startY, startX, endX, endY;

    getline(readMaze, str);                                    // Read the first line from File
    str.erase(remove(str.begin(), str.end(), ' '), str.end()); // removes the spaces in the string
    size = str.length();                                       // length=breadth=size (square matrix)

    char **maze = new char *[size]; // dynamic 2d array to store the maze
    for (int i = 0; i < size; i++)
        maze[i] = new char[size];

    for (int i = 0; i < size; i++)
        maze[0][i] = str[i]; // put the first line in the array

    for (int j = 1; j < size; j++)
    {
        getline(readMaze, str);
        str.erase(remove(str.begin(), str.end(), ' '), str.end());
        for (int i = 0; i < size; i++)
        {
            maze[j][i] = str[i];
            if (str[i] == 'A')
            {
                startX = i;
                startY = j;
            }
            if (str[i] == 'B')
            {
                endX = i;
                endY = j;
            }
        }
    }
    readMaze.close();

    traverse(maze, startX, startY);

    maze[startX][startY] = 'A';
    maze[endY][endX] = 'B';
    ofstream MazeOutput("mazesolver.txt");
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {

            if (maze[i][j] == 'v')
                maze[i][j] = '0';
            cout << maze[i][j] << " ";
            MazeOutput << maze[i][j] << " ";
        }
        cout << endl;
        MazeOutput << endl;
    }

    cout << "\n*The output is written to->mazesolver.txt" << endl
         << endl;
    MazeOutput.close(); // Close the file

    for (int i = 0; i < size; i++)
    {
        delete[] maze[i];
    }
    delete[] maze; // clear the heap memory allocation

    return 0;
}
