#ifndef VECTOR_H
#define VECTOR_H

class Vector {
public:
    Vector();
    ~Vector();

    void Add(int value);
    void Delete(int value);
    void Print();
    int Size();
    int Capacity();

private:
    int* data;
    int size;
    int capacity;
};

#endif // VECTOR_H