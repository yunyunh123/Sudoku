# Sudoku Game

# Libaries/Packages used:
For C++ code:
  - C++ Standard Library
  - SFML Library
For python:
  - Requests
  - JSON
  - Pprint
  - Random

# Compiling and Executing
The Sudoku application is compiled and executed by typing the following lines in the terminal:

  make main

  main

To create more puzzles and store them into "problems.txt", type the following line in the terminal:

  make prob

The makefile contains all classes and libraries needed for compiling.

# Introduction and Rules
Sodoku is a puzzle played on a 9x9 grid. There are 9 rows, 9 columns, and 9 (3x3) squares. Each row, column, and square has 9 boxes. While some boxes are already filled in, others can be filled out with the numbers 1-9.

The objective of the game: Each row, column, and square needs to be filled out without repeating any numbers.

# Grid
The grid has 81 boxes. Only empty boxes can be selected. To do so, click on the box using the cursor. Type any number between 1 and 9, inclusive. Any other characters, including 0, are prohibited. To change the number, the user should first 'delete' or 'backspace', then refill the box.

Use the cursor to select another box.

# Buttons
On the right side of the window, the user should see 4 buttons. Select a button by using the cursor and clicking on the button.

New Game: Clicking on this button will refill the grid with another puzzle. The puzzle's difficulty will change randomly.

Restart: This button restarts the grid but keeps the same puzzle. It will also restart the "Correct?" and "Start Time" button to its original state.

Correct?: Click on this button to check if the puzzle was solved correctly. If not, the button will display "No, Retry!". Keep clicking on this button to check your progress. Once the puzzle is solved correctly, the button will display "Congrats!".

Start Time: Clicking on this button will start or restart the time.

# Closing the application
Close the window by clicking the 'x' on the top-right corner. By doing so, the application is done executing.