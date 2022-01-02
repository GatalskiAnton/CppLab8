#include "gtest/gtest.h"
#include "Calculator.h"


TEST(Stack, MainFunction) {
    StackOnArray<int> Stack;
    Stack << 1;
    Stack << 2;
    Stack << 3;
    Stack << 4;
    Stack << 5;
    ASSERT_EQ(Stack.GetSize(), 5);
    ASSERT_EQ(Stack.top(), 5);
    ASSERT_EQ(Stack.pop(), 5);
    ASSERT_EQ(Stack.pop(), 4);
    Stack.push(5);
    ASSERT_EQ(Stack.top(), 5);
    ASSERT_EQ(Stack.IsEmpty(), false);
}

TEST(Calculator, Operation) {
    ASSERT_EQ(CalculateExpression("2+2"), 4);
    ASSERT_EQ(CalculateExpression("2*2"), 4);
    ASSERT_EQ(CalculateExpression("2^3"), 8);
    ASSERT_EQ(CalculateExpression("4/2"), 2);
    ASSERT_EQ(CalculateExpression("4-2"), 2);
}

TEST(Calculator, Expression) {
    ASSERT_EQ(CalculateExpression("2+2*2"), 6);
    ASSERT_EQ(CalculateExpression("-(1+1)"), -2);
    ASSERT_EQ(CalculateExpression("1--1"), 2);
    ASSERT_EQ(CalculateExpression("12+3^2"), 21);
    ASSERT_EQ(CalculateExpression("12/3-7"), -3);
    ASSERT_EQ(CalculateExpression("4--4+12^(1+1)"), 152);
    ASSERT_EQ(CalculateExpression("(1)+(1)"), 2);
    ASSERT_EQ(CalculateExpression("12*0"), 0);
    ASSERT_EQ(CalculateExpression("12/10+15/3"), 6.2);
    ASSERT_EQ(CalculateExpression("7/(1+1)+7"), 10.5);
    ASSERT_EQ(CalculateExpression("1--1--1-1-1-1-1-1--1"), -1);
    ASSERT_EQ(CalculateExpression("1-"), 1);
    ASSERT_EQ(CalculateExpression("-0"), 0);
    ASSERT_EQ(CalculateExpression("4--4+(1+1)*12"), 32);
    ASSERT_EQ(CalculateExpression("12.4*2.5"), 31);
    ASSERT_EQ(CalculateExpression("13.333333333333333*3"), 40);
    ASSERT_EQ(CalculateExpression("(-15+7)*3"), -24);
    ASSERT_EQ(CalculateExpression("7+-5"), 2);
    ASSERT_EQ(CalculateExpression("12/-3"), -4);
    ASSERT_EQ(CalculateExpression("-12/-3"), 4);
    ASSERT_EQ(CalculateExpression("-1*5"), -5);
    ASSERT_EQ(CalculateExpression("-1*-5"), 5);
    ASSERT_EQ(CalculateExpression("-5+-5"), -10);
    ASSERT_EQ(CalculateExpression("-(-5+-5)"), 10);
}

