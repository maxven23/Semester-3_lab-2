#include "BinaryTree.h"

template <class TKey, class TItem> 
class IDictionary {
private:
	//BinaryTree<TKey, TItem>* Tree;
	int Capacity;
	int Count;

public:
	BinaryTree<TKey, TItem>* Tree;
	IDictionary(int capacity) {
		this->Capacity = capacity;
		this->Count = 0;
		this->Tree = new BinaryTree<TKey, TItem>();
	}

	int GetCapacity() {
		return this->Capacity;
	}
	int GetCount() {
		return this->Count;
	}

	TItem Get(TKey key, int(*comp)(TKey, TKey)) {
		auto node = this->Tree->findNode(key, comp);
		if (node != nullptr) {
			return node->item;
		}
		else return NULL;
	}

	bool ContainsKey(TKey key, int(*comp)(TKey, TKey)) {
		return this->Tree->toCheck(key, comp);
	}

	void Add(TKey key, TItem item, int(*comp)(TKey, TKey)) {
		this->Tree->toInsert(key, item, comp);
		++this->Count;
	}

	void Remove(TKey key, int(*comp)(TKey, TKey)) {
		this->Tree->removeNode(key, comp);
		return;
	}
};