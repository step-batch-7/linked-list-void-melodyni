#include "../linkedlist.h"

void green(){
  printf("\033[1;30m");
}

void red(){
  printf("\033[0;31m");
}

void white(){
  printf("\033[1;0m");
}

void print_result(int passed,char *message){
  if(passed){
    green();
    printf("   ✔ %s\n",message);
  }else{
    red();
    printf("   ✘ %s\n",message);
  }
  white();
}

void test_create_list(){
  printf("\ncreate_list\n");
  char message[] = "should initialise an empty list";
  List_ptr list = create_list();
  Status status = list != NULL &&  list->first == NULL &&  list->last == NULL && list->length == 0;
  print_result(status,message);
  destroy_list(list);
}

void test_add_to_start(){
  printf("\nadd_to_start\n");
  char message[] = "should add integer in the beginning of list";
  List_ptr list = create_list();
  int num = 2;
  Status status = add_to_start(list,&num);
  Status is_passed = status && (*(int *)(list->first->element) == 2) && (list->length == 1);
  print_result(status,message);
  destroy_list(list);

  char message2[] = "should add character at the beginning of list";
  List_ptr list2 = create_list();
  char letter = 'R';
  Status status2 = add_to_start(list2,&letter);
  Status is_passed2 = status2 && (*(char *)(list2->first->element) == 'R') && (list2->length == 1);
  print_result(status2,message2);
  destroy_list(list2);
}

void test_add_to_list(){
  printf("\nadd_to_list\n");
  char message[] = "should add integer at the end of list";
  List_ptr list = create_list();
  int num = 2;
  Status status = add_to_list(list,&num);
  Status is_passed = status && (*(int *)(list->last->element) == 2) && (list->length == 1);
  print_result(status,message);
  destroy_list(list);

  char message2[] = "should add double at the end of list";
  List_ptr list2 = create_list();
  double num2 = 2.567;
  Status status2 = add_to_list(list2,&num2);
  Status is_passed2 = status2 && (*(int *)(list2->last->element) == 2.567) && (list2->length == 1);
  print_result(status2,message2);
  destroy_list(list2);
}

void test_insert_at(){
  printf("\ninsert_at\n");
  char message[] = "should insert the given value at the begining of list";
  List_ptr list = create_list();
  int num = 2;
  int num2 = 99;
  add_to_list(list,&num);
  Status status = insert_at(list,&num2,0);
  Status is_passed = status && (*(int *)(list->first->element) == 99) && (list->length == 2);
  print_result(status,message);
  destroy_list(list);

  char message2[] = "should insert the given value at given position in list";
  List_ptr list2 = create_list();
  char char1 = 'R';
  char char2 = 'A';
  char char3 = 'I';
  char char4 = 'G';
  add_to_list(list2, &char1);
  add_to_list(list2, &char2);
  add_to_list(list2, &char3);
  Status status2 = insert_at(list2, &char4, 2);
  Prev_Current_Pair *pair = get_prev_curr_pair(list2,2);
  Status is_passed2 = status2 && (*(char *)(pair->current->element) == 'G') && (list2->length == 4);
  print_result(status2,message2);
  destroy_list(list2);

  char message3[] = "should not insert in list if position is invalid";
  List_ptr list3 = create_list();
  int num3 = 2;
  int num4 = 99;
  add_to_list(list3,&num3);
  Status status3 = insert_at(list3,&num4,5);
  Status is_passed3 = !status3 && (list3->length == 1);
  print_result(is_passed3,message3);
  destroy_list(list3);

  char message4[] = "should insert at the end of list ";
  List_ptr list4 = create_list();
  int num5 = 2;
  int num6 = 99;
  add_to_list(list4,&num4);
  Status status4 = insert_at(list4,&num6,1);
  Status is_passed4 = status4 && (list4->length == 2) && (*(int *)(list->last->element) == 99);
  print_result(is_passed4,message4);
  destroy_list(list4);
}

