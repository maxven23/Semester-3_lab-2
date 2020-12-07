#pragma once
#include "Headers.h"
#include <stdio.h>
#include <Windows.h>



template <class TKey, class TItem>
class BinaryTree {
public:
	struct Node {
		TKey key;
		TItem item;
		Node* left;
		Node* right;

		Node(TKey key, TItem item) {
			this->key = key;
			this->item = item;
			this->left = nullptr;
			this->right = nullptr;
		}

		pair<TKey, TItem> Get() {
			pair<TKey, TItem> p;
			p.first = this->key;
			p.second = this->item;
			return p;
		}
	};

public:
	Node* root;

public:
	//----------Конструкторы----------//
	BinaryTree(TKey key, TItem item) {
		this->root = new Node(key, item);
	};

	BinaryTree(Node* root) {
		this->root = root;
	};

	BinaryTree() {
		this->root = nullptr;
	};

	//-------------Методы--------------//

	Node* getRoot() {
		return this->root;
	};

	// Проверка на наличие элемента в дереве
	bool toCheck(TKey key, int(*comp)(TKey, TKey)) {
		Node* temp;
		temp = this->root;

		while (temp != nullptr) {
			if (comp(temp->Get().first, key) == -1) {
				temp = temp->left;
			}
			else if (comp(temp->Get().first, key) == 1) {
				temp = temp->right;
			}
			else {
				return true;
			}
		}
		
		if (temp == nullptr) {
			return false;
		}
	};

	// Поиск узла по ключу с заданного узла
	Node* findNode(Node* Node, TKey key, int(*comp)(TKey, TKey)) {
		if (this->root == nullptr) {
			throw std::exception("ERROR: Tree is EMPTY");
		}

		if (Node->key == key) {
			return Node;
		}
		else {
			if (comp(Node->key, key) == 1) {
				return findNode(Node->right, key, comp);
			}
			else {
				return findNode(Node->left, key, comp);
			}
		}
		return nullptr;
	};

	// Поиск узла с заданным ключом во всём дереве
	Node* findNode(TKey key, int(*comp)(TKey, TKey)) {
		return findNode(this->root, key, comp);
	};

	// map для поддерева, начиная с заданного узла
	void map(Node* Node, TItem (*foo)(TItem)) {
		Node->item = foo(Node->item);

		if (Node->right != nullptr) {
			map(Node->right, foo);
		}
		if (Node->left != nullptr) {
			map(Node->left, foo);
		}
	};

	// map для всего деева
	void map(TItem (*foo)(TItem)) {
		if (this->root == nullptr) {
			std::cout << "Tree is EMPTY" << std::endl;;
		}
		else {
			map(this->root, foo);
		}
	};

	// "Высота" поддерева, длина самой длинной ветви начиная с заданного узла
	static int getHeight(Node* Node)
	{
		int L = 0;
		int R = 0;
		if (Node->left == nullptr && Node->right == nullptr) {
			return 0;
		}
		else {
			if (Node->right != nullptr) {
				R = getHeight(Node->right) + 1;
			}
			else {
				R = 0;
			}

			if (Node->left != nullptr) {
				L = getHeight(Node->left) + 1;
			}
			else {
				L = 0;
			}
		}

		if (L > R) {
			return L;
		}
		else {
			return R;
		}
	};

	// "Высота" всего дерева
	int getHeight() {
		if (this->root == nullptr) {
			throw std::exception("ERROR: Tree is EMPTY");
		}

		return (getHeight(this->root));
	};

	// Получение поддерева по элементу
	BinaryTree<TKey, TItem>* getSubTree(TKey key, int(*comp)(TKey, TKey)) {
		Node* temp = this->findNode(key, comp);
		BinaryTree<TKey, TItem>* subTree = new BinaryTree<TKey, TItem>(temp);

		return subTree;
	};

