#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <stdbool.h>
#include <time.h>

#define MAX_NODES 1000
#define MAX_EDGES 5000
#define INF DBL_MAX

typedef struct {
    int u, v;       
    double weight;  
} Edge;

const char* get_boba_place_name(int node) {
    switch (node) {
        case 100: return "Xing Fu Tang";
        case 101: return "BOBA KAFE";
        case 102: return "FIFTYLAN Koreatown";
        case 103: return "Biao Sugar";
        default: return "Unknown";
    }
}

void bellman_ford(int source, int numEdges, Edge edges[], int numDestinations, int destinations[]) {
    double dist[MAX_NODES];
    int pred[MAX_NODES]; // Predecessor array to reconstruct paths

    // Initialize distances and predecessors
    for (int i = 0; i < MAX_NODES; i++) {
        dist[i] = INF;
        pred[i] = -1;
    }
    dist[source] = 0.0;

    // Relax edges repeatedly
    for (int i = 1; i <= MAX_NODES - 1; i++) {
        for (int j = 0; j < numEdges; j++) {
            int u = edges[j].u;
            int v = edges[j].v;
            double weight = edges[j].weight;
            if (dist[u] != INF && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pred[v] = u;
            }
        }
    }

    // Check for negative-weight cycles
    for (int j = 0; j < numEdges; j++) {
        int u = edges[j].u;
        int v = edges[j].v;
        double weight = edges[j].weight;
        if (dist[u] != INF && dist[u] + weight < dist[v]) {
            printf("Graph contains a negative-weight cycle\n");
            return;
        }
    }

    // Print shortest paths
    for (int d = 0; d < numDestinations; d++) {
        int target = destinations[d];
        const char* placeName = get_boba_place_name(target);
        if (dist[target] == INF) {
            printf("No path to %s\n", placeName);
        } else {
            printf("Shortest path from Penn Station to %s (distance: %.2f): ", placeName, dist[target]);
            int path[MAX_NODES], pathSize = 0;
            for (int at = target; at != -1; at = pred[at]) {
                path[pathSize++] = at;
            }
            for (int i = pathSize - 1; i >= 0; i--) {
                printf("%d%s", path[i], i > 0 ? " -> " : "\n");
            }
        }
    }
}

int main() {
    int numEdges = 0;
    Edge edges[MAX_EDGES];
    int source = 500;    // Penn Station node
    int destinations[] = {100, 101, 102, 103}; // Boba stores
    int numDestinations = sizeof(destinations) / sizeof(destinations[0]);

    FILE *file = fopen("input.txt", "r");
    if (!file) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    while (fscanf(file, "%d %d %lf", &edges[numEdges].u, &edges[numEdges].v, &edges[numEdges].weight) == 3) {
        // Add both directions to treat the graph as undirected
        edges[numEdges + 1].u = edges[numEdges].v;
        edges[numEdges + 1].v = edges[numEdges].u;
        edges[numEdges + 1].weight = edges[numEdges].weight;
        numEdges += 2;
    }
    fclose(file);

    clock_t start = clock();
    bellman_ford(source, numEdges, edges, numDestinations, destinations);
    clock_t end = clock();

    double elapsedTime = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Bellman-Ford execution time: %.6f seconds\n", elapsedTime);

    return 0;
}
