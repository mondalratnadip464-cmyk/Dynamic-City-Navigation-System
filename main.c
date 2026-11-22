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
