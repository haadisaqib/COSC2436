#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include "ArgumentManager.h"
#include <fstream>
#include <sstream>

using namespace std;

struct line {
    line* right;
    line* left;
    int p;
    int order;       // insertion order: lower means inserted earlier
    string command;
    string data;

    line() : right(nullptr), left(nullptr), p(0), order(0) {}

    // Order first by priority (lower priority value = higher precedence)
    // When priorities are equal, lower order (i.e., earlier insertion) comes first.
    bool operator>(const line& other) const {
        if (p == other.p)
            return order > other.order;
        return p > other.p;
    }
};


//helper functions
void rosa_parks(queue<line>& q) {
    //pop the first element from the queue and push it to the back of the queue
    line temp = q.front();
    q.pop();
    q.push(temp);
}

// --- BST Helper Functions ---

// Insert a message (represented as a line structure) into the BST.
// The BST ordering is based solely on the length of the string (line.data).
// If the length of the new message is less than the current node's string length, go left;
// if greater, go right; if equal, replace the node's data.
line* insertBST(line* root, const line& msg) {
    if (root == nullptr) {
        line* newNode = new line();
        newNode->data = msg.data;
        newNode->p = msg.p;         // Not used for BST ordering, but stored.
        newNode->order = msg.order; // Not used in BST comparisons, but stored.
        newNode->command = msg.command;
        return newNode;
    }
    int newLen = msg.data.size();
    int currentLen = root->data.size();
    
    if (newLen < currentLen) {
        root->left = insertBST(root->left, msg);
    } else if (newLen > currentLen) {
        root->right = insertBST(root->right, msg);
    } else {
        // If equal in length, replace the node's data.
        root->data = msg.data;
    }
    return root;
}

// Inorder traversal: Left subtree, node, then right subtree.
void inorder_traversal(line* root, ofstream& output) {
    if (root == nullptr)
        return;
    inorder_traversal(root->left, output);
    output << root->data << endl;
    inorder_traversal(root->right, output);
}

// Preorder traversal: Node, then left subtree, then right subtree.
void preorder_traversal(line* root, ofstream& output) {
    if (root == nullptr)
        return;
    output << root->data << endl;
    preorder_traversal(root->left, output);
    preorder_traversal(root->right, output);
}

// Postorder traversal: Left subtree, then right subtree, then node.
void postorder_traversal(line* root, ofstream& output) {
    if (root == nullptr)
        return;
    postorder_traversal(root->left, output);
    postorder_traversal(root->right, output);
    output << root->data << endl;
}

// --- End BST Helper Functions ---

void read_input_and_init_queue(string inputFile, 
                               priority_queue<line, vector<line>, greater<line>>& commandQueue, 
                               queue<line>& messageQueue) {
    // Open the input file.
    ifstream input(inputFile);
    if (!input) {
        cerr << "Error opening input file." << endl;
        return;
    }
    
    // Read all non-empty lines into a vector.
    vector<string> fileLines;
    string currLine;
    while (getline(input, currLine)) {
        if (!currLine.empty())
            fileLines.push_back(currLine);
    }
    input.close();
    
    if (fileLines.empty())
        return;

    // The last line contains the BST traversal method.
    string traversalMethod = fileLines.back();
    fileLines.pop_back();

    int orderCount = 0;  // to track insertion order
    // Process each line (command) in the file except the traversal method.
    for (const string &lineStr : fileLines) {
        line l;
        l.order = orderCount++;  // assign and increment the order count

        // Extract the priority value (number inside parentheses).
        size_t openParen = lineStr.find('(');
        size_t closeParen = lineStr.find(')', openParen);
        if (openParen != string::npos && closeParen != string::npos) {
            string priorityStr = lineStr.substr(openParen + 1, closeParen - openParen - 1);
            l.p = stoi(priorityStr);
        } else {
            l.p = 0;  // Default priority if not found.
        }

        // Extract the command type (everything before ':').
        size_t colonPos = lineStr.find(':');
        if (colonPos != string::npos) {
            l.command = lineStr.substr(0, colonPos);
        } else {
            l.command = lineStr;
        }
        
        // For BST command, use the traversal method as its data.
        if (l.command == "BST") {
            l.data = traversalMethod;
        } else {
            // For other commands, extract the string inside the square brackets.
            size_t openBracket = lineStr.find('[');
            size_t closeBracket = lineStr.find(']', openBracket);
            if (openBracket != string::npos && closeBracket != string::npos) {
                l.data = lineStr.substr(openBracket + 1, closeBracket - openBracket - 1);
            }
        }
        
        // Push the line object into the command (priority) queue.
        commandQueue.push(l);
    }
}

