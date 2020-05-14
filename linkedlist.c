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

Status add_to_start(List_ptr list, Element value){
  Node_ptr new_node = create_node(value);
  if(list->first == NULL){
    list->first= new_node;
    list->last = new_node;
  }
  else{
    new_node->next = list->first;
    list->first = new_node;
  }
  list->length++;
  return Success;
}

Prev_Current_Pair *get_prev_curr_pair(List_ptr list, int position){
  Prev_Current_Pair *pair = malloc(sizeof(Prev_Current_Pair));
  Node_ptr p_walk = list->first;
  while(position > 1){
    if(p_walk != NULL){
      p_walk = p_walk->next;
      position--;
    }
  }
  pair->prev = p_walk;
  pair->current = p_walk->next;
  return pair;
}

Status insert_at(List_ptr list, Element value, int position){
  if((position < 0 )|| (position > list->length)){
    return Failure;
  }
  if(position == 0){
    return add_to_start(list,value);
  }
  if(position == list->length){
    return add_to_list(list,value);
  }
  Node_ptr new_node = create_node(value);
  Prev_Current_Pair *pair = get_prev_curr_pair(list,position);
  new_node->next = pair->current;
  pair->prev->next = new_node;
  list->length++;
  free(pair);
  return Success;
}

int search(List_ptr list, Element value, Matcher matcher){
  Node_ptr p_walk = list->first;
  int index = 0;
  while(p_walk != NULL){
    if((* matcher)(p_walk->element,value)){
      return index;
    }
    index++;
    p_walk = p_walk->next;
  }
  return -1;
}

Status add_unique(List_ptr list, Element value, Matcher matcher){
  int index = search(list,value,matcher);
  if(index == -1){
    return add_to_list(list,value);
  }
  return Failure;
}

Element remove_from_start(List_ptr list){
  if(list->first == NULL){
    return NULL;
  }
  if(list->length == 1){
    list->last = NULL;
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
  Prev_Current_Pair *pair = get_prev_curr_pair(list,list->length-1);
  Element value = pair->current->element;
  list->last = pair->prev;
  free(pair->current);
  pair->prev->next = NULL;
  list->length--;
  free(pair);
  return value;
}

Element remove_at(List_ptr list, int position){
  if(position < 0 || position >= list->length){
    return NULL;
  }
  if(position == 0){
    return remove_from_start(list);
  }
  if(position == list->length-1){
    return remove_from_end(list);
  }
  Prev_Current_Pair *pair = get_prev_curr_pair(list,position);
  Node_ptr node_to_remove = pair->current;
  Element value = pair->current->element;
  pair->prev->next = pair->current->next;
  free(node_to_remove);
  free(pair);
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
