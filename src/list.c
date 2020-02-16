
#include <stdlib.h>

#include "list.h"

void list_insert_begin(struct list* l, void* data) {
  struct node* new_node = (struct node*)malloc(sizeof(struct node));
  new_node->data = data;
  new_node->prev = NULL;
  new_node->next = l->start;
  l->start->prev = new_node;
  l->start = new_node;
}