#include "Graph.h"

Boolean compareElement(void *a, void *b){
    return strcmp((char*)a,(char*)b) == 0 ? FALSE : TRUE;
}

void* copyElement(void *toCopy){
    char *element = (char*) malloc((strlen((char*)toCopy)+1)*(sizeof(char)));
    strcpy(element,(char*)toCopy);
    return (void*)element;
}

char* label(void* element){
    return (char*)element;
}

Boolean areConnected(Graph *graph, char *a, char *b) {
    if (!a || !b){
        return FALSE;
    }
    return SetIsIn(GraphGetReachableNeighbors(graph,a),b);
}
