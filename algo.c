#include <stdio.h>
#include <graph.h>

//?
void insert_node_cmd(pnode *head, int node_num){
    pnode* current = head;
    while (current->next!=NULL && current->node_num!=node_num) {
        current = current->next;
    }
    /* now we can add a new variable */
    if (current->node_num!=node_num){
        current->next = (struct GRAPH_NODE_*) malloc(sizeof(struct GRAPH_NODE_));
        current->next->node_num = node_num; 
        current->next->next = NULL;
    }
}
//(1)A:
void insert_edge_cmd(pnode *head, int weight, pnode endpoint, int node_num){
    pnode* current = head;
    while (current->node_num!=node_num && current->next!=NULL) {
        current = current->next;
    }
    /* now we can add a new variable */
    if(current->node_num == node_num){
        pedge* edges = current->edges;
        while((edges->next) != NULL){
            edges = edges->next;
        }
        edges->next = (struct edge_*) malloc(sizeof(struct edge_));
        edges->next->weight = weight;
        edges->next->endpoint = endpoint;
        edges->next->next = NULL;
    }
    else if (current->node_num!=node_num && current->next==NULL){
        current->next->node_num = node_num;
        current = current->next;
        pedge* edges = current->edges;
        while((edges->next) != NULL){
            edges = edges->next;
        }
        edges->next = (struct edge_*) malloc(sizeof(struct edge_));
        edges->next->weight = weight;
        edges->next->endpoint = endpoint;
        edges->next->next = NULL;
    }
    
}
//(3)
void delete_node_cmd(pnode *head, int node_num){
   //start from the first link
   pnode* current = head;
   pnode* previous = NULL;
   //if list is not empty
   if(head != NULL) {
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
        }
        else if(current->node_num == node_num){
            //bypass the current link
            previous->next = current->next;
        }
   }
}
//(2)
void delete_out_edges_cmd(pnode *head, int node_num){
   //start from the first link
   pnode* currentNode = head;
   //if list is not empty
   if(head != NULL) {
    //navigate through list
    while(currentNode->node_num != node_num) {
        //if it is last node
        if(currentNode->next != NULL) {
            //move to next link
            currentNode = currentNode->next;
        }
    }
    if (currentNode->node_num==node_num){
        pedge* current = *currentNode->edges;
        pedge* next = NULL;
 
        while (current != NULL){
            next = current->next;
            free(current);
            current = next;
        }
    // deref currentNode->edges to affect the real head back in the caller.
        *currentNode->edges = NULL
    }
   }
}
//(4)
void delete_in_edges_cmd(pnode *head, int node_num){
  //start from the first link
   pnode* currentNode = head;
   //if list is not empty
   if(head != NULL) {
    //navigate through list
    while(currentNode->next != NULL) {
        pedge* currentEdge = currentNode->edges; 
        pedge* previousEdge = NULL;
        while(currentEdge->next != NULL){
            if(currentEdge->endpoint==node_num){
                //store reference to current link
                previousEdge = currentEdge;
                //move to next link
                currentEdge = currentEdge->next;
                //found a match, update the link
                if(currentEdge == currentNode->edges) {
                //change first to point to next link
                currentNode->edges = currentNode->edges->next;
                }
                else{
                //bypass the current link
                previousEdge->next = currentEdge->next;
                }
            }
            currentEdge = currentEdge->next;
        }
        currentNode = currentNode->next;

    }
   }
}

void D(pnode *head, int node_num){
    delete_out_edges_cmd(*head, node_num);
    delete_in_edges_cmd(*head, node_num);
    delete_node_cmd(*head, node_num);
}

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