// GROUP:   Data Science
// ID:      20227020
// Assign:  10
// Assign:  MatChain
// UVA:     348
// Name:    Farida Hamid Mohamed

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int p[11];

int T[11][11];
int D[11][11];


int MatChain(int a, int b) {
    int infinity = 1000000000;
    if (T[a][b] != -1) {
        return T[a][b];
    }
    if (a + 1 == b) {
        return T[a][b] = 0;
    }
    int min_cost = infinity;
    for (int i = a + 1; i < b; i++) {
        int cost = MatChain(a, i) + MatChain(i, b) + p[a] * p[i] * p[b];
        if (cost < min_cost) {
            min_cost = cost;
            D[a][b] = i;
        }
    }
    return T[a][b] = min_cost;
}


void MatChainTopDown(int n) {
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            T[i][j] = -1;
        }
    }
    MatChain(0, n);
}
void MatChainBottomUp(int n) {
    int infinity = 1000000000;

    for (int i = 0; i < n; i++) {
        T[i][i + 1] = 0;
    }
    for (int t = 2; t <= n; t++) {
        for (int i = 0; i + t <= n; i++) {
            int j = i + t;
            T[i][j] = infinity;
            for (int k = i + 1; k < j; k++) {
                int cost = T[i][k] + T[k][j] + p[i] * p[k] * p[j];
                if (cost < T[i][j]) {
                    T[i][j] = cost;
                    D[i][j] = k;
                }
            }
        }
    }
}
void MatChainSol(int a, int b) {
    if (a + 1 == b) {
        cout << "A" << a + 1;
        return;
    }
    cout << "(";
    MatChainSol(a, D[a][b]);
    cout << " x ";
    MatChainSol(D[a][b], b);
    cout << ")";
}

void Compute() {
    int test = 1;
    while (true) {
        int n;
        cin >> n;
        if (n == 0) {
            break;
        }
        for (int i = 0; i < n; i++) {
            cin >> p[i] >> p[i + 1];
        }
        MatChainTopDown(n);
        //MatChainBottomUp(n);
        cout << "Case " << test++ << ": ";
        MatChainSol(0, n);
        cout << endl;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    // freopen("input_assign10_00348.txt", "r", stdin);
    Compute();
    return 0;
}
