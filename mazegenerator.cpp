/*


    **Four corners(first and last column and row) are left for the boundary
    **'A' is fixed at 1,1 and 'B' changes randomly in the row before the last

*/
#include <iostream>
#include <cstdlib>
#include <stack>
#include <ctime>
#include <fstream>

#define N 0 // north
#define S 1 // south
#define E 2 // east
#define W 3 // west

using namespace std;

int locX = 1, locY = 1;

int horizontal(int direction, int x)
{
    if (direction == E)
        return x + 1;
    else if (direction == W)
        return x - 1;
    else
        return x;
}

int vertical(int direction, int y)
{
    if (direction == N)
        return y - 1;
    else if (direction == S)
        return y + 1;
    else
        return y;
}

bool available(int x, int y, int direction, char **maze, int size)
{
    x = horizontal(direction, x);
    y = vertical(direction, y);

    if (maze[y][x] == '0' || x >= (size - 1) || x <= 0 || y <= 0 || y >= (size - 1))
    {
        return false;
    }

    if (direction == N)
    {
        if (maze[y][x - 1] != '0' && maze[y - 1][x] != '0' && maze[y][x + 1] != '0' && maze[y - 1][x - 1] != '0' && maze[y - 1][x + 1] != '0')
        {
            return true;
        }
    }
    if (direction == S)
    {
        if (maze[y][x - 1] != '0' && maze[y + 1][x] != '0' && maze[y][x + 1] != '0' && maze[y + 1][x - 1] != '0' && maze[y + 1][x + 1] != '0')
        {
            return true;
        }
    }
    if (direction == E)
    {
        if (maze[y][x + 1] != '0' && maze[y - 1][x] != '0' && maze[y + 1][x] != '0' && maze[y - 1][x + 1] != '0' && maze[y + 1][x + 1] != '0')
        {
            return true;
        }
    }
    if (direction == W)
    {
        if (maze[y][x - 1] != '0' && maze[y - 1][x] != '0' && maze[y + 1][x] != '0' && maze[y - 1][x - 1] != '0' && maze[y + 1][x - 1] != '0')
        {
            return true;
        }
    }
    return false;
}

main()
{
    int size;

    cout << "\n****************************************************************************************\n"
            "****************************RANDOM MAZE GENERATOR***************************************\n\n"
         << " Note:" << endl;
    cout << "\t*size should be greater than 4" << endl
         << "\t*size=n   -> n*n maze" << endl;
    cout << "\n size: ";
    cin >> size;

    while (size < 5)
    {
        cout << "Invalid input.Enter a size greater than 4" << endl
             << endl;
        cout << "size:";
        cin >> size;
    }

    char **maze = new char *[size]; // dynamic 2d array to store the maze
    for (int i = 0; i < size; i++)
        maze[i] = new char[size];

    for (int i = 0; i < size; i++) // initializing the array to 1
    {
        for (int j = 0; j < size; j++)
        {
            maze[i][j] = '1';
        }
    }

    srand(time(0));

    stack<int> xStack; // x coordinate
    stack<int> yStack; // y coordinate

    int numPosition = 0; // number of free positions
    int direction = 0;   // random direction
    maze[1][1] = '0';    // avoid clusturing and creating 2 paths around A if it is unmarked in the beginning

    do
    {

        for (int i = 0; i < 4; i++)
        {
            if (available(locX, locY, i, maze, size))
                numPosition++;
        }

        if (numPosition == 1) // if one only possible move is there
        {
            if (available(locX, locY, N, maze, size))
                locY = vertical(N, locY);
            else if (available(locX, locY, S, maze, size))
                locY = vertical(S, locY);
            else if (available(locX, locY, E, maze, size))
                locX = horizontal(E, locX);
            else if (available(locX, locY, W, maze, size))
                locX = horizontal(W, locX);
        }

        else if (numPosition == 0) // backtracking
        {
            locX = xStack.top();
            locY = yStack.top();
            xStack.pop();
            yStack.pop();
        }

        else if (numPosition > 1) // if more than 1 possible move, push in to the  stack
        {
            xStack.push(locX);
            yStack.push(locY);

            do
            {
                direction = rand() % 4; // random direction
            } while (!available(locX, locY, direction, maze, size));

            locX = horizontal(direction, locX);
            locY = vertical(direction, locY);
        }

        maze[locY][locX] = '0';
        numPosition = 0;

    } while (!xStack.empty()); // or yStack

    cout << endl;

    maze[1][1] = 'A'; // A is always set at 1,1 of the maze
    int flag = 0, yrand, xrand;
    while (flag == 0)
    {
        yrand = size - 2; // row before the last
        xrand = rand() % (size - 2) + 1;
        if (maze[yrand][xrand] == '0')
        {
            maze[yrand][xrand] = 'B';
            flag = 1;
        }
    }

    ofstream MazeFile("mazeoutput.txt");
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {

            cout << maze[i][j] << " ";     // print solution
            MazeFile << maze[i][j] << " "; // Write to the file
        }
        cout << endl;
        MazeFile << endl;
    }
    cout << endl;
    cout << "*The output is written to->mazeoutput.txt" << endl
         << endl;

    MazeFile.close(); // Close the file
    for (int i = 0; i < size; i++)
    {
        delete[] maze[i]; // clear the heap memory allocation
    }
    delete[] maze;
    return 0;
}
