#include <iostream>
#include <string>
#include <regex>
#include <fstream>
#include "ArgumentManager.h"

using namespace std;

struct Song {
    string title;
    int duration;
    bool favorite;
    Song* next;
    Song* prev;

Song() : title(""), duration(0), favorite(false), next(nullptr), prev(nullptr) {}

};

void addSong(Song*& head, const string& t, int d, bool f) {
    Song* curr = head;
    //construct a new song object
    Song* newSong = new Song();
    newSong->title = t;
    newSong->duration = d;
    newSong->favorite = f;
    //best case
    if (head == nullptr) {
        head = newSong;
        head->prev = nullptr;
        head->next = nullptr;
        return;
    }
    while (curr->next != nullptr) {
        curr = curr->next;
    }
    curr->next = newSong;
    newSong->prev = curr;
    newSong->next = nullptr;
}

int sizeOf(Song* head) {
    Song* curr = head;
    if (head == nullptr) {
        return 0;
    }
    int count = 0;
    while (curr != nullptr) {
        count++;
        curr = curr->next;
    }
    return count;
}

void printList(Song* head) {
    if (head == nullptr) {
        return;   
    }
    //recursive case
    cout << head->title << endl;
    printList(head->next);
}

void printListReverse(Song* head) {
    if (head == nullptr) {
        return;   
    }
    //recursive case
    printListReverse(head->next);
    cout << head->title << endl;
}

void deleteSong(Song*& head, const string& t) {
    //base
    if (head == nullptr) {
        return;
    }
    //first node to del is head
    while (head != nullptr && head->title == t) {
        Song* toDelete = head;
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        }
        delete toDelete;
    }
    //del in middle or end
    Song* curr = head;
    while (curr != nullptr) {
        if (curr->title == t) {
            if (curr->prev != nullptr) {
                curr->prev->next = curr->next;
            }
            if (curr->next != nullptr) {
                curr->next->prev = curr->prev;
            }
            Song* toDelete = curr;
            curr = curr->next;
            delete toDelete;
        } else {
            curr = curr->next;
        }
    }
}

int playlistTime(Song* head) {
    Song* curr = head;
    int sum = 0;
    while (curr != nullptr) {
        sum += curr->duration;
        curr = curr->next;
    }
    return sum;
}

Song* createSmartPlaylist(int timeLimit, Song* original) {
    // case1: empty list
    if (original == nullptr) {
        return nullptr;
    }
    // case2: original playlist fits in time limit
    if (playlistTime(original) <= timeLimit) {
        Song* allSongsCopy = nullptr;
        Song* temp = original;
        while (temp != nullptr) {
            addSong(allSongsCopy, temp->title, temp->duration, temp->favorite);
            temp = temp->next;
        }
        return allSongsCopy;
    }

    // case3: create a new smartplaylist
    Song* smartPlaylist = nullptr;      
    int timeLeft = timeLimit;
    Song* lastFavoriteAdded = nullptr;

    // 1) Forward pass: add all FAVORITES if they fit
    {
        Song* curr = original;
        while (curr != nullptr) {
            if (curr->favorite && curr->duration <= timeLeft) {
                addSong(smartPlaylist, curr->title, curr->duration, curr->favorite);
                timeLeft -= curr->duration;
                lastFavoriteAdded = curr; 
            }
            curr = curr->next;
        }
    }

    // 2) If NO favorites were added, add NON-favorites in forward order
    if (lastFavoriteAdded == nullptr) {
        Song* curr = original;
        while (curr != nullptr) {
            if (!curr->favorite && curr->duration <= timeLeft) {
                addSong(smartPlaylist, curr->title, curr->duration, curr->favorite);
                timeLeft -= curr->duration;
            }
            curr = curr->next;
        }
        return smartPlaylist;
    }

    // 3) Backward pass from 'lastFavoriteAdded'
    {
        Song* back = lastFavoriteAdded->prev;
        while (back != nullptr) {
            if (!back->favorite && back->duration <= timeLeft) {
                addSong(smartPlaylist, back->title, back->duration, back->favorite);
                timeLeft -= back->duration;
            }
            back = back->prev;
        }
    }

    // 4) forward pass from 'lastFavoriteAdded'
    {
        Song* fwd = lastFavoriteAdded->next;
        while (fwd != nullptr) {
            if (!fwd->favorite && fwd->duration <= timeLeft) {
                addSong(smartPlaylist, fwd->title, fwd->duration, fwd->favorite);
                timeLeft -= fwd->duration;
            }
            fwd = fwd->next;
        }
    }

    // Return the playlist
    return smartPlaylist;
}

