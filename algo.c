#include <stdio.h>
/*
 * structr to single node
 */
struct AdjListNode {
    int dest;
    struct AdjListNode* next;
};

// A structure to all the nodes
struct AdjList {
    struct AdjListNode* head;
};
// A structure to the graph
struct Graph {
    int v; //size
    struct AdjList* array;
};
int A(){
    int size=0;
    scanf("%d" , size);


}
