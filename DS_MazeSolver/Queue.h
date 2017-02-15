#pragma once
#include <iostream>

template <typename T>
class queue
{
private:

	struct Box
	{
		T data;
		Box* next;
		Box(const T& data):data(data), next(NULL)
		{} 
		Box(const Box& other)
		{
			data = other.data;
			if(other.next != NULL)
			{
				next = new Box(*(other.next));
			}
			else
				next = NULL;
		}
	};

	Box* first, *last;
	int length;

	void free();
	void copyQueue(const queue<T>& otherQueue);
 
public:

	queue():first(NULL), last(NULL), length(0) {}
	queue(const queue<T>& other);
	queue<T>& operator=(const queue<T>& other);
	~queue();

public:

	bool isEmpty() const;
	void enqueue(const T& ); //aka pushBack
	T peek(); //aka peekFront
	void dequeue(); //aka popFront
	int getLength() const;
};

template<typename T>
void queue<T>::free()
{
	while(first)
	{
		dequeue();
	}	
	first = NULL;
	last = NULL;
}

template<typename T>
void queue<T>::copyQueue(const queue<T>& otherQueue)
{
	if(otherQueue.first == NULL)
	{
		first = last = NULL;
		length = otherQueue.length;
	}
	else
	{
		first = new Box(*(otherQueue.first));
		/*Box* current = first;
		while(current->next != NULL)
		{
			current = current->next;
		}
		last = current;*/

		Box* currentOther = otherQueue.first;
		Box* currentThis = first;

		while(currentOther->next != NULL)
		{			
			currentThis->next = new Box(*(currentOther->next));

			currentThis = currentThis->next;
			currentOther = currentOther->next;
		}

		last = currentThis;
		length = otherQueue.length;
	}
}

template<typename T>
queue<T>::queue(const queue<T>& other)
{
	copyQueue(other);
}

template<typename T>
queue<T>& queue<T>::operator=(const queue<T>& other)
{
	if(this != &other)
	{
		free();
		copyQueue(other);
	}
	return this;
}

template<typename T>
queue<T>::~queue()
{
	while(first)
	{
		Box* nextBox = first->next;
		delete first;
		first = nextBox;
	}
}

template <typename T>
void queue<T>::enqueue(const T& info)
{
	Box* newBox = new Box(info);
	if(first == NULL)
		first = newBox;
	else
		last->next = newBox;
	last = newBox;
	length++;
}

template <typename T>
T queue<T>::peek()
{
	if(first)
		return first->data;
	else
		throw "List is empty! There is nothing to peek!";
}

template<typename T>
void queue<T>::dequeue()
{
	if(!first)
		throw "List is Empty! There is nothing to pop!";
	Box* forDelete = first;
	first = first->next;
	delete forDelete;
	length--;
}

template<typename T>
bool queue<T>::isEmpty() const
{
	return first == NULL;
}

template<typename T>
int queue<T>::getLength() const
{
	return length;
}