string bracketedList(Song* head) {
    ostringstream oss;
    oss << "[";
    Song* curr = head;
    while (curr != nullptr) {
        oss << curr->title;
        if (curr->next != nullptr) {
            oss << ", ";
        }
        curr = curr->next;
    }
    oss << "]";
    return oss.str();
}

string bracketedListReverse(Song* head) {
    // Find the tail
    if (head == nullptr) {
        return "[]";
    }
    Song* tail = head;
    while (tail->next != nullptr) {
        tail = tail->next;
    }

    ostringstream oss;
    oss << "[";
    Song* curr = tail;
    while (curr != nullptr) {
        oss << curr->title;
        if (curr->prev != nullptr) {
            oss << ", ";
        }
        curr = curr->prev;
    }
    oss << "]";
    return oss.str();
}

//Utility functions 
void trim(string &s) {
    const char* whitespace = " \t\n\r\f\v";
    // left trim
    s.erase(0, s.find_first_not_of(whitespace));
    // right trim
    s.erase(s.find_last_not_of(whitespace) + 1);
}

vector<string> splitByComma(const string& str) {
    vector<string> tokens;
    size_t start = 0;
    size_t end;
    while ((end = str.find(',', start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));
        start = end + 1;
    }
    tokens.push_back(str.substr(start));
    return tokens;
}

//read input file and produce output file
void readInputFileWriteOutput(const string& inputfile, const string& outputfile, Song*& head)
{
    ifstream in(inputfile);
    ofstream out(outputfile);

    if (!in.is_open() || !out.is_open()) {
        cerr << "Error opening input/output file.\n";
        return;
    }

    string line;
    while (getline(in, line)) {
        trim(line);

        // Skip empty lines
        if (line.empty()) {
            continue;
        }
        // 1) AddSong(...)
        if (line.rfind("AddSong(", 0) == 0) {
            size_t start = line.find('(');
            size_t end   = line.rfind(')');
            if (start != string::npos && end != string::npos && end > start) {
                string inside = line.substr(start + 1, end - (start + 1));
                vector<string> args = splitByComma(inside);
                if (args.size() == 3) {
                    for (auto &arg : args) {
                        trim(arg);
                    }
                    string title = args[0];
                    int duration = stoi(args[1]);
                    bool fav = (args[2] == "True" || args[2] == "true");
                    addSong(head, title, duration, fav);
                }
            }
        }
        // 2) DeleteSong(...)
        else if (line.rfind("DeleteSong(", 0) == 0) {
            size_t start = line.find('(');
            size_t end   = line.rfind(')');
            if (start != string::npos && end != string::npos && end > start) {
                string inside = line.substr(start + 1, end - (start + 1));
                trim(inside);
                // inside is the song title
                deleteSong(head, inside);
            }
        }
        // 3) PrintPlaylist()
        else if (line == "PrintPlaylist()") {
            out << bracketedList(head) << endl;
        }
        // 4) PrintReversedPlaylist()
        else if (line == "PrintReversedPlaylist()") {
            out << bracketedListReverse(head) << endl;
        }
        // 5) CreateSmartPlaylist(...)
        else if (line.rfind("CreateSmartPlaylist(", 0) == 0) {
            size_t start = line.find('(');
            size_t end   = line.rfind(')');
            if (start != string::npos && end != string::npos && end > start) {
                string inside = line.substr(start + 1, end - (start + 1));
                trim(inside);
                int timeLimit = stoi(inside);
                Song* sp = createSmartPlaylist(timeLimit, head);
                out << bracketedList(sp) << endl;
            }
        }
        // else: Unrecognized command, skip or handle error
    }

    in.close();
    out.close();
}

int main(int argc, char *argv[]) {
    ArgumentManager am(argc, argv);
    string inputfile = am.get("input");
    string outputfile = am.get("output");

    Song* head = nullptr;

    // Read and process input, then write results to output
    readInputFileWriteOutput(inputfile, outputfile, head);

    return 0;
}
