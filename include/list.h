
#ifndef __LIST_H__
#define __LIST_H__

struct list {
  struct node* start;
};

struct node {
  void* data;
  struct node* next;
  struct node* prev;
};

void list_insert_begin(struct list*, void* data);

#define list_for_each_node(node, list) \
  for (node = list->start; node != NULL; node = node->next;)

#endif
