//
// Created by ag629 on 20.12.2021.
//
#include <iostream>
#include <cmath>
#include <string>
#include "Calculator.h"
#include "Stack.h"


int Calculate(int FirstValue, int SecondValue, char operation) {
    if(operation == '+')
        return FirstValue + SecondValue;
    if(operation == '-')
        return FirstValue - SecondValue;
    if(operation == '*')
        return FirstValue * SecondValue;
    if(operation == '/' && SecondValue != 0)
        return FirstValue / SecondValue;
    if(operation == '^')
        return pow(FirstValue, SecondValue);
    throw std::runtime_error("problem with your expression");

}

bool IsOperation(char element) {
    if (element == '+' || element == '-' || element == '*' || element == '/' || element == '^')
        return true;
    return false;
}

int Priority(char element) {
    if (element == '^')
        return 3;
    if (element == '*' || element == '/')
        return 2;
    if (element == '+' || element == '-')
        return 1;
    return -1;
}

double CalculateExpression(std::string expression) {
    std::string convert_string_to_double = "";
    StackOnArray<char> operations;
    StackOnArray<double> result;
    for (int i = 0; i < expression.size(); ++i) {
        if (!IsOperation(expression[i])){
            result.push(expression[i] - '0');
        }else{
            if (Priority(expression[i]) <= Priority(operations.top())){
                std::cout << operations.top() << "\n";
                result.push(Calculate(result[result.GetSize() - 2], result[result.GetSize() - 1], operations.top()));
            }else{
                operations.push(expression[i]);
            }
        }
    }
//    std::cout << operations.pop() << "\n";
//    std::cout << operations.pop() << "\n";
//
//    std::cout << "-------------------------------------------------------\n";
//    std::cout << result.pop() << "\n";
//    std::cout << result.pop() << "\n";
//    std::cout << result.pop() << "\n";
    while(!operations.IsEmpty()){
        double SecondValue = result.pop();
        double FirstValue = result.pop();
        result.push(Calculate(FirstValue, SecondValue, operations.top()));
        operations.pop();
    }
    return result.top();
}
