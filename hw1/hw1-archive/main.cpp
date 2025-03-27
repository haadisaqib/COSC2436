#include <iostream>
#include <fstream>
#include "ArgumentManager.h"
#include <string>
#include <algorithm>
#include <regex>

using namespace std;

struct Node {
    string name;
    int age;
    int deposit;
    int numOfDrinks;
    Node* next;

    //Constructor 
    Node(string n, int a, int d, int drinks) {
    name = n;
    age = a;
    deposit = d;
    numOfDrinks = drinks;
    next = nullptr;
    }
};

//To anyone who is reading this: I am sorry for the mess. 
void printLL(Node* head) {
    Node* current = head;
    while (current != nullptr) {
        cout << "[name: " << current->name << "; age: " << current->age
             << "; deposit: " << current->deposit << "; numOfDrinks: " << current->numOfDrinks << "]\n";
        current = current->next;
    }
}

int sizeOf(Node* head) {
    int counter = 0;
    Node* current = head;
    while (current != nullptr) {
        counter++;
        current = current->next;
    }
    return counter;
}

void addToLL(Node*& head ,int index, string name, int age, int deposit, int numOfDrinks){
    //make new node to add
    Node* toAdd = new Node(name, age, deposit, numOfDrinks);
    
    //case1: duplicate cases
    Node* current = head;
    while (current != nullptr) {
        if (current->age == age && current->name == name) {
            current->deposit = deposit;
            current->numOfDrinks = numOfDrinks;
            delete toAdd;
            return;
        }
        current = current->next;
    }

    //case1: add at head
    if (index == 0) {
        toAdd->next = head;
        head = toAdd;
        return;
    }

    //case2: empty list
    if (head == nullptr) {
        head = toAdd;
        return;
    }

    int size = sizeOf(head);

    //case3: index is greater than size
    if (index > size) {
        Node* p = head;
        while (p->next != nullptr) {
            p = p->next;
        }
        p->next = toAdd;
        return;
    }

    // 7) Insert at the valid index [1..sz]
    Node* p2 = head;
    int counter = 0;
    while (counter < index - 1) {
        p2 = p2->next;
        counter++;
    }

    toAdd->next = p2->next;  
    p2->next = toAdd;  
}

void removeFromLL (Node*& head, string attr, string value) {
    Node* current = head;
    Node* prev = nullptr;
    
    //check if head is null
    if (head == nullptr) {
        return;
    }

    //traverse through linked list
    while (current != nullptr) {
        //remove by name
        if (attr == "name" && current->name == value) {
        // If it's truly a single-node list
            if (current == head && current->next == nullptr) {
                delete current;
                head = nullptr;
                return;
            }
            // Last node in a multi-node list
            else if (current->next == nullptr) {
                prev->next = nullptr;
                delete current;
                return;
            }
            //case2: remove from beginning
            if (current == head) {
                head = current->next;
                delete current;
                current = head;
                continue;
            }
            //case3: remove from middle || end
            if (current != head) {
                prev->next = current->next;
                delete current;
                current = prev->next;
                continue;
            }
        }

        //remove by age
        if (attr == "age" && current->age == stoi(value)) {
            // If it's truly a single-node list
            if (current == head && current->next == nullptr) {
                delete current;
                head = nullptr;
                return;
            }
            // Last node in a multi-node list
            else if (current->next == nullptr) {
                prev->next = nullptr;
                delete current;
                return;
            }
            //case2: remove from beginning
            if (current == head) {
                head = current->next;
                delete current;
                current = head;
                continue;
            }
            //case3: remove from middle || end
            if (current != head) {
                prev->next = current->next;
                delete current;
                current = prev->next;
                continue;
            }
        }

        //remove by deposit
        if (attr == "deposit" && current->deposit == stoi(value)) {
            // If it's truly a single-node list
            if (current == head && current->next == nullptr) {
                delete current;
                head = nullptr;
                return;
            }
            // Last node in a multi-node list
            else if (current->next == nullptr) {
                prev->next = nullptr;
                delete current;
                return;
            }
            //case2: remove from beginning
            if (current == head) {
                head = current->next;
                delete current;
                current = head;
                continue;
            }
            //case3: remove from middle || end
            if (current != head) {
                prev->next = current->next;
                delete current;
                current = prev->next;
                continue;
            }
        }

        //remove by number of drinks
        if (attr == "numOfDrinks"  || attr == "number of drinks" && current->numOfDrinks == stoi(value)) {
            // If it's truly a single-node list
            if (current == head && current->next == nullptr) {
                delete current;
                head = nullptr;
                return;
            }
            // Last node in a multi-node list
            else if (current->next == nullptr) {
                prev->next = nullptr;
                delete current;
                return;
            }
            //case2: remove from beginning
            if (current == head) {
                head = current->next;
                delete current;
                current = head;
                continue;
            }
            //case3: remove from middle || end
            if (current != head) {
                prev->next = current->next;
                delete current;
                current = prev->next;
                continue;
            }
        }
        prev = current;
        current = current->next;
    }
}

