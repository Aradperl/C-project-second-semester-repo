#ifndef PRO_H
#define CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#define PRO_H
#define White 0
#define Gray 1
#define Black 2

// Structs of Q1
typedef struct {
    int neighbor;
    int cost;
} Edge;
typedef struct edge_node {
    Edge e;
    struct edge_node *next;
} EdgeNode;
typedef struct {
    EdgeNode *head;
    EdgeNode *tail;
} EdgeList;

// Structs of Q2
typedef struct {
    int computer;
    int min;
} Candidate;
typedef struct candidate_node {
    Candidate c;
    struct candidate_node *next;
    struct candidate_node *prev;
} CandidateNode;
typedef struct {
    CandidateNode *head;
    CandidateNode *tail;
} CandidateList;

// Q1 functions
int checkAllocation(void* ptr);
EdgeNode* createEdgeNode(Edge edg);
void SortEdgeList(EdgeList* lst,Edge edg,int ComputerNum);
EdgeList *build_net(int n);
void free_net(EdgeList* network, int n);


// Q2 functions
unsigned char* BuildBitArray(int n);
CandidateNode* createCandNode(int v);
void addToCandidateList(CandidateNode** location, CandidateList* lst, CandidateNode* newNode);
int DeleteMin(CandidateList* priority);
void DecreaseKey(CandidateNode* location, EdgeNode* Node);
void verifyPrimMST(EdgeList* Net, int* Prim, int n);
int* build_prim_tree(EdgeList* Net, int n);

// Bit Array Helper functions
void set_bit(unsigned char* bit_array, int bit_index);
void clear_bit(unsigned char* bit_array, int bit_index);
bool is_bit_set(unsigned char* bit_array, int bit_index);

// Q3 functions
EdgeList *build_paths(int* tree,int n);
void free_paths(EdgeList* paths, int n);

// Q4 functions
void find_and_print_path(EdgeList primpaths[], int n, int first, int last);
void FindPath(int u, int* colors, int* Parent, EdgeList primpaths[], int last);
void printPath(int v, int* Parent, int first);

#endif //PRO_H
