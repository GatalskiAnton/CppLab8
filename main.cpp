#include <iostream>
#include "Stack.h"
#include "Calculator.h"
int main() {
    std::string expression = "1+2*3";
    std::cout << CalculateExpression(expression);
    return 0;
}
