#include<iostream>
#include<string>
#include<vector>
#include<time.h>
#include<thread>

typedef unsigned short us;

using namespace std;

int strToInt(string& str) {
	int res = 0;
	bool was = false;
	for (int i = 0; i < str.size(); i++) {
		if (str[i] < '0' || str[i]>'9') break;
		res *= 10;
		res += str[i] - '0';
		was = true;
	}
	return was ? res : -1;
}
bool playAgain() {
	char ch;
	do {
		cout << "Play again? (y or n)"; cin >> ch;
		cin.clear();
		while (cin.get() != '\n');
	} while (ch != 'y' && ch != 'Y' && ch != 'n' && ch != 'N');
	return (ch == 'y' || ch == 'Y');
}

class Game {
private:
	us sizeMap;
	us sizeWinComb;
	string FPN, SPN; // FPN == first player name
	bool withBot;
	int** gameComb; // All moves
	void setGameComb() {
		int value = 0;
		gameComb = new int* [sizeMap];
		for (int i = 0; i < sizeMap; i++) {
			gameComb[i] = new int[sizeMap];
			for (int j = 0; j < sizeMap; j++, value++)
				gameComb[i][j] = value;
		}
		return;
	}
public:
	Game() {}
	void selectMode() {
		system("cls");

		cout << "\tSelect mode\n\n";

		cout << "1. Play together\n";
		cout << "2. Play with bot\n\n";
		string select = "";

		do {
			cout << "Enter mode: "; cin >> select;
			cin.clear();
			while (cin.get() != '\n');
		} while (select != "1" && select != "2");

		cout << "\n\n";

		withBot = select == "2";
	}
	void writeNames() {
		cout << "\tPlayer names\n\n";

		cout << "Enter the name of the first player: "; cin >> FPN;
		cin.clear();
		while (cin.get() != '\n');
		if (!withBot) {
			cout << "Enter the name of the second player: "; cin >> SPN;
			cin.clear();
			while (cin.get() != '\n');
		}
		else SPN = "BOT";

		cout << "\n\n";

		return;
	}
	void selectSizeMap() {
		cout << "\tSize game MAP\n\n";
		string ch;
		do {
			cout << "Enter a map size from 2 to 10: "; cin >> ch;
			cin.clear();
			while (cin.get() != '\n');
			sizeMap = strToInt(ch);
		} while (sizeMap < 2 || sizeMap>10);
		cout << "\n\n";

		this->setGameComb();


		return;
	}
	void selectWinComb() {
		cout << "\tSize win combination\n\n";
		string ch;
		do {
			cout << "Enter the size of the winning combination (min=2, max=sizeMap): "; cin >> ch;
			cin.clear();
			while (cin.get() != '\n');
			sizeWinComb = strToInt(ch);
		} while (sizeWinComb<2 || sizeWinComb>sizeMap);
		return;
	}
	void printMap(bool turn) {
		system("cls");

		int X = sizeMap * 5 + 1;

		cout << "\tTurn ";
		if (turn) cout << FPN << "  X";
		else cout << SPN << "  O";

		cout << "\n\n\t";

		cout << '+';
		for (int i = 1; i < X - 1; i++)
			cout << '-';
		cout << '+';
		cout << endl;

		for (int i = 0; i < sizeMap; i++) {
			cout << '\t';

			cout << '|';
			for (int j = 0; j < sizeMap; j++) {
				cout << ' ';
				if (gameComb[i][j] <= 9 || gameComb[i][j] >= 100) cout << ' ';
				if (gameComb[i][j] == 100) cout << 'X';
				else if (gameComb[i][j] == 101) cout << 'O';
				else cout << gameComb[i][j];
				cout << " |";
			}
			cout << endl;

			cout << '\t';
			cout << '+';
			for (int i = 1; i < X - 1; i++)
				cout << '-';
			cout << '+';
			cout << endl;
		}

		return;
	}
	void printWinPlayer(bool turn) {
		cout << "\tWined ";
		if (turn) cout << FPN;
		else cout << SPN;
		cout << endl;
	}
	bool checkWin() {
		int checkSize = sizeMap - sizeWinComb;
		bool win = false;

		for (int i = 0; i < sizeMap; i++) {
			for (int j = 0; j <= checkSize; j++) {
				win = true;
				int stop = sizeWinComb - 1;
				for (int a = j; stop; a++, stop--) {
					if (gameComb[i][a] != gameComb[i][a + 1]) { win = false; break; }
				}
				if (win) return win;
			}
		}

		for (int i = 0; i <= checkSize; i++) {
			for (int j = 0; j < sizeMap; j++) {
				win = true;
				int stop = sizeWinComb - 1;
				for (int a = i; stop; a++, stop--) {
					if (gameComb[a][j] != gameComb[a + 1][j]) { win = false; break; }
				}
				if (win) return win;
			}
		}

		for (int i = 0; i <= checkSize; i++) {
			for (int j = 0; j <= checkSize; j++) {
				win = true;
				int stop = sizeWinComb - 1;
				for (int a = i, b = j; stop; a++, b++, stop--) {
					if (gameComb[a][b] != gameComb[a + 1][b + 1]) { win = false; break; }
				}
				if (win) return win;
			}
		}

		for (int i = 0; i <= checkSize; i++) {
			for (int j = sizeMap - 1; j >= (sizeWinComb - 1); j--) {
				win = true;
				int stop = sizeWinComb - 1;
				for (int a = i, b = j; stop; a++, b--, stop--) {
					if (gameComb[a][b] != gameComb[a + 1][b - 1]) { win = false; break; }
				}
				if (win) return win;
			}
		}

		return win;
	}
	bool move(int number, bool turn) {
		if (number < 0 || number >= (sizeMap * sizeMap)) return false;
		int i = number / sizeMap;
		int j = number % sizeMap;
		if (gameComb[i][j] >= 100) return false;
		if (turn) gameComb[i][j] = 100;
		else gameComb[i][j] = 101;
		return true;
	}
	void botMove() {
		vector<pair<int, int>> place;

		for (int i = 0; i < sizeMap; i++) {
			for (int j = 0; j < sizeMap; j++) {
				if (gameComb[i][j] >= 100) continue;
				int temp = gameComb[i][j];
				gameComb[i][j] = 101;
				if (this->checkWin()) return;
				gameComb[i][j] = temp;
				place.push_back({ i,j });
			}
		}

		for (int i = 0; i < sizeMap; i++) {
			for (int j = 0; j < sizeMap; j++) {
				if (gameComb[i][j] >= 100) continue;
				int temp = gameComb[i][j];
				gameComb[i][j] = 100;
				if (this->checkWin()) {
					gameComb[i][j] = 101;
					return;
				}
				gameComb[i][j] = temp;
			}
		}

		int r = rand() % place.size();

		gameComb[place[r].first][place[r].second] = 101;
		return;
	}
	us getSizeMap() { return sizeMap; }
	bool getStatusBot() { return withBot; }
	us getSizeWinComb() { return sizeWinComb; }
	void fullClear() {
		if (gameComb != nullptr) {
			for (int i = 0; i < sizeMap; i++) delete[]gameComb[i];
			delete[]gameComb;
		}
		SPN = FPN = ""; sizeMap = sizeWinComb = 0; gameComb = nullptr;
		return;
	}
	~Game() {
		if (gameComb != nullptr) {
			for (int i = 0; i < sizeMap; i++) delete[]gameComb[i];
			delete[]gameComb;
		}
	}
};


int main() {
	srand(time(0));

	Game game;
	do {
		game.fullClear(); // if to play again
		game.selectMode(); // game mode with bot or without bot
		game.writeNames(); // Player names if have bot that one name
		game.selectSizeMap(); // Size map
		game.selectWinComb(); // The size of the winning combination

		bool turn = rand() % 2;
		string number;
		int count = 0;
		int sizeMap = game.getSizeMap();
		sizeMap *= sizeMap;

		while (1) {
			game.printMap(turn);

			if (game.getStatusBot() && !turn) {
				game.botMove();
				this_thread::sleep_for(chrono::seconds(1));
			}
			else {
				do {
					cout << "\n\tEnter number: "; cin >> number;
					cin.clear();
					while (cin.get() != '\n');
				} while (!game.move(strToInt(number), turn));
			}

			count++;
			game.printMap(turn);

			bool win = game.checkWin();
			if (win || (sizeMap == count)) {
				if (win) game.printWinPlayer(turn);
				else cout << "\tDRAW\n";
				break;
			}

			turn = !turn;
		}

	} while (playAgain());
	return 0;
}