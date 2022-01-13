//
// Created by tairm on 1/10/2022.
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#define INFINITY 9999
pnode graph;
int weight;
void  build_graph_cmd(pnode *head){
    int size = 0;
    scanf("%d",&size);
    D(head,size);
    char n = 0;
    int i = 0;
    while(i<size) {
        scanf("%c", n);
        insert_node_cmd(head, n);
        i++;
    }
}

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
typedef struct Dijkstra_Node{
    pnode node;
    int dist;
    int tag;
    struct Dijkstra_Node *prev; //for array of path
    struct Dijkstra_Node *next;
} dnode, *pdnode;

void free_dij(pdnode arr) {
    while (arr != NULL){
        pdnode t = arr;
        arr = arr->next;
        free(t);
    }
}
pnode dist_prev(pnode head, int i){
    pdnode n = NULL;
    pdnode *pn = &n;
    while (head!= NULL){
        *pn = (pnode) malloc(sizeof (pnode));
        if(*pn == NULL) {
            printf("There is not enough memory. Exiting.\n");
            return NULL;
        }
        (*pn)->node = head;
        if(head->node_num==i){// if the head is the src
            (*pn)->prev = *pn;
            (*pn)->dist = 0;
        }
        else{
            (*pn)->prev = NULL;
            (*pn)->dist = INFINITY;
        }
        (*pn)->tag =0;
        (*pn)->next =NULL;
        pn = &((*pn))->next;
        head = head->next;
    }
    return n;
}
pdnode min_neighbor(pdnode u){
    pdnode res=NULL;
    while (u!=NULL){

        if(!u->tag && u->dist<INFINITY && (res == NULL || res->dist < u->dist)){
            res = u;
        }
        u = u->next;
    }
    if (res!=NULL){
        res->tag = 1;
    }
    return res;
}



//pdnode getDiNode(int x, pdnode List){
//    while (List != NULL){
//        if (List->node->node_num == x){
//            return List;
//        }
//        List = List->next;
//    }
//    return NULL;

int S(pnode head, int src, int dest){
    pdnode src_node = dist_prev(head,src);
    pdnode v = min_neighbor(src_node);
    pdnode u = NULL;
    while (v!=NULL){
        pedge e = v->node->edges;
        while (e !=NULL){

            while (src_node != NULL){
                if (src_node->node->node_num == e->endpoint->node_num){
                   u=src_node;
                }
                src_node= src_node->next;
            }
            int weight = v->dist + e->weight;
            if(weight< u->dist){
                u->dist = weight;
                u->prev = u;
            }
            e = e->next;

        }
        u = min_neighbor(dist_prev(head,src));
    }
    int ans = min_neighbor(u)->dist;
    return ans;

}

void swap(int* arr, int i, int j){
    int temp = arr[i];
    arr[i]= arr[j];
    arr[j] = temp;
}

void permutation_array(int* arr, int len){
    int curr = 0;
    for (int i = 0; i < len-1; ++i){
        int dist = S(graph, arr[i], arr[i+1]);
        if (dist == -1){
            curr = INFINITY;
            return;
        }
        curr += dist;
    }
    if (curr < weight){
        weight = curr;
    }
}

void arr_input(int* a,int* b, int len) {
    for (int i = 0; i < len; ++i){
        b[i] = a[i];
    }
}


void check( int i ,int* arr, int len){
    if (i == len -1 ){
        int current = 0;
        for (int j = 0; j < len-1; ++j){
            int dist = S(graph, arr[j], arr[i+1]);
            if (dist == -1){
                current = INFINITY;
                return;
            }
            current += dist;
        }
        if (current < weight){
            weight = current;
        }
        return;
    }
    for (int j = i; j < len; ++j) {
        int* new = (int*)(calloc(len, sizeof(int)));
        arr_input(arr,new,len);
        swap(new,i, j);
        check(i + 1, new, len);
        free(new);
    }
}

int T(pnode h){   ////The main function
    weight = INFINITY ;
    int l = 0;
    graph = h;
    scanf("%d", &l);
    int *arr = (int *) (calloc(l, sizeof(int)));
    for (int i = 0; i < l; i++) {
        scanf("%d", &arr[i]);
    }
    int *new = (int *) (calloc(l, sizeof(int)));
    arr_input(arr,new,l);
    check(0,new,l);
    free(arr);
    free(new);
    if (weight == INFINITY){
        weight = -1;
    }
    return weight;
}