Status match_int(Element value_a, Element value_b){
  int num_a = *(int *)value_a;
  int num_b = *(int *)value_b;
  return num_a == num_b;
}

void test_add_unique(){
  printf("\nadd unique\n");
  char message[] = "should add given value if it does not exist in list";
  List_ptr list = create_list();
  int num = 2;
  int num2 = 3;
  add_to_list(list,&num);
  Status status = add_unique(list, &num2, &match_int);
  Status is_passed = status && (*(int *)(list->last->element) == 3) && (list->length == 2);
  print_result(is_passed,message);
  destroy_list(list);

  char message2[] = "should not add given value if it exists in list";
  List_ptr list2 = create_list();
  int num3 = 2;
  int num4 = 2;
  add_to_list(list2,&num3);
  Status status2 = add_unique(list2, &num4, &match_int);
  Status is_passed2 = !status2 && (list2->length == 1);
  print_result(is_passed2,message2);
  destroy_list(list2);
}

void test_remove_from_start(){
  printf("\nremove_from_start\n");
  char message[] = "should remove and give the first element from given list";
  List_ptr list = create_list();
  int num = 2;
  int num2 = 3;
  add_to_list(list,&num);
  add_to_list(list,&num2);
  Element value = remove_from_start(list);
  Status status = (*(int *)value == 2) && (list->length == 1) && *(int *)list->first->element == 3;
  print_result(status,message);
  destroy_list(list);

  char message2[] = "should remove the element from list if list has only one element";
  List_ptr list2 = create_list();
  int num3 = 2;
  add_to_list(list2,&num3);
  Element value2 = remove_from_start(list2);
  Status status2 = (*(int *)value2 == 2) && (list2->length == 0) && list2->first == NULL;
  print_result(status2,message2);
  destroy_list(list2);

  char message3[] = "should not remove if list is empty";
  List_ptr list3 = create_list();
  Element value3 = remove_from_start(list3);
  Status status3 = value3 == NULL && (list3->length == 0) && list3->first == NULL;
  print_result(status3,message3);
  destroy_list(list3);
}

void test_remove_from_end(){
  printf("\nremove_from_end\n");
  char message[] = "should remove and give the last element from given list";
  List_ptr list = create_list();
  int num = 2;
  int num2 = 3;
  int num3 = 4;
  int num4 = 5;
  add_to_list(list,&num);
  add_to_list(list,&num2);
  add_to_list(list,&num3);
  add_to_list(list,&num4);
  Element value = remove_from_end(list);
  Status status = (*(int *)value == 5) && (list->length == 3) && *(int *)(list->last->element) == 4;
  print_result(status,message);
  destroy_list(list);

  char message2[] = "should not remove if list is empty";
  List_ptr list2 = create_list();
  Element value2 = remove_from_end(list2);
  Status status2 = value2 == NULL && (list2->length == 0) && list2->last == NULL && list2->first == NULL;
  print_result(status2,message2);
  destroy_list(list2);

  char message3[] = "should not remove if list is empty";
  List_ptr list3 = create_list();
  int num5 = 99;
  add_to_list(list3,&num5);
  Element value3 = remove_from_end(list3);
  Status status3 = (*(int *)value3 == 99) && (list3->length == 0) && list3->last == NULL && list3->first == NULL;
  print_result(status3,message3);
  destroy_list(list3);
}

void test_clear_list(){
  printf("\nclear_list\n");
  char message[] = "should empty the given list";
  List_ptr list = create_list();
  int num = 2;
  int num2 = 3;
  add_to_list(list,&num);
  add_to_list(list,&num2);
  Status status = clear_list(list);
  Status is_passed = list != NULL && list->first == NULL &&  list->last == NULL && list->length == 0;
  print_result(is_passed,message);
  destroy_list(list);
}

int main(){
  test_create_list();
  test_add_to_list();
  test_add_to_start();
  test_insert_at();
  test_add_unique();
  test_remove_from_start();
  test_remove_from_end();
  test_clear_list();
  return 0;
}