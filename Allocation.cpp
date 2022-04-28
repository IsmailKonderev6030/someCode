#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main()
{
	vector<int> CostHome;
	vector<int> res;

	int trying = 0;
	int temp_res = 0;

	cin >> trying;

	for (int i = 1; i <= trying; i++) {
		int B = 0;
		int number_home = 0;
		cin >> number_home >> B;

		for (int j = 0; j < number_home; j++) {
			int cost = 0;
			cin >> cost;
			CostHome.push_back(cost);
		}
		sort(CostHome.begin(), CostHome.end());

		for (int sum = 0; sum + CostHome[temp_res] <= B && temp_res < CostHome.size(); temp_res++)
			sum += CostHome[temp_res];
		res.push_back(temp_res);

		temp_res = 0;
		CostHome.clear();
	}

	for (int i = 1; i <= res.size(); i++)
		cout << "Case #" << i << ": " << res[i - 1] << "\n";

	return 0;
}