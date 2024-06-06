#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include "stack.h"
#include "calculator.h"

#define MAX_EXPRESSION_LENGTH 100
#define STEP 0.001 // Шаг интегрирования

int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == 'i' || c == 'n' || c == 'p' || c == 'I' || c == 's' || c == 'c' || c == 't' || c == 'k' || c == 'a' || c == 'A';
}

int isOperand(char c) {
    return isdigit(c) || c == '.';
}

void processOperator(Stack* stack, char op) {
    float operand1, operand2, result;
    switch(op) {
        case '+':
            operand2 = pop(stack);
            operand1 = pop(stack);
            result = operand1 + operand2;
            break;
        case '-':
            operand2 = pop(stack);
            operand1 = pop(stack);
            result = operand1 - operand2;
            break;
        case '*':
            operand2 = pop(stack);
            operand1 = pop(stack);
            result = operand1 * operand2;
            break;
        case '/':
            operand2 = pop(stack);
            operand1 = pop(stack);
            if (operand2 == 0) {
                printf("Ошибка: Деление на ноль\n");
                exit(EXIT_FAILURE);
            }
            result = operand1 / operand2;
            break;
        case '^':
            operand2 = pop(stack);
            operand1 = pop(stack);
            result = pow(operand1, operand2);
            break;
        case 'i':
            operand1 = pop(stack);
            result = -operand1;
            break;
        case 'n':
            operand1 = pop(stack);
            if (operand1 == 0) {
                printf("Ошибка: Деление на ноль\n");
                exit(EXIT_FAILURE);
            }
            result = 1 / operand1;
            break;
        case 'p':
            operand1 = pop(stack);
            result = sqrt(operand1);
            break;
        case 's':
            operand1 = pop(stack);
            result = sin(operand1);
            break;
        case 'c':
            operand1 = pop(stack);
            result = cos(operand1);
            break;
        case 't':
            operand1 = pop(stack);
            result = tan(operand1);
            break;
        case 'I': {
            operand1 = pop(stack);
            if (operand1 == 0) {
                printf("Ошибка: Интеграл от нуля\n");
                exit(EXIT_FAILURE);
            }
            float integral = 0;
            for (float x = 0; x <= operand1; x += STEP) {
                integral += x * STEP;
            }
            result = integral;
            break;
        }
        case 'A': {
            int count = (int)pop(stack);
            if (count <= 0) {
                printf("Ошибка: Недопустимое количество элементов для среднего арифметического\n");
                exit(EXIT_FAILURE);
            }
            float sum = 0;
            for (int i = 0; i < count; i++) {
                sum += pop(stack);
            }
            result = sum / count;
            break;
        }
        default:
            printf("Ошибка: Неизвестный оператор '%c'\n", op);
            exit(EXIT_FAILURE);
    }
    push(stack, result);
}

float evaluateRPN(char* expr, float x) {
    Stack stack;
    initStack(&stack);
    char* token = strtok(expr, " ");
    while (token != NULL) {
        if (isOperand(token[0])) {
            push(&stack, atof(token));
        } else if (isOperator(token[0])) {
            processOperator(&stack, token[0]);
        } else if (token[0] == 'x') {
            push(&stack, x);
        }
        token = strtok(NULL, " ");
    }
    float result = pop(&stack);
    clearStack(&stack); // Очистка стека после вычисления
    return result;
}

int main() {
    char expr[MAX_EXPRESSION_LENGTH];
    printf("Введите выражение в обратной польской записи: ");
    fgets(expr, MAX_EXPRESSION_LENGTH, stdin);
    expr[strcspn(expr, "\n")] = '\0';
    float result = evaluateRPN(expr, 0); // Передаем значение x = 0 для начала
    printf("Результат: %.2f\n", result);
    return 0;
}
