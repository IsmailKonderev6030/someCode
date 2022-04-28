// Программа которая ищет условие в тексте

#include<iostream>
#include<string>
using namespace std;

string MinWindowSubstring(string strArr[]) {

	bool bll = false;

	string res = ""; // Для возврата результата
	string conditions = strArr[1];


	int number_trying[2] = { 0,0 }; // Кол-во попыток удволитровить условие
	int index_one_byte = 0; // Тут будет храниться индекс первого байта 


	for (int i = 0; i < (strArr[0].size() - strArr[1].size()); i++) {
		if (conditions.find(strArr[0][i]) != 4294967295)
			for (int j = i; j < strArr[0].size() && conditions.size(); j++) {
				if (conditions.find(strArr[0][j]) != 4294967295) {
					conditions.erase(conditions.find(strArr[0][j]), 1);
				}
				number_trying[1]++;
			}
		if (!bll && !conditions.size()) { number_trying[0] = number_trying[1]; bll = true; }
		if (!conditions.size() && number_trying[0] >= number_trying[1]) {
			index_one_byte = i;
			number_trying[0] = number_trying[1];
		}
		number_trying[1] = 0;
		conditions = strArr[1];
	}

	for (int i = 0; i < number_trying[0]; i++)
		res += strArr[0][index_one_byte++];

	return res;

}

int main()
{
	string a[2] = { "ahffaksfajeeubsne", "jefaa" };
	cout << MinWindowSubstring(a) << "\n";



	return 0;
}