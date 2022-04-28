#include<iostream>
#include<vector>
#include<iterator>

using namespace std;

vector<int> SumPlates(vector<vector<int>>& AllPlates) {
	vector<int> res;
	for (vector<int> plates : AllPlates) {
		int sum = 0;
		for (int number : plates)
			sum += number;
		res.push_back(sum);
	}
	return res;
}
int MaxVector(vector<int> vr) {
	int res = 0;
	int max = 0;
	for (int i = 0; i < vr.size(); i++) {
		if (max <= vr[i]) {
			max = vr[i];
			res = i;
		}
	}
	return res;
}
bool DeleteAllStrok(vector<vector<int>>& temp, int HM) {
	for (int i = 0; i < temp.size(); i++) {
		temp[i].resize(HM);
	}
	return true;
}
int main()
{
	z
		vector<int> res;

	int trying = 0;
	cin >> trying;

	for (int t = 1; t <= trying; t++) {
		res.push_back(0);
		vector<vector<int>> AllPlates;
		int How_Many = 0;

		int N = 0;
		cin >> N;
		int K = 0;
		cin >> K >> How_Many;
		if (K > How_Many) K = How_Many;
		for (int n = 0; n < N; n++) {
			vector<int> temp_v;
			for (int k = 0; k < K; k++) {
				int P = 0;
				cin >> P;
				temp_v.push_back(P);
			}
			AllPlates.push_back(temp_v);
		}
		for (; How_Many > 0; How_Many--) {
			DeleteAllStrok(AllPlates, How_Many);
			int index_one = MaxVector(SumPlates(AllPlates));
			auto iter = AllPlates[index_one].begin();
			res[t - 1] += (*iter);
			AllPlates[index_one].erase(iter);

		}
	}
	cout << '\n';
	for (int i = 1; i <= res.size(); i++)
		cout << "Case #" << i << ": " << res[i - 1] << '\n';


	return 0;
}