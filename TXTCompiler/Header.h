#pragma once
#include <iostream>
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
			return true;
		break;
	default:
		cout << "Wrong OPERATOR ;/";
		break;
	}
}

bool opr_check(char x)
{
	if (x == '+' || x == '-' || x == '*' || x == '/' || x == '^' || x == '(' || x == ')')
		return true;
	return false;
}

string postfixer(string expression)
{
	Stack<char> stk;
	string ans = "";
	int size = 0;
	while (expression[size] != '\0')
	{
		if (expression[size] != ' ')
		{
			if (!opr_check(expression[size]))
				ans += expression[size];
			else
			{
				while (!stk.isEmpty() && prcd(stk.peek(), expression[size]))
					ans += stk.pop();
				if (expression[size] != ')')
					stk.push(expression[size]);
				else
					stk.pop();
			}
			while (expression[size + 1] == '\0' && !stk.isEmpty())
				ans += stk.pop();
		}
		size++;
	}
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
	return reverse_str(postfixer(expression));
}

string infixer(string expression)
{
	Stack<string> stk;
	int size = 0;
	string ans;
	bool prefix = false;
	if (opr_check(expression[size]))
	{
		expression = reverse_str(expression);
		prefix = true;
	}
		
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
				string op1 = stk.pop();
				string op2 = stk.pop();
				temp_str += '(';
				temp_str += op2;
				temp_str += expression[size];
				temp_str += op1;
				temp_str += ')';
				stk.push(temp_str);
			}
		}
		size++;
	}
	ans = stk.pop();
	if (prefix)
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