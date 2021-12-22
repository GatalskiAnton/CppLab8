#include <iostream>
#include "Stack.h"
#include "Calculator.h"
int main() {
    std::string expression;
    std::cin >> expression;
    std::cout << CalculateExpression(expression);
    return 0;
}
