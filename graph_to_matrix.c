#include <stdio.h>
#include <stdbool.h>

#define MAX_NODES 100

unsigned char adjacencyMatrix[MAX_NODES][MAX_NODES / 8 + 1];

void insertEdge(int node1, int node2) {
    adjacencyMatrix[node1][node2 / 8] |= (1 << (node2 % 8));
    adjacencyMatrix[node2][node1 / 8] |= (1 << (node1 % 8));
}

void deleteEdge(int node1, int node2) {
    adjacencyMatrix[node1][node2 / 8] &= ~(1 << (node2 % 8));
    adjacencyMatrix[node2][node1 / 8] &= ~(1 << (node1 % 8));
}

bool isNeighbor(int node1, int node2) {
    return (adjacencyMatrix[node1][node2 / 8] & (1 << (node2 % 8))) != 0;
}

void getNeighbors(int node, int numNodes) {
    printf("Neighbors of node %d: ", node);
    for (int i = 0; i < numNodes; i++) {
        if (isNeighbor(node, i)) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

bool DFS(int startNode, int targetNode, int visited[], int path[], int numNodes) {
    visited[startNode] = 1;
    path[path[0] + 1] = startNode;
    path[0]++;

    if (startNode == targetNode) {
        for (int i = 1; i <= path[0]; i++) {
            printf("%d ", path[i]);
        }
        printf("\n");
        return true;
    }

    for (int i = 0; i < numNodes; i++) {
        if (isNeighbor(startNode, i) && !visited[i]) {
            if (DFS(i, targetNode, visited, path, numNodes)) {
                return true;
            }
        }
    }

    visited[startNode] = 0;
    path[0]--;
    return false;
}

void findPath(int startNode, int targetNode, int numNodes) {
    int visited[MAX_NODES] = {0};
    int path[MAX_NODES + 1] = {0};
    if (!DFS(startNode, targetNode, visited, path, numNodes)) {
        printf("No path from %d to %d\n", startNode, targetNode);
    }
}

int maxDegree(int numNodes) {
    int maxDegree = 0;
    for (int i = 0; i < numNodes; i++) {
        int degree = 0;
        for (int j = 0; j < numNodes; j++) {
            if (isNeighbor(i, j)) {
                degree++;
            }
        }
        if (degree > maxDegree) {
            maxDegree = degree;
        }
    }
    return maxDegree;
}

int minDegree(int numNodes) {
    int minDegree = numNodes;
    for (int i = 0; i < numNodes; i++) {
        int degree = 0;
        for (int j = 0; j < numNodes; j++) {
            if (isNeighbor(i, j)) {
                degree++;
            }
        }
        if (degree < minDegree) {
            minDegree = degree;
        }
    }
    return minDegree;
}

float avgDegree(int numNodes) {
    int totalDegree = 0;
    for (int i = 0; i < numNodes; i++) {
        int degree = 0;
        for (int j = 0; j < numNodes; j++) {
            if (isNeighbor(i, j)) {
                degree++;
            }
        }
        totalDegree += degree;
    }
    return (float)totalDegree / numNodes;
}

int main() {
    int numNodes = 5;

    insertEdge(1, 3);
    insertEdge(1, 4);
    insertEdge(2, 3);
    insertEdge(2, 4);
    insertEdge(4, 0);
    insertEdge(4, 2);

    getNeighbors(3, numNodes);
    findPath(1, 4, numNodes);

    printf("Max Degree: %d\n", maxDegree(numNodes));
    printf("Min Degree: %d\n", minDegree(numNodes));
    printf("Avg Degree: %.2f\n", avgDegree(numNodes));

    return 0;
}
