#ifndef GRAPH_
#define GRAPH_

typedef struct GRAPH_NODE_ *pnode;;

typedef struct edge_ {
    int weight;
    pnode endpoint;
    struct edge_ *next;
} edge, *pedge;


typedef struct GRAPH_NODE_ {
    int node_num;
    pedge edges;
    struct GRAPH_NODE_ *next;
} node, *pnode;




void build_graph_cmd(pnode *head);
void insert_node_cmd(pnode *head, int node_num);
void delete_node_cmd(pnode *head, int );
void printGraph_cmd(pnode head); //for self debug
void deleteGraph_cmd(pnode* head);
int S(pnode head , int , int );
int T(pnode head);
void D(pnode *head, int node_num);

#endif
