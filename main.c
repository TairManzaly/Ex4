#include <stdio.h>
#include "graph.h"
int main(){
    pnode new = NULL;
    pnode *head = &new;
    char i;
    while (scanf("%c")!=EOF){
        scanf("%c",&i);
        if (i=='A'){
            build_graph_cmd(head);
        }
        if(i=='B'){
            int nodeNum;
            scanf("%c" , &nodeNum);
            insert_node_cmd(head,nodeNum);
        }
        if(i=='D'){
            int nodeNum;
            scanf("%c" , &nodeNum);
            D(head,nodeNum);
        }
        if (i == 'S'){
            int src,dst;
            scanf("%d %d", &src,&dst);
            int sp = S(new,src,dst);
            printf("Dijsktra shortest path: %d \n",&sp);
        }
        if (i=='T'){
            int tsp =  T(new);
            printf("TSP shortest path: %d \n",&tsp);
        }

    }
    return 0;
}