#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

void initStack(Stack* stack) {
    stack->top = NULL;
}

Node* createNode(float data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Ошибка: Не удалось выделить память для узла\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void push(Stack* stack, float data) {
    Node* newNode = createNode(data);
    newNode->next = stack->top;
    stack->top = newNode;
}

float pop(Stack* stack) {
    if (stack->top == NULL) {
        printf("Ошибка: Стек пуст\n");
        exit(EXIT_FAILURE);
    }
    Node* temp = stack->top;
    float data = temp->data;
    stack->top = stack->top->next;
    free(temp);
    return data;
}

float top(Stack* stack) {
    if (stack->top == NULL) {
        printf("Ошибка: Стек пуст\n");
        exit(EXIT_FAILURE);
    }
    return stack->top->data;
}

// Новая функция очистки стека
void clearStack(Stack* stack) {
    while (stack->top != NULL) {
        pop(stack);
    }
}
