#include<iostream>
#include<string>
using namespace std;

void FindKickAndStart(string& txt, int K[], int S[]) {

	int sum_char = 0;

	for (int i = 0; i < txt.size(); i++) {
		if (i + 3 < txt.size())
			if (txt[i] == 'K' && txt[i + 3] == 'K') {
				for (int temp = i; temp <= i + 3; temp++)
					sum_char += txt[temp];
				if (sum_char == 290) { *K = i; K++; i += 3; } // Если сложить KICK = 290
				sum_char = 0;
			}
		if (i + 4 < txt.size())
			if (txt[i] == 'S' && txt[i + 4] == 'T') {
				for (int temp = i; temp <= i + 4; temp++)
					sum_char += txt[temp];
				if (sum_char == 398) { *S = i; S++; i += 4; } //Если сложить START = 398
				sum_char = 0;
			}
	}
	return;
}
void All_1(int I[]) {
	for (int i = 0; i < 25; i++)
		I[i] = -1;
}
int HappyDay(string& txt) {

	int K[25], S[25]; // Для функции Find...Start
	All_1(K); All_1(S); // Присвоить -1 каждому элементу массива
	int res = 0; // Для вывода кол-во счястливых случаев

	FindKickAndStart(txt, K, S);

	for (int i = 0; K[i] != -1; i++)
		for (int j = 0; S[j] != -1; j++)
			if (K[i] < S[j]) res++;

	return res;
}


int main()
{
	int number = 0;
	string txt[100];

	cin >> number;

	for (int i = 0; i < number; i++)
		cin >> txt[i];

	for (int i = 0; i < number; i++)
		cout << "Case #" << i + 1 << ": " << HappyDay(txt[i]) << "\n";

	return 0;
}