# PROJECT REPORT: Dynamic City Navigation System Using Graph Data Structures in C

**Department of Electronics and Communication Engineering**  
**Institute of Engineering & Management (IEM), Kolkata**  
**Coursework:** 3rd-Semester Data Structures and Algorithms (DSA)  
**Date of Submission:** 30/10/2026  

**Submitted by:**
- **Soham Banerjee** (Enrollment No: `12025052003341`, Roll No: `320`)
- **Ratnadip Mondal** (Enrollment No: `12025052003338`, Roll No: `317`)
- **Swapnil Dutta** (Enrollment No: `12025052003321`, Roll No: `300`)
- **Devansh Kandhway** (Enrollment No: `12025052003337`, Roll No: `316`)

**Guided by:** Prof. Debojyoti Sengupta, Prof. Amit Kr. Das, and Prof. Sourajit Adhikari  

---

## Acknowledgment

The successful completion of this project would not have been possible without the guidance, support, and encouragement of several esteemed individuals. We express our profound gratitude to our respected Director, **Dr. Satyajit Chakrabarti**, for fostering an inspiring academic environment at the Institute of Engineering & Management, Kolkata, and providing the institutional infrastructure necessary to pursue this work.

We extend our heartfelt thanks to our Head of the Department, **Prof. Malay Gangopadhyay**, for his visionary leadership and continuous encouragement. We are deeply indebted to our project guides, **Prof. Debojyoti Sengupta**, **Prof. Amit Kr. Das**, and **Prof. Sourajit Adhikari**, for their invaluable mentorship, technical insight, and supervision throughout every stage of development.

---

## Abstract

In modern transportation and logistics, determining optimal transit routes is essential for efficient mobility and resource management. The **Dynamic City Navigation System** is a console-based routing application developed in the C programming language, designed to model real-world road networks and compute the optimal shortest path between user-defined locations.

Traditional route-finding prototypes often rely on rigid, hardcoded inputs that require source-code modifications to update network topologies. This project bridges that gap by offering a dynamic runtime environment where users register custom city names, connect them with weighted road segments representing physical distances, and compute exact routing paths on the fly. The core system architecture utilizes an **Adjacency Matrix** to represent the topological graph structure in memory and implements **Dijkstra's Shortest Path Algorithm** using a greedy relaxation strategy, enhanced with case-insensitive string lookups, UTF-8 console pin visualization, and automated travel time and fuel consumption telemetry.

---

## 1. Introduction

### 1.1 Project Motivation
In modern urban infrastructure, efficient pathfinding is critical for logistics, transportation, and personal navigation. Translating abstract data structures such as graphs into functional applications demonstrates how foundational algorithms power real-world GPS navigation tools.

### 1.2 Objectives
- Design and implement an undirected, weighted graph data structure from scratch in C.
- Provide an interactive runtime Command Line Interface (CLI) for registering custom nodes (cities) and weighted edges (roads).
- Implement Dijkstra's Shortest Path Algorithm for optimal route computation and predecessor backtracking.
- Output structured visual terminal itineraries enriched with estimated travel time and fuel consumption metrics.

### 1.3 Problem Statement
Given an undirected, weighted graph $G = (V, E)$ representing a dynamic network of cities $V$ and connecting road distances $E$, compute the shortest path, intermediate waypoints, total travel distance, estimated transit duration, and fuel usage between any user-specified source and destination city at runtime.

### 1.4 Scope of the Project
Built as a lightweight 3rd-semester DSA application, the system supports modular graph scaling up to `MAX_CITIES` (`15` nodes), handles input capitalization mismatches gracefully, and provides color-coded UTF-8 terminal feedback across Windows and Unix-like environments.