	// Проверка деревьев на равенство
	bool isEqual(BinaryTree<TKey, TItem>* Tree, int(*comp)(TKey, TKey)) {
		if ((this->getRoot() == nullptr && Tree->getRoot() != nullptr) || 
			(this->getRoot() != nullptr && Tree->getRoot() == nullptr)) {
			return false;
		}

		if (this->getRoot() == nullptr && Tree->getRoot()) {
			return true;
		}

		Node* Right = this->root->right;
		Node* Left = this->root->left;
		Node* treeRight = Tree->getRoot()->right;
		Node* treeLeft = Tree->getRoot()->left;
		bool out = true;

		if (Left != nullptr && treeLeft != nullptr) {
			out = out && this->getSubTree(Left->key, comp)->isEqual(Tree->getSubTree(treeLeft->key, comp));
		}

		if (Left == nullptr && treeLeft == nullptr) {
			out = true;
		}
		else {
			out = false;
		}

		if (Right != nullptr && treeRight != nullptr) {
			out = out && this->getSubTree(Right->key, comp)->isEqual(Tree->getSubTree(treeRight->key, comp));
		}

		if (Right == nullptr && treeRight == nullptr) {
			out = true;
		}
		else {
			out = false;
		}
		return out;
	};

	// Проверка на вхождение поддерева в исходной дерево
	bool toCheckSubtree(BinaryTree<TKey, TItem>* subTree, int(*comp)(TKey, TKey)) {
		if (subTree->getRoot() == nullptr && this->getRoot() != nullptr) {
			return false;
		}
		if (subTree->getRoot() == this->getRoot()) {
			return true;
		}
		if (this->toCheck(subTree->getRoot()->key, comp))	{
			return this->getSubTree(subTree->getRoot()->key, comp)->isEqual(subTree, comp);
		}
		else {
			return false;
		}
	};

	// (НЕТ) Прошивка с заданного узла
	static Sequence<Node*>* Chain(Node* node, std::string order)	{
		Sequence<Node*>* list = nullptr;

		for (size_t i = 0; i < order.length(); i++)	{
			switch (order[i]) {

			case 'N':
				if (list == nullptr) {
					list = new ListSequence<Node*>();
					list->Prepend(node);
				}
				else {
					Sequence<Node*>* list1 = nullptr;
					list1 = new ListSequence<Node*>();
					list1->Prepend(node);

					list = list->Concat(list1);
				}
				break;

			case 'R':
				if (node->right != nullptr) {
					if (list == nullptr) {
						list = Chain(node->right, order);
					}
					else {
						list = list->Concat(Chain(node->right, order));
					}
				}
				break;

			case 'L':
				if (node->left != nullptr)  {
					if (list == nullptr) {
						list = Chain(node->left, order);
					}
					else {
						list = list->Concat(Chain(node->left, order));
					}
				}
				break;
			}
		}
		return list;
	};

	// (НЕТ) Прошивка всего дерева
	Sequence<Node*>* Chain(std::string order) {
		return this->Chain(this->root, order);
	};


	// Восстановление дерева из списка узлов
	Node* deChain(Sequence<Node*>* Chain) {
		Sequence<Node*>* listLR = new ListSequence<Node*>();
		Sequence<Node*>* listN = Chain;
		ArraySequence<bool>* listCheck = new ArraySequence<bool>(listN->GetSize());
		
		for (int i = 0; i < listN->GetSize(); i++) {
			if (listN->Get(i)->left != nullptr) {
				listLR->Prepend(listN->Get(i)->left);
			}

			if (listN->Get(i)->right != nullptr) {
				listLR->Prepend(listN->Get(i)->right);
			}

			listCheck->Set(i, false);
		}

		for (int i = 0; i < listN->GetSize(); i++) {
			for (int k = 0; k < listLR->GetSize(); k++) {
				if (listLR->Get(k) == listN->Get(i)) {
					listCheck->Set(i, true);
				}
			}
		}

		for (int i = 0; i < listCheck->GetSize(); i++) {
			if (listCheck->Get(i) == false) {
				return listN->Get(i);
			}
		}
		
		return nullptr;
	};


	//---------------------------БЛОК-БАЛАНСИРОВКИ------------------------------------
	// Балансировка Day–Stout–Warren
	void DSW() {
		if (nullptr != root) {
			createBackbone();
			createBalancedBT();
		}
	};

