#pragma once
#include "Sequence.h"
#include "DynamicArray.h"

template <class T>

class ArraySequence : public Sequence<T> {
private:
	DynamicArray<T>* items;
	int size;
public:
	// Конструкторы
	ArraySequence(int size) {
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

	ArraySequence(int size, DynamicArray<T>* items) {
		this->size = size;
		this->items = new DynamicArray<T>(size);
		for (int i = 0; i < size; i++) {
			this->items->Set(i, items->Get(i));
		}
	};

	ArraySequence(const ArraySequence<T>& tocopy) {
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
		for (int i = 0; i < index - 1; i++) {
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
		delete[] temp;
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
		ArraySequence<T>* copy;
		copy = new ArraySequence<T>(this->items->GetSize(), this->items);
		return copy;
	};

	// Получение подпослед. по индексам
	virtual Sequence<T>* GetSubSequence(int start, int end) override {
		if (start < 0 || start >= this->size || end < 0 || end >= this->size)
			throw std::exception("INDEX ERROR: Index out of range");
		ArraySequence<T>* subseq;
		subseq = new ArraySequence(end - start + 1);
		int previndex = 0;
		for (int i = start; i < end; i++) {
			subseq->items->Set(previndex, this->items->Get(i));
			++previndex;
		}
		return subseq;
	};

	// Объединение двух последовательностей
	virtual Sequence<T>* Concat(Sequence<T>* toConcat) override {
		ArraySequence<T>* conc;
		conc = new ArraySequence<T>(this->size + toConcat->GetSize());
		for (int i = 0; i < this->size; i++) {
			conc->items->Set(i, this->items->Get(i));
		}
		for (int i = 0; i < toConcat->GetSize(); i++) {
			conc->items->Set(this->size + i, toConcat->Get(i));
		}
		return conc;
	};
	/*
	void qsortRecursive(ArraySequence<T>* mas, int size) {

		int i = 0;
		int j = size - 1;

		int mid = mas->Get(size / 2);

		//Делим массив
		do {
			//Пробегаем элементы, ищем те, которые нужно перекинуть в другую часть
			//В левой части массива пропускаем(оставляем на месте) элементы, которые меньше центрального
			while (mas->Get(i) < mid) {
				i++;
			}
			//В правой части пропускаем элементы, которые больше центрального
			while (mas->Get(j) > mid) {
				j--;
			}

			if (i <= j) {
				T tmp = mas->Get(i);
				mas->Set(i, mas->Get(j));
				mas->Set(j, tmp);

				i++;
				j--;
			}
		} while (i <= j);

		if (j > 0) {
			qsortRecursive(mas, j + 1);
		}
		if (i < size) {
			qsortRecursive(mas->GetSubSequence(mas->Get(i), mas->GetSize()), size - i);
		}
	}
	*/
};