### 1.5 Relevant Theory and Concepts
- **Graph Theory:** A graph $G = (V, E)$ consists of a set of vertices $V$ (cities) and edges $E$ (roads) with positive weights $w(u, v)$ representing physical distances in kilometers.
- **Adjacency Matrix:** A 2D array `adj_matrix[V][V]` storing edge weights, providing $O(1)$ edge weight lookups.
- **Dijkstra's Algorithm:** A greedy Single-Source Shortest Path (SSSP) algorithm that iteratively finalizes unvisited vertices with minimum cumulative distance and relaxes adjacent edges.

---

## 2. Literature Review

### 2.1 Theoretical Foundations & Evolution of Shortest-Path Algorithms
Originating from Leonhard Euler's 1736 Seven Bridges of Königsberg problem, graph theory models pairwise connectivity in physical and digital networks:
- **Dijkstra's Algorithm (1959):** Proposed by Edsger W. Dijkstra, solving SSSP on non-negative weighted graphs in $O(V^2)$ time using an adjacency matrix or $O((V + E)\log V)$ with a binary min-heap.
- **Bellman-Ford Algorithm (1958):** Supports negative edge weights at a higher time complexity of $O(V \cdot E)$, making it slower than Dijkstra for strictly positive road distances.
- **A\* Search Algorithm:** Extends Dijkstra's algorithm with spatial heuristics (e.g., Euclidean distance) for large-scale commercial GPS engines.

### 2.2 Gap in Conventional Academic Prototypes
Conventional textbook implementations typically rely on static, pre-compiled integer matrices (`node 0` to `node N`), lack natural language string mapping, and output raw numerical costs without commuter context. This project addresses these limitations through runtime node/edge registration, case-insensitive string resolution, and structured route visualization.

---

## 3. Methodology

### 3.1 Five-Stage Algorithmic Pipeline
1. **Graph Initialization (`init_graph`):** Sets `num_cities = 0`, diagonal elements `adj_matrix[i][i] = 0`, and all distinct pairs `adj_matrix[i][j] = INF` (`999999`).
2. **Dynamic Node Insertion (`add_city`):** Validates capacity (`num_cities < MAX_CITIES`), checks for duplicate names via case-insensitive search, and maps the city string to index `0` to `V - 1`.
3. **Bidirectional Weight Assignment (`add_road`):** Resolves both city names to indices `(u, v)` and assigns symmetric weights `adj_matrix[u][v] = distance` and `adj_matrix[v][u] = distance`.
4. **Dijkstra's Greedy Relaxation (`find_shortest_path`):** Maintains `dist[]`, `visited[]`, and `parent[]` arrays of size `MAX_CITIES`. For each unvisited vertex `u` with minimum `dist[u]`, relaxes each unvisited neighbor `v`:
   $$\text{if } \neg\text{visited}[v] \land \text{adj\_matrix}[u][v] \neq \text{INF} \land \text{dist}[u] + \text{adj\_matrix}[u][v] < \text{dist}[v]$$
   $$\text{then } \text{dist}[v] = \text{dist}[u] + \text{adj\_matrix}[u][v], \quad \text{parent}[v] = u$$
5. **Path Backtracking & Telemetry (`print_pinned_route`):** Traverses `parent[]` from destination back to source, reverses the path order, and computes secondary metrics:
   $$\text{Estimated Travel Time (mins)} = \left\lfloor \frac{\text{Total Distance (km)}}{40.0\text{ km/h}} \times 60 \right\rfloor$$
   $$\text{Estimated Fuel Used (Liters)} = \text{Total Distance (km)} \times 0.08\text{ L/km}$$

### 3.2 Tools & Technologies Used
- **Language:** C (ISO C99/C11 standard)
- **Compiler:** GCC (MinGW-w64 on Windows / standard GCC on Linux/macOS)
- **Libraries:** `stdio.h`, `stdlib.h`, `limits.h`, `string.h`, `strings.h` (`strcasecmp`), and `windows.h` (`SetConsoleOutputCP(65001)` guarded via `#ifdef _WIN32`).

---

## 4. Implementation