	void createBackbone() {
		Node* grandParent = nullptr;
		Node* parent = root;
		Node* leftChild;

		while (nullptr != parent) {
			leftChild = parent->left;
			if (nullptr != leftChild) {
				grandParent = rotateRight(grandParent, parent, leftChild);
				parent = leftChild;
			}
			else {
				grandParent = parent;
				parent = parent->right;
			}
		}
	};

	Node* rotateRight(Node* grandParent, Node* parent, Node* leftChild) {
		if (nullptr != grandParent) {
			grandParent->right = leftChild;
		}
		else {
			root = leftChild;
		}
		parent->left = leftChild->right;
		leftChild->right = parent;
		return grandParent;
	};

	void createBalancedBT() {
		int n = 0;
		for (Node* tmp = root; tmp != nullptr; tmp = tmp->right) {
			n++;
		}

		int m = greatestPowerOf2LessThanN(n + 1) - 1;
		makeRotations(n - m);

		while (m > 1) {
			makeRotations(m /= 2);
		}
	};

	int greatestPowerOf2LessThanN(int n) {
		int x = MSB(n);
		return (1 << x);
	};

	int MSB(int n) {
		int ndx = 0;
		while (1 < n) {
			n = (n >> 1);
			ndx++;
		}
		return ndx;
	};

	void makeRotations(int bound) {
		Node* grandParent = nullptr;
		Node* parent = root;
		Node* child = root->right;
		for (; bound > 0; bound--) {
			if (child != nullptr && child->right != nullptr) {
				rotateLeft(grandParent, parent, child);
				grandParent = child;
				parent = grandParent->right;
				child = parent->right;
			}
			else {
				break;
			}
		}
	};

	void rotateLeft(Node* grandParent, Node* parent, Node* rightChild) {
		if (nullptr != grandParent) {
			grandParent->right = rightChild;
		}
		else {
			root = rightChild;
		}
		parent->right = rightChild->left;
		rightChild->left = parent;
	};
	//---------------------------------------------------------------------------

	// Вставка элемента
	void toInsert(TKey key, TItem item, int(*comp)(TKey, TKey)) {
		if (this->toCheck(key, comp)) {
			return;
		}

		Node* toInsert = new Node(key, item);
		Node* p = this->root;
		Node* p1 = nullptr;

		while (p != nullptr) {
			p1 = p;
			if (comp(key, p->Get().first) == 1) {
				p = p->left;
			}
			else {
				p = p->right;
			}
		}

		if (p1 == nullptr) {
			this->root = toInsert;
		}
		else {
			if (comp(key, p1->Get().first) == 1) {
				p1->left = toInsert;
			}
			else {
				p1->right = toInsert;
			}
		}

		DSW();
	};

	// Удаление элемента по ключу
	bool removeNode(Node* node, TKey key, int(*comp)(TKey, TKey)) {
		if (node == nullptr) {
			return false;
		}

		bool where;
		Node* temp = node;
		Node* temp1 = nullptr;

		if (temp->left == nullptr && temp->right == nullptr) {
			if (temp->key == key) {
				delete temp;
				return true;
			}
			else {
				return false;
			}
		}
		while (temp != nullptr && temp->key != key) {
			if (comp(key, temp->key) == 1) {
				where = false;
				temp1 = temp;
				temp = temp->left;
			}
			else {
				if (comp(key, temp->key) == -1) {
					where = true;
					temp1 = temp;
					temp = temp->right;
				}
			}
		}
		if (temp == nullptr) {
			std::cout << "ERROR: Tree is EMPTY" << std::endl;
			return false;
		}
		else {
			if (temp->right == nullptr && temp->left == nullptr) {
				if (!where) {
					temp1->left = nullptr;
				}
				else {
					temp1->right = nullptr;
				}
				delete temp;
				return true;
			}
			else {
				if (temp->right != nullptr && temp->left == nullptr) {
					if (temp1->left == temp) {
						temp1->left = temp->right;
					}
					else {
						temp1->right = temp->right;
					}
					delete temp;
					return true;
				}
				else {
					if (temp->left != nullptr && temp->right == nullptr) {
						if (temp1->left == temp) {
							temp1->left = temp->left;
						}
						else {
							temp1->right = temp->left;
						}
						delete temp;
						return true;
					}
					else {
						if (temp->left != nullptr && temp->right != nullptr) {
							Node* temp2 = nullptr;
							temp1 = temp;
							temp2 = temp;
							where = true;
							temp = temp->right;
							while (temp->left != nullptr) {
								temp2 = temp;
								where = false;
								temp = temp->left;
							}
							temp1->item = temp->item;

							if (temp->right != nullptr) {
								if (where) {
									temp2->right = temp->right;
								}
								else {
									temp2->left = temp->right;
								}

								delete temp;
								return true;
							}
							else {
								if (where) {
									temp2->right = nullptr;
								}
								else {
									temp2->left = nullptr;
								}

								delete temp;
								return true;
							}
						}
					}
				}
			}
		}
	};

