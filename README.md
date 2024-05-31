# Humbug


## Input format
* The `board` is seen as a grid with possibly, some missing tiles (see figure). 
* $0$-indexing is used to represent coordinates (see figure).
    
    - The first lines contains, 2 spaces integers $n$, $m$, the number of rows and columns in the board.
    - Each of the following $n$ lines contain $m$ spaced integers, describing that position on the board as:  
        - $0$ : not a tile on board  
        - $1$ : empty tile on board  
        - $2$ : tile with star
        - $3$ : snail
        - $4$ : grasshopper
        - $5$ : ladybug
        - $6$ : honeybee
        - $7$ : spider
        - $8$ : butterfly
    - The next line contains an integer $t$, the number of walls.
    - Each of the next $t$ lines describe a wall.
    - If a wall is shared by $2$ tiles, it will appear twice.
    - Each of the $t$ lines contain $2$ spaces integers, describing a cell and a single character from $\{L , R , U , D\}$ describing the position of the wall in that cell (see figure).
    - The next line contained $q$, the maximum number of moves allowed. 



## Output format
* If it is not possible to complete the game in the given input number of steps, the output file contains a single line, that has written `not possible!`
* Otherwise, each of the lines, sequentially describle the move used to compete the game as:
    - `coordinate -> move_direction`
    - Here `move_direction` is one of $\{L , R , U , D\}$ (see figure)
    - for example: `(2,2) -> D`
* It is assured that there will necesarily be a `bug` at the `coordinate` presented in the output. 

<p align="center">
<img src= "./Images/input_desc.jpeg" alt = "io fomrat description" width = "600">
</p>

## Sample input
<p align="center">
<img src= "./Images/input_example.jpg" alt = "io fomrat description" width = "600">
</p>

The above image is encoded as given below:
```
6 6
0 0 0 0 7 0
0 0 0 0 6 0
0 0 0 0 1 0
2 1 4 7 1 0
2 0 1 0 1 2
2 0 0 0 0 0
4
3 0 L
4 5 L
4 4 R
5 0 D
10
```
and can be solved in $10$ steps as:
```
(3,2) -> R
(1,4) -> D
(4,4) -> L
(4,2) -> L
(3,4) -> D
(0,4) -> D
(4,4) -> R
(3,3) -> L
(3,4) -> L
(3,0) -> D
```

## Performace


* Compile commands:
```
        g++ -std=c++20 -o ./src/main     ./src/main.cpp
        g++ -std=c++20 -o ./src/main -O1 ./src/main.cpp
        g++ -std=c++20 -o ./src/main -O2 ./src/main.cpp
        g++ -std=c++20 -o ./src/main -O3 ./src/main.cpp
```

* Runtime (seconds) for various problem sizes.
  
<div align="center">

| `max_moves` | `O0` | `O1` | `O2` | `O3` |
|-------|----|----|----|----|
| $Least$ | $13$   |  $4$  |  $3$  | $6$   |
| $100$    | $40$   | $9$   | $4$   |  $7$  |
| $1000$   | $367$   | $85$   | $34$   |  $71$  |
| $10000$   | $3178$   | $572$   | $363$   |  $385$  |
</div>
