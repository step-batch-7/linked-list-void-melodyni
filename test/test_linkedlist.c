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

void test_remove_from_start(){
  printf("\nremove_from_start\n");
  char message[] = "should remove and give the first element from given list";
  List_ptr list = create_list();
  int num = 2;
  int num2 = 3;
  add_to_list(list,&num);
  add_to_list(list,&num2);
  Element value = remove_from_start(list);
  Status status = (*(int *)value == 2) && (list->length == 1);
  print_result(status,message);
  destroy_list(list);
}

void test_remove_from_end(){
  printf("\nremove_from_end\n");
  char message[] = "should remove and give the last element from given list";
  List_ptr list = create_list();
  int num = 2;
  int num2 = 3;
  add_to_list(list,&num);
  add_to_list(list,&num2);
  Element value = remove_from_end(list);
  Status status = (*(int *)value == 3) && (list->length == 1);
  print_result(status,message);
  destroy_list(list);
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
  print_result(status,message);
  destroy_list(list);
}

int main(){
  test_create_list();
  test_add_to_list();
  test_remove_from_start();
  test_remove_from_end();
  test_clear_list();
  return 0;
}