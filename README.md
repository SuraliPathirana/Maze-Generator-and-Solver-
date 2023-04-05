# Maze-Generator-and-Solver-
![image](https://user-images.githubusercontent.com/78686787/230157183-00f19bde-7569-40e0-94a1-775972695efe.png)

 A single cell represents a single block on the puzzle. A ‘0’ would represent a white block which would be part of a path and 1 would represent a black block which would
 be a part of a wall.The starting point and the goal must always be on white blocks and must be denoted by the letters “A” and “B” respectively. All horizontal blocks must be space separated. For example, the puzzle in the above image would be represented by a 21x21 grid as follows:
 
 ![image](https://user-images.githubusercontent.com/78686787/230157587-39d02a56-be54-476b-98d6-5c76d3f848ae.png)
 
The solver algorithm creates a random square-shaped puzzle of a given size with one solution. The generated puzzle is also saved to a text file.The solver algorithm is completely seperate 
from the generator and uses recursion and backtracking. The solution path found by the algorithm is denoted by replacing the cells with “#” symbols and saved to a separate text file


![image](https://user-images.githubusercontent.com/78686787/230158467-7fcaece7-512a-463c-9026-80e33fcd109c.png)
