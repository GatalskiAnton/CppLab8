#ifndef STACKONARRAY_STACKONARRAY_H
#define STACKONARRAY_STACKONARRAY_H

#include <iostream>

template<typename T>
class StackOnArray {
private:
    int capacity;
    int size;
    T *stack = new T[capacity];
public:
    StackOnArray() : size(0), capacity(0) {};

    void push(T data) {
        if (size + 1 >= capacity) {
            T *new_stack = new T[capacity + 10];
            for (int i = 0; i <= size; ++i) {
                new_stack[i] = stack[i];
            }
            capacity += 10;
            delete[] stack;
            stack = new_stack;
        }
        stack[size++] = data;

    };

    int GetSize() {
        return this->size;
    }

    T pop() {
        T result = stack[--size];
        return result;
    }

    T top() {
        return stack[size - 1];
    }

    bool IsEmpty() {
        return !size;
    }

    friend void operator<<(StackOnArray<T> &stack, T data) {
        stack.push(data);
    }

    void print(std::ostream &Out) {
        for (int i = size - 1; i >= 0; --i)
            Out << stack[i] << '\n';
    }

    friend bool operator==(StackOnArray<T> stack1, StackOnArray<T> stack2) {
        return stack1.GetSize() == stack2.GetSize();
    }

    friend bool operator<(StackOnArray<T> stack1, StackOnArray<T> stack2) {
        return stack1.GetSize() < stack2.GetSize();
    }

    T &operator[](const int index) {
        return stack[index];
    }

    StackOnArray<T> &StackOnArray<T>::operator=(const StackOnArray<T> &InputStack) {
        this->size = InputStack.GetSize();
        this->Top = InputStack.Top;
        for (size_t i = 1; i <= size; ++i) {
            stack[i] = InputStack.st[i];
        }
        return *this;
    }

};


#endif //STACKONARRAY_STACKONARRAY_H
