#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <vector>

#define NUM_VERTICES 6

using namespace std;

// Structure for the nodes in the adjacency list
struct adjacency_list_node {
    char node_name;
    adjacency_list_node* next_node = NULL;
};

// Structure for the nodes in the graph
struct graph_node {
    char node_name;
    vector<graph_node*> ptr; // To store adjacent nodes
};

// Structure for the nodes in the vertex array
struct vertex_array_node {
    char node_name;
    adjacency_list_node* list_base_addr = NULL; // Head of the adjacency list
    graph_node* node_addr = NULL; // Graph node associated with this vertex
    vertex_array_node* next_node = NULL;
};

// Head and tail pointers for the adjacency list
adjacency_list_node* al_head = NULL;
adjacency_list_node* al_tail = NULL;

// Head and tail pointers for the vertex array
vertex_array_node* va_head = NULL;
vertex_array_node* va_tail = NULL;
vertex_array_node* temp_va_tail = NULL;

// Function to create a new vertex in the vertex array
void create_vertex_array(vertex_array_node* new_node) {
    if (va_head == NULL) {
        va_head = new_node;
        va_tail = va_head;
        temp_va_tail = va_head;
    } else {
        va_tail->next_node = new_node;
        va_tail = new_node;
    }
}

// Function to create a new node in the adjacency list
void create_adjacency_linked_list(adjacency_list_node* new_node, vertex_array_node* vertex_node_addr) {
    if (al_head == NULL) {
        vertex_node_addr->list_base_addr = new_node;
        al_head = new_node;
        al_tail = new_node;
    } else {
        al_tail->next_node = new_node;
        al_tail = new_node;
    }
}

// Function to traverse the adjacency list
void traverse_adjacency_list(adjacency_list_node* base_addr) {
    while (base_addr != NULL) {
        printf("%c -> ", base_addr->node_name);
        base_addr = base_addr->next_node;
    }
    printf("NULL");
}

// Function to add an edge between two nodes in the graph
void add_edge(graph_node* src_node, graph_node* dst_node) {
    src_node->ptr.push_back(dst_node);
    dst_node->ptr.push_back(src_node);
}

int main() {
    srand(time(NULL));
    bool is_edge;
    adjacency_list_node* new_al_node = NULL;
    graph_node* new_graph_node = NULL;
    vertex_array_node* new_va_node = NULL;

    temp_va_tail = va_tail;

    for (size_t i = 0; i < NUM_VERTICES; i++) {
        new_va_node = (vertex_array_node*)calloc(1, sizeof(vertex_array_node));
        new_va_node->node_name = (65 + i);
        new_graph_node = (graph_node*)calloc(1, sizeof(graph_node));
        new_graph_node->node_name = (65 + i);
        new_va_node->node_addr = new_graph_node;
        create_vertex_array(new_va_node);

        al_head = NULL;
        al_tail = NULL;

        for (size_t j = 0; j < NUM_VERTICES; j++) {
            if (i == j)
                continue;
            else {
                is_edge = rand() % 2;

                if (is_edge == true) {
                    new_al_node = (adjacency_list_node*)calloc(1, sizeof(adjacency_list_node));
                    new_al_node->node_name = (65 + j);
                    create_adjacency_linked_list(new_al_node, new_va_node);
                    add_edge(new_graph_node, va_head->node_addr);
                    /* Add an edge to the graph
                    for establishing actual connections between nodes */
                }
            }
        }
    }

    printf("Following is the information about the graph:\n\n");

    temp_va_tail = va_head;
    while (temp_va_tail != NULL) {
        printf("Adjacency List of Node %c is: ", temp_va_tail->node_name);
        traverse_adjacency_list(temp_va_tail->list_base_addr);
        printf("\n");
        temp_va_tail = temp_va_tail->next_node;
    }
    
    /* Create actual connections between nodes in the graph
    ~ when we create_adjacency_linked_list,With that we established connections...
    we can see in main function
    we calling "add_edge(new_graph_node, va_head->node_addr);" after calling "create_adjacency_linked_list" */

    printf("\n\nEdges of Nodes/Vertices... \n\n");

    temp_va_tail = va_head;

    for (size_t i = 0; i < NUM_VERTICES; i++) {
        al_tail = temp_va_tail->list_base_addr;

        printf("Edges for Node %c: ", temp_va_tail->node_name);
        while (al_tail != NULL) {
            printf("%c ", al_tail->node_name);
            al_tail = al_tail->next_node;
        }
        printf("\n");

        temp_va_tail = temp_va_tail->next_node;
    }

    return 0;
}

/*	overview...
     this code establishes actual connections between nodes in a graph.
	also It creates adjacency list data structures to represent the connections between nodes (vertices)
	and also adds edges between nodes using the add_edge function. */
