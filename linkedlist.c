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

Element remove_from_start(List_ptr list){
  if(list->first == NULL){
    return NULL;
  }
  Node_ptr node_to_remove = list->first;
  list->first = list->first->next;
  Element value = node_to_remove->element;
  free(node_to_remove);
  list->length--;
  return value;
}

Element remove_from_end(List_ptr list){
  if(list->first == NULL){
    return NULL;
  }
  if(list->length == 1){
    return remove_from_start(list);
  }
  Node_ptr p_walk = list->first;
  while(p_walk->next->next != NULL){
    p_walk = p_walk->next;
  }
  list->last = p_walk;
  Element value = p_walk->next->element;
  free(p_walk->next);
  p_walk->next = NULL;
  list->length--;
  return value;
 }

Status clear_list(List_ptr list){
  Status status = Success;
  Element value;
  while(list->first != NULL){
    value = remove_from_end(list);
    if(value == NULL){
      status = Failure;
    }
  }
  list->last = NULL;
  return status;
}

void destroy_list(List_ptr list){
  clear_list(list);
  free(list);
}
