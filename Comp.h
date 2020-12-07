#include <iostream>

// Не получалось использовать Greater, поэтому Bigger :^)
template <class T>
bool bigger(T first, T second) {
	return first > second;
}

template <class T>
bool lower(T first, T second) {
	return first < second;
}