	// Удаление узла по элементу
	bool removeNode(TKey key, int(*comp)(TKey, TKey)) {
		return removeNode(this->root, key, comp);
	};

	// Сохранение дерева по обходу в строку
	
	std::string toString(std::string order) {
		std::string res;
		Sequence<Node*>* chainTree = this->Chain(order);
		if (this->root == nullptr) {
			throw std::exception("ERROR: Tree is EMPTY");
		}

		for (int i = 0; i < chainTree->GetSize(); i++) {
			if (i == 0) {
				string strkey = (chainTree->Get(i)->key);
				string stritem = std::to_string(chainTree->Get(i)->item);
				
				res += strkey + ": " + stritem + " ";
			}
			else {
				string strkey = (chainTree->Get(i)->key);
				string stritem = std::to_string(chainTree->Get(i)->item);

				res += "-> " + strkey + ": " + stritem + " ";
			}
		}
		return res;
	};
	
	Sequence<pair<TKey, TItem>>* first_n(std::string order, int n) {
		
		Sequence<Node*>* chainTree = this->Chain(order);
		if (this->root == nullptr) {
			throw std::exception("ERROR: Tree is EMPTY");
		}
		pair<TKey, TItem> p;
		ArraySequence<pair<TKey, TItem>>* newlist = new ArraySequence<pair<TKey, TItem>>(n);
		for (int i = 0; i < n; i++) {
			p.first = chainTree->Get(i)->key;
			p.second = chainTree->Get(i)->item;
			newlist->Append(p);
		}
		return newlist;
	};

	// reduce
	/*
	T reduce(T(*foo)(T, T), T startItem, std::string order) {
		if (this->root == nullptr) {
			throw std::exception("ERROR: Tree is EMPTY");
		}
		T out = { 0 };
		Sequence<Node<T>*>* ChainTree = this->Chain(order);

		for (int i = 0; i < ChainTree->GetSize(); i++) {
			if (i == 0) {
				out = foo(ChainTree->Get(i)->Get(), startItem);
			}
			else {
				out = foo(ChainTree->Get(i)->Get(), out);
			}
		}
		delete ChainTree;
		return out;
	};
	*/

	// where
	/*
	Sequence<Node<T>*>* Where(bool(*foo)(T), std::string order) {
		if (this->getRoot() == nullptr) {
			throw std::exception("ERROR: Tree is EMPTY");
		}
		Sequence<Node<T>*>* list = this->Chain(order);
		Sequence<Node<T>*>* out = new ListSequence<Node<T>*>();
		for (int i = 0; i < list->GetSize(); i++) {
			if (foo(list->Get(i)->Get()) == true) {
				out->Prepend(list->Get(i));
			}
		}
		delete list;
		return out;
	};
	*/


	// Вывод дерева
	
	void printTree(Node* node, int level)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		if (node)
		{
			printTree(node->left, level + 1);
			for (int i = 0; i < level - this->getHeight(); i++) cout << "          ";
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 2));
			std::cout << "lvl" << level - this->getHeight() << ": ";
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
			std::cout << node->Get().first << ": " << node->Get().second << std::endl;
			printTree(node->right, level + 1);
		}
	};

	void printTree() {
		this->printTree(this->getRoot(), this->getHeight());
	};
	
};