// Processes the commands in the priority queue and applies them to the message queue.
// When encountering a "BST" command, the function removes the front message from the message queue,
// inserts it into a BST, and saves the traversal method (Inorder, Preorder, or Postorder) from the BST command's data.
// At the end, the BST is traversed in the chosen order and the output (one node per line) is written to the output file.
void process_queues(string outputFile, 
                    priority_queue<line, vector<line>, greater<line>>& pq, 
                    queue<line>& mq) {
    // Open the output file.
    ofstream output(outputFile);
    if (!output) {
        cerr << "Error opening output file." << endl;
        return;
    }
    
    line* bstRoot = nullptr;
    string traversalType = ""; // Will be set from the BST command.
    
    while (!pq.empty()) {
        line currentCommand = pq.top();
        pq.pop();
        
        if (currentCommand.command == "ADD") {
            if (mq.empty()) continue;
            // ADD:[x,y] -> Insert character y after every occurrence of x.
            char marker = currentCommand.data[0];
            char addChar = currentCommand.data[2];
            string msg = mq.front().data;
            string newMsg;
            for (char c : msg) {
                newMsg.push_back(c);
                if (c == marker)
                    newMsg.push_back(addChar);
            }
            mq.front().data = newMsg;
            rosa_parks(mq);
        }
        else if (currentCommand.command == "REMOVE") {
            if (mq.empty()) continue;
            // REMOVE:[x] -> Remove every occurrence of x.
            char removeChar = currentCommand.data[0];
            string msg = mq.front().data;
            string newMsg;
            for (char c : msg) {
                if (c != removeChar)
                    newMsg.push_back(c);
            }
            mq.front().data = newMsg;
            rosa_parks(mq);
        }
        else if (currentCommand.command == "REPLACE") {
            if (mq.empty()) continue;
            // REPLACE:[x,y] -> Replace every occurrence of x with y.
            char marker = currentCommand.data[0];
            char replacement = currentCommand.data[2];
            string msg = mq.front().data;
            for (size_t i = 0; i < msg.size(); i++) {
                if (msg[i] == marker)
                    msg[i] = replacement;
            }
            mq.front().data = msg;
            rosa_parks(mq);
        }
        else if (currentCommand.command == "SWAP") {
            if (mq.empty()) continue;
            // SWAP:[a,b] -> For each character, swap a with b and vice versa.
            char char1 = currentCommand.data[0];
            char char2 = currentCommand.data[2];
            string msg = mq.front().data;
            for (size_t i = 0; i < msg.size(); i++) {
                if (msg[i] == char1)
                    msg[i] = char2;
                else if (msg[i] == char2)
                    msg[i] = char1;
            }
            mq.front().data = msg;
            rosa_parks(mq);
        }
        if (currentCommand.command == "DECODE") {
            // For DECODE commands, push the encoded message (currentCommand.data) onto the message queue.
            mq.push(currentCommand);
        }
        else if (currentCommand.command == "BST") {
            // When BST command is encountered, take the front message from the message queue,
            // insert it into the BST, and store the traversal method (from currentCommand.data).
            if (!mq.empty()) {
                line msg = mq.front();
                mq.pop();
                bstRoot = insertBST(bstRoot, msg);
                traversalType = currentCommand.data;
            }
        }
    }
    
    // Traverse the BST using the selected traversal method and print each node on a new line.
    if (bstRoot != nullptr) {
        if (traversalType == "Inorder")
            inorder_traversal(bstRoot, output);
        else if (traversalType == "Preorder")
            preorder_traversal(bstRoot, output);
        else if (traversalType == "Postorder")
            postorder_traversal(bstRoot, output);
    }
    output.close();
}

int main(int argc, char* argv[]) {
    // Use ArgumentManager to manage command-line arguments.
    ArgumentManager am(argc, argv);
    string inputFile = am.get("input");
    string outputFile = am.get("output");

    // Initialize the command (priority) and message queues.
    priority_queue<line, vector<line>, greater<line>> commandQueue;
    queue<line> messageQueue;

    // Read input file and initialize queues.
    read_input_and_init_queue(inputFile, commandQueue, messageQueue);

    // Process all commands; this will transform the messages and build/traverse the BST.
    process_queues(outputFile, commandQueue, messageQueue);

    return 0;
}