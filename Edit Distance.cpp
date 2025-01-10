 #include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

char a[82];
char b[82];

int D[81][81];

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T1[81][81];


int EditDist1(int n, int m) {
    if (n == 0){
        return m;
    }
    if (m == 0){
        return n;
    }
    if (T1[n][m] != -1){
        return T1[n][m];
    }

    if (a[n - 1] == b[m - 1]) {
        T1[n][m] = EditDist1(n - 1, m - 1);
    } else {
        T1[n][m] = 1 + min(EditDist1(n - 1, m), min(EditDist1(n, m - 1), EditDist1(n - 1, m - 1)));
    }

    D[n][m] = T1[n][m];
    return T1[n][m];
}


int ComputeEditDist1(int N, int M) {
    for (int i = 0; i <= N; i++)
        for (int j = 0; j <= M; j++)
            T1[i][j] = -1;

    int result = EditDist1(N, M);

    for (int i = 0; i <= N; i++)
        for (int j = 0; j <= M; j++)
            D[i][j] = T1[i][j];

    return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T2[81][81];

int ComputeEditDist2(int N, int M) {
    for (int i = 0; i <= N; i++){
     T2[i][0] = i;
    }
    for (int j = 0; j <= M; j++){
        T2[0][j] = j;
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            if (a[i - 1] == b[j - 1]){
                T2[i][j] = T2[i - 1][j - 1];
            }
            else T2[i][j] = 1 + min(T2[i - 1][j], min(T2[i][j - 1], T2[i - 1][j - 1]));
        }
    }

    for (int i = 0; i <= N; i++)
        for (int j = 0; j <= M; j++)
            D[i][j] = T2[i][j];

    return T2[N][M];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////


int T3[2][81];

int ComputeEditDist3(int N, int M) {
    int cur = 0;
    for (int j = 0; j <= M; j++){
        T3[cur][j] = j;
    }

    for (int i = 1; i <= N; i++) {
        cur = 1 - cur;
        T3[cur][0] = i;

        for (int j = 1; j <= M; j++) {
            if (a[i - 1] == b[j - 1]){
                T3[cur][j] = T3[1 - cur][j - 1];
            }
            else T3[cur][j] = 1 + min(T3[1 - cur][j], min(T3[cur][j - 1], T3[1 - cur][j - 1]));
        }


        for (int j = 0; j <= M; j++){
            D[i][j] = T3[cur][j];
        }
    }
    return T3[cur][M];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////


int T4[81];

int ComputeEditDist4(int N, int M) {
    for (int j = 0; j <= M; j++){
        T4[j] = j;
    }

    for (int i = 1; i <= N; i++) {
        int prev = T4[0];
        T4[0] = i;

        for (int j = 1; j <= M; j++) {
            int temp = T4[j];
            if (a[i - 1] == b[j - 1]){
                T4[j] = prev;
            }
            else T4[j] = 1 + min(prev, min(T4[j - 1], T4[j]));
            prev = temp;

            D[i][j] = T4[j];
        }
    }
    return T4[M];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////


int EditDistSol(int N, int M) {
    int i = N, j = M;
    int op_count = 0;

    while (i > 0 || j > 0) {
        if (i > 0 && j > 0 && a[i - 1] == b[j - 1]) {

            i--;
            j--;
        }
        else if (j > 0 && D[i][j] == D[i][j - 1] + 1) {

            cout << ++op_count << " Insert " << (i + 1) << "," << b[j - 1] << endl;
            j--;
        }
        else if (i > 0 && D[i][j] == D[i - 1][j] + 1) {

            cout << ++op_count << " Delete " << i << endl;
            i--;
        }
        else if (i > 0 && j > 0 && D[i][j] == D[i - 1][j - 1] + 1) {

            cout << ++op_count << " Replace " << i << "," << b[j - 1] << endl;
            i--;
            j--;
        }
        else if (j > 0) {

            cout << ++op_count << " Insert " << (i + 1) << "," << b[j - 1] << endl;
            j--;
        }
        else if (i > 0) {

            cout << ++op_count << " Delete " << i << endl;
            i--;
        }
    }

    return 0;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////


int ComputeEditDist(int N, int M) {
    //return ComputeEditDist1(N, M);
    return ComputeEditDist2(N, M);
    //return ComputeEditDist3(N, M);
     //return ComputeEditDist4(N, M);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Compute() {
    int cas = 0;
    while (true) {
        a[0] = 0; b[0] = 0;
        if (!fgets(a, 82, stdin)) break;
        fgets(b, 82, stdin);

        a[strlen(a) - 1] = 0;
        b[strlen(b) - 1] = 0;

        if (cas) cout << endl;
        int N = strlen(a), M = strlen(b);
        cout << ComputeEditDist(N, M) << endl;
        EditDistSol(N, M);
        cas++;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    Compute();
    return 0;
}
