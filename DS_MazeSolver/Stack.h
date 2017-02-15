#pragma once
#include <iostream>

template<typename T>
struct box
{
	T data;
	box<T>* previous;
};

template<typename T>
class Stack
{
	box<T>* top;
	void copyStack(const Stack<T>& st);

public:
	Stack();
	Stack(const Stack<T>& );
	Stack operator=(const Stack<T>& );
	~Stack();

	bool isEmpty() const;
	void push(const T& newElem);
	void pop();
	T peek();
};

template<typename T>
Stack<T>::Stack():top(NULL){}

template<typename T>
void Stack<T>::copyStack(const Stack<T>& right)
{
	box<T>* current = right.top;
	if(!current)
		top = NULL;
	else
	{
		top = new box<T>;
		top->data = current->data;
		top->previous = NULL;
		box<T>* prev = top;
		while(current)
		{
			box<T>* newBox = new box<T>;
			newBox->data = current->data;
			newBox->previous = NULL;
			prev->previous = newBox;
			prev = newBox;
			current = current->previous;
		}
	}
}

template<typename T>
Stack<T>::Stack(const Stack<T>& other)
{
	copyStack(other);
}

template<typename T>
Stack<T> Stack<T>::operator=(const Stack<T>& other)
{
	if(this != &other)
	{
		copyStack(other);
	}
	return *this;
}

template<typename T>
Stack<T>::~Stack()
{
	while(top)
	{
		pop();
		/*box<T>* prev = top->previous;
		delete [] top;
		top = prev;*/
	}
}

template<typename T>
bool Stack<T>::isEmpty() const
{
	return top == NULL;
}

template<typename T>
void Stack<T>::push(const T& newElement)
{
	box<T>* ptrNewBox = new box<T>;
	ptrNewBox->data = newElement;
	ptrNewBox->previous = top;
	top = ptrNewBox;
}

template<typename T>
void Stack<T>::pop()
{
	if(isEmpty())
		throw "Stack is empty! You cannot pop an empty stack!";
	box<T>* prev = top->previous;
	delete [] top;
	top = prev;
}

template<typename T>
T Stack<T>::peek()
{
	if(isEmpty())
		throw "Stack is empty! There is nothing to peek!";
	return top->data;
}