### 4.1 Modular Function Design
- `init_graph()` — Resets vertex counter and populates the adjacency matrix.
- `get_city_index()` — Performs case-insensitive city lookup using `strcasecmp()`.
- `add_city()` — Validates capacity and uniqueness before inserting a city.
- `add_road()` — Validates vertex existence and records undirected road weights.
- `show_cities()` — Displays a numbered roster of all registered cities.
- `find_shortest_path()` — Executes Dijkstra's algorithm between user-selected endpoints.
- `print_pinned_route()` — Renders the visual waypoint chain and transit telemetry.

### 4.2 Challenges Faced & Resolutions
- **Windows UTF-8 Icon Scrambling:** Legacy Windows console code pages (CP1252) corrupt multi-byte UTF-8 emojis (`🟢`, `📍`, `🚗`, `🏁`). Resolved by invoking `SetConsoleOutputCP(65001)` inside `#ifdef _WIN32` at startup while preserving cross-platform portability.
- **Case-Sensitivity Mismatches:** Standard `strcmp()` fails when user capitalization differs from stored labels. Resolved using `strcasecmp()` from `<strings.h>` across all city validation and search routines.

---

## 5. Results & Discussion

### 5.1 Experimental Verification
Configuring a 4-city test network (`Home`, `College`, `Station`, `Airport`) with roads `Home–College (5 km)`, `College–Station (4 km)`, `Station–Airport (15 km)`, `Home–Station (20 km)`, and `Home–Airport (30 km)` yields the optimal route **`Home -> College -> Station -> Airport`** with a total distance of **`24 km`**, estimated travel time of **`~36 mins`**, and estimated fuel consumption of **`1.92 Liters`**.

### 5.2 Limitations & Future Work
- **Memory Scaling:** The $O(V_{\max}^2)$ adjacency matrix can be replaced with an **Adjacency List + Min-Heap Priority Queue** for large sparse networks.
- **Data Persistence:** Adding file I/O (`fopen`/`fscanf`/`fprintf`) will allow saving and loading road topologies across sessions.
- **Multi-Word Inputs:** Migrating from `scanf("%s")` to `fgets()` will support multi-word city names containing whitespace.

---

## 6. Conclusion

The Dynamic City Navigation System successfully demonstrates how graph data structures and Dijkstra's greedy shortest-path algorithm can be engineered into a responsive, user-friendly C application. By combining runtime network construction, fault-tolerant case-insensitive lookups, UTF-8 visual route mapping, and practical commuter telemetry, the project meets all academic and functional objectives set for the 3rd-semester DSA coursework.

---

## 7. References

1. Cormen, T. H., Leiserson, C. E., Rivest, R. L., & Stein, C. (2009). *Introduction to Algorithms* (3rd ed.). MIT Press.
2. Kernighan, B. W., & Ritchie, D. M. (1988). *The C Programming Language* (2nd ed.). Prentice Hall.
3. Dijkstra, E. W. (1959). "A note on two problems in connexion with graphs." *Numerische Mathematik*, 1(1), 269–271.
4. Sedgewick, R., & Wayne, K. (2011). *Algorithms* (4th ed.). Addison-Wesley Professional.
5. Microsoft Developer Network (MSDN). *Console Code Page Identifiers and `SetConsoleOutputCP` Function Documentation*.

---

## Appendix A: Complete Source Code (`main.c`)

