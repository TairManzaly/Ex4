//
// Created by tairm on 1/10/2022.
#include <stdio.h>
#include <stdlib.h>
#include "nodes.c"
#include "minHeap.c"
#include "graph.h"
#define INFINITY 9999

void insert_node_cmd(pnode *head, int node_num){
    pnode current = head;
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
    pnode current = head;
    while (current->node_num!=node_num && current->next!=NULL) {
        current = current->next;
    }
    /* now we can add a new variable */
    if(current->node_num == node_num){
        pedge edges = current->edges;
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
        pedge edges = current->edges;
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
    pnode n = head;
    pnode current = head;
    pnode previous = NULL;
    //if list is not empty
    if(n != NULL) {
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
        if(current == n) {
            //change first to point to next link
            n = n->next;
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
    pnode currentNode = head;
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
            pedge current = currentNode->edges;
            pedge next = NULL;

            while (current != NULL){
                next = current->next;
                free(current);
                current = next;
            }
            // deref currentNode->edges to affect the real head back in the caller.
            currentNode->edges = NULL;
        }
    }
}
//(4)
void delete_in_edges_cmd(pnode *head, int node_num){
    //start from the first link
    pnode currentNode = head;
    //if list is not empty
    if(head != NULL) {
        //navigate through list
        while(currentNode->next != NULL) {
            pedge currentEdge = currentNode->edges;
            pedge previousEdge = NULL;
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
//void dijkstra(node head){
//    int V = 0;
//    node n = head;
//    while(n.next!=NULL){
//        V++;
//        n = *n.next;
//    }
//
//    struct MinHeap *Q = createMinHeap(V);
//    double dist[V];
//    double prev[V];
//
//
//}
void free_dij(pdnode arr) {
    while (arr != NULL){
        pdnode t = arr;
        arr = arr->next;
        free(t);
    }
}


pdnode dijkstra(pnode n, int i){
    pdnode head = NULL;
    pdnode *t = &head;
    while (n != NULL)
    {
        (*t) = (pdnode)malloc(sizeof(pdnode)); //allocate mamory
        if ((*t) == NULL){
            printf("Error");
            return NULL;
        }
        (*t)->node = n;
        if (n->node_num == i){
            (*t)->prev = (*t);
            (*t)->weight = 0;
        }
        else{
            (*t)->prev = NULL;
            (*t)->weight = INFINITY ;
        }
        (*t)->tag = 0;
        (*t)->next = NULL;
        t = &((*t)->next);
        n = n->next;
    }
    return head;
}

pdnode min(pdnode head){
    pdnode result = NULL;
    while (head != NULL){
        if (!head->tag && head->weight < INFINITY  && (result == NULL || result->weight < head->weight)){
            result = head;
        }
        head = head->next;
    }
    if (result != NULL){
        result->tag = 1;
    }
    return result;
}


pdnode getDijNode(int x, pdnode List){
    while (List != NULL){
        if (List->node->node_num == x){
            return List;
        }
        List = List->next;
    }
    return NULL;
}

int S(pnode head, int src, int dest){  //The main function
    pdnode list = dijkstra(head, src);
    pdnode node_u = min(list);
    while (node_u != NULL){
        pedge Edge = node_u->node->edges;
        while (Edge != NULL){
            pdnode node_v = getDijNode(Edge->endpoint->node_num,list);
            int dist = node_u->weight + Edge->weight;
            if (node_v->weight > dist){
                node_v->weight = dist;
                node_v->prev = node_u;
            }
            Edge = Edge->next;
        }
        node_u = min(list);
    }
    int res = getDijNode(dest,list)->weight;
    res = (res == INFINITY )? -1: res;
    free_dij(list);
    return res;
}





int main(){
        struct GRAPH_NODE_ *pnode = NULL;
        struct GRAPH_NODE_ **head = NULL;
        head = (struct GRAPH_NODE_*)malloc(1*sizeof(struct GRAPH_NODE_));
        if (head == NULL){
            printf("There is not enough memory. Exiting.\n");
            return 0;
        }
        *head = pnode;
}