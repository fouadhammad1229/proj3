#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <vector>

namespace cop4530 {

template <typename T>
class Stack {
public:
    Stack();                        // constructor
    ~Stack();                       // destructor
    Stack(const Stack<T>&);         // copy constructor
    Stack(Stack<T> &&);             // move constructor
    Stack<T>& operator=(const Stack<T>&);  // copy assignment
    Stack<T>& operator=(Stack<T>&&);       // move assignment

    bool empty() const;             // check if the stack is empty
    void clear();                   // clear the stack
    void push(const T& x);          // copy push
    void push(T&& x);               // move push
    void pop();                     // pop the top element
    T& top();                       // access top element (mutable)
    const T& top() const;           // access top element (const)
    int size() const;               // get stack size

    void print(std::ostream& os, char ofc = ' ') const; // print stack

    // comparison operators
    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const Stack<U>& a);
    template <typename U>
    friend bool operator==(const Stack<U>&, const Stack<U>&);
    template <typename U>
    friend bool operator!=(const Stack<U>&, const Stack<U>&);
    template <typename U>
    friend bool operator<=(const Stack<U>& a, const Stack<U>& b);

private:
    std::vector<T> data;  // internal storage using STL vector
};

} // namespace cop4530

#include "stack.hpp"

#endif

