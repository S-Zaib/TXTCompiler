#pragma once
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
using namespace std;


template <typename T>
class Node
{
public:
	T data;
	Node<T>* next;
	Node()
	{
		T data = 0;
		next = NULL;
	}
	Node(T data)
	{
		this->data = data;
		next = NULL;
	}
};
template <typename T>
class Stack
{
	Node<T>* top;
public:
	Stack()
	{
		top = NULL;
	}
	void push(T data)
	{
		if (!top)
		{
			top = new Node<T>(data);
			return;
		}
		Node<T>* temp = new Node<T>(data);
		temp->next = top;
		top = temp;
	}
	T pop()
	{
		if (!top)
		{
			cout << "Error, Empty Stack!\n";
			return 0;
		}
		Node<T>* temp = top;
		top = top->next;
		T temp_data = temp->data;
		delete temp;
		return temp_data;
	}
	T peek()
	{
		if (!top)
		{
			cout << "Error, Empty Stack!\n";
			return 0;
		}
		return top->data;
	}
	bool isEmpty()
	{
		if (!top)
			return true;
		return false;
	}
	void print()
	{
		Node<T>* curr = top;
		while (curr)
		{
			cout << curr->data << ' ';
			curr = curr->next;
		}
	}
};
template <typename T>
class Queue
{
	Node<T>* head;
	Node<T>* tail;
public:
	Queue()
	{
		head = NULL;
		tail = NULL;
	}
	void enqueue(T data)
	{
		if (!head)
		{
			head = new Node<T>(data);
			tail = head;
			return;
		}
		Node<T>* temp = new Node<T>(data);
		tail->next = temp;
		tail = temp;
	}
	T dequeue()
	{
		if (!head)
		{
			cout << "Error, Queue Empty!\n";
			return 0;
		}
		Node<T>* temp = head;
		head = head->next;
		T temp_data = temp->data;
		delete temp;
		return temp_data;
	}
	T peek()
	{
		if (!head)
		{
			cout << "Error, Queue Empty!\n";
			return 0;
		}
		return head->data;
	}
	bool isEmpty()
	{
		if (!head)
			return true;
		return false;
	}
	void print()
	{
		Node<T>* curr = head;
		while (curr)
		{
			cout << curr->data << ' ';
			curr = curr->next;
		}
	}
};

// + - * / ^ ( ) 
bool prcd(char op1, char op2)
{
	switch (op2)
	{
	case '(':
		if(op1 != ')')
			return false;
		return true;
		break;
	case ')':
		if (op1 != '(')
			return true;
		return false;
		break;
	}
	switch (op1)
	{
	case '(':
		return false;
		break;
	case ')':
		cout << "SUUS" << endl;
		break;
	case '-':
		if (op2 == '-')
			return true;
		return false;
		break;
	case '+':
		if (op2 == '+')
			return true;
		return false;
		break;
	case '/':
		if (op2 == '+' || op2 == '-' || op2 == '/')
			return true;
		return false;
		break;
	case '*':
		if (op2 == '+' || op2 == '-' || op2 == '*')
			return true;
		return false;
		break;
	case '^':
	case '$':
			return true;
		break;
	default:
		cout << "Wrong OPERATOR ;/";
		break;
	}
}

bool opr_check(char x)
{
	if (x == '+' || x == '-' || x == '*' || x == '/' || x == '^' || x == '$' || x == '(' || x == ')')
		return true;
	return false;
}

string postfixer(string expression)
{
	Stack<char> stk;
	string ans = "";
	int size = 0;
	int brkt_count = 0;
	while (expression[size] != '\0')
	{
		if (expression[size] != ' ')
		{
			if (expression[size] == '(')
				brkt_count++;
			if (!opr_check(expression[size]))
				ans += expression[size];
			else
			{
				while (!stk.isEmpty() && prcd(stk.peek(), expression[size]))
					ans += stk.pop();
				if (expression[size] != ')')
					stk.push(expression[size]);
				else
				{
					stk.pop();
					brkt_count--;
				}
			}
			while (expression[size + 1] == '\0' && !stk.isEmpty())
				ans += stk.pop();
		}
		size++;
	}
	if(brkt_count != 0)
		return "Invalid Expression!";
	return ans;
}

