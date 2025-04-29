#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <algorithm>
#include "ArgumentManager.h"

using namespace std;

struct Node {
    int key;
    Node *left;
    Node *right;
    int height;
    Node(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
};

class AVL {
private:
    Node *root;

    int height(Node *n) { return n ? n->height : 0; }

    int getBalance(Node *n) { return n ? height(n->left) - height(n->right) : 0; }

    Node *rightRotate(Node *y) {
        Node *x = y->left;
        Node *T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = 1 + max(height(y->left), height(y->right));
        x->height = 1 + max(height(x->left), height(x->right));
        return x;
    }

    Node *leftRotate(Node *x) {
        Node *y = x->right;
        Node *T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = 1 + max(height(x->left), height(x->right));
        y->height = 1 + max(height(y->left), height(y->right));
        return y;
    }

    Node *insert(Node *node, int key) {
        if (!node)
            return new Node(key);
        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);
        else // duplicate key
            return node;

        node->height = 1 + max(height(node->left), height(node->right));
        int balance = getBalance(node);

        // Left Left
        if (balance > 1 && key < node->left->key)
            return rightRotate(node);
        // Right Right
        if (balance < -1 && key > node->right->key)
            return leftRotate(node);
        // Left Right
        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        // Right Left
        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }

    Node *minValueNode(Node *node) {
        Node *current = node;
        while (current->left)
            current = current->left;
        return current;
    }

    Node *remove(Node *node, int key) {
        if (!node)
            return node;
        if (key < node->key)
            node->left = remove(node->left, key);
        else if (key > node->key)
            node->right = remove(node->right, key);
        else {
            if (!node->left || !node->right) {
                Node *temp = node->left ? node->left : node->right;
                if (!temp) {
                    temp = node;
                    node = nullptr;
                } else {
                    *node = *temp;
                }
                delete temp;
            } else {
                Node *temp = minValueNode(node->right);
                node->key = temp->key;
                node->right = remove(node->right, temp->key);
            }
        }
        if (!node)
            return node;

        node->height = 1 + max(height(node->left), height(node->right));
        int balance = getBalance(node);

        // Left Left
        if (balance > 1 && getBalance(node->left) >= 0)
            return rightRotate(node);
        // Left Right
        if (balance > 1 && getBalance(node->left) < 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        // Right Right
        if (balance < -1 && getBalance(node->right) <= 0)
            return leftRotate(node);
        // Right Left
        if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }

    void levelPrint(Node *root, ostream &out) {
        if (!root)
            return;
        queue<Node *> q;
        q.push(root);
        while (!q.empty()) {
            int count = q.size();
            for (int i = 0; i < count; ++i) {
                Node *node = q.front();
                q.pop();
                out << node->key;
                if (i != count - 1)
                    out << " ";
                if (node->left)
                    q.push(node->left);
                if (node->right)
                    q.push(node->right);
            }
            if (!q.empty())
                out << "\n";
        }
    }

    void destroy(Node *node) {
        if (!node)
            return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    AVL() : root(nullptr) {}

    ~AVL() { destroy(root); }

    void insert(int key) { root = insert(root, key); }

    void remove(int key) { root = remove(root, key); }

    void print(ostream &out) { levelPrint(root, out); }
};

int main(int argc, char *argv[]) {
    ArgumentManager am(argc, argv);
    string inputFile = am.get("input");
    string outputFile = am.get("output");
    ifstream infile(inputFile);
    ofstream outfile(outputFile);

    AVL tree;
    string line;
    while (getline(infile, line)) {
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());
        if (line.empty())
            continue;
        // remove spaces
        line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());
        if (line.empty())
            continue;

        if (line.find("Insert") != string::npos) {
            size_t l = line.find('(');
            size_t r = line.find(')');
            if (l != string::npos && r != string::npos && r > l + 1) {
                int val = stoi(line.substr(l + 1, r - l - 1));
                tree.insert(val);
            }
        } else if (line.find("Remove") != string::npos) {
            size_t l = line.find('(');
            size_t r = line.find(')');
            if (l != string::npos && r != string::npos && r > l + 1) {
                int val = stoi(line.substr(l + 1, r - l - 1));
                tree.remove(val);
            }
        }
    }

    tree.print(outfile);
    return 0;
}