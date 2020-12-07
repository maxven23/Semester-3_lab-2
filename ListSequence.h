#pragma once
#include "Sequence.h"
#include "LinkedList.h"

template <class T>

class ListSequence : public Sequence<T> {
private:
	LinkedList<T>* items;
	int size;
public:
	// Конструкторы
	ListSequence() {
		this->items = new LinkedList<T>();
		this->size = 0;
	};

	ListSequence(LinkedList<T>* items, int size) {
		this->size = size;
		this->items = new LinkedList<T>();
		for (int i = 0; i < size; i++) {
			this->Prepend(items->Get(i));
		}
	};

	ListSequence(T* items, int count) {
		this->items = new LinkedList<T>(items, count);
	};

	ListSequence(const ListSequence<T>& list) {
		this->size = list.size;
		this->items = new LinkedList<T>(list.GetSize());
		for (int i = 0; i < list.GetSize(); i++) {
			this->Prepend(list.Get(i));
		}
	};

	// Получение длины послед.
	virtual int GetSize() const override {
		return this->items->GetSize();
	};

	// Получение элемента послед. по индексу
	virtual T Get(const int index) const override {
		if (index < 0 || index > this->size)
			throw std::exception("INDEX ERROR: Index out of range");
		return this->items->Get(index);
	};

	// Получение последнего элемента послед.
	virtual T GetLast() const override {
		return this->items->GetLast();
	};

	// Получение первого элемента послед.
	virtual T GetFirst() const override {
		return this->items->GetFirst();
	};

	virtual void Set(int index, T item) override {
		this->items->Set(index, item);
	}

	// Добавление элемента в начало
	virtual void Append(T item) override {
		this->items->Append(item);
		++this->size;
	};

	// Добавление элемента в конец
	virtual void Prepend(T item) override {
		this->items->Prepend(item);
		++this->size;
	};

	// Добавление элемента по индексу
	virtual void Insert(int index, T item) override {
		this->items->InsertAt(item, index);
		++this->size;
	};


	// Удаление элемента по индексу
	virtual void RemoveAt(int index) override {
		if (index < 0 || index >= this->size)
			throw std::exception("INDEX ERROR: Index out of range");
		this->items->RemoveAt(index);
		--this->size;
	};

	// Удаление элемента по значению
	virtual void Remove(T item) override {
		for (int i = 0; i < this->size; i++) {
			if (this->items->Get(i) == item) {
				this->items->RemoveAt(i);
				break;
			}
		}
		--this->size;
	};

	// Удаление всех элементов по значению
	virtual void RemoveAll(T item) override {
		for (int i = 0; i < this->size; i++) {
			if (this->items->Get(i) == item) {
				RemoveAt(i);
				i--;
			}
		}
	};

	// Объединение послед.
	virtual Sequence<T>* Concat(Sequence<T>* toConcat) override {
		ListSequence<T>* tempList;
		tempList = new ListSequence<T>();
		T* temp;
		temp = new T[this->GetSize() + toConcat->GetSize()];
		for (int i = 0; i < this->GetSize(); i++) {
			temp[i] = this->Get(i);
		}
		for (int i = 0; i < toConcat->GetSize(); i++) {
			temp[i + this->GetSize()] = toConcat->Get(i);
		}
		for (int i = 0; i < this->GetSize() + toConcat->GetSize(); i++) {
			tempList->Prepend(temp[i]);
		}
		return tempList;
	};

	// Получение подпослед. по индексам
	virtual Sequence<T>* GetSubSequence(int start, int end) override {
		if (start < 0 || start >= this->size || end < 0 || end >= this->size || end < start)
			throw std::exception("INDEX ERROR: Index out of range");
		ListSequence<T>* newList;
		newList = new ListSequence();
		newList->items = this->items->GetSubList(start, end);
		newList->size = newList->GetSize();
		this->size = newList->GetSize();
		return newList;
	};

	// Копирование послед.
	virtual Sequence<T>* Copy() override {
		ListSequence<T>* copy;
		copy = new ListSequence<T>();
		for (int i = 0; i < this->size; i++) {
			copy->items->Prepend(this->Get(i));
		}
		return copy;
	};

	void Print() {
		for (int i = 0; i < this->GetSize(); i++) {
			std::cout << "#" << i + 1 << ": " << this->Get(i) << std::endl;
		}
	}

	// Деструктор
	~ListSequence() {
		delete this->items;
	};
};