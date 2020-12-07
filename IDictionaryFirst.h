#pragma once
#include "Headers.h"
#include "SortedArray.h"
using namespace std;


template <typename TKey, typename TElem>
class IDictionary 
{
private:
	int Capacity;
	int Count;

	SortedArray<pair<TKey, TElem>>* items;
	
public:
	IDictionary(int Cap) {
		this->Count = 0;
		this->Capacity = Cap;

		items = new SortedArray<pair<TKey, TElem>>(0);
	}

public:
	int getCapacity() {
		return this->Capacity;
	};
	int getCount() {
		return this->Count;
	}

	TElem Get(TKey key) {
		for (int i = 0; i < this->items->GetSize(); i++) {
			if (this->items->Get(i).first == key) {
				return this->items->Get(i).second;
			}
		}
		return NULL;
	}

	bool ContainsKey(TKey key) {
		for (int i = 0; i < this->items->GetSize(); i++) {
			if (this->items->Get(i).first == key) {
				return true;
			}
		}
		return false;
	}

	void Add(TKey key, TElem element) {
		pair<TKey, TElem> p;
		p.first = key;
		p.second = element;

		++this->Count;
		this->items->Add(p);
	}

	void Remove(TKey key) {
		for (int i = 0; i < this->items->GetSize(); i++) {
			if (this->items->Get(i).first == key) {
				this->items->RemoveAt(i);
				return;
			}
		}
		throw std::exception("No such key detected");
		return;
	}
};
