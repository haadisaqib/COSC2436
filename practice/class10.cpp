#include <iostream>

using namespace std;

struct node {
    int val;
    node* right;
    node* left;

    node(int x){val = x; left = right = nullptr;}
};

class tree{
    private:
        node* root;

    public:
        tree();
        void inorder_traverse_tree_rec(node* cu){
            if (root == nullptr) return;
            else {
                inorder_traverse_tree_rec(cu->left);
                cout<< cu->val << endl;
                inorder_traverse_tree_rec(cu->right);
            }
        };
        void preorder_traverse_tree_rec(node* cu){
            if (root == nullptr) return;
            else {
                cout<< cu->val << endl;
                preorder_traverse_tree_rec(cu->left);
                preorder_traverse_tree_rec(cu->right);
            }
        };
        void postorder_traverse_tree_rec(node* cu){
            if (root == nullptr) return;
            else {
                postorder_traverse_tree_rec(cu->left);
                postorder_traverse_tree_rec(cu->right);
                cout<< cu->val << endl;
            }
        };
        bool search(node* cu, int target) {
            if (cu->val == target) return true;
            if (cu == nullptr) return false;
            else {
                search(cu->left, target);
                search(cu->right, target);
            }
        };

        int h(node* root) {
            int h_left = 1;
            int h_right = 1;
            if (root == nullptr) return 0;
            h(root->left);
            h_left++;
            h(root->right);
            h_right++;
            return max(h_right,h_left);
        }

        void insert(int val);

};

int main() {

}