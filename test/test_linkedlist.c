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

void test_remove_at(){
  printf("\nremove_at\n");
  char message[] = "should remove from the begining of list";
  List_ptr list = create_list();
  int num = 2;
  add_to_list(list,&num);
  Element value = remove_at(list,0);
  Status is_passed = *(int *)value == 2 && list->first == NULL && (list->length == 0);
  print_result(is_passed,message);
  destroy_list(list);

  char message2[] = "should remove from given position in list";
  List_ptr list2 = create_list();
  char char1 = 'R';
  char char2 = 'A';
  char char3 = 'G';
  char char4 = 'I';
  add_to_list(list2, &char1);
  add_to_list(list2, &char2);
  add_to_list(list2, &char3);
  add_to_list(list2, &char4);
  Element value2 = remove_at(list2, 2);
  Prev_Current_Pair *pair = get_prev_curr_pair(list2,2);
  Status is_passed2 = *(char *)value2 == 'G' && (*(char *)(pair->current->element) == 'I') && (list2->length == 3);
  print_result(is_passed2,message2);
  destroy_list(list2);

  char message3[] = "should not remove from list if position is invalid";
  List_ptr list3 = create_list();
  int num2 = 2;
  add_to_list(list3,&num2);
  Element value3 = remove_at(list3,5);
  Status is_passed3 =  value3 == NULL && (list3->length == 1);
  print_result(is_passed3,message3);
  destroy_list(list3);

  char message4[] = "should remove from the end of list ";
  List_ptr list4 = create_list();
  int num5 = 2;
  int num6 = 99;
  add_to_list(list4,&num5);
  add_to_list(list4,&num6);
  Element value4 = remove_at(list4,1);
  Status is_passed4 = *(int *)value4 == 99 && (list4->length == 1) && (*(int *)(list->last->element) == 2);
  print_result(is_passed4,message4);
  destroy_list(list4);
}

void test_remove_first_occurrence(){
  printf("\nremove_first_occurrence\n");
  char message[] = "should remove first occurrence of given value ";
  List_ptr list = create_list();
  int num = 2;
  int num2 = 3;
  int num3 = 3;
  add_to_list(list,&num);
  add_to_list(list,&num2);
  add_to_list(list,&num3);
  Element value = remove_first_occurrence(list, &num2 ,&match_int);
  Status is_passed = *(int *)value == 3 && (list->length == 2);
  print_result(is_passed, message);
  destroy_list(list);

  char message2[] = "should not remove if value does not exist in list ";
  List_ptr list2 = create_list();
  int num4 = 2;
  int num5 = 99;
  add_to_list(list2,&num4);
  Element value2 = remove_first_occurrence(list2, &num5, &match_int);
  Status is_passed2 = value2 == NULL && (list2->length == 1);
  print_result(is_passed2, message2);
  destroy_list(list2);

  char message3[] = "should not remove if list is empty";
  List_ptr list3 = create_list();
  int num6 = 99;
  Element value3 = remove_first_occurrence(list3, &num6 , &match_int);
  Status is_passed3 = value3 == NULL && (list3->length == 0);
  print_result(is_passed3, message3);
  destroy_list(list3);

  char message4[] = "should remove first occurrence in list having given value only";
  List_ptr list4 = create_list();
  int num7 = 2;
  int num8 = 2;
  add_to_list(list4,&num7);
  Element value4 = remove_first_occurrence(list4, &num8, &match_int);
  Status is_passed4 = *(int *)value4 == 2 && (list4->length == 0);
  print_result(is_passed4, message4);
  destroy_list(list4);
}

void test_remove_all_occurrences(){
  printf("\nremove_all_occurrences\n");
  char message[] = "should remove all occurrences of given value ";
  List_ptr list = create_list();
  int num = 2;
  int num2 = 3;
  int num3 = 3;
  add_to_list(list,&num);
  add_to_list(list,&num2);
  add_to_list(list,&num3);
  List_ptr result_list = remove_all_occurrences(list, &num2 ,&match_int);
  Status is_passed = list->length == 1 && search(result_list, &num2, &match_int) == -1;
  print_result(is_passed, message);
  destroy_list(list);

  char message2[] = "should not remove if value does not exist in list ";
  List_ptr list2 = create_list();
  int num4 = 2;
  int num5 = 99;
  add_to_list(list2,&num4);
  List_ptr result_list2 = remove_all_occurrences(list2, &num5, &match_int);
  Status is_passed2 = (list2->length == 1) && search(result_list2, &num5, &match_int) == -1;
  print_result(is_passed2, message2);
  destroy_list(list2);

  char message3[] = "should not remove if list is empty";
  List_ptr list3 = create_list();
  int num6 = 99;
  List_ptr result_list3 = remove_all_occurrences(list3, &num6 , &match_int);
  Status is_passed3 = list3->length == 0 && search(result_list3, &num6, &match_int) == -1;
  print_result(is_passed3, message3);
  destroy_list(list3);

  char message4[] = "should remove the value from list having given value only";
  List_ptr list4 = create_list();
  int num7 = 2;
  int num8 = 2;
  List_ptr result_list4 = remove_all_occurrences(list4, &num8, &match_int);
  Status is_passed4 = list4->length == 0 && search(result_list4, &num8, &match_int) == -1;
  print_result(is_passed4, message4);
  destroy_list(list4);
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

Element increment(Element value){
  Element num = malloc(sizeof(Element));
  int number = (*(int *)value) + 1;
  memcpy(num, &number, sizeof(int));
  return num;
}

Status are_int_equal(Element data_a, Element data_b){
  int a = *(int *)data_a;
  int b = *(int *)data_b;
  return a == b;
}

void test_map(){
  printf("\nmap\n");
  List_ptr list = create_list();
  int num = 2;
  int num2 = 3;
  int num3 = 4;
  add_to_list(list,&num);
  add_to_list(list,&num2);
  add_to_list(list,&num3);

  List_ptr expected = create_list();
  int num4 = 3;
  int num5 = 4;
  int num6 = 5;
  add_to_list(expected,&num4); 
  add_to_list(expected,&num5);
  add_to_list(expected,&num6);

  List_ptr actual = map(list,&increment);
  char message[] = "should increment each element in the given list by one";
  print_result(compare(actual,expected,&are_int_equal),message);
  destroy_list(list);
  destroy_list(actual);
  destroy_list(expected);

  List_ptr list2 = create_list();
  List_ptr expected2 = create_list();
  List_ptr actual2 = map(list2, &increment);
  char message2[] = "should map empty array";
  print_result(compare(actual2,expected2,&are_int_equal),message2);
  destroy_list(list2);
  destroy_list(actual2);
  destroy_list(expected2);
}

int main(){
  test_create_list();
  test_add_to_list();
  test_add_to_start();
  test_insert_at();
  test_remove_at();
  test_add_unique();
  test_remove_from_start();
  test_remove_from_end();
  test_remove_first_occurrence();
  test_remove_all_occurrences();
  test_clear_list();
  test_map();
  return 0;
}