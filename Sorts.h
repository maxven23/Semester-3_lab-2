#include "Headers.h"
#include <ctime>


template <class T>
class ISorter {
public:
	long long comparasions;
	long long iterations;

	virtual long long getIter() = 0;
	virtual long long getComp() = 0;

	virtual void Sort(Sequence<T>* input, bool(*comp)(T, T)) = 0;

protected:
	void Swap(Sequence<T>* seq, int index1, int index2)
	{
		T item = seq->Get(index1);
		seq->Set(index1, seq->Get(index2));
		seq->Set(index2, item);
	}
};


template <class T>
// Пузырьковая сортировка
class bubbleSorter : public ISorter<T> 
{
public:
	bubbleSorter() {
		this->comparasions = 0;
		this->iterations = 0;
	}

	long long getComp() {
		return this->comparasions;
	}
	long long getIter() {
		return this->iterations;
	}

	void Sort(Sequence<T>* arr, bool(*comp)(T, T)) override {

		for (int i = 0; i < arr->GetSize(); i++) {
			for (int j = 0; j < arr->GetSize() - i - 1; j++) {
				if (comp(arr->Get(j), arr->Get(j + 1))) {

					this->Swap(arr, j, j + 1);
					++this->iterations;

				}
				++this->comparasions;
			}
		}
	}
};


template <class T>
// Быстрая сортировка
class quickSorter : public ISorter<T>
{
public:
	quickSorter() {
		this->comparasions = 0;
		this->iterations = 0;
	}
	long long getComp() {
		return this->comparasions;
	}
	long long getIter() {
		return this->iterations;
	}

	void Sort(Sequence<T>* arr, bool(*comp)(T, T)) override {
		quickSort(arr, comp, 0, arr->GetSize() - 1);
	}

	void quickSort(Sequence<T>* arr, bool(*comp)(T, T), int left, int right) {

		int i = left, j = right;

		T middle = arr->Get((left + right) / 2);

		while (i <= j) {
			while (!(comp(arr->Get(i), middle)) && !(arr->Get(i) == middle)) {
				this->comparasions++;
				i++;
			}
			while ((comp(arr->Get(j), middle))) {
				this->comparasions++;
				j--;
			}
			if (i <= j) {

				this->Swap(arr, i, j);
				this->iterations++;

				i++;
				j--;
			}
		};

		// Рекурсивный вызов
		if (left < j)
			quickSort(arr, comp, left, j);
		if (i < right)
			quickSort(arr, comp, i, right);

	}
};


template <class T>
// Сортировка вставками
class insertSorter : public ISorter<T>
{
public:
	insertSorter() {
		this->comparasions = 0;
		this->iterations = 0;
	}

	long long getComp() {
		return this->comparasions;
	}
	long long getIter() {
		return this->iterations;
	}

	void Sort(Sequence<T>* arr, bool(*comp)(T, T)) override {

		T temp;

		for (int i = 0; i < arr->GetSize() - 1; i++)
		{
			int key = i + 1;
			temp = arr->Get(key);
			for (int j = i + 1; j > 0; j--)
			{
				++this->comparasions;
				if (!(comp(temp, arr->Get(j - 1))) && !(temp == arr->Get(j - 1)))
				{
					arr->Set(j, arr->Get(j - 1));
					key = j - 1;
					++this->iterations;
				}
			}
			arr->Set(key, temp);
		}
	}
};


template <class T>
// Сортировка простым выбором
class selectSorter : public ISorter<T>
{
public:

	selectSorter() {
		this->comparasions = 0;
		this->iterations = 0;
	}

	long long getComp() {
		return this->comparasions;
	}
	long long getIter() {
		return this->iterations;
	}

	void Sort(Sequence<T>* arr, bool(*comp)(T, T)) override {

		for (int startIndex = 0; startIndex < arr->GetSize(); ++startIndex) {

			int smallestIndex = startIndex;

			for (int currentIndex = startIndex + 1; currentIndex < arr->GetSize(); ++currentIndex) {

				if (!(comp(arr->Get(currentIndex), arr->Get(smallestIndex))) && !(arr->Get(currentIndex) == arr->Get(smallestIndex))) {
					++this->comparasions;
					smallestIndex = currentIndex;
				}
			}

			this->Swap(arr, startIndex, smallestIndex);
			++this->iterations;
		}
	}
};


template <class T>
// Сотрировка Шелла
class shellSorter : public ISorter<T>
{
public:

	shellSorter() {
		this->comparasions = 0;
		this->iterations = 0;
	}
	long long getComp() {
		return this->comparasions;
	}

	long long getIter() {
		return this->iterations;
	}

	void Sort(Sequence<T>* arr, bool(*comp)(T, T)) override {

		int step, i, j;

		// Выбор шага
		for (step = arr->GetSize() / 2; step > 0; step /= 2)
			// Перечисление элементов, которые сортируются на определённом шаге
			for (i = step; i < arr->GetSize(); i++) {
				// Перестановка элементов внутри подмассива, пока i-тый не будет отсортирован
				++this->comparasions;
				for (j = i - step; j >= 0 && (comp(arr->Get(j), arr->Get(j + step))); j -= step, ++this->comparasions)
				{

					this->Swap(arr, j, j + step);
					++this->iterations;

				}
			}
	}
};


template <class T> 
void shuffle(Sequence<T>* arr) {

	srand(time(NULL));

	for (int i = 0; i < arr->GetSize(); ++i) {
		T tmp = arr->Get(i);
		int r = rand() % arr->GetSize();
		arr->Set(i, arr->Get(r));
		arr->Set(r, tmp);
	}

	if (arr->GetSize() <= 1000) {
		cout << "----------------------------------Shuffled Array----------------------------------" << endl << endl;

		cout << "[";
		for (int i = 0; i < arr->GetSize() - 1; ++i) {
			cout << arr->Get(i) << ",  ";
		}
		cout << arr->Get(arr->GetSize() - 1) << "]" << endl << endl;

		cout << "----------------------------------------------------------------------------------" << endl;
	}
};