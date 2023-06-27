/*This library has functions to deal with DIRECTED graphs in an adjacency matrix
representation.

OBS: the maximum number of nodes is 256, because a lot of variables are uint8_t. 
If you want to use more nodes, then you must adjust the code to meet your requirements*/

#ifndef PRINT_FUNC
#define PRINT_FUNC
#include <stdio.h>
#include <stdlib.h>
#endif
#include "adj_matrix.h"


struct adjm_graph {
    uint8_t num_nodes;
    bool** edges;
};


/*Tries to create a graph based on the given number of nodes. Returns a pointer
to the new graph on success and NULL on failure.*/
graph* create_graph(int num_nodes) {
    graph* g = (graph*)malloc(sizeof(graph));

    if (g == NULL) {
        printf("%s\n", "Memory allocation for graph failed. Aborting...");
        return NULL;
    }

    g->num_nodes = num_nodes;

    // Allocating memory for the adjacency matrix.
    g->edges = (bool**)calloc(num_nodes, sizeof(bool*));

    if (g->edges == NULL) {
        printf("%s\n", "Memory allocation for g->edges failed. Aborting...");
        free(g);
        return NULL;
    }

    for (int i=0; i < num_nodes; i++) {
        g->edges[i] = (bool*)calloc(num_nodes, sizeof(bool));

        if (g->edges[i] == NULL) {
            printf("Memory allocation for g->edges[%d] failed. Aborting...\n", i);
            destroy_graph(g);
            return NULL;
        }
    }

    return g;
}


/*Frees up the memory allocated for the given graph. Note that it does not set
the g pointer to NULL automatically.*/
void destroy_graph(graph* g) {
    if (g) {
        if (g->edges) {
            for (int i=0; i < g->num_nodes; i++) {
                if (g->edges[i]) {
                    free(g->edges[i]);
                }
            }
        }

        free(g->edges);
        free(g);
    }
}


/*Prints out the content of the given graph.*/
void print_graph(graph* g) {
    if (g == NULL) {
        printf("%s\n", "Graph is NULL.");
        return;
    }

    printf("%s\n", "digraph {");

    for (int from=0; from < g->num_nodes; from++) {
        for (int to=0; to < g->num_nodes; to++) {
            if (g->edges[from][to] != 0) {
                printf("%d --> %d;\n", from, to);
            }
        }
    }

    printf("%s\n", "}");
}


/*Checks to see if there is an edge between start and finish nodes. Returns
true if there is one and false if ther isnt any.*/
bool has_edge(graph* g, uint8_t from_node, uint8_t to_node) {
    if (g->edges[from_node][to_node])
        return true;
    
    else
        return false;
}


/*Tries to create an edge between the start and finish nodes. Returns true on
success and false on failure.*/
bool add_edge(graph* g, uint8_t from_node, uint8_t to_node) {
    if (has_edge(g, from_node, to_node)) {
        printf("An edge already exists between nodes %u and %u.", from_node, to_node);
        return false;
    }
    else {
        g->edges[from_node][to_node] = true;
        return true;
    }
}


/*Tries to remove an edge between the start and finish nodes. Returns true on
success and false on failure.*/
bool remove_edge(graph* g, uint8_t from_node, uint8_t to_node) {
    if (!has_edge(g, from_node, to_node)) {
        printf("There is no edge between nodes %u and %u", from_node, to_node);
        return false;
    }
    else {
        g->edges[from_node][to_node] = false;
        return true;
    }
}
