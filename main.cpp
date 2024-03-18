#include <iostream>
#include <sstream>
#include <cmath>
#include <stack>
using namespace std;

struct Leksema //Структура, описывающая любое число или операцию
{
	char type; // 0 для чисел, "+" для операции сложения и т.д.
	double value; //Значение (только для чисел). У операций значение всегда "0"
};

bool Maths(stack <Leksema>& Stack_n, stack <Leksema>& Stack_o, Leksema& item) { //Математическая функция, которая производит расчеты
	//Функция имеет тип bool, чтобы при возникновении какой-либо ошибки возвращать "false"
	double a, b, c;
	a = Stack_n.top().value; //Берется верхнее число из стека с числами
	Stack_n.pop(); //Удаляется верхнее число из стека с числами
	switch (Stack_o.top().type) {  //Проверяется тип верхней операции из стека с операциями
	case '+': //Если тип верхней операции из стека с операциями сложение
		b = Stack_n.top().value;
		Stack_n.pop();
		c = a + b;
		item.type = '0';
		item.value = c;
		Stack_n.push(item); //Результат операции кладется обратно в стек с числами
		Stack_o.pop();
		break;

	case '-':
		b = Stack_n.top().value;
		Stack_n.pop();
		c = b - a;
		item.type = '0';
		item.value = c;
		Stack_n.push(item);
		Stack_o.pop();
		break;

	case '^':
		b = Stack_n.top().value;
		Stack_n.pop();
		c = pow(b, a);
		item.type = '0';
		item.value = c;
		Stack_n.push(item);
		Stack_o.pop();
		break;

	case '*':
		b = Stack_n.top().value;
		Stack_n.pop();
		c = a * b;
		item.type = '0';
		item.value = c;
		Stack_n.push(item);
		Stack_o.pop();
		break;

	case '/':
		b = Stack_n.top().value;
		if (a == 0) {
			cout << "Error! Cannot divide by 0!" << endl;
			return false;
		}
		else {
			Stack_n.pop();
			c = (b / a);
			item.type = '0';
			item.value = c;
			Stack_n.push(item);
			Stack_o.pop();
			break;
			
	case 'e':
		c = exp(a);
		item.type = '0';
		item.value = c;
		Stack_n.push(item);
		Stack_o.pop();
		break;
		
	case 's':
	    c = sqrt(a);
	    item.type = '0';
		item.value = c;
		Stack_n.push(item);
		Stack_o.pop();
		break;
		
	case 'r':
	    c = round(a);
	    item.type = '0';
		item.value = c;
		Stack_n.push(item);
		Stack_o.pop();
		break;
		
	case 'a':
	    c = abs(a);
	    item.type = '0';
		item.value = c;
		Stack_n.push(item);
		Stack_o.pop();
		break;
		
	default:
		cout << "Error!" << endl;
		return false;
		break;
		}
	}
	return true;
}

int getRang(char Ch) { //Функция возвращает приоритет операции: "1" для сложения и вычитания, "2" для умножения и деления и т.д.
	if (Ch == 'e' || Ch == 's' || Ch == 'r' || Ch == 'a')return 4;
	if (Ch == '^')return 3;
	if (Ch == '+' || Ch == '-')return 1;
	if (Ch == '*' || Ch == '/')return 2;
	else return 0;
}

