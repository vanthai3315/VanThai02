### Johnson's algorithm is a powerful solution for solving the all-pairs shortest paths problem, 
### especially in sparse graphs with negative edge weights, where it significantly outperforms 
### the simpler but less scalable Floyd–Warshall algorithm.

----------------------------
**Overview** 

- In the problem of finding the shortest paths between all pairs of vertices in a directed weighted graph (which may contain negative edge weights but no negative-weight cycles), choosing the right algorithm is crucial for optimizing performance.
- In this project, we implemented and compared two classical algorithms:

- Johnson's Algorithm: Optimized for sparse graphs, and works well with negative edge weights (as long as there are no negative cycles). It combines Bellman-Ford and Dijkstra.
- Floyd–Warshall Algorithm: Easy to implement, efficient for small or dense graphs, based on dynamic programming with a time complexity of O(n³).

- The program provides the following features:
   + Input data manually or from a file (Data.txt)
   + Generate random graphs (sparse or dense)
   + Measure and compare execution time and memory usage
   + Print all shortest paths from each vertex
   + Run both algorithms and compare their output and performance

----------------------------

----------------------------
**Features** 

- Multiple data input options: Users can manually input graph data via keyboard or automatically load data from Data.txt file.
- Dual algorithm support: The program implements and allows users to run both Johnson algorithm and Floyd–Warshall algorithm on the same data set to compare running time and memory space.
- Random graph generation: Supports automatic generation of sparse and dense graphs with configurable number of vertices. This feature is useful for testing and evaluating performance with different data sources to make comparison more objective.
- Execution time measurement: Measure and display execution time (in milliseconds) for each separate algorithm using a high-precision timer. Note that if you also run and print the results, the running time will be longer than usual.
- Memory usage report: Calculates the estimated memory usage (in bytes) of each algorithm based on internal data structures (e.g. adjacency list, edge list, matrix).
- Shortest path output: Provides a detailed printout of the shortest paths from each source vertex to every other vertex, including the actual path and total cost. This feature can be enabled or disabled for more efficient timing.
- File-based graph input format: Accepts graph input from a text file in a specific format: the first line specifies the number of vertices and edges, followed by the lines (start_vertex, end_vertex, weight).
- Side-by-side comparison: Allows users to compare the performance and output of Johnson and Floyd–Warshall on the same input, whether manually entered or randomly generated.
- Users can clearly understand the program's features through menu design and program structure construction.

---------------------------

--------------------------------------------------
**How to Build and Run** 

Using Visual Studio 2022
### 1. Create or Open a Project
- Open **Visual Studio 2022**
- Go to **File > Open > Project/Solution...**
- Choose your existing `.sln` file  
  *(or create a new C++ Console App project if starting fresh)*

### 2. Add Source and Header Files
- In **Solution Explorer**, right-click on the project name → **Add > Existing Item...**
- Add all `.cpp` and `.h` files from the project directory

### 3. Setup File Input (Optional)
If you want to load data from `Data.txt`, make sure:
- The file is placed in the **same directory as your `.vcxproj` file**, or
- Set the **Working Directory**:
  - Right-click project → **Properties**
  - Go to **Configuration Properties > Debugging**
  - Set **Working Directory** to `$(ProjectDir)`

### 4. Build the Project
- Press **Ctrl + Shift + B** or go to **Build > Build Solution**

### 5. Run the Program
- Press **Ctrl + F5** to run without debugger *(console remains open)*
- Or press **F5** to run with debugger

----------------------------

----------------------------
**File Structure** 

Do An Nhom 5/
│
├── Header Files/
│   ├── floydWarshall.h               # Declaration of the Floyd–Warshall class and methods
│   ├── generateRandomGraph.h         # Header for random graph generation functions
│   ├── JohnsonAlgorithm.h            # Declaration of the Johnson algorithm class
│   ├── measureExecutionTime.h        # Header for execution time measurement
│   └── Standard_Library.h            # Contains standard library includes and common macros
│
├── Source Files/
│   ├── Data.txt                      # Sample input data file
│   ├── floydWarshall.cpp             # Implementation of Floyd–Warshall algorithm
│   ├── generateRandomGraph.cpp       # Implementation of random graph generation
│   ├── JohnsonAlgorithm.cpp          # Implementation of Johnson's algorithm
│   ├── Main.cpp                      # Main menu interface and program flow
│   └── readme.md                     # This documentation file

---------------------------
---------------------------
**Input File Format (Data.txt)** 

- The input file must follow the structure below:
   + The first line contains two integers:
         n — the number of vertices
         m — the number of edges
- The following m lines each describe a directed edge, containing three integers: start_vertex end_vertex weight
- Format:
      <number_of_vertices> <number_of_edges>
      <start_vertex_1> <end_vertex_1> <weight_1>
      ...
      <start_vertex_m> <end_vertex_m> <weight_m>
- Example: 
			10 17
			0 1 1
			0 2 3
			1 4 2
			2 4 8
			2 5 5
			3 1 1
			3 6 4
			3 9 7
			4 3 5
			4 6 14
			4 7 6
			5 8 1
			5 7 4
			5 9 11
			6 9 7
			8 7 2
			9 7 5

----------------------

----------------------------
**Future Improvements** 

Although the current version of the project provides complete functionality for comparing Johnson's algorithm and Floyd–Warshall, several enhancements could be considered for future development:
- Extend to Undirected Graphs: Modify the input and algorithm logic to support undirected graphs, allowing broader application beyond strictly directed graphs.
- Export Results to File: Enable exporting shortest path results to external files (e.g., .txt or .csv) so that users can store, share, or re-access computed results later.
- Multithreaded Execution (Performance Boost): Run Johnson and Floyd–Warshall in parallel threads, improving overall performance and enabling efficient comparison on large graphs. Future versions may also allow loading data in different formats (e.g., adjacency matrices) to support alternative input methods.

----------------------------

----------------------------
**Notes** 

- Negative weight cycles: Johnson algorithm will terminate with an error if it detects negative weight cycles in the graph. Make sure your input graph does not contain such cycles.
- Floyd–Warshall time complexity: Although Floyd–Warshall has a simpler implementation, it uses O(n³) time and O(n²) space, making it unsuitable for very large graphs.
- Use of Johnson space: Johnson uses more complex data structures such as adjacency lists and reweighting but scales better in sparse graphs.
- Only processes streams of data from files and has a rule for file data, not applicable to all forms of input data.
- Consistency of results: Both algorithms are guaranteed to return the same shortest path result (if no negative cycles exist).
- If both algorithms print the result, the running time and storage space will be different from when only printing the result (time, storage space).

---------------------
