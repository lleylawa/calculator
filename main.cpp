#include <iostream>
#include <sstream>
#include <cmath>
#include <stack>
using namespace std;

struct Leksema {
    char type;
    double value;
};

bool Maths(stack <Leksema>& Stack_n, stack <Leksema>& Stack_o, Leksema& item) {
    double a, b, c;
    a = Stack_n.top().value;
    Stack_n.pop();
    switch (Stack_o.top().type) {
    case '+':
        b = Stack_n.top().value;
        Stack_n.pop();
        c = a + b;
        break;
    case '-':
        b = Stack_n.top().value;
        Stack_n.pop();
        c = b - a;
        break;
    case '^':
        b = Stack_n.top().value;
        Stack_n.pop();
        c = pow(b, a);
        break;
    case '*':
        b = Stack_n.top().value;
        Stack_n.pop();
        c = a * b;
        break;
    case '/':
        b = Stack_n.top().value;
        Stack_n.pop();
        if (a == 0) {
            cerr << "Error! Cannot divide by 0!" << endl;
            return false;
        }
        c = b / a;
        break;
    case 'e':
        c = exp(a);
        break;
    case 's':
        c = sqrt(a);
        break;
    case 'r':
        c = round(a);
        break;
    case 'a':
        c = abs(a);
        break;
    default:
        cerr << "Error!" << endl;
        return false;
    }
    item.type = '0';
    item.value = c;
    Stack_n.push(item);
    Stack_o.pop();
    return true;
}

int getRang(char Ch) {
    if (Ch == 'e' || Ch == 's' || Ch == 'r' || Ch == 'a') return 4;
    if (Ch == '^') return 3;
    if (Ch == '+' || Ch == '-') return 1;
    if (Ch == '*' || Ch == '/') return 2;
    return 0;
}

int main() {
    cout << "Welcome to the Calculator!" << endl;
    cout << "Please enter your arithmetic expression: ";
    while (true) {
        system("cls");
        string str;
        getline(cin, str);
        stringstream sstr{ str };

        char Ch;
        double value;
        bool unary_minus_flag = true;
        stack<Leksema> Stack_n;
        stack<Leksema> Stack_o;
        Leksema item;
        while (sstr >> Ch) {
            if (Ch == ' ') {
                continue;
            }
            if (Ch == 'e' || Ch == 's' || Ch == 'r' || Ch == 'a') {
                string func;
                func.push_back(Ch);
                sstr >> Ch;
                func.push_back(Ch);
                sstr >> Ch;
                func.push_back(Ch);
                if (func == "exp") {
                    item.type = 'e';
                }
                else if (func == "abs") {
                    item.type = 'a';
                }
                else if (func == "sqrt") {
                    item.type = 's';
                }
                else if (func == "round") {
                    item.type = 'r';
                }
                item.value = 0;
                Stack_o.push(item);
                continue;
            }
            if (Ch >= '0' && Ch <= '9' || Ch == '-' && unary_minus_flag) {
                sstr.putback(Ch);
                sstr >> value;
                item.type = '0';
                item.value = value;
                Stack_n.push(item);
                unary_minus_flag = false;
                continue;
            }
            if (Ch == '+' || Ch == '-' || Ch == '*' || Ch == '/' || Ch == '^') {
                while (!Stack_o.empty() && getRang(Ch) <= getRang(Stack_o.top().type)) {
                    if (!Maths(Stack_n, Stack_o, item)) {
                        return 0;
                    }
                }
                item.type = Ch;
                item.value = 0;
                Stack_o.push(item);
                unary_minus_flag = true;
                continue;
            }
            if (Ch == '(') {
                item.type = Ch;
                item.value = 0;
                Stack_o.push(item);
                unary_minus_flag = true;
                continue;
            }
            if (Ch == ')') {
                while (!Stack_o.empty() && Stack_o.top().type != '(') {
                    if (!Maths(Stack_n, Stack_o, item)) {
                        return 0;
                    }
                }
                Stack_o.pop();
                continue;
            }
            cout << "Expression entered incorrectly!" << endl;
            return 0;
        }
        while (!Stack_o.empty()) {
            if (!Maths(Stack_n, Stack_o, item)) {
                return 0;
            }
        }
        cout << "Result: " << Stack_n.top().value << endl;
        cout << "Thank you for using the Calculator!" << endl;
    }
    return 0;
}
