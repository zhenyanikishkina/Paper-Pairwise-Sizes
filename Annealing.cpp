#include <bits/stdc++.h>
using namespace std;

int main() {
	int N = 878, n = 10000;
	vector<vector<int>> B(N, vector<int>(N));
	ifstream fin1("B.txt");
	ifstream fin2("A.txt");
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			fin1 >> B[i][j];
		}
	}

	vector<vector<int>> A(N, vector<int>(n));
	vector<vector<int>> C(N, vector<int>(N));
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < n; ++j) {
			fin2 >> A[i][j];
		}
	}

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			for (int k = 0; k < n; ++k) {
				C[i][j] += A[i][k] * A[j][k];
			}
		}
	}

	int E = 0;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
            if (i != j) {
			    E += abs(C[i][j] - B[i][j]);
            }
		}
	}
	cout << E << endl;

	double T0 = 1;
	double T = T0;
	int iter = 0;
	srand(time(NULL));

	for (int it = 1; it < 50000000; ++it) {
		int I = rand() % N;
		int J = rand() % n;
		int E_cur = E;

		for (int j = 0; j < N; ++j) {
			if (j == I) {
				continue;
			}
			E_cur -= abs(C[I][j] - B[I][j]);
			int pr = A[I][J] & A[j][J];
			A[I][J] ^= 1;
			int cur = A[I][J] & A[j][J];
			A[I][J] ^= 1;
			E_cur += abs(C[I][j] - pr + cur - B[I][j]);
		}

		for (int i = 0; i < N; ++i) {
			if (i == I) {
				continue;
			}
			E_cur -= abs(C[i][I] - B[i][I]);
			int pr = A[i][J] & A[I][J];
			A[I][J] ^= 1;
			int cur = A[i][J] & A[I][J];
			A[I][J] ^= 1;
			E_cur += abs(C[i][I] - pr + cur - B[i][I]);
		}

		// E_cur -= abs(C[I][I] - B[I][I]);
		// E_cur += abs(C[I][I] - (A[I][J] & A[I][J]) + ((A[I][J] ^ 1) & (A[I][J] ^ 1)) - B[I][I]);


		int delta_E = E_cur - E;
		if (delta_E > 0) {
			double tmp = exp(-(double)delta_E / T);
			if ((double)rand() / RAND_MAX <= tmp) {
				A[I][J] ^= 1;
				for (int j = 0; j < N; ++j) {
					if (j == I) {
						continue;
					}
					A[I][J] ^= 1;
					C[I][j] -= A[I][J] & A[j][J];
					A[I][J] ^= 1;
					C[I][j] += A[I][J] & A[j][J];
				}
				for (int i = 0; i < N; ++i) {
					if (i == I) {
						continue;
					}
					A[I][J] ^= 1;
					C[i][I] -= A[i][J] & A[I][J];
					A[I][J] ^= 1;
					C[i][I] += A[i][J] & A[I][J];
				}
				A[I][J] ^= 1;
				C[I][I] -= A[I][J] & A[I][J];
				A[I][J] ^= 1;
				C[I][I] += A[I][J] & A[I][J];

				E = E_cur;
			}
		} else {
			iter++;

			A[I][J] ^= 1;
			for (int j = 0; j < N; ++j) {
				if (j == I) {
					continue;
				}
				A[I][J] ^= 1;
				C[I][j] -= A[I][J] & A[j][J];
				A[I][J] ^= 1;
				C[I][j] += A[I][J] & A[j][J];
			}
			for (int i = 0; i < N; ++i) {
				if (i == I) {
					continue;
				}
				A[I][J] ^= 1;
				C[i][I] -= A[i][J] & A[I][J];
				A[I][J] ^= 1;
				C[i][I] += A[i][J] & A[I][J];
			}
			A[I][J] ^= 1;
			C[I][I] -= A[I][J] & A[I][J];
			A[I][J] ^= 1;
			C[I][I] += A[I][J] & A[I][J];

			E = E_cur;
			if (iter % 100000) {
				cout << it << " " << E << endl;
			}
		}

		T = T0 / it;
	}

	ofstream fout("tmp.txt");
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < n; ++j) {
			fout << A[i][j] << " ";
		}
		fout << endl;
	}

	cout << E << endl;

	fout.close();
	fin1.close();
	fin2.close();

	return 0;
}
