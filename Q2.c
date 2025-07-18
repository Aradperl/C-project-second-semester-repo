#include "pro.h"


// Builds an array of bits and reset
unsigned char* BuildBitArray(int n) {
    // Calculate number of bytes needed for bit array
    int numBytes = (n + 7) / 8;  // Ceiling division by 8

    // Allocate and initialize bit array (all bits to 0)
    unsigned char* inT = (unsigned char*)calloc(numBytes, sizeof(unsigned char));
    if (inT == NULL || !checkAllocation((void*)inT)) {
        return NULL;
    }
    return inT;
}

// Creates a new node of CandidateNode
CandidateNode* createCandNode(int v) {
    CandidateNode* newNode = (CandidateNode*)malloc(sizeof(CandidateNode));
    if (newNode == NULL || !checkAllocation((void*)newNode)) {
        return NULL;
    }
    newNode->c.computer = v;
    newNode->c.min = INT_MAX;  // Initialize to INT_MAX instead of -1
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Add node to candidate list
void addToCandidateList(CandidateNode** location,CandidateList* lst, CandidateNode* newNode) {
    if (lst->head == NULL) {
        lst->head = newNode;
        lst->tail = newNode;
        newNode->next = NULL;
        newNode->prev = NULL;
    } else {
        newNode->prev = lst->tail;  // Set new node's prev to current tail
        lst->tail->next = newNode;  // Set current tail's next to new node
        lst->tail = newNode;        // Update tail to new node
        newNode->next = NULL;
    }
    location[newNode->c.computer]=newNode;
}

// Deletes the computer from priority with the lowest price
int DeleteMin(CandidateList* priority) {
    int lowest = INT_MAX;
    CandidateNode* CandLowest = NULL;
    CandidateNode* temp = priority->head;

    // Find node with the lowest min value
    while(temp != NULL) {
        if (temp->c.min <= lowest) {
            lowest = temp->c.min;
            CandLowest = temp;
        }
        temp = temp->next;
    }

    // Remove CandLowest from the list
    if (CandLowest == priority->head) {
        priority->head = CandLowest->next;
        if (priority->head) {
            priority->head->prev = NULL;
        }
    } else if (CandLowest == priority->tail) {
        priority->tail = CandLowest->prev;
        if (priority->tail) {
            priority->tail->next = NULL;
        }
    } else {
        CandLowest->next->prev = CandLowest->prev;
        CandLowest->prev->next = CandLowest->next;
    }

    int computer = CandLowest->c.computer;
    free(CandLowest);
    return computer;
}

// Updates the minimum cost of a candidate node when a better path is found
void DecreaseKey(CandidateNode* location,EdgeNode* v) {
    location->c.min=v->e.cost;
}

// Helper function to set a specific bit
void set_bit(unsigned char* bit_array, int bit_index) {
    int byte_index = bit_index / 8;
    int bit_position = bit_index % 8;
    bit_array[byte_index] |= (1 << bit_position);
}

// Helper function to clear a specific bit
void clear_bit(unsigned char* bit_array, int bit_index) {
    int byte_index = bit_index / 8;
    int bit_position = bit_index % 8;
    bit_array[byte_index] &= ~(1 << bit_position);
}

// Helper function to check if a specific bit is set
bool is_bit_set(unsigned char* bit_array, int bit_index) {
    int byte_index = bit_index / 8;
    int bit_position = bit_index % 8;
    return (bit_array[byte_index] & (1 << bit_position)) != 0;
}

// Builds a Minimum Spanning Tree using Prim's algorithm, returns array where Prim[i] is parent of node i
int* build_prim_tree(EdgeList* Net, int n) {
    // Step 1: For every v set value to INT_MAX and Prim value is -1
    int* min = (int*)calloc(n, sizeof(int));
    int* Prim = (int*)calloc(n, sizeof(int));
    CandidateNode** location = (CandidateNode**)calloc(n, sizeof(CandidateNode*));
    checkAllocation(min);
    checkAllocation(Prim);
    checkAllocation(location);

    // Initialize all values to INT_MAX and Prim to -1
    for(int i = 0; i < n; i++) {
        min[i] = INT_MAX;
        Prim[i] = -1;
    }

    // Step 2: Build inT such that for every v the value is false (0)
    unsigned char* inT = BuildBitArray(n);

    // Initialize priority queue
    CandidateList priority;
    priority.head = NULL;
    priority.tail = NULL;

    // Create and add nodes to candidate list
    for(int j = 0; j < n; j++) {
        CandidateNode* newNode = createCandNode(j);
        addToCandidateList(location, &priority, newNode);
    }

    // Step 3: Pick initial computer (v0 = 0 in this case)
    int v0 = 0;  // Could be modified to accept user input
    min[v0] = 0;
    Prim[v0] = -1;
    location[v0]->c.min = 0;  // Update priority queue for v0

    // Main Prim's algorithm loop
    while(priority.head != NULL) {
        int u = DeleteMin(&priority);
        location[u] = NULL;
        if (min[u] == INT_MAX) {
            printf("No spanning tree available.\n");
            free(min);
            free(Prim);
            free(location);
            free(inT);
            exit(0);
        }

        // Mark vertex as included in MST
        set_bit(inT, u);

        // Check all adjacent vertices
        for (EdgeNode* v = Net[u].head; v != NULL; v = v->next) {
            int neighbor = v->e.neighbor;
            // If neighbor not in MST and edge weight is less than current known minimum
            if (!is_bit_set(inT, neighbor) && v->e.cost < min[neighbor]) {
                min[neighbor] = v->e.cost;
                Prim[neighbor] = u;
                DecreaseKey(location[neighbor], v);
            }
        }
    }

    // Cleanup
    free(inT);
    free(location);

    // Free candidate list
    CandidateNode* current = priority.head;
    while (current != NULL) {
        CandidateNode* temp = current;
        current = current->next;
        free(temp);
    }

    free(min);
    return Prim;
}