```c
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <strings.h> // For case-insensitive string comparison (strcasecmp)

#ifdef _WIN32
#include <windows.h> // Required for fixing Windows emoji encoding
#endif

#define MAX_CITIES 15
#define INF 999999

// ANSI Color Codes for Terminal UI
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define CYAN "\033[1;36m"
#define RED "\033[1;31m"
#define BOLD "\033[1m"
#define RESET "\033[0m"

typedef struct {
    int num_cities;
    char city_names[MAX_CITIES][30];
    int adj_matrix[MAX_CITIES][MAX_CITIES];
} CityGraph;

// Initialize graph
void init_graph(CityGraph *g) {
    g->num_cities = 0;
    for (int i = 0; i < MAX_CITIES; i++) {
        for (int j = 0; j < MAX_CITIES; j++) {
            g->adj_matrix[i][j] = (i == j) ? 0 : INF;
        }
    }
}

// Find city index by name (case-insensitive)
int get_city_index(CityGraph *g, const char *name) {
    for (int i = 0; i < g->num_cities; i++) {
        if (strcasecmp(g->city_names[i], name) == 0) {
            return i;
        }
    }
    return -1;
}

// Add a new custom city dynamically
void add_city(CityGraph *g) {
    if (g->num_cities >= MAX_CITIES) {
        printf(RED "[!] Error: Maximum city limit reached (%d).\n" RESET, MAX_CITIES);
        return;
    }
    char name[30];
    printf(YELLOW "Enter city name: " RESET);
    scanf("%s", name);

    if (get_city_index(g, name) != -1) {
        printf(RED "[!] City '%s' already exists in the network!\n" RESET, name);
        return;
    }

    strcpy(g->city_names[g->num_cities], name);
    g->num_cities++;
    printf(GREEN "[✓] City '%s' added successfully!\n" RESET, name);
}

// Add a road (edge) between two custom cities with distance weight
void add_road(CityGraph *g) {
    if (g->num_cities < 2) {
        printf(RED "[!] Please add at least 2 cities first before adding roads.\n" RESET);
        return;
    }

    char c1[30], c2[30];
    int distance;

    printf(YELLOW "Enter first city name : " RESET);
    scanf("%s", c1);
    printf(YELLOW "Enter second city name: " RESET);
    scanf("%s", c2);
    printf(YELLOW "Enter road distance (km): " RESET);
    scanf("%d", &distance);

    int u = get_city_index(g, c1);
    int v = get_city_index(g, c2);

    if (u == -1 || v == -1) {
        printf(RED "[!] Error: One or both cities do not exist! Add them first.\n" RESET);
        return;
    }

    g->adj_matrix[u][v] = distance;
    g->adj_matrix[v][u] = distance; // Undirected road
    printf(GREEN "[✓] Road added between %s and %s (%d km)!\n" RESET, c1, c2, distance);
}

// Display all registered cities
void show_cities(CityGraph *g) {
    if (g->num_cities == 0) {
        printf(RED "No cities added yet.\n" RESET);
        return;
    }
    printf(CYAN "\n--- Registered Cities in Network ---\n" RESET);
    for (int i = 0; i < g->num_cities; i++) {
        printf(" %d. %s\n", i + 1, g->city_names[i]);
    }
    printf(CYAN "------------------------------------\n" RESET);
}

// Pinned Route Function with Emojis & Pins
void print_pinned_route(int parent[], int dest_index, CityGraph *g, int dist[]) {
    int path[MAX_CITIES];
    int length = 0;
    int curr = dest_index;

    while (curr != -1) {
        path[length++] = curr;
        curr = parent[curr];
    }

    printf(GREEN "\n+-----------------------------------------------------------------+\n" RESET);
    printf(BOLD GREEN "             📍 PINNED NAVIGATION ROUTE (Shortest Path)          " RESET);
    printf(GREEN "\n+-----------------------------------------------------------------+\n" RESET);

    for (int i = length - 1; i >= 0; i--) {
        int u = path[i];
        if (i == length - 1) {
            printf("  🟢 STARTING POINT : %s\n", g->city_names[u]);
        } else {
            int prev = path[i + 1];
            int weight = g->adj_matrix[prev][u];
            printf("       │\n");
            printf("       ├── 🚗 Drive %d km\n", weight);
            if (i == 0) {
                printf("       ▼\n");
                printf("  🏁 DESTINATION    : " BOLD YELLOW "%s [PINNED TARGET]" RESET "\n", g->city_names[u]);
            } else {
                printf("       ▼\n");
                printf("  📍 WAYPOINT       : %s\n", g->city_names[u]);
            }
        }
    }

    float avg_speed_kmh = 40.0;
    int time_minutes = (int)(((float)dist[dest_index] / avg_speed_kmh) * 60);
    float fuel_liters = (float)dist[dest_index] * 0.08;

    printf(GREEN "+-----------------------------------------------------------------+\n" RESET);
    printf("  " BOLD "Total Distance    " RESET ": %d km\n", dist[dest_index]);
    printf("  " BOLD "Est. Travel Time  " RESET ": ~%d mins (at 40 km/h)\n", time_minutes);
    printf("  " BOLD "Est. Fuel Used    " RESET ": %.2f Liters\n", fuel_liters);
    printf(GREEN "+-----------------------------------------------------------------+\n" RESET);
}

// Dijkstra's Algorithm Implementation
void find_shortest_path(CityGraph *g) {
    if (g->num_cities < 2) {
        printf(RED "[!] Add at least 2 cities and roads first.\n" RESET);
        return;
    }

    char start[30], dest[30];
    show_cities(g);

    printf(YELLOW "Enter starting city: " RESET);
    scanf("%s", start);
    printf(YELLOW "Enter destination  : " RESET);
    scanf("%s", dest);

    int src = get_city_index(g, start);
    int dest_idx = get_city_index(g, dest);

    if (src == -1 || dest_idx == -1) {
        printf(RED "[!] Error: One or both city names not found!\n" RESET);
        return;
    }

    int dist[MAX_CITIES];
    int visited[MAX_CITIES];
    int parent[MAX_CITIES];

    for (int i = 0; i < g->num_cities; i++) {
        dist[i] = INF;
        visited[i] = 0;
        parent[i] = -1;
    }

    dist[src] = 0;

    for (int count = 0; count < g->num_cities - 1; count++) {
        int min = INF, u = -1;
        for (int v = 0; v < g->num_cities; v++) {
            if (!visited[v] && dist[v] <= min) {
                min = dist[v];
                u = v;
            }
        }

        if (u == -1) break;
        visited[u] = 1;

        for (int v = 0; v < g->num_cities; v++) {
            if (!visited[v] && g->adj_matrix[u][v] && dist[u] != INF && 
                dist[u] + g->adj_matrix[u][v] < dist[v]) {
                dist[v] = dist[u] + g->adj_matrix[u][v];
                parent[v] = u;
            }
        }
    }

    if (dist[dest_idx] == INF) {
        printf(RED "No path exists between %s and %s.\n" RESET, start, dest);
    } else {
        print_pinned_route(parent, dest_idx, g, dist);
    }
}

int main() {
    // Enable UTF-8 encoding so emojis and pin symbols render properly on Windows
    #ifdef _WIN32
    SetConsoleOutputCP(65001);
    #endif

    CityGraph g;
    init_graph(&g);
    int choice;

    do {
        printf(CYAN "\n========================================\n" RESET);
        printf(BOLD "       DYNAMIC CITY NAVIGATION          \n" RESET);
        printf(CYAN "========================================\n" RESET);
        printf(" 1. Add a Custom City\n");
        printf(" 2. Add a Road Between Cities\n");
        printf(" 3. View All Cities\n");
        printf(" 4. Find Shortest Path (Dijkstra)\n");
        printf(" 5. Exit\n");
        printf(YELLOW "Enter your choice (1-5): " RESET);
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_city(&g);
                break;
            case 2:
                add_road(&g);
                break;
            case 3:
                show_cities(&g);
                break;
            case 4:
                find_shortest_path(&g);
                break;
            case 5:
                printf("Exiting program. Safe travels!\n");
                break;
            default:
                printf(RED "Invalid choice! Please enter 1-5.\n" RESET);
        }
    } while (choice != 5);

    return 0;
}
```
