#pragma once
#include <iostream>

template <typename T>
class linkedList
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
	int size;
	void free();
	void copyList(const linkedList<T>& otherList);

public:

	class listIterator
	{
	private:
		friend class linkedList<T>; // ????!?!?!?!?
		Box* currentPosition;
		linkedList<T>* owner;
		listIterator(Box* position, linkedList<T>* list):currentPosition(position), owner(list)
		{}

	public:

		listIterator(linkedList<T> list);
		listIterator& operator++();
		//listIterator operator++(int a);
		T& operator*();
		bool operator==(const listIterator& right);
		bool operator!=(const listIterator& right);
		operator bool() const;
	};

	linkedList():first(NULL), last(NULL), size(0)
	{}

	linkedList(const linkedList<T>& other);

	linkedList<T>& operator=(const linkedList<T>& other);

	linkedList<T>& operator+=(const linkedList<T>& other);

	~linkedList();
public:

	listIterator begin(); 
	listIterator end();
	bool isEmpty() const;
	void pushBack(const T& );
	void pushFront(const T& );
	T peekFront();
	T peekBack();
	T peekAt(listIterator iter);
//	bool popBack();// this is not a constant operation => I don't need it :D
	void popFront();
	void popAfter(listIterator iter); // &&& mestq iteratora!!
	void removeElement(T&);
	int getSize() const;
};

template<typename T>
void linkedList<T>::free()
{
	while(first)
	{
		Box* nextBox = first->next;
		delete first;
		first = nextBox;
	}	
	first = NULL;
	last = NULL;
}

template<typename T>
void linkedList<T>::copyList(const linkedList<T>& otherList)
{	
	//fucking suspicious
	if(otherList.first == NULL || otherList.size <= 0)
	{
		first = last = NULL;
		size = 0;
	}
	else
	{
		first = new Box(*(otherList.first));

		Box* currentOther = otherList.first;
		Box* currentThis = first;

		while(currentOther->next != NULL)
		{			
			currentThis->next = new Box(*(currentOther->next));

			currentThis = currentThis->next;
			currentOther = currentOther->next;
		}

		last = currentThis;
		size = otherList.size;
	}
}

template<typename T>
linkedList<T>::linkedList(const linkedList<T>& other)
{
	copyList(other);
}

template<typename T>
linkedList<T>& linkedList<T>::operator=(const linkedList<T>& other)
{
	if(this != &other)
	{
		free();
		copyList(other);
	}
	return *this;
}

template <class T>
linkedList<T>& linkedList<T>::operator+=(const linkedList<T>& other)
{
	if(!other.first || this == &other)
		return *this;

	Box* current = other.first;
	while(current->next)
	{
		pushBack(current->data);
		current = current->next;
	}
	pushBack(current->data);
	return *this;
}

template<typename T>
linkedList<T>::~linkedList()
{
	while(first)
	{
		Box* nextBox = first->next;
		delete first;
		first = nextBox;
	}
}

template<typename T>
typename linkedList<T>::listIterator linkedList<T>::begin() 
{
	return listIterator(first, this);
}

template<typename T>
typename linkedList<T>::listIterator linkedList<T>::end()  
{
	if(!last)
		return listIterator(NULL, this);
	return listIterator(last->next, this); 
}

template<typename T>
linkedList<T>::listIterator::listIterator(linkedList<T> list)
{
	currentPosition = list.first;
	owner = list;
}

template<typename T>
typename linkedList<T>::listIterator& linkedList<T>::listIterator::operator++()
{
	if(currentPosition)
		currentPosition = currentPosition->next;
	return *this;
}

//template<typename T>
//typename linkedList<T>::listIterator linkedList<T>::listIterator::operator++(int a)
//{
//	linkedList<T>::listIterator(*this) iterator;
//	++(*this); //?!?!?
//	return iterator;
//}

template<typename T>
typename T& linkedList<T>::listIterator::operator*()
{
	if(!currentPosition)
		throw "Invalid position for the iterator to call operator*!\n";
	return currentPosition->data;
}

template<typename T>
bool linkedList<T>::listIterator::operator==(const listIterator& right)
{
	return (owner == right.owner && currentPosition == right.currentPosition);
}

template<typename T>
bool linkedList<T>::listIterator::operator!=(const listIterator& right)
{
	return !(*this == right);
}

template<typename T>
linkedList<T>::listIterator::operator bool() const
{
	return currentPosition != NULL;
}


template <typename T>
void linkedList<T>::pushBack(const T& info)
{
	Box* newBox = new Box(info);
	if(first == NULL)
		first = newBox;
	else
		last->next = newBox;
	last = newBox;
	size++;
}

template <typename T>
void linkedList<T>::pushFront(const T& info)
{
	Box* newBox = new Box(info);
	if(first == NULL)
	{
		first = newBox;
		last = newBox;
	}
	else
	{
		newBox->next = first;
		first = newBox;
	}		
	size++;
}

template <typename T>
T linkedList<T>::peekFront()
{
	if(first)
		return first->data;
	else
		throw "List is empty! There is nothing to peek!";
}

template <typename T>
T linkedList<T>::peekBack()
{
	if(last)
		return last->data;
	else
		throw "List is empty! There is nothing to peek!";
}

template<typename T>
void linkedList<T>::popFront()
{
	if(!first)
		throw "List is Empty! There is nothing to pop!";
	

	Box* forDelete = first;
	first = first->next;
	delete forDelete;
	if(first == NULL)
		last = NULL;
	size--;

}

template<typename T>
void linkedList<T>::removeElement(T& elem)//no precautions taken, may be a dangerous function to call...
{
	if(elem == first->data)
	{
		popFront();
		return;
	}
	for(linkedList<T>::listIterator iter = begin(); iter != end(); ++iter)
	{
		if(iter.currentPosition->next && iter.currentPosition->next->data == elem) 
		{
			popAfter(iter);
			return;
		}
	}

}
template<typename T>
void linkedList<T>::popAfter(listIterator iter)
{
	if(!iter.currentPosition || !iter.currentPosition->next)
		throw "Trying to pop after last! Impossibru !";

	// If last element pop...
	if (last == iter.currentPosition->next)
		last = iter.currentPosition;

	Box* current = iter.currentPosition;
	++iter;
	
	current->next = iter.currentPosition->next;
	delete iter.currentPosition;
	size--;
}

template<typename T>
bool linkedList<T>::isEmpty() const
{
	return first == NULL;
}

template<typename T>
T linkedList<T>::peekAt(listIterator iter)
{
	return iter.currentPosition->data;
}

template<typename T>
int linkedList<T>::getSize() const
{
	return size;
}