string reverse_str(string str)
{
	Stack<char> stk;
	string ans = "";
	for (int i = 0; str[i] != '\0'; i++)
		stk.push(str[i]);
	while (!stk.isEmpty())
		ans += stk.pop();
	return ans;
}

string prefixer(string expression)
{
	expression = reverse_str(expression);
	for (int i = 0; expression[i] != '\0'; i++)
	{
		if (expression[i] == '(')
			expression[i] = ')';
		else if (expression[i] == ')')
			expression[i] = '('; 
	}
	string temp = postfixer(expression);
	if(temp != "Invalid Expression!")
		return reverse_str(temp);
	return temp;
}

string eval_func(string num1, char opr, string num2)
{
	string ans = "";
	int n_ans;
	int n1 = 0, n2 = 0;
	for (int i = 0; num1[i] != '\0'; i++)
		n1 = n1 * 10 + (num1[i] - '0');
	for (int i = 0; num2[i] != '\0'; i++)
		n2 = n2 * 10 + (num2[i] - '0');
	switch (opr)
	{
	case '+':
		n_ans = n1 + n2;
		break;
	case '-':
		n_ans = n1 - n2;
		break;
	case '*':
		n_ans = n1 * n2;
		break;
	case '/':
		n_ans = n1 / n2;
		break;
	case '^':
	case '$':
		n_ans = pow(n1, n2);
		break;
	default:
		cout << "Wrong OPERATOR ;/";
		break;
	}
	while (n_ans)
	{
		ans += (n_ans % 10) + '0';
		n_ans /= 10;
	}
	return reverse_str(ans);
}

string infixer(string expression)
{
	if (expression == "Invalid Expression!")
		return expression;
	Stack<string> stk;
	int size = 0;
	string ans;
	bool prefix = false, eval = true;
	if (opr_check(expression[size]))
	{
		expression = reverse_str(expression);
		prefix = true;
	}
	for (int i = 0; expression[i] != '\0'; i++)
		if ((expression[i] >= 'a' && expression[i] <= 'z') || (expression[i] >= 'A' && expression[i] <= 'Z'))
			eval = false;
	
	while (expression[size] != '\0')
	{
		string temp_str = "";
		if (expression[size] != ' ')
		{
			if (!opr_check(expression[size]))
			{
				temp_str += expression[size];
				stk.push(temp_str);
			}
			else
			{
				string num1 = stk.pop();
				string num2 = stk.pop();
				if (!eval)
				{
					temp_str += '(';
					temp_str += num2;
					temp_str += expression[size];
					temp_str += num1;
					temp_str += ')';
					stk.push(temp_str);
				}
				else
				{
					if (!prefix)
						stk.push(eval_func(num2, expression[size], num1));
					else
						stk.push(eval_func(num1, expression[size], num2));
				}
			}
		}
		size++;
	}
	ans = stk.pop();
	if (prefix && !eval)
	{
		ans = reverse_str(ans);
		for (int i = 0; ans[i] != '\0'; i++)
		{
			if (ans[i] == '(')
				ans[i] = ')';
			else if (ans[i] == ')')
				ans[i] = '(';
		}
	}
	return ans;
}

void read_file(string filename)
{
	ifstream file;
	file.open(filename);
	string str;
	bool start = false, head = false, postfix = false, prefix = false, infix = false;
	Stack<string> stk;
	while (getline(file, str))
	{
		if (str == "|start|")
			start = true;
		else if (str == "|\\start|")
			start = false;
		if (start)
		{
			if (str == "|head|")
				head = true;
			else if (str == "|\\head|")
				head = false;
			else if (str == "|postfix|")
				postfix = true;
			else if (str == "|\\postfix|")
				postfix = false;
			else if (str == "|prefix|")
				prefix = true;
			else if (str == "|\\prefix|")
				prefix = false;
			else if (str == "|infix|")
				infix = true;
			else if (str == "|\\infix|")
				infix = false;
			else if (head)
				cout << str << endl;
			else if (postfix)
				cout << postfixer(str) << endl;
			else if (prefix)
				cout << prefixer(str) << endl;
			else if (infix)
				cout << infixer(str) << endl;
		}
	}
	file.close();
}