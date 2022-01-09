#include <stdio.h>
#include <graph.h>
/*
 * structr to single node
 */
// struct AdjListNode {
//     int dest;
//     struct AdjListNode* next;
// };

// // A structure to all the nodes
// struct AdjList {
//     struct AdjListNode* head;
// };
// // A structure to the graph
// struct Graph {
//     int v; //size
//     struct AdjList* array;
// };
// int A(){
//     int size=0;
//     scanf("%d" , size);

// }

void insert_node_cmd(pnode *head, struct GRAPH_NODE_ new){
    pnode* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    /* now we can add a new variable */
    current->next = (struct GRAPH_NODE_*) malloc(sizeof(struct GRAPH_NODE_));
    current->next->new = new; //?
    current->next->next = NULL;
}

void delete_node_cmd(pnode *head, int node_num){
   //start from the first link
   pnode* current = head;
   pnode* previous = NULL;
   //if list is empty
   if(head == NULL) {
      return NULL;
   }
   //navigate through list
   while(current->node_num != node_num) {
      //if it is last node
      if(current->next != NULL) {
         //store reference to current link
         previous = current;
         //move to next link
         current = current->next;
      }
   }
   //found a match, update the link
   if(current == head) {
      //change first to point to next link
      head = head->next;
   } else {
      //bypass the current link
      previous->next = current->next;
   }    
}


void delete_node_cmd(pnode *head);

int main{
    struct GRAPH_NODE_ *pnode = NULL;
    struct GRAPH_NODE_ **head = NULL;
    head = (struct GRAPH_NODE_*)malloc(1*sizeof(struct GRAPH_NODE_));
    if (head == NULL){
        printf("There is not enough memory. Exiting.\n");
        return 0;
    }
    *head = pnode;
}