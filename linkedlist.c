#include "linkedlist.h"

Node_ptr create_node(Element value){
  Node *node = (Node *)malloc(sizeof(Node));
  node->element = value;
  node->next = NULL;
  return node;
}

List_ptr create_list(void){
  LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
  list->first = NULL;
  list->last = NULL;
  list->length = 0;
  return list;
}

Status add_to_list(List_ptr list, Element value){
  Node_ptr new_node = create_node(value);
  Node_ptr *node_to_set = &list->first;
  if(list->first != NULL){
    node_to_set = &list->last->next;
  }
  (*node_to_set) = new_node;
  list->last = new_node;
  list->length++;
  return Success;
}

