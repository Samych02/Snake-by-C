#pragma once

#include "structure.h"

Node* create_linked_list();
int get_list_size(const Node* head);
Node* front_insert(Node* head, const NodeType* data);
Node* back_insert(Node* head, const NodeType* data);
NodeType get_list_head(const Node* head);
NodeType get_list_tail(const Node* head);
Node* free_linked_list(Node* head);

