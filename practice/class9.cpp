//extra 332

//implement linear probing

//if val cannot be added (table is full), then print "unable to add"

//use an array of nodes

#include <iostream>

using namespace std;

struct ht {
    int index;
    int val = -1;
}; 

void init_indexes(ht table[], int size) {
    for (int i = 0; i < size; i++) {
        table[i].index = i;
    }
    return;
}

bool is_tablefull(ht table[],int size) {   //checks if the hash table is full
    for (int i = 0; i < size; i++) {
        if (table[i].val == -1) {
            return false;
        }
    }
    return true;
}

bool is_occ(ht table[], int index) {                //is the index/node full? if it is full, we have to use linear probing
    if (table[index].val == -1) {
        return false;
    } else {
        return true;
    }
}

int hash_func(int val, int size) {
    int index = val % size;                 //val % 10 shows what index to place in
    return index;
}

void insert_via_linear_probing(ht table[], int val, int size) {
    // int key = hash_func(v, size);
    // bool is_full = is_full(table, key);
    
    //1. check if whole table is full, if yes, then cout error: table full
    if (is_tablefull(table, size) == true) {
        cout<<"table is full"<< endl;
        return;
    }
    //2. int index = hash_func(val, size), if not occupied, insert with table[index].val = val, else, move to step 3. 
    int index = hash_func(val, size);
    
    //3. start linear probing
    if (is_occ(table,index)==false) {
        table[index].val = val;         //places value into empty index
        table[index].index = index;
    } else {
        while(is_occ(table,index)==true) {                 
            index = (index + 1) % size;
        }
        table[index].val = val;         //places value into empty index
        table[index].index = index;
    }
}

void printhash(ht table[], int size) {
    for (int i = 0; i < size; i++) {
        cout << table[i].index << " | " << table[i].val << endl;
    }
}

int main() {
    //array of structs
    int size = 20;
    ht hashtable[size];
    init_indexes(hashtable, size);
    int val1 = 11;
    int val2 = 1000001;
    int val3 = 64;
    int val4 = 80;
    int val5 = 5;
    int val6 = 632;
    int val7 = 111;
    int val8 = 792;
    int val9 = 1011;
    int val10 = 9090909;
    insert_via_linear_probing(hashtable, val1, size);
    insert_via_linear_probing(hashtable, val2, size);
    insert_via_linear_probing(hashtable, val3, size);
    insert_via_linear_probing(hashtable, val4, size);
    insert_via_linear_probing(hashtable, val5, size);
    insert_via_linear_probing(hashtable, val6, size);
    insert_via_linear_probing(hashtable, val7, size);
    insert_via_linear_probing(hashtable, val8, size);
    insert_via_linear_probing(hashtable, val9, size);
    insert_via_linear_probing(hashtable, val10, size);
    insert_via_linear_probing(hashtable, val10, size);


    printhash(hashtable, size);
    return 0;
}

