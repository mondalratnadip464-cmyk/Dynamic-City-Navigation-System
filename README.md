# Dynamic City Navigation System Using Graph Data Structures in C

![Language](https://img.shields.io/badge/Language-C%20(C99%2FC11)-00599C?style=flat-square&logo=c)
![Algorithm](https://img.shields.io/badge/Algorithm-Dijkstra's%20Shortest%20Path-2EA44F?style=flat-square)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey?style=flat-square)
![Course](https://img.shields.io/badge/Course-3rd%20Sem%20DSA%20Project-orange?style=flat-square)
![License](https://img.shields.io/badge/License-MIT-blue?style=flat-square)

A console-based, runtime-configurable routing engine built in **C** that models real-world road networks as undirected weighted graphs and computes optimal shortest paths using **Dijkstra's Greedy Algorithm**.

Developed as a **3rd-Semester Data Structures and Algorithms (DSA)** project at the **Department of Electronics and Communication Engineering, Institute of Engineering & Management (IEM), Kolkata**.

---

## Table of Contents

- [Overview & Motivation](#overview--motivation)
- [Key Features](#key-features)
- [Repository Structure](#repository-structure)
- [System Architecture & Complexity](#system-architecture--complexity)
- [Getting Started](#getting-started)
- [Interactive Usage & Sample Output](#interactive-usage--sample-output)
- [Limitations & Future Enhancements](#limitations--future-enhancements)
- [Project Team & Supervision](#project-team--supervision)
- [References](#references)
- [License](#license)

---

## Overview & Motivation

Traditional academic pathfinding implementations rely on static, hardcoded adjacency matrices with numeric vertex IDs (`0` to `N-1`), requiring source-code edits and recompilation whenever a road or city changes.

The **Dynamic City Navigation System** bridges the gap between theoretical graph algorithms and interactive utility software by allowing users to:
1. Dynamically register custom city names at runtime without modifying source code.
2. Connect cities with bidirectional weighted road segments (distances in kilometers).
3. Query optimal routes using natural, case-insensitive city names and receive visual waypoint telemetry alongside travel time and fuel consumption estimates.

---

## Key Features

- **Dynamic Runtime Topology:** Add up to `15` custom cities (`MAX_CITIES`) and define bidirectional road weights interactively via a menu-driven CLI.
- **Dijkstra's Shortest-Path Engine:** Guarantees mathematically optimal minimum-distance routes across connected non-negative road networks with predecessor backtracking (`parent[]`).
- **Case-Insensitive City Resolution:** Uses `strcasecmp()` to match location queries regardless of capitalization (e.g., `"home"`, `"HOME"`, and `"Home"` resolve identically) and prevents duplicate node registration.
- **Cross-Platform UTF-8 & ANSI Console UI:** Automatically configures Windows terminals via `SetConsoleOutputCP(65001)` (`#ifdef _WIN32`) while remaining natively compatible with Linux/macOS terminals to render color-coded status alerts and pinned route icons (`🟢`, `📍`, `🚗`, `🏁`).
- **Automated Commuter Telemetry:** Converts raw shortest-path distance into actionable transit metrics:
  - **Estimated Travel Time:** Calculated at an average urban transit velocity of **40 km/h**.
  - **Estimated Fuel Consumption:** Calculated at **0.08 Liters/km** (equivalent to **12.5 km/L** vehicle mileage).

---

## Repository Structure

```text
Dynamic-City-Navigation-System/
├── main.c                  # Complete C implementation (Adjacency Matrix + Dijkstra + CLI)
├── Makefile                # Cross-platform build, run, and automated benchmark script
├── sample_input.txt        # Automated CLI input script for the Home -> Airport test case
├── README.md               # Main GitHub project documentation
├── LICENSE                 # MIT License
├── .gitignore              # Git ignore rules for compiled binaries and IDE files
└── docs/
    └── PROJECT_REPORT.md   # Full 3rd-Semester DSA Academic Project Report
```

---

## System Architecture & Complexity

### Core Data Structure (`CityGraph`)

All network state is encapsulated within a centralized `CityGraph` structure:

```c
#define MAX_CITIES 15
#define INF 999999

typedef struct {
    int num_cities;
    char city_names[MAX_CITIES][30];
    int adj_matrix[MAX_CITIES][MAX_CITIES];
} CityGraph;
```

### Algorithmic Complexity

| Operation | Implementation Mechanism | Time Complexity | Space Complexity |
| :--- | :--- | :---: | :---: |
| **Graph Initialization** | 2D Adjacency Matrix zero/sentinel (`INF`) fill | $O(V_{\max}^2)$ | $O(V_{\max}^2)$ |
| **City Lookup / Validation** | Linear scan with `strcasecmp()` | $O(V)$ | $O(1)$ |
| **Add Bidirectional Road** | Symmetric matrix assignment (`G[u][v] = G[v][u] = w`) | $O(V)$ (lookup) + $O(1)$ | $O(1)$ |
| **Shortest Path Search** | Dijkstra's greedy relaxation over Adjacency Matrix | $O(V^2)$ | $O(V)$ |
| **Route Reconstruction** | Reverse traversal of `parent[]` array | $O(V)$ | $O(V)$ |

*(Where $V$ is the number of registered cities and $V_{\max} = 15$.)*

---

## Getting Started

### Prerequisites

- **C Compiler:** `gcc` (MinGW-w64 on Windows, GCC on Linux, or Apple Clang on macOS) supporting C99/C11.
- **Terminal:** Windows Terminal / PowerShell / Command Prompt (UTF-8 supported) or any Unix bash/zsh terminal.

### Compilation & Execution

#### Option 1: Using GCC Directly
```bash
# Clone the repository
git clone https://github.com/<your-username>/Dynamic-City-Navigation-System.git
cd Dynamic-City-Navigation-System

# Compile the source code
gcc main.c -o city_nav -Wall -Wextra

# Run the application (Linux/macOS)
./city_nav

# Run the application (Windows)
city_nav.exe
```

#### Option 2: Using `Makefile`
```bash
make          # Compiles main.c into city_nav
make run      # Compiles and launches the interactive CLI
make test     # Runs the automated Home -> Airport sample benchmark
make clean    # Removes compiled binaries
```

---

## Interactive Usage & Sample Output

### Menu Options
```text
========================================
       DYNAMIC CITY NAVIGATION          
========================================
 1. Add a Custom City
 2. Add a Road Between Cities
 3. View All Cities
 4. Find Shortest Path (Dijkstra)
 5. Exit
Enter your choice (1-5):
```

### Experimental Verification (`Home` -> `Airport`)

Consider a 4-city network configured with the following bidirectional roads:
- `Home` <-> `College` (**5 km**)
- `College` <-> `Station` (**4 km**)
- `Station` <-> `Airport` (**15 km**)
- `Home` <-> `Station` (**20 km** — direct highway alternative)
- `Home` <-> `Airport` (**30 km** — direct outer ring road)

Querying the shortest path from **`Home`** to **`Airport`** bypasses the longer direct roads (`30 km` and `20 + 15 = 35 km`) in favor of the optimal multi-hop route (`5 + 4 + 15 = 24 km`):

```text
+-----------------------------------------------------------------+
             📍 PINNED NAVIGATION ROUTE (Shortest Path)          
+-----------------------------------------------------------------+
  🟢 STARTING POINT : Home
       │
       ├── 🚗 Drive 5 km
       ▼
  📍 WAYPOINT       : College
       │
       ├── 🚗 Drive 4 km
       ▼
  📍 WAYPOINT       : Station
       │
       ├── 🚗 Drive 15 km
       ▼
  🏁 DESTINATION    : Airport [PINNED TARGET]
+-----------------------------------------------------------------+
  Total Distance    : 24 km
  Est. Travel Time  : ~36 mins (at 40 km/h)
  Est. Fuel Used    : 1.92 Liters
+-----------------------------------------------------------------+
```

---

## Limitations & Future Enhancements

- **Fixed Static Capacity (`MAX_CITIES = 15`):** Currently uses a pre-allocated 2D array ($O(V^2)$ memory). Future versions will transition to a dynamic **Adjacency List** paired with a **Min-Heap Priority Queue** to achieve $O((V + E)\log V)$ time complexity for large sparse road networks.
- **Volatile Memory Storage:** Graph configurations exist in RAM during active sessions. Adding File I/O (`map.txt` / CSV serialization) will enable saving and reloading custom city maps across sessions.
- **Multi-Word City Names:** Replacing `scanf("%s", ...)` with `fgets()` and newline sanitization will allow spaces in location names (e.g., `"Salt Lake"`, `"New Town"`).
- **Dynamic Traffic Weights:** Incorporating real-time congestion multipliers or A* heuristic routing.

---

## Project Team & Supervision

**Institution:** Institute of Engineering & Management (IEM), Kolkata  
**Department:** Electronics and Communication Engineering (ECE) — 3rd Semester  

### Student Authors

| Sl. No. | Student Name | Enrollment Number | Class Roll No. |
| :---: | :--- | :---: | :---: |
| 1 | **Soham Banerjee** | `12025052003341` | `320` |
| 2 | **Ratnadip Mondal** | `12025052003338` | `317` |
| 3 | **Swapnil Dutta** | `12025052003321` | `300` |
| 4 | **Devansh Kandhway** | `12025052003337` | `316` |

### Faculty Guidance & Institutional Support

- **Project Guides:** Prof. Debojyoti Sengupta, Prof. Amit Kr. Das, and Prof. Sourajit Adhikari
- **Head of Department (ECE):** Prof. Malay Gangopadhyay
- **Director (IEM Kolkata):** Dr. Satyajit Chakrabarti

---

## References

1. T. H. Cormen, C. E. Leiserson, R. L. Rivest, and C. Stein, *Introduction to Algorithms*, 3rd ed. MIT Press, 2009.
2. B. W. Kernighan and D. M. Ritchie, *The C Programming Language*, 2nd ed. Prentice Hall, 1988.
3. E. W. Dijkstra, *"A note on two problems in connexion with graphs,"* Numerische Mathematik, vol. 1, pp. 269–271, 1959.
4. R. Sedgewick and K. Wayne, *Algorithms*, 4th ed. Addison-Wesley Professional, 2011.
5. Microsoft Learn Documentation, *Console Code Page Identifiers (`SetConsoleOutputCP`)*, Windows Console API Reference.

---

## License

This project is licensed under the **MIT License** — see the [LICENSE](LICENSE) file for details.