int main()
{
     cout << "Welcome to the Calculator!" << endl;
     cout << "Please enter your arithmetic expression: ";
     while (true) {
        system("cls");
        std::string str;
        getline(cin, str);
        stringstream sstr{str};

        char Ch; //Переменная, в которую будет записываться текущий обрабатываемый символ
        double value;
        bool flag = true; //Нужен для того, чтобы программа смогла отличить унарный минус (-5) от вычитания (2-5)
        stack<Leksema> Stack_n; //Стек с числами
        stack<Leksema> Stack_o; //Стек с операциями
        Leksema item; //Объект типа Leksema
        while (true) {
            Ch = sstr.peek(); //Смотрим на первый символ
            if (Ch == '\377')break; //Если достигнут конец строки, выходим из цикла
            if (Ch == ' ') { //Игнорирование пробелов
                sstr.ignore();
                continue;
            }
            if (Ch == 'e' || Ch == 'a') { //Если прочитана функция
                char foo[3];
                for (int i = 0; i < 3; i++) {
                    Ch = sstr.peek();
                    foo[i] = Ch;
                    sstr.ignore();
                }
                if (foo[0] == 'e' && foo[1] == 'x' && foo[2] == 'p') {
                    item.type = 'e';
                    item.value = 0;
                    Stack_o.push(item);
                    continue;
                }
                if (foo[0] == 'a' && foo[1] == 'b' && foo[2] == 's') {
                    double operand;
                    sstr >> operand; // Read the operand of abs(a) function
                    item.type = 'a'; // Indicate that it's an abs(a) function
                    item.value = operand;
                    Stack_n.push(item); // Push the operand onto the number stack
                    continue;
                }
            }
            if (Ch == 's') { //Если прочитана функция    
                char foo[4];
                for (int i = 0; i < 4; i++) {
                    Ch = sstr.peek();
                    foo[i] = Ch;
                    sstr.ignore();
                }
                if (foo[0] == 's' && foo[1] == 'q' && foo[2] == 'r' && foo[3] == 't') {
                    item.type = 's';
                    item.value = 0;
                    Stack_o.push(item); //Операция кладется в стек с операциями
                    continue;
                }
            }
            if (Ch == 'r') { //Если прочитана функция
                char foo[5]; 
                for (int i = 0; i < 5; i++) {
                    Ch = sstr.peek();
                    foo[i] = Ch;
                    sstr.ignore();
                }
                if (foo[0] == 'r' && foo[1] == 'o' && foo[2] == 'u' && foo[3] == 'n' && foo[4] == 'd') {
                    item.type = 'r';
                    item.value = 0;
                    Stack_o.push(item); //Операция кладется в стек с операциями
                    continue;
                }             
            }    
            if (Ch >= '0' && Ch <= '9' || Ch == '-' && flag == 1) { //Если прочитано число
                sstr >> value;
                item.type = '0';
                item.value = value;
                Stack_n.push(item); //Число кладется в стек с числами
                flag = 0;
                continue;
            }
            if (Ch == '+' || Ch == '-' && flag == 0 || Ch == '*' || Ch == '/' || Ch == '^') { //Если прочитана операция
                if (Stack_o.size() == 0) { //Если стек с операциями пуст
                    item.type = Ch;
                    item.value = 0;
                    Stack_o.push(item); //Операция кладется в стек с операциями
                    sstr.ignore();
                    continue;
                }
                if (Stack_o.size() != 0 && getRang(Ch) > getRang(Stack_o.top().type)) { //Если стек с операциями НЕ пуст, но приоритет текущей операции выше верхней в стеке с операциями
                    item.type = Ch;
                    item.value = 0;
                    Stack_o.push(item); //Операция кладется в стек с операциями
                    sstr.ignore();
                    continue;
                }
                if (Stack_o.size() != 0 && getRang(Ch) <=
                                           getRang(Stack_o.top().type)) {//Если стек с операциями НЕ пуст, но приоритет текущей операции ниже либо равен верхней в стеке с операциями
                    if (Maths(Stack_n, Stack_o, item) == false) { //Если функция вернет "false", то прекращаем работу
                        system("pause");
                        return 0;
                    }
                    continue;
                }
            }
            if (Ch == '(') { //Если прочитана открывающаяся скобка
                item.type = Ch;
                item.value = 0;
                Stack_o.push(item); //Операция кладется в стек с операциями
                sstr.ignore();
                continue;
            }
            if (Ch == ')') { //Если прочитана закрывающаяся скобка
                while (Stack_o.top().type != '(') {
                    if (Maths(Stack_n, Stack_o, item) == false) { //Если функция вернет "false", то прекращаем работу
                        system("pause");
                        return 0;
                    } else continue; //Если все хорошо
                }
                Stack_o.pop();
                sstr.ignore();
                continue;
            } else { //Если прочитан какой-то странный символ
                cout << "Expression entered incorrectly!" << endl;
                system("pause");
                return 0;
            }
        }
        while (Stack_o.size() != 0) { //Вызываем матем. функцию до тех пор, пока в стеке с операциями не будет 0 элементов
            if (Maths(Stack_n, Stack_o, item) == false) { //Если функция вернет "false", то прекращаем работу
                system("pause");
                return 0;
            } else continue; //Если все хорошо
        }
        cout << "Result: " << Stack_n.top().value << endl;
        cout << "Thank you for using the Calculator!" << endl;
        system("pause");
    }
    return 0;
}
