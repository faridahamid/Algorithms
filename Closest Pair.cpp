// GROUP:   03 DS2
// ID:      20227020
// Assign:  08
// Assign:  ClosetsPair
// UVA:     10245
// Name:    Farida Hamid Mohamed Fathi

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <cmath>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Type>
void Merge(Type* a, int n, bool (*IsBefore)(Type& a, Type& b)){
    int m=n/2;
    int i = 0, j = m, k = 0;
    Type* temp = new Type[n];

    while (i < m && j < n) {
        if (IsBefore(a[i], a[j])) {
            temp[k++] = a[i++];
        } else {
            temp[k++] = a[j++];
        }
    }

    while (i < m) {
        temp[k++] = a[i++];
    }

    while (j < n) {
        temp[k++] = a[j++];
    }

    for (i = 0; i < n; i++) {
        a[i] = temp[i];
    }

    delete[] temp;
}

template<class Type>
void MergeSort(Type* a, int n, bool (*IsBefore)(Type& a, Type& b)){
    if (n < 2) {
        return;
    }

    int m = n / 2;
    MergeSort(a, m, IsBefore);
    MergeSort(a + m, n - m, IsBefore);
    Merge(a, n, IsBefore);


}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Point
{
    double x,y;
};

bool IsBeforeX(Point& a, Point& b){
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}
bool IsBeforeY(Point& a, Point& b){
    return a.y<b.y || (a.y==b.y && a.x<b.x);
}

double dist(Point& a, Point& b){
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////


double ClosestPair(Point* p, int n){
    double infinity =1000000;
    if (n<2){
        return infinity;
    }
    MergeSort(p,n,IsBeforeX);
    Point *x=new Point[n];
    double close=infinity;
    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = i + 1; j < n && (p[j].x - p[i].x) < close; j++) {
            x[count++] = p[j];
        }
        MergeSort(x, count, IsBeforeY);

        for (int j = 0; j < count; j++) {
            for (int k = j + 1; k < count && (x[k].y - x[j].y) < close; k++) {
                double distance = dist(x[j], x[k]);
                if (distance < close) {
                    close = distance;
                }
            }
        }
    }

    delete[] x;
    return close;
}




////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(){
    while(true) {

        int n;
        cin >> n;
        if (n == 0) {
            break;
        }

        Point *points = new Point[n];

        for (int i = 0; i < n; i++) {
            cin >> points[i].x >> points[i].y;
        }


        double result = ClosestPair(points, n);


        cout.precision(4);
        cout << fixed;
        if (result >= 10000.0) {
            cout << "INFINITY" << endl;
        } else {
            cout << result << endl;
        }

        delete[] points;
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////