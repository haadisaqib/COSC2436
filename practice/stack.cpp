#include <iostream>
#include <stdexcept>

template <typename T>
class Stack {
private:
    T* data;
    int top;
    int capacity;

public:
    // Constructor
    Stack(int capacity) : capacity(capacity), top(-1) {
        data = new T[capacity];
    }

    // Destructor
    ~Stack() {
        delete[] data;
    }

    // Push operation
    void push(const T& value) {
        if (top == capacity - 1) {
            throw std::overflow_error("Stack overflow");
        }
        data[++top] = value;
    }

    // Pop operation
    T pop() {
        if (top == -1) {
            throw std::underflow_error("Stack underflow");
        }
        return data[top--];
    }

    // Peek operation
    T peek() const {
        if (top == -1) {
            throw std::underflow_error("Stack is empty");
        }
        return data[top];
    }

    // IsEmpty operation
    bool isEmpty() const {
        return top == -1;
    }

    // Size operation
    int size() const {
        return top + 1;
    }
};

int main() {
    Stack<int> stack(5);
    stack.push(1);
    stack.push(2);
    stack.push(3);

    std::cout << "Top element: " << stack.peek() << std::endl;
    std::cout << "Stack size: " << stack.size() << std::endl;

    while (!stack.isEmpty()) {
        std::cout << "Popped: " << stack.pop() << std::endl;
    }

    return 0;
}