void sortLL(Node*& head, string attr) {
    // case1: Empty or single list
    if (head == nullptr || head->next == nullptr) {
        return;  
    }

    Node* prev = nullptr;
    Node* current = head;
    Node* nextNode = nullptr;

    // traverse passes MUST BE < size - 1 
    for (int i = 0; i < sizeOf(head) - 1; i++) { 
        prev = nullptr;                // reset
        current = head;                // reset
        nextNode = current->next;      // reset
        while (nextNode != nullptr) {
            if (attr == "age") { 
                if (current->age > nextNode->age) {
                    if (prev == nullptr) {
                        // Case1: Swapping involves the head of the list
                        head = nextNode;
                    } else {
                        // Case2: Swapping nodes in the middle or end
                        prev->next = nextNode;
                    }

                    current->next = nextNode->next; 
                    nextNode->next = current;        

                    //update pointers after the swap
                    prev = nextNode;
                    nextNode = current->next;
                    continue; 
                }
            }

            //sort by name
            if (attr == "name") { 
                if (current->name > nextNode->name) {
                    if (prev == nullptr) {
                        head = nextNode;
                    } else {
                        prev->next = nextNode;
                    }

                    current->next = nextNode->next;
                    nextNode->next = current;

                    prev = nextNode;
                    nextNode = current->next;
                    continue;  
                }
            }

            //sort by deposit
            if (attr == "deposit") {
                if (current->deposit > nextNode->deposit) {
                    if (prev == nullptr) {
                        head = nextNode;
                    } else {
                        prev->next = nextNode;
                    }

                    current->next = nextNode->next;
                    nextNode->next = current;

                    prev = nextNode;
                    nextNode = current->next;
                    continue;  
                }
            }

            //sort by number of drinks
            if (attr == "numOfDrinks") {
                if (current->numOfDrinks > nextNode->numOfDrinks) {
                    if (prev == nullptr) {
                        head = nextNode;
                    } else {
                        prev->next = nextNode;
                    }

                    current->next = nextNode->next;
                    nextNode->next = current;

                    prev = nextNode;
                    nextNode = current->next;
                    continue;  
                }
            }

            //If no swap is needed, move forward
            prev = current;
            current = nextNode;
            nextNode = nextNode->next;
        }
    }
}

