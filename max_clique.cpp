#include <bits/stdc++.h>
using namespace std;

int main() {
	int N = 878;
	vector<vector<int>> B(N, vector<int>(N));
	ifstream fin1("B.txt");
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			fin1 >> B[i][j];
		}
	}

	vector<vector<int>> ans(N);
	vector<vector<int>> gr(N, vector<int>(N));
	gr = B;
	for (int i = 0; i < N; ++i) {
		gr[i][i] = 0;
	}
	
	int T = 0;
	while (true) {
		vector<int> arr;
		int mn = 1e9;
		// 
		vector<vector<int>> gr_cp(N, vector<int>(N));
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				if (gr[i][j] != 0) {
					gr_cp[i][j] = 1;
				}
			}
		}
		vector<int> v(N);
		for (int i = 0; i < N; ++i) {
			int sum = 0;
			for (int j = 0; j < N; ++j) {
				sum += gr_cp[i][j];
			}
			v[i] = sum;
		}
		while (true) {
			int cnt = 0;
			int ind = -1, mn = 1e9;
			for (int i = 0; i < N; ++i) {
				if (v[i] != 0) {
					cnt += 1;
				}
				if (v[i] < mn && v[i] != 0) {
					mn = v[i];
					ind = i;
				}
			}
			if (ind == -1) {
				break;
			}
			if (mn < cnt - 1) {
				for (int j = 0; j < N; ++j) {
					if (gr_cp[ind][j] == 1) {
						gr_cp[ind][j] = 0;
						gr_cp[j][ind] = 0;
						v[ind] -= 1;
						v[j] -= 1;
					}
				}
			} else {
				break;
			}
		}
		arr.clear();
		mn = 1e9;
		for (int i = 0; i < N; ++i) {
			if (v[i] != 0) {
				arr.push_back(i);
			}
		}
		for (auto i : arr) {
			for (auto j : arr) {
				if (gr_cp[i][j] != 0) {
					mn = min(mn, gr_cp[i][j]);
				}
			}
		}
		// 
		for (int i : arr) {
			for (int k = 0; k < mn; ++k) {
				ans[i].push_back(T + k);
			}
		}
		T += mn;
		for (int i : arr) {
			for (int j : arr) {
				if (i != j) {
					gr[i][j] = max(gr[i][j] - mn, 0);
				}
			}
		}
		int ss = 0;
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				ss += gr[i][j];
			}
		}
		cout << T << " " << arr.size() << " " << ss << endl;

		if (ss == 0) {
			break;
		}

		if (T % 5000 == 0) {
			vector<vector<int>> a(N, vector<int>(T));
			for (int i = 0; i < N; ++i) {
				for (auto it : ans[i]) {
					a[i][it] = 1;
				}
			}
			ofstream out("raseb.txt");
			for (int i = 0; i < N; ++i) {
				for (int j = 0; j < T; ++j) {
					out << a[i][j] << " ";
				}
				out << endl;
			}
			out.close();
		}
	}

	vector<vector<int>> a(N, vector<int>(T));
	for (int i = 0; i < N; ++i) {
		for (auto it : ans[i]) {
			a[i][it] = 1;
		}
	}
	ofstream out("raseb.txt");
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < T; ++j) {
			out << a[i][j] << " ";
		}
		out << endl;
	}
	out.close();

	fin1.close();


	return 0;
}

