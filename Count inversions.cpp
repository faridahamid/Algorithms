#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////


long long CountInvMerge(long long* a, int n) {
    long long* temp = new long long[n];
    int mid = n / 2;
    int i = 0, j = mid, k = 0;
    long long inv_count = 0;


    while (i < mid && j < n) {
        if (a[i] <= a[j]) {
            temp[k++] = a[i++];
        } else {
            temp[k++] = a[j++];
            inv_count += (mid - i);
        }
    }


    while (i < mid) {
        temp[k++] = a[i++];
    }


    while (j < n) {
        temp[k++] = a[j++];
    }


    for (int m = 0; m < n; m++) {
        a[m] = temp[m];
    }

    delete[] temp;
    return inv_count;
}

long long CountInv(long long* a, int n) {
    if (n <= 1) return 0;

    int mid = n / 2;
    long long left_inv = CountInv(a, mid);
    long long right_inv = CountInv(a + mid, n - mid);
    long long merge_inv = CountInvMerge(a, n);

    return left_inv + right_inv + merge_inv;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    int n;
    while (true) {
        cin >> n;
        if (n == 0) {
            break;
        }

        long long* a = new long long[n];
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        long long inv_count = CountInv(a, n);
        cout << inv_count << endl;

        delete[] a;
    }

    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
