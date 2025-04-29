#include <iostream>
using namespace std;

// Node structure for BST
class Node {
public:
    int data;
    int height;
    int balanceFactor;
    Node* left;
    Node* right;

    Node(int value) {
        data = value;
        int height = 1; // Height of the node
        int balanceFactor = 0; // Balance factor of the node
        left = nullptr;
        right = nullptr;
    }
};



// BST class
class BST {
private:
    Node* root;

    Node* leftRotate(Node* node) {
        Node* y = node->right;
        Node* T2 = y->left;

        // Perform rotation
        y->left = node;
        node->right = T2;

        // Update heights
        updateHeight(node);
        updateHeight(y);

        return y;
    }

    Node* rightRotate(Node* node) {
        Node* x = node->left;
        Node* T2 = x->right;

        // Perform rotation
        x->right = node;
        node->left = T2;

        // Update heights
        updateHeight(node);
        updateHeight(x);

        return x;
    }

    // Helper function to insert a node recursively
    Node* insert(Node* node, int value) {
        // 1. Normal BST insertion
        if (node == nullptr)
            return new Node(value);
    
        if (value < node->data)
            node->left = insert(node->left, value);
        else if (value > node->data)
            node->right = insert(node->right, value);
        else
            return node; // Duplicate keys not allowed
    
        // 2. Update height of this node
        updateHeight(node);
    
        // 3. Get balance factor
        int balance = getBalanceFactor(node);
    
        // 4. Check balance and perform rotations
    
        // Left Left Case
        if (balance > 1 && value < node->left->data)
            return rightRotate(node);
    
        // Right Right Case
        if (balance < -1 && value > node->right->data)
            return leftRotate(node);
    
        // Left Right Case
        if (balance > 1 && value > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    
        // Right Left Case
        if (balance < -1 && value < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    
        // 5. Return the node (unchanged if balanced)
        return node;
    }
    

    // Helper function to search a node recursively
    bool search(Node* node, int value) {
        if (node == nullptr) return false;
        if (node->data == value) return true;
        if (value < node->data)
            return search(node->left, value);
        else
            return search(node->right, value);
    }

    // Helper function to find the minimum value node
    Node* findMin(Node* node) {
        while (node && node->left != nullptr)
            node = node->left;
        return node;
    }

    // Helper function to delete a node recursively
    Node* deleteNode(Node* node, int value) {
        if (node == nullptr) return node;

        if (value < node->data) {
            node->left = deleteNode(node->left, value);
        } else if (value > node->data) {
            node->right = deleteNode(node->right, value);
        } else {
            // Node with one child or no child
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            // Node with two children
            Node* temp = findMin(node->right);
            node->data = temp->data;
            node->right = deleteNode(node->right, temp->data);
        }


        // Update height of the current node
        updateHeight(node);
        // Get balance factor
        int balance = getBalanceFactor(node);
        // Check balance and perform rotations
        // Left Left Case
        if (balance > 1 && getBalanceFactor(node->left) >= 0)
            return rightRotate(node);
        // Left Right Case
        if (balance > 1 && getBalanceFactor(node->left) < 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        // Right Right Case
        if (balance < -1 && getBalanceFactor(node->right) <= 0)
            return leftRotate(node);
        // Right Left Case
        if (balance < -1 && getBalanceFactor(node->right) > 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        // Return the node (unchanged if balanced)
        return node;
    }

    // Inorder traversal helper function
    void inorder(Node* node) {
        if (node != nullptr) {
            inorder(node->left);
            cout << node->data << " ";
            inorder(node->right);
        }
    }

public:
    // Constructor
    BST() {
        root = nullptr;
    }

    int getHeight(Node* node) {
        return (node == nullptr) ? 0 : node->height;
    }    

    void updateHeight(Node* node) {
        if (node == nullptr) return;
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    }    

    int getBalanceFactor(Node* node) {
        if (node == nullptr) return 0;
        return getHeight(node->left) - getHeight(node->right);
    }
    
    // Public insert function
    void insert(int value) {
        root = insert(root, value);
    }

    // Public search function
    bool search(int value) {
        return search(root, value);
    }

    // Public delete function
    void deleteNode(int value) {
        root = deleteNode(root, value);
    }

    // Public inorder function
    void inorder() {
        inorder(root);
        cout << endl;
    }
};

// Main function to test the BST
int main() {
    BST tree;


    return 0;
}
