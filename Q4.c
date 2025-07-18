#include "pro.h"

// Flag to indicate if the path was found
static bool path_found = false;

// Recursive function that explores paths from current node u to target node last, marking visited nodes
void FindPath(int u, int* colors, int* Parent, EdgeList primpaths[], int last) {
    colors[u] = Gray;

    EdgeNode* temp = primpaths[u].head;
    while (temp != NULL && !path_found) { // Check path_found to stop early
        int v = temp->e.neighbor;
        if (colors[v] == White) {
            Parent[v] = u;
            if (v == last) {
                path_found = true; // Set flag when path is found
                return;
            } else {
                FindPath(v, colors, Parent, primpaths, last);
            }
        }
        temp = temp->next;
    }
    colors[u] = Black;
}

// Removed unused colors and primpaths
void printPath(int v, int* Parent, int first) {
    if (v == first)
        printf("%d ", v);
    else {
        printPath(Parent[v], Parent, first);
        printf("%d ", v);
    }
}

// Uses DFS to find and print a path between two nodes in the minimum spanning tree
void find_and_print_path(EdgeList primpaths[], int n, int first, int last) {
    int Colors[n];
    int Parent[n];
    path_found = false; // Reset flag for each search

    for (int i = 0; i < n; i++) {
        Colors[i] = White;
        Parent[i] = -1; // Initialize Parent array
    }

    // Input validation for first and last
    if (first < 0 || first >= n || last < 0 || last >= n) {
        printf("Invalid input.\n");
        return;
    }
    if (first == last) {
        printf("%d\n", first); // Path is just the node itself
        return;
    }

    FindPath(first, Colors, Parent, primpaths, last);

    if (path_found) { // Only print if path was found
        printPath(last, Parent, first);
        printf("\n"); // Add a newline for better output
    } else {
        printf("No path found from %d to %d\n", first, last);
    }
}