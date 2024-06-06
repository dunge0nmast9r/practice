#ifndef STACK_H
#define STACK_H

typedef struct Node {
    float data;
    struct Node* next;
} Node;

typedef struct Stack {
    Node* top;
} Stack;

void initStack(Stack* stack);
void push(Stack* stack, float data);
float pop(Stack* stack);
float top(Stack* stack);
void clearStack(Stack* stack); // Новый прототип функции очистки

#endif

