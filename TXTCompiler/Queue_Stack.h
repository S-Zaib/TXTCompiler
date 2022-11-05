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
