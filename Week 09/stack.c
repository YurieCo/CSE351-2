/*
 * stack.c
 * University of Washington
 * CSE 351 Spring 2013
 * Jeremy Lee
 *
 * An implementation of a stack in c, using malloc and free
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * List node struct
 * We implement our stack using a linked list
 */
struct node {
  int data;
  struct node* next;
};

/*
 * Function headers
 * You need these or else the compiler will complain
 */
void push(struct node** list, int n);
int pop(struct node** list);
void printStack(struct node* list);

/*
 * Demonstrate the correctness of our implementation
 */
int main() {
  struct node* head = NULL;
  push(&head, 3);
  push(&head, 5);
  push(&head, 7);
  push(&head, 9);
  push(&head, 11);
  pop(&head);
  pop(&head);
  pop(&head);
  pop(&head);
  pop(&head);
}

/*
 * Push an int onto the stack
 * list: the address of the list head pointer
 * n: the int to push. Must be >= 0
 */
void push(struct node** list, int n) {
  struct node* newNode = (struct node*)malloc(sizeof(struct node));
  printf("PUSH: %d\n", n);
  if(newNode == NULL) {
    printf("Malloc failed\n");
    return;
  }
  newNode->data = n;
  if(*list == NULL) {
    *list = newNode;
    newNode->next = NULL;
  } else {
    newNode->next = *list;
    *list = newNode;
  }
  printStack(*list);
}

/*
 * Pop an int off the stack
 * list: the address of the list head pointer
 * returns: the int on top of the stack
 */
int pop(struct node** list) {
  struct node* temp;
  int n;
  if(*list == NULL) {
    printf("You can't do that\n");
    return -1;
  }
  temp = *list;
  *list = (*list)->next;
  n = temp->data;
  free(temp);
  printf("POP: %d\n", n);
  printStack(*list);
  return n;
}

/*
 * Print the contents of the stack
 * list: the list head pointer
 */
void printStack(struct node* list) {
  struct node* current;
  current = list;
  while(current != NULL) {
    printf("%d ", current->data);
    current = current->next;
  }
  printf("\n");
}
