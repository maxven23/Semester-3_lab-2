#pragma once

template <class T> 

class Sequence 
{
public:
	// Получение подпослед. / копирование послед. / объединение послед.
	virtual Sequence<T>* GetSubSequence(int start, int end) = 0;
	virtual Sequence<T>* Copy() = 0;
	virtual Sequence<T>* Concat(Sequence<T>* toConcat) = 0;

	// Основные функции декомпозиции
	virtual int GetSize() const = 0;
	virtual T Get(int index) const = 0;
	virtual T GetLast() const = 0;
	virtual T GetFirst() const = 0;

	// Основные операции (не требуются в представлении)
	virtual void Set(int index, T item) = 0;
	virtual void Append(T item) = 0;
	virtual void Prepend(T item) = 0;
	virtual void Insert(int index,  T item) = 0;
	virtual void Remove(T item) = 0;
	virtual void RemoveAll(T item) = 0;
	virtual void RemoveAt(int index) = 0;
};