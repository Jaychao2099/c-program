#include <windows.h>
#pragma comment(linker, "/subsystem:console")
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 100

typedef struct {
    int adjacencyMatrix[MAX_VERTICES][MAX_VERTICES];
    int numVertices;
    bool isDirected;
} Graph;

void initGraph(Graph* g, int numVertices, bool isDirected) {
    g->numVertices = numVertices;
    g->isDirected = isDirected;
    for (int i = 0; i < numVertices; i++)
        for (int j = 0; j < numVertices; j++)
            g->adjacencyMatrix[i][j] = 0;
}

void addEdge(Graph* g, int from, int to) {
    g->adjacencyMatrix[from][to]++;
    if (!g->isDirected) {
        g->adjacencyMatrix[to][from]++;
    }
}

int inDegree(Graph* g, int v) {
    int degree = 0;
    for (int i = 0; i < g->numVertices; i++)
        degree += g->adjacencyMatrix[i][v];
    return degree;
}

int outDegree(Graph* g, int v) {
    int degree = 0;
    for (int i = 0; i < g->numVertices; i++)
        degree += g->adjacencyMatrix[v][i];
    return degree;
}

bool isConnected(Graph* g) {
    bool visited[MAX_VERTICES] = {false};
    int stack[MAX_VERTICES], top = -1;
    stack[++top] = 0;
    visited[0] = true;

    while (top >= 0) {
        int v = stack[top--];
        for (int i = 0; i < g->numVertices; i++) {
            if ((g->adjacencyMatrix[v][i] > 0 || g->adjacencyMatrix[i][v] > 0) && !visited[i]) {
                stack[++top] = i;
                visited[i] = true;
            }
        }
    }

    for (int i = 0; i < g->numVertices; i++)
        if (!visited[i])
            return false;
    return true;
}

bool hasEulerPath(Graph* g, int* start, int* end) {
    int oddCount = 0;
    *start = -1;
    *end = -1;

    for (int i = 0; i < g->numVertices; i++) {
        int inDeg = inDegree(g, i);
        int outDeg = outDegree(g, i);

        if (g->isDirected) {
            if (inDeg == outDeg) continue;
            if (inDeg == outDeg + 1) {
                if (*end != -1) return false;
                *end = i;
            } else if (outDeg == inDeg + 1) {
                if (*start != -1) return false;
                *start = i;
            } else {
                return false;
            }
        } else {
            int degree = inDeg;  // For undirected graph, inDegree = outDegree
            if (degree % 2 != 0) {
                oddCount++;
                if (oddCount > 2) return false;
                if (*start == -1) *start = i;
                else *end = i;
            }
        }
    }

    if (g->isDirected) {
        return (*start != -1 && *end != -1) || (*start == -1 && *end == -1);
    } else {
        return oddCount == 0 || oddCount == 2;
    }
}

void DFS(Graph* g, int v, int* path, int* pathIndex) {
    for (int i = 0; i < g->numVertices; i++) {
        while (g->adjacencyMatrix[v][i] > 0) {
            g->adjacencyMatrix[v][i]--;
            if (!g->isDirected) g->adjacencyMatrix[i][v]--;
            DFS(g, i, path, pathIndex);
        }
    }
    path[(*pathIndex)++] = v;
}

void findEulerPath(Graph* g) {
    int start, end;
    if (!isConnected(g)) {
        printf("The graph is not connected. No Euler path exists.\n");
        return;
    }
    if (!hasEulerPath(g, &start, &end)) {
        printf("No Euler path exists in this graph.\n");
        return;
    }

    if (start == -1) start = 0;  // If all vertices have even degree, start from any vertex

    int path[MAX_VERTICES * MAX_VERTICES];
    int pathIndex = 0;

    DFS(g, start, path, &pathIndex);

    printf("Euler Path: ");
    for (int i = pathIndex - 1; i >= 0; i--) {
        printf("%d", path[i]);
        if (i > 0) printf(" -> ");
    }
    printf("\n");
}

int main() {
    Graph g;
    int numVertices, numEdges;
    char graphType;

    printf("Is the graph directed? (y/n): ");
    scanf(" %c", &graphType);
    bool isDirected = (graphType == 'y' || graphType == 'Y');

    printf("Enter the number of vertices: ");
    scanf("%d", &numVertices);
    initGraph(&g, numVertices, isDirected);

    printf("Enter the number of edges: ");
    scanf("%d", &numEdges);

    printf("Enter the edges (format: a b, means from a to b):\n");
    for (int i = 0; i < numEdges; i++) {
        int from, to;
        scanf("%d %d", &from, &to);
        if (from < 0 || from >= numVertices || to < 0 || to >= numVertices) {
            printf("Invalid vertex. Vertices should be between 0 and %d\n", numVertices - 1);
            i--;
            continue;
        }
        addEdge(&g, from, to);
    }

    findEulerPath(&g);

    return 0;
}