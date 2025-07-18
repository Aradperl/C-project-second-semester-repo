#include "pro.h"

// Checks the allocation of the memory
int checkAllocation(void* ptr)
{
    if (ptr == NULL)
    {
        return 0; // Indicate failure
    }
    return 1; // Indicate success
}

// Creates a new node of Edge
EdgeNode* createEdgeNode(Edge edg) {
    EdgeNode* newNode = (EdgeNode*)malloc(sizeof(EdgeNode));
    if (!checkAllocation(newNode)) {
        return NULL; // Return NULL on allocation failure
    }
    newNode->e = edg;
    newNode->next = NULL;
    return newNode;
}

// Inserting a connection information to right place in the right spot in the array
void SortEdgeList(EdgeList* lst,Edge edg,int ComputerNum) {
    EdgeList* CurrentList= &lst[ComputerNum];
    EdgeNode* newNode=createEdgeNode(edg);
    if (newNode == NULL) return; // Handle allocation failure from createEdgeNode
    if(CurrentList->head==NULL) {
        CurrentList->head=newNode;
        CurrentList->tail=newNode;
        return;
    }
    if (newNode->e.neighbor < CurrentList->head->e.neighbor) {
        newNode->next = CurrentList->head;
        CurrentList->head = newNode;
        return;
    }
    EdgeNode* prev = CurrentList->head;
    EdgeNode* temp = prev->next;

    while (temp != NULL && temp->e.neighbor < newNode->e.neighbor) {
        prev = temp;
        temp = temp->next;
    }
    prev->next = newNode;
    newNode->next = temp;
    if (temp == NULL)
        CurrentList->tail = newNode;
}

// Builds a network of computers
EdgeList *build_net(int n) {
    int a, b, price, m;
    Edge newEdg;
    EdgeList* lst = (EdgeList*)malloc(n * sizeof(EdgeList));
    if (!checkAllocation(lst)) {
        return NULL; // Return NULL on allocation failure
    }
    scanf("%d",&m);
    // Initialize all lists
    for (int i = 0; i < n; i++) {
        lst[i].head = NULL;
        lst[i].tail = NULL;
    }
    // Reads the computers numbers and the price of the line
    for (int j = 0; j < m; j++) {
        scanf("%d %d %d", &a, &b, &price);
        // Checks for invalid values
        if (a < 0 || a >= n || b < 0 || b >= n || price < 0) {
            printf("Invalid input.\n"); // Print error here
            free_net(lst, n); // Free already allocated memory
            exit(0);
        }
        
        // Add the connection between A to B
        newEdg.cost = price;
        newEdg.neighbor = b;
        SortEdgeList(lst, newEdg, a);
        
        // Add the connection between B to A
        newEdg.neighbor = a;
        SortEdgeList(lst, newEdg, b);
    }
    return lst;
}

// Frees the memory allocated for the network
void free_net(EdgeList* network, int n) {
    if (network == NULL || n <= 0) return;

    for (int i = 0; i < n; i++) {
        EdgeNode* current = network[i].head;
        while (current != NULL) {
            EdgeNode* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(network);
}



