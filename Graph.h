#ifndef UNTITLED22_GRAPH_H
#define UNTITLED22_GRAPH_H

#include <string.h>
#include <stdlib.h>
#include "set.h"


typedef struct node{
    Set s;
    struct node *next;
} Node;

typedef struct{
    Node* head;
} List;

typedef struct {
    List verticesList;
} Graph;


Graph* GraphCreate();
void GraphDestroy(Graph* graph);
Result GraphAddVertic(Graph* graph,char* verticData);
Result GraphAddEdge(Graph* graph,char* source, char* destination);
Result GraphRemoveVertic(Graph* graph,char* verticData);
Result GraphRemoveEdge(Graph* graph,char* source, char* destination);
Set GraphGetNeighbors(Graph* graph, char* source);
Set GraphGetReachableNeighbors(Graph* graph, char* source);
Boolean GraphAreConnected(Graph* graph, char *a, char *b);


#endif
