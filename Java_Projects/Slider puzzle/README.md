<h1>Slider puzzle</h1>

Java program to solve find the best solution to any slider puzzle.

Launch with :
```
java -jar out/artifacts/SliderPuzzleSolver/SliderPuzzleSolver.jar < puzzle
```

Puzzle format :
```
1 2 3                                     
4 5 6                 OK !        
7 8 0           

1      3 4    
8 6 2                 also OK !
 0          5 7  
 
1 2 13
4 65 6                not OK :(
7 8 -1

Use 0 to represent the missing tile.
No duplicate values.
Values in range from 0 to (n^2 - 1), n being the puzzle width. (e.g. 3 for the puzzles above)
```
