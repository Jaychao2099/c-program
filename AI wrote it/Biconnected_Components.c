#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 1000

typedef struct Edge {
    int u, v;
} Edge;

int dfn[MAX_NODES], low[MAX_NODES], time = 0;
Edge edgeStack[MAX_NODES * MAX_NODES];
int top = -1;
int bcc_count = 0;
int graph[MAX_NODES][MAX_NODES];
int visited[MAX_NODES];
int n; // 節點數

void pushEdge(int u, int v) {
    edgeStack[++top].u = u;
    edgeStack[top].v = v;
}

Edge popEdge() {
    return edgeStack[top--];
}

void dfs(int v, int parent) {
    dfn[v] = low[v] = ++time;
    int children = 0; // 用來計算根節點的子節點數

    for (int u = 0; u < n; u++) {
        if (graph[v][u] == 0) continue; // 略過沒有邊的節點

        if (dfn[u] == -1) { // u 尚未被訪問
            pushEdge(v, u); // 將 (v, u) 加入邊棧
            children++; // 計算子節點數
            dfs(u, v);
            low[v] = (low[v] < low[u]) ? low[v] : low[u]; // low[v] = min(low[v], low[u])

            // 判斷是否為 articulation point 並提取一個 biconnected component
            if ((parent == -1 && children > 1) || (parent != -1 && dfn[v] <= low[u])) {
                printf("Biconnected component %d: ", ++bcc_count);
                Edge e;
                do {
                    e = popEdge();
                    printf("(%d, %d) ", e.u, e.v);
                } while (e.u != v || e.v != u);
                printf("\n");
            }
        }
        else if (u != parent && dfn[u] < dfn[v]) { // back edge
            pushEdge(v, u);
            low[v] = (low[v] < dfn[u]) ? low[v] : dfn[u]; // low[v] = min(low[v], dfn[u])
        }
    }

    // 特別處理根節點
    if (parent == -1 && children == 1 && top >= 0) {
        printf("Biconnected component %d: ", ++bcc_count);
        while (top >= 0) {
            Edge e = popEdge();
            printf("(%d, %d) ", e.u, e.v);
        }
        printf("\n");
    }
}

void findBiconnectedComponents() {
    for (int i = 0; i < n; i++) {
        dfn[i] = -1; // 初始化 dfn 值
        low[i] = -1; // 初始化 low 值
    }

    for (int i = 0; i < n; i++) {
        if (dfn[i] == -1) { // 若未訪問過
            dfs(i, -1);
        }
    }
}

int main() {
    int edges;
    printf("Enter the number of nodes and edges: ");
    scanf("%d %d", &n, &edges);

    // 初始化圖
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            graph[i][j] = 0;
        }
    }

    printf("Enter each edge (u v):\n");
    for (int i = 0; i < edges; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u][v] = 1;
        graph[v][u] = 1;
    }

    findBiconnectedComponents();

    printf("Total Biconnected Components: %d\n", bcc_count);

    return 0;
}
