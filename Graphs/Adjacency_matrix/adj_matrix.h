/*This library has functions to deal with DIRECTED graphs in an adjacency matrix
representation.

OBS: the maximum number of nodes is 256, because a lot of variables are uint8_t. 
If you want to use more nodes, feel free to adjust the code to meet your requirements*/

#ifndef ADJ_MATRIX_H
#define ADJ_MATRIX_H

#include <stdbool.h>
#include <stdint.h>

typedef struct adjm_graph graph;

graph* create_graph(int num_nodes);
void destroy_graph(graph* g);
void print_graph(graph* g);
bool has_edge(graph* g, uint8_t from_node, uint8_t to_node);
bool add_edge(graph* g, uint8_t from_node, uint8_t to_node);
bool remove_edge(graph* g, uint8_t from_node, uint8_t to_node);

#endif   // ADJ_MATRIX_H
