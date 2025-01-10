#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Obj {
    int v; // value (price) of object
    int w; // weight of object
};

Obj a[1000];


////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T1[1001][31];
bool D[1001][31];
int Knapsack1(int n, int w) {
    if (n == 0){
        return 0;
    }
    if (D[n][w]){
        return T1[n][w];
    }

    if (a[n - 1].w > w)
        T1[n][w] = Knapsack1(n - 1, w);
    else
        T1[n][w] = max(Knapsack1(n - 1, w), Knapsack1(n - 1, w - a[n - 1].w) + a[n - 1].v);
    D[n][w] = true;

    return T1[n][w];
}
int ComputeKnapsack1(int N, int W) {
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= W; j++) {
            D[i][j] = false;
        }
    }
    return Knapsack1(N, W);
}
int T2[1001][31];

int ComputeKnapsack2(int N, int W) {
    for (int w = 0; w <= W; w++) {
        T2[0][w] = 0;
    }
    for (int n = 1; n <= N; n++) {
        for (int w = 0; w <= W; w++) {
            int v1 = 0, v2 = 0, v;

            if (w >= a[n - 1].w)
                v1 = a[n - 1].v + T2[n - 1][w - a[n - 1].w];
            v2 = T2[n - 1][w];

            if (v1 > v2) {
                v = v1;
                D[n][w] = true;
            } else {
                v = v2;
                D[n][w] = false;
            }

            T2[n][w] = v;
        }
    }
    return T2[N][W];
}
int T3[2][31];
int ComputeKnapsack3(int N, int W) {
    int cur = 0;
    for (int w = 0; w <= W; w++){
        T3[cur][w] = 0;
    }
    for (int n = 1; n <= N; n++) {
        cur = 1 - cur;
        for (int w = 0; w <= W; w++) {
            int v1 = 0, v2 = 0;


            if (w >= a[n - 1].w)
                v1 = a[n - 1].v + T3[1 - cur][w - a[n - 1].w];

            v2 = T3[1 - cur][w];

            T3[cur][w] = max(v1, v2);
        }
    }
    return T3[cur][W];
}
int T4[31];


int ComputeKnapsack4(int N, int W) {

    for (int w = 0; w <= W; w++) {
        T4[w] = 0;
    }

    for (int n = 1; n <= N; n++) {
        for (int w = W; w >= 0; w--) {
            if (w >= a[n - 1].w) {
                int v1 = a[n - 1].v + T4[w - a[n - 1].w];
                int v2 = T4[w];
                T4[w] = max(v1, v2);
            }
        }
    }
    return T4[W];
}

int ComputeKnapsack(int N, int W) // Here we can choose the method
{
    //return ComputeKnapsack1(N,W);
    //return ComputeKnapsack2(N,W);
    //return ComputeKnapsack3(N,W);
    return ComputeKnapsack4(N,W);
}
void Compute() {
    int test;
    cin >> test;

    while (test--) {
        int N;
        cin >> N;

        for (int i = 0; i < N; i++) {
            int P, W;
            cin >> P >> W;
            a[i] = {P, W};
        }

        int m;
        cin >> m;

        int total_value = 0;
        for (int i = 0; i < m; i++) {
            int max_w;
            cin >> max_w;

            total_value += ComputeKnapsack(N, max_w);
        }

        cout << total_value << endl;
    }
}
int main() {
    Compute();
    return 0;
}





