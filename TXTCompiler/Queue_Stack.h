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
	bool remove(T data)
	{
		if (!top)
			return false;
		Node<T>* curr = top;
		if (top->data == data)
		{
			top = top->next;
			delete curr;
			return true;
		}
		while (curr->next)
		{
			if (curr->next->data == data)
			{
				Node<T>* temp = curr->next;
				curr->next = curr->next->next;
				delete temp;
				return true;
			}
			curr = curr->next;
		}
		return false;
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
	~Stack()
	{
		while (top)
		{
			Node<T>* temp = top;
			top = top->next;
			delete temp;
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
	void insert_on_priority(T F)
	{
		if (!head)
		{
			head = new Node<T>(F);
			tail = head;
			return;
		}
		Node<T>* curr = head;
		if (head->data.priorty < F.priorty)
		{
			Node<T>* temp = new Node<T>(F);
			temp->next = head;
			head = temp;
			return;
		}
		while (curr->next)
		{
			if (curr->next->data.priorty < F.priorty)
			{
				Node<T>* temp = new Node<T>(F);
				temp->next = curr->next;
				curr->next = temp;
				return;
			}
			curr = curr->next;
		}
		Node<T>* temp = new Node<T>(F);
		curr->next = temp;
		tail = temp;
	}
	T dequeue()
	{
		if (!head)
		{
			cout << "Error, Queue Empty!\n";
			return T();
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
			cout << curr->data << endl;
			curr = curr->next;
		}
	}
	void remove(T data)
	{
		if (!head)
			return;
		Node<T>* curr = head;
		if (head->data == data)
		{
			head = head->next;
			delete curr;
			return;
		}
		while (curr->next)
		{
			if (curr->next->data == data)
			{
				Node<T>* temp = curr->next;
				curr->next = curr->next->next;
				delete temp;
				return;
			}
			curr = curr->next;
		}
	}
	~Queue()
	{
		while (head)
		{
			Node<T>* temp = head;
			head = head->next;
			delete temp;
		}
	}
};

//Priorty Queue with max 4 size
template <typename T>
class PriortyQueue
{
	Node<T>* head;
	Node<T>* tail;
	int count;
	int size;
public:
	PriortyQueue()
	{
		head = NULL;
		tail = NULL;
		count = 0;
		size = 4;
	}
	PriortyQueue(int size)
	{
		head = NULL;
		tail = NULL;
		count = 0;
		this->size = size;
	}
	void enqueue(T data)
	{
		if (count == size)
		{
			cout << "Error, Queue Full!\n";
			return;
		}
		if (!head)
		{
			head = new Node<T>(data);
			tail = head;
			count++;
			return;
		}
		Node<T>* curr = head;
		if (head->data.priorty < data.priorty)
		{
			Node<T>* temp = new Node<T>(data);
			temp->next = head;
			head = temp;
			count++;
			return;
		}
		while (curr->next)
		{
			if (curr->next->data.priorty < data.priorty)
			{
				Node<T>* temp = new Node<T>(data);
				temp->next = curr->next;
				curr->next = temp;
				count++;
				return;
			}
			curr = curr->next;
		}
		Node<T>* temp = new Node<T>(data);
		curr->next = temp;
		tail = temp;
		count++;
	}
	T dequeue()
	{
		if (!head)
		{
			cout << "Error, Queue Empty!\n";
			return T();
		}
		Node<T>* temp = head;
		head = head->next;
		T temp_data = temp->data;
		count--;
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
	void remove(T data)
	{
		if (!head)
		{
			cout << "Error, Queue Empty!\n";
			return;
		}
		Node<T>* curr = head;
		if (head->data == data)
		{
			head = head->next;
			delete curr;
			count--;
			return;
		}
		while (curr->next)
		{
			if (curr->next->data == data)
			{
				Node<T>* temp = curr->next;
				curr->next = curr->next->next;
				delete temp;
				count--;
				return;
			}
			curr = curr->next;
		}
		cout << "Error, Data not found!\n";
	}
	bool isEmpty()
	{
		if (!head)
			return true;
		return false;
	}
	bool find(T data)
	{
		if (!head)
		{
			cout << "Error, Queue Empty!\n";
			return false;
		}
		Node<T>* curr = head;
		while (curr)
		{
			if (curr->data == data)
				return true;
			curr = curr->next;
		}
		return false;
	}
	void set_size(int size)
	{
		this->size = size;
	}
	int get_size()
	{
		return size;
	}
	int get_count()
	{
		return count;
	}
	void print()
	{
		Node<T>* curr = head;
		while (curr)
		{
			cout << curr->data << endl;
			curr = curr->next;
		}
	}
	~PriortyQueue()
	{
		while (head)
		{
			Node<T>* temp = head;
			head = head->next;
			delete temp;
		}
	}
};

struct file_data
{
	string filename;
	int priorty;
	friend ostream& operator<<(ostream& out, const file_data& data)
	{
		out << data.filename << " " << data.priorty;
		return out;
	}
	bool operator==(const file_data& data)
	{
		if (filename == data.filename && priorty == data.priorty)
			return true;
		return false;
	}
};

class LRU
{
	PriortyQueue<file_data> priorityQ;
	Queue<file_data> LRU_Q;
	int faults;
	int hits;
	int size;
	int count;
public:
	LRU(int size)
	{
		faults = 0;
		hits = 0;
		this->size = size;
		count = 0;
	}
	void add(file_data data)
	{
		if (priorityQ.find(data))
		{
			hits++;
			LRU_Q.remove(data);
			LRU_Q.enqueue(data);
			return;
		}
		if (count == size)
		{
			file_data temp = LRU_Q.dequeue();
			priorityQ.remove(temp);
			count--;
		}
		faults++;
		priorityQ.enqueue(data);
		LRU_Q.enqueue(data);
		count++;
	}
	void print()
	{
		cout << "Hits: " << hits << endl;
		cout << "Faults: " << faults << endl;
		cout << "PP" << endl;
		priorityQ.print();
		cout << "LL" << endl;
		LRU_Q.print();
	}
};