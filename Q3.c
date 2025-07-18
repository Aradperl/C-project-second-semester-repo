#include "pro.h"

// Converts the MST parent array into adjacency lists for each node, creating paths between all nodes
EdgeList *build_paths(int* Prim, int n) {
    // Input validation
    if (Prim == NULL || n <= 0) {
        printf("Invalid input\n");
        return NULL;
    }

    EdgeList* PrimPaths = (EdgeList*)malloc(n * sizeof(EdgeList));
    checkAllocation(PrimPaths);
    
    Edge temp;
    EdgeNode* newEdge;
    
    // Initialize all lists
    for (int i = 0; i < n; i++) {
        PrimPaths[i].head = NULL;
        PrimPaths[i].tail = NULL;
    }
    
    // Build paths from Prim's minimum spanning tree
    for (int j = 0; j < n; j++) {
        if (Prim[j] != -1) {
            temp.neighbor = Prim[j];
            temp.cost = 0;  // Set a default cost, should be updated with actual edge cost
            newEdge = createEdgeNode(temp);
            SortEdgeList(PrimPaths, newEdge->e, j);
        }
        for (int k = 0; k < n; k++) {
            if (Prim[k] == j) {
                temp.neighbor = k;
                temp.cost = 0;  // Set a default cost, should be updated with actual edge cost
                newEdge = createEdgeNode(temp);
                SortEdgeList(PrimPaths, newEdge->e, j);
            }
        }
    }
    
    return PrimPaths;
}

// Free the paths structure
void free_paths(EdgeList* paths, int n) {
    if (paths == NULL || n <= 0) return;
    
    for (int i = 0; i < n; i++) {
        EdgeNode* current = paths[i].head;
        while (current != NULL) {
            EdgeNode* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(paths);
}