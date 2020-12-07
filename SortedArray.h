#pragma once
#include "Sequence.h"
#include "DynamicArray.h"
#include "Sorts.h"
#include "Comp.h"

template <class TKey, class TItem>
bool lowerPair(pair<TKey, TItem> first, pair<TKey, TItem> second) {
	return first.first < second.first;
}

template <class T>

class SortedArray : public Sequence<T> {
private:
	DynamicArray<T>* items;
	int size;
public:
	// Конструкторы
	SortedArray(int size) {
		int current_size;
		if (size < 0) {
			std::cout << "WARNING!!! INPUTED SIZE < 0. IT WAS SETTED TO 1" << std::endl;
			current_size = 1;
		}
		else
			current_size = size;
		this->items = new DynamicArray<T>(current_size);
		this->size = size;
		this->items = new DynamicArray<T>(size);
	};

	SortedArray(int size, DynamicArray<T>* items) {
		this->size = size;
		this->items = new DynamicArray<T>(size);
		for (int i = 0; i < size; i++) {
			this->items->Set(i, items->Get(i));
		}
	};

	SortedArray(const SortedArray<T>& tocopy) {
		this->size = tocopy.size;
		this->items = new DynamicArray(tocopy.items);
	};

	// Получение размера последовательности
	virtual int GetSize() const override {
		return this->items->GetSize();
	};

	// Получение элемента последовательности по индексу
	virtual T Get(const int index) const override {
		return this->items->Get(index);
	};

	// Получение последнего элемента последовательности
	virtual T GetLast() const override {
		return this->items->GetLast();
	};

	// Получение первого элемента последовательности
	virtual T GetFirst() const override {
		return this->items->GetFirst();
	};


	void Add(T item) {
		/*
		if (this->size == 0) {
			this->Prepend(item);
		}
		else 
		{
			if (item < this->GetFirst()) {
				this->Append(item);
				return;
			}
			else if (item > this->GetLast()) {
				this->Prepend(item);
				return;
			}
			else
				for (int i = 1; i < this->size - 1; i++) 
				{
					if (item < this->Get(i)) 
					{
						this->Insert(i, item);
						return;
					}
				}
		}
		*/
		this->Prepend(item);
		quickSorter<T>* qsorter = new quickSorter<T>();
		qsorter->Sort(this, lowerPair);
		delete qsorter;
	}
	// Установка / изменение элемента по индексу
	void Set(int index, T item) override {
		this->items->Set(index, item);
	};

	// Добавление элемента в начало
	virtual void Append(T item) override {
		DynamicArray<T>* temp = new DynamicArray<T>(this->GetSize() + 1);
		for (int i = 1; i < this->size + 1; i++) {
			temp->Set(i, this->items->Get(i - 1));
		}
		temp->Set(0, item);
		if (this->size != 0)
			delete this->items;
		++this->size;
		
		this->items = temp;
	};

	// Добавление элемента в конец
	virtual void Prepend(T item) override {
		DynamicArray<T>* temp = new DynamicArray<T>(this->GetSize() + 1);
		for (int i = 0; i < this->size; i++) {
			temp->Set(i, this->items->Get(i));
		}
		temp->Set(this->GetSize(), item);
		if (this->size != 0)
			delete this->items;
		++this->size;
		
		this->items = temp;
	};

	// Добавление элемента по индексу
	virtual void Insert(int index, T item) override {
		DynamicArray<T>* temp = new DynamicArray<T>(this->GetSize() + 1);
		for (int i = 0; i < index; i++) {
			temp->Set(i, this->items->Get(i));
		}
		temp->Set(index, item);
		for (int i = index + 1; i < this->GetSize() + 1; i++) {
			temp->Set(i, this->items->Get(i - 1));
		}
		if (this->size != 0)
			delete this->items;
		++this->size;
		
		this->items = temp;
	};

	// Удаление элемента по иднексу
	virtual void RemoveAt(int index) override {
		if (index < 0 || index >= this->size)
			throw std::exception("INDEX ERROR: Index out of range");
		DynamicArray<T>* temp;
		temp = new DynamicArray<T>(this->size - 1);
		for (int i = 0; i < index; i++) {
			temp->Set(i, this->items->Get(i));
		}
		for (int i = index + 1; i < this->size; i++) {
			temp->Set(i, this->items->Get(i));
		}
		delete items;
		--this->size;
		this->items = temp;
		quickSorter<T>* qsorter = new quickSorter<T>();
		qsorter->Sort(this, lowerPair);
		delete qsorter;
		delete temp;
	};

	// Удаление элемента по значению
	virtual void Remove(T item) override {
		for (int i = 0; i < this->size; i++) {
			if (this->items->Get(i) == item) {
				RemoveAt(i);
				break;
			}
		}
	};

	// Удаление всех одинаковых элементов
	virtual void RemoveAll(T item) override {
		int tempsize = this->size;
		for (int i = 0; i < tempsize; i++) {
			if (this->items->Get(i) == item) {
				RemoveAt(i);
				tempsize--;
				i--;
			}
		}
	};

	// Копирование последовательности
	virtual Sequence<T>* Copy() override {
		SortedArray<T>* copy;
		copy = new SortedArray<T>(this->items->GetSize(), this->items);
		return copy;
	};

	// Получение подпослед. по индексам
	virtual Sequence<T>* GetSubSequence(int start, int end) override {
		if (start < 0 || start >= this->size || end < 0 || end >= this->size)
			throw std::exception("INDEX ERROR: Index out of range");
		SortedArray<T>* subseq;
		subseq = new SortedArray(end - start + 1);
		int previndex = 0;
		for (int i = start; i < end; i++) {
			subseq->items->Set(previndex, this->items->Get(i));
			++previndex;
		}
		return subseq;
	};

	// Объединение двух последовательностей
	virtual Sequence<T>* Concat(Sequence<T>* toConcat) override {
		SortedArray<T>* conc;
		conc = new SortedArray<T>(this->size + toConcat->GetSize());
		for (int i = 0; i < this->size; i++) {
			conc->items->Set(i, this->items->Get(i));
		}
		for (int i = 0; i < toConcat->GetSize(); i++) {
			conc->items->Set(this->size + i, toConcat->Get(i));
		}
		return conc;
	};
};