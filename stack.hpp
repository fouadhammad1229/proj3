#ifndef STACK_HPP
#define STACK_HPP

#include "stack.h"

namespace cop4530 {
    
    // Constructor
    template <typename T>
    Stack<T>::Stack() {}

    // Destructor
    template <typename T>
    Stack<T>::~Stack() {
        clear();
    }
    
    // Copy Constructor
    template <typename T>
    Stack<T>::Stack(const Stack<T>& other) : data(other.data) {}

    // Move Constructor
    template <typename T>
    Stack<T>::Stack(Stack<T>&& other) : data(std::move(other.data)) {}


    // Copy Assignment Operator
    template <typename T>
    Stack<T>& Stack<T>::operator=(const Stack<T>& other) {
        if (this != &other) {
            data = other.data;
        }
        return *this;
    }

    // Move Assignment Operator
    template <typename T>
    Stack<T>& Stack<T>::operator=(Stack<T>&& other) {
        if (this != &other) {
            data = std::move(other.data);
        }
        return *this;
    }

    // Empty Checker
    template <typename T>
    bool Stack<T>::empty() const {
        return data.empty();
    }

    // Clear the stack
    template <typename T>
    void Stack<T>::clear() {
        data.clear();
    }

    // Push stack (copy)
    template <typename T>
    void Stack<T>::push(const T& x) {
        data.push_back(x);
    }

    // Push Stack (move)
    template <typename T>
    void Stack<T>::push(T&& x) {
        data.push_back(std::move(x));
    }

    // Pop top element
    template <typename T>
    void Stack<T>::pop() {
        if (!empty()) {
            data.pop_back();
        }
    }

    // Access top element (mutable)
    template <typename T>
    T& Stack<T>::top() {
        return data.back();
    }

    // Access top element (constant)
    template <typename T>
    const T& Stack<T>::top() const {
        return data.back();
    }

    // Gets stack size
    template <typename T>
    int Stack<T>::size() const {
        return data.size();
    }

    template <typename T>
    void Stack<T>::print(std::ostream& os, char ofc) const {
        for (auto it = data.rbegin(); it != data.rend(); ++it) {
            os << *it << ofc;
        }
    }

    // Prints stack
    template <typename T>
    std::ostream& operator<<(std::ostream& os, const Stack<T>& a) {
        a.print(os);
        return os;
    }

/*
 * Comparison Operators
 */

    template <typename T>
    bool operator==(const Stack<T>& a, const Stack<T>& b) {
        return a.data == b.data;
    }

    template <typename T>
    bool operator!=(const Stack<T>& a, const Stack<T>& b) {
        return !(a == b);
    }

    template <typename T>
    bool operator<=(const Stack<T>& a, const Stack<T>& b) {
        return a.data <= b.data;
    }

}

#endif

