#include <iostream>
#include <string>
#include <stack>

using namespace std;

bool balanced_parentheses(std::string s) {
    stack<char> st;
    int size = s.size();

    if (size == 1) return false;

    for (int i = 0; i < size; i++) {
        char ch = s[i];

        if (ch == '{' || ch == '(' || ch == '[') {
            st.push(ch);
        } else if (st.empty()) {
            return false;
        } else if ((ch == '}' && st.top() != '{') ||
                   (ch == ']' && st.top() != '[') ||
                   (ch == ')' && st.top() != '(')) {
            return false;
        } else {
            st.pop();
        }
    }

    return st.empty();
}

int main() {
    string string1 = "((()))";
    string string2 = "[][[]]";
    string string3 = "[{()}]";

    cout << balanced_parentheses(string1) << endl;
    cout << balanced_parentheses(string2) << endl;
    cout << balanced_parentheses(string3) << endl;
}