#include "vector.h"
#include <iostream>

Vector::Vector() {
    capacity = 2;
    size = 0;
    data = new int[capacity]; 
}

Vector::~Vector() {
    delete[] data;
}

void Vector::Add(int value) {
    //check to double capacity of list, otherwise append input
    if (size == capacity) {
        int* temp = new int[capacity * 2];
        for (int i = 0; i < size; ++i) {
            temp[i] = data[i];
        }
        delete[] data;
        data = temp;
        capacity *= 2;
    }
    data[size++] = value;
}

void Vector::Delete(int value) {
    int index = 0;
    bool value_exists = false;
    //find values index
    for (int i = 0; i < size; ++i) {
        if (data[i] == value) {
            index = i;
            value_exists = true;
            break;
        }
    }
    //if index found, overwrite elements to left side. 
    if (value_exists) {
        for (int i = index; i < size - 1; ++i) {
            data[i] = data[i + 1];
        }
        size--;
        //deallocate memory if capacity is twice the size of vector
        if (size <= capacity / 2) {
            int* temp = new int[capacity / 2];
            for (int i = 0; i < size; ++i) {
                temp[i] = data[i];
            }
            delete[] data;
            data = temp;
            capacity /= 2;
        }
    }
}

void Vector::Print() {
    //iterate and print each element
    if (size == 0) {
        std::cout << "\n";
    } else {
        for (int i = 0; i < size; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }
}

int Vector::Size() {
    return size;
}

int Vector::Capacity() {
    return capacity;
}