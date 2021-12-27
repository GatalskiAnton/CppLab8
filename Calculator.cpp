#include "Calculator.h"
#include <cmath>
#include <string>


int Priority(char PartOfExpression) {
    if (PartOfExpression == '^') return 3;
    if (PartOfExpression == '*' || PartOfExpression == '/') return 2;
    if (PartOfExpression == '+' || PartOfExpression == '-') return 1;
    return -1;
}

double Calculate(double FirstValue, double SecondValue, char Operation) {
    if (Operation == '+') return FirstValue + SecondValue;
    if (Operation == '-') return FirstValue - SecondValue;
    if (Operation == '*') return FirstValue * SecondValue;
    if (Operation == '/') {
        if (SecondValue == 0)
            throw std::runtime_error("Cant' divide on 0");
        return FirstValue / SecondValue;
    }
    if (Operation == '^')
        return pow(FirstValue, SecondValue);
    return 0;
}

bool IsOperation(char PartOfExpression) {
    return PartOfExpression == '*' || PartOfExpression == '/' || PartOfExpression == '+' || PartOfExpression == '-'
           || PartOfExpression == '^';
}


string DeleteSpaces(string Expression) {
    string DeletedSpaces = {};
    for (int i = 0; i < Expression.size(); ++i) {
        if (Expression[i] != ' ')
            DeletedSpaces += Expression[i];
    }
    return DeletedSpaces;
}

int CountOpenedBrackets(string Expression) {
    int CountOpenedBrackets = 0;
    for (int i = 0; i < Expression.size(); ++i) {
        if (Expression[i] == ')')
            ++CountOpenedBrackets;
    }
    return CountOpenedBrackets;
}

int CountClosedBrackets(string Expression) {
    int CountClosedBrackets = 0;
    for (int i = 0; i < Expression.size(); ++i) {
        if (Expression[i] == '(')
            ++CountClosedBrackets;
    }
    return CountClosedBrackets;
}

int CountOperations(string Expression) {
    int CountOperations = 0;
    for (int i = 0; i < Expression.size(); ++i) {
        if (IsOperation(Expression[i]) && Expression[i] != '(' && Expression[i] != ')' && i != Expression.size() - 1 &&
            i != 0 && Expression[i - 1] != '(')
            ++CountOperations;
    }
    return CountOperations;
}

void Check(string &Expression) {
    if (CountOpenedBrackets(Expression) != CountClosedBrackets(Expression))
        throw runtime_error("Incorrect expression");
}

double CalculateExpression(string Expression) {
    string ForExpression{};
    ForExpression = DeleteSpaces(Expression);
    Expression = ForExpression;
    Check(Expression);
    if (CountOperations(Expression) == 0 && CountOpenedBrackets(Expression) == 0)
        return stod(Expression);
    else if (CountOperations(Expression) == 0) {
        ForExpression = "";
        for (int i = 0; i < Expression.size(); ++i) {
            if (Expression[i] != '(' && Expression[i] != ')')
                ForExpression += Expression[i];
        }
        return stod(ForExpression);
    }
    StackOnArray<char> operations;
    StackOnArray<double> result;
    for (int i = 0; i < Expression.size(); ++i) {
        if (IsOperation(Expression[i])) {
            if (i == 0 && Expression[i++] == '-') {
                if (Expression[i] == '(') {
                    string ForExpressionInBrackets = "0";
                    ForExpressionInBrackets += ForExpression;
                    return CalculateExpression(ForExpressionInBrackets);
                } else {
                    while (!IsOperation(Expression[i]))
                        ForExpression += Expression[i++];
                    result.push(stod(ForExpression));
                }
            }
            while (!(operations.IsEmpty()) && Priority(Expression[i]) <= Priority(operations.top())) {
                double SecondValue = result.pop();
                double FirstValue = result.pop();
                result.push(Calculate(FirstValue, SecondValue, operations.pop()));
            }
            operations.push(Expression[i]);
            if (Expression[i + 1] == '-') {
                if (Expression[i + 2] == '(') {
                    ++i;
                    ForExpression = "";
                    while (Expression[i] != ')')
                        ForExpression += Expression[++i];
                    result.push(-CalculateExpression(ForExpression));
                } else {
                    ForExpression = " ";
                    i++;
                    while ((!IsOperation(Expression[i]) || Expression[i] == '-') && i != Expression.size())
                        ForExpression += Expression[i++];
                    --i;
                    result.push(stod(ForExpression));
                }
            }
        } else {
            if (Expression[i] == '(') {
                if (Expression[i + 1] == '-') {
                    ++i;
                    ForExpression = "";
                    while (Expression[i] != ')')
                        ForExpression += Expression[i++];
                    result.push(CalculateExpression(ForExpression));
                } else
                    operations.push(Expression[i]);
            } else if (Expression[i] == ')') {
                while ((operations.top()) != '(') {
                    double SecondValue = result.pop();
                    double FirstValue = result.pop();
                    result.push(Calculate(FirstValue, SecondValue, operations.pop()));
                }
                operations.pop();
            } else {
                ForExpression = " ";
                while (!IsOperation(Expression[i]) && Expression[i] != ')' && Expression[i] != '('
                       && i != Expression.size()) {
                    ForExpression += Expression[i++];
                }
                --i;
                result.push(stod(ForExpression));
            }
        }
    }
    while (!(operations.IsEmpty())) {
        double SecondValue = result.pop();
        double FirstValue = result.pop();
        result.push(Calculate(FirstValue, SecondValue, operations.pop()));
    }
    return result.top();
}