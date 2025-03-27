#include <iostream>
#include <tuple>
#include <queue>
#include <stack>
#include <fstream>
#include <regex>
#include "ArgumentManager.h"

using namespace std;
//What is a person?
using person = tuple<string, int, int>;

struct Player {
    string name;
    int black;
    int red;
};

struct Card {
    char color;
    int count;
};

//print stack is purely for testing, program doesn't need this func
void printStack(stack<Card> s) {
    if (s.empty()) {
        cout << "Stack is empty." << endl;
        return;
    }
    stack<Card> tempStack = s; 
    cout << "Stack (top to bottom): ";
    while (!tempStack.empty()) {
        Card temp = tempStack.top();
        cout << temp.color << temp.count << " ";
        tempStack.pop();
    }
    cout << endl;
}

void printQueueToFile(const queue<Player>& q, const string& filename) {
    // Attempt to open output file
    std::ofstream out(filename);
    if (!out.is_open()) {
        std::cerr << "Failed to open output file: " << filename << std::endl;
        return;
    }

    // Write each player's name, one per line
    queue<Player> tempQ(q);
    while (!tempQ.empty()) {
        out << tempQ.front().name << "\n";
        tempQ.pop();
    }
    out.close();
}

//move front of queue to back of queue
void rosaParks(queue<Player>& line) {
    Player frontPerson = line.front();
    line.pop();
    line.push(frontPerson);
    return;
}

void initializeGame(queue<Player>& line, 
    stack<Card>& cards,
    const string& inputFile,
    const string& commandFile,
    bool& inputEmpty, bool& commandEmpty)
{
    ifstream input(inputFile);
    if (!input.is_open()) {
        return;
    }
    ifstream command(commandFile);
    if (!command.is_open()) {
        return;
    }

    // Check if input file is empty
    input.seekg(0, ios::end);  
    if (input.tellg() == 0) {  
        input.close();
        inputEmpty = true;
        return;
    }

    // Check if command file is empty
    command.seekg(0, ios::end);
    if (command.tellg() == 0) {
        command.close();
        commandEmpty = true;
        return;
    }

    // Initialize Queue (Participants)
    string lineText;
    input.seekg(0, ios::beg);

    while (getline(input, lineText)) {
        if (!lineText.empty() && lineText.back() == '\r') {
            lineText.pop_back();
        }

        size_t commaPos = lineText.find(',');
        if (commaPos != string::npos) {
            string name = lineText.substr(0, commaPos);
            string numStr = lineText.substr(commaPos + 1);

            name.erase(name.find_last_not_of(" ") + 1);
            numStr.erase(0, numStr.find_first_not_of(" "));

            if (numStr.size() == 2 && isdigit(numStr[0]) && isdigit(numStr[1])) {
                int black = numStr[0] - '0';
                int red = numStr[1] - '0';

                line.push({name, black, red}); // ✅ Use struct instead of tuple
            }
        }
    }

    input.close();

    // Initialize Stack (Commands)
    string lineTextCommand;
    command.seekg(0, ios::beg);

    while (getline(command, lineTextCommand)) {
        if (!lineTextCommand.empty() && lineTextCommand.back() == '\r') {
            lineTextCommand.pop_back();
        }

        if (lineTextCommand.length() > 1) {
            char color = lineTextCommand[0];
            int count = stoi(lineTextCommand.substr(1));

            cards.push({color, count}); // ✅ Use struct instead of pair
        }
    }

    command.close();
}

void runGame(queue<Player>& line, stack<Card>& cards, const string& opFile) {
    // Open the output file
    ofstream out(opFile);
    if (!out.is_open()) {
        cerr << "Failed to open output file: " << opFile << endl;
        return;
    }

    // Distribute cards until we run out OR the queue is empty
    while (!cards.empty()) {
        if (line.empty()) {
            break; 
        }

        // 1) Take the top card
        Card topCard = cards.top();
        cards.pop();

        // 2) Check if anyone needs this card color
        bool neededBySomeone = false;
        {
            queue<Player> copyQ = line;
            while (!copyQ.empty()) {
                Player p = copyQ.front();
                copyQ.pop();
                if ((topCard.color == 'B' && p.black > 0) ||
                    (topCard.color == 'R' && p.red > 0)) {
                    neededBySomeone = true;
                    break;
                }
            }
        }

        // If nobody needs it, burn it
        if (!neededBySomeone) {
            continue; 
        }

        // 3) Distribute leftover in a single pass
        int leftover = topCard.count;
        int passLimit = line.size(); // limit to one pass of the queue

        while (leftover > 0 && passLimit-- > 0 && !line.empty()) {
            Player& frontPlayer = line.front();

            int needed = 0;
            bool finishedOneColor = false; 
            bool usedUpCard = false;

            // BLACK CARD
            if (topCard.color == 'B') {
                needed = frontPlayer.black;
                if (needed == 0) {
                    line.push(frontPlayer);
                    line.pop();
                    continue;
                }
                if (leftover >= needed) {
                    leftover -= needed;
                    frontPlayer.black = 0;
                    finishedOneColor = true;
                    usedUpCard = (leftover == 0);
                } else {
                    frontPlayer.black -= leftover;
                    leftover = 0;
                    usedUpCard = true;
                }
            }

            // RED CARD
            else if (topCard.color == 'R') {
                needed = frontPlayer.red;
                if (needed == 0) {
                    line.push(frontPlayer);
                    line.pop();
                    continue;
                }
                if (leftover >= needed) {
                    leftover -= needed;
                    frontPlayer.red = 0;
                    finishedOneColor = true;
                    usedUpCard = (leftover == 0);
                } else {
                    frontPlayer.red -= leftover;
                    leftover = 0;
                    usedUpCard = true;
                }
            }

            // If fully satisfied, remove the player
            if (frontPlayer.black == 0 && frontPlayer.red == 0) {
                line.pop();
            }
            // Otherwise, if they finished one color or used up the card chunk, move them back
            else if (finishedOneColor || usedUpCard) {
                Player temp = frontPlayer;
                line.pop();
                line.push(temp);
            }
        }

        // 4) If leftover > 0 after one pass, we burn the remainder
        // (Do nothing; just don't put the card back)
    }

    // If line is empty, everyone got their cards => no losers
    if (line.empty()) {
        out << "No Losers!" << endl;
    } else {
        // Print remaining players => these are losers
        printQueueToFile(line, opFile);
    }

    out.close(); // Close the file
}


int main(int argc, char* argv[]) {
    ArgumentManager am(argc, argv);
    std::string inputfile = am.get("input");
    std::string outputfile = am.get("output");
    std::string commandfile = am.get("command");

    // card stack
    std::stack<Card> cards;

    // game queue
    std::queue<Player> line;

    // flags indicating empty input/command
    bool inputEmpty = false;
    bool commandEmpty = false;

    // Initialize game data (fills 'line' and 'cards')
    initializeGame(line, cards, inputfile, commandfile, inputEmpty, commandEmpty);

    // If no input -> no participants => "No Game!"
    if (inputEmpty) {
        std::ofstream out(outputfile);
        if (out.is_open()) {
            out << "No Game!" << std::endl;
            out.close();
        } else {
            std::cerr << "Failed to open output file: " << outputfile << std::endl;
        }
        return 0;
    }

    // If no commands -> just print the queue and exit
    if (commandEmpty) {
        printQueueToFile(line, outputfile);
        return 0;
    }

    // Otherwise, run the game
    runGame(line, cards, outputfile);

    return 0;
}
