#pragma once
#include "IDictionary.h"
#include "Headers.h"

template <class TKey>
int comppair(pair<TKey, TKey> pair1, pair<TKey, TKey> pair2) {
	if (pair1.first > pair2.first) {
		return -1;
	}
	else if (pair1.first < pair2.first) {
		return 1;
	}
	else {
		if (pair1.second < pair2.second) {
			return 1;
		}
		else if (pair1.second > pair2.second) {
			return -1;
		}
		else return 0;
	}
};


class TicTacToe {
private:
	int current_player;
	IDictionary<pair<int, int>, char>* Dict = new IDictionary<pair<int, int>, char>(9);

public:
	TicTacToe(int player = 0) {
		this->current_player = player;
	}

	bool CheckPos(pair<int, int> pos) {
		return Dict->ContainsKey(pos, comppair<int>);
	}

	void Play(int player) {
		// COMPUTER
		if (player = 0) {
			PlayPVE();
		}
		// PLAYER
		else if (player = 1) {
			PlayPVP();
		}
	}

	void PlayPVP() {

	}
	void PlayPVE() {

	}
}