void initializeListFromFile(const string& inputfile, const string& outputfile, Node*& head) {
    ifstream input(inputfile);
    if (!input.is_open()) {
        cerr << "Failed to open input file: " << inputfile << endl;
        return;
    }

    ofstream output(outputfile);
    if (!output.is_open()) {
        cerr << "Failed to open output file: " << outputfile << endl;
        return;
    }

    // Check if input file is empty
    input.seekg(0, ios::end);  // Move to end of file
    if (input.tellg() == 0) {  // If file position is at 0, it's empty
        output.close();
        input.close();
        return;
    }
    input.seekg(0, ios::beg);  // Reset file pointer to beginning

    // Initialize the linked list
    int index = 0;
    regex pattern("\\[name:\\s*([^;]+);\\s*age:\\s*(\\d+);\\s*deposit:\\s*(\\d+);\\s*number of drinks:\\s*(\\d+)\\]");

    string line;
    while (getline(input, line)) {
        smatch match;
        if (regex_search(line, match, pattern)) {
            string name = match[1].str();
            int age = stoi(match[2].str());
            int deposit = stoi(match[3].str());
            int numOfDrinks = stoi(match[4].str());

            addToLL(head, index, name, age, deposit, numOfDrinks);
            index++;
        }
    }

    // Write the initialized linked list to the output file
    Node* current = head;

    while (current != nullptr) {
    output << "[name: " << current->name << "; age: " << current->age
           << "; deposit: " << current->deposit << "; number of drinks: " << current->numOfDrinks << "]";
    
    if (current->next != nullptr) {  
        output << "\n";  // Only add newline if it's NOT the last node
    }

    current = current->next;
    }

    input.close();
    output.close();
}

void processCommandFile(const string& commandfile, const string& outputfile, Node*& head) {
    ifstream command(commandfile);
    if (!command.is_open()) {
        cerr << "Failed to open command file: " << commandfile << endl;
        return;
    }

    // Check if command file is empty
    command.seekg(0, ios::end);
    if (command.tellg() == 0) {
        cout << "Command file is empty. No changes made." << endl;
        command.close();
        return;
    }
    command.seekg(0, ios::beg);  // Reset file pointer

    string line;
    regex addPattern(R"(Add\s*\((\d+)\)\s*\[name:\s*([^;]+);\s*age:\s*(\d+);\s*deposit:\s*(\d+);\s*number of drinks:\s*(\d+)\])");
    regex removePattern(R"(Remove\s*\(\s*([^:]+):\s*([^\)]+)\))");
    regex sortPattern(R"(Sort\s*\(\s*([^)]+)\))");

    while (getline(command, line)) {
        smatch match;

        // Handle Add Command
        if (regex_search(line, match, addPattern)) {
            int index = stoi(match[1].str());
            string name = match[2].str();
            int age = stoi(match[3].str());
            int deposit = stoi(match[4].str());
            int numOfDrinks = stoi(match[5].str());

            addToLL(head, index, name, age, deposit, numOfDrinks);
            continue;
        }

        // Handle Remove Command
        if (regex_search(line, match, removePattern)) {
            string attr = match[1].str();
            string value = match[2].str();

            removeFromLL(head, attr, value);
            continue;
        }

        // Handle Sort Command
        if (regex_search(line, match, sortPattern)) {
            string attr = match[1].str();
            sortLL(head, attr);
            continue;
        }
    }

    command.close();

    // Write Updated Linked List to Output File
    ofstream output(outputfile);
    if (!output.is_open()) {
        cerr << "Failed to open output file: " << outputfile << endl;
        return;
    }

    Node* current = head;
    while (current != nullptr) {
        output << "[name: " << current->name << "; age: " << current->age
               << "; deposit: " << current->deposit << "; number of drinks: " << current->numOfDrinks << "]";
        
        if (current->next != nullptr) {
            output << "\n";
        }

        current = current->next;
    }

    output.close();
}

int main(int argc, char* argv[]) {
    ArgumentManager am(argc, argv);
    string inputfile = am.get("input");
    string outputfile = am.get("output");
    string commandfile = am.get("command");

    Node* head = nullptr;

    // Initialize Linked List from Input File
    initializeListFromFile(inputfile, outputfile, head);

    // Move on to processing the command file (next step)
    processCommandFile(commandfile, outputfile, head);

    return 0;
}

