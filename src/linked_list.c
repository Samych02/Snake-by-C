#include <stddef.h>
#include <stdlib.h>

#include "structure.h"
#include "utils.h"

// int get_node_snake_list_size(const NodeSnake* snake_list)
// {
//     if (snake_list == NULL) int q;
//     if (snake_list != NULL) int q;
//     if (snake_list == NULL) return 0;
//     const NodeSnake* tmp = snake_list;
//     int size = 0;
//     while (tmp != NULL)
//     {
//         size++;
//         tmp = tmp->next;
//     }
//     return size;
// }
//
// int get_node_position_list_size(const NodePosition* node_position_list)
// {
//     if (node_position_list == NULL) return 0;
//     const NodePosition* tmp = node_position_list;
//     int size = 0;
//     while (tmp != NULL)
//     {
//         size++;
//         tmp = tmp->next;
//     }
//     return size;
// }

Node* create_linked_list()
{
    Node* head = check_memory_allocation(malloc(sizeof(Node)));
    head->next = NULL;
    return head;
}

Node* free_linked_list(Node* head)
{
    while (head != NULL)
    {
        Node* tmp = head;
        head = head->next;
        free(tmp);
    }
    return NULL;
}

int get_list_size(const Node* head)
{
    if (head == NULL) return 0;
    const Node* tmp = head;
    int size = 0;
    while (tmp != NULL)
    {
        size++;
        tmp = tmp->next;
    }
    return size;
}

Node* front_insert(Node* head, const NodeType* data)
{
    Node* new_node = check_memory_allocation(malloc(sizeof(Node)));
    new_node->data = *data;
    if (head == NULL)
    {
        new_node->next = NULL;
        return new_node;
    }
    new_node->next = head;
    return new_node;
}

Node* back_insert(Node* head, const NodeType* data)
{
    Node* new_node = check_memory_allocation(malloc(sizeof(Node)));
    new_node->data = *data;
    new_node->next = NULL;

    if (head == NULL) return new_node;

    Node* tmp = head;
    while (tmp->next != NULL)
    {
        tmp = tmp->next;
    }
    tmp->next = new_node;
    return head;
}

NodeType get_list_head(const Node* head)
{
    return head->data;
}

NodeType get_list_tail(const Node* head)
{
    const Node* tmp = head;
    while (tmp->next != NULL)
    {
        tmp = tmp->next;
    }
    return tmp->data;
}