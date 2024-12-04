// GROUP:   Data Science 3
// ID:      20227020
// Assign:  01
// Assign:  ArrayHeap
// UVA:     10954
// Name:    Farida Hamid Mohamed Fathi Hamid

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Value>
struct Array
{
	int  n, sz;
	Value* arr;

	void Initialize();
       
	void Destroy();
	void AddLast(Value v);
	void RemoveLast();
	Value& operator[](int i);
};

template<class Value>
void Array<Value>::Initialize() {
    n=0;
    sz=10;
    arr=new Value[sz];
}

template<class Value>
void Array<Value>::Destroy(){
    delete [] arr;
}
template<class Value>
void Array<Value>::AddLast(Value v){
    if(n==sz){
        sz=sz*2;
        Value*arr2=new Value[sz];
        for (int i=0;i<n;i++) {
            arr2[i] = arr[i];
        }
        delete[] arr;
        arr=arr2;



    }
    arr[n++]=v;
}
template <class Value>
void Array<Value>::RemoveLast() {
    if(n>0){
        n--;
    }
    if(n>0 && n<(sz/4)){
        sz=sz/2;
        Value*arr3=new Value[sz];
        for (int i=0;i<n;i++) {
            arr3[i] = arr[i];
        }
        delete[] arr;
        arr=arr3;
    }

}

template<class Value>
Value& Array<Value>::operator[](int i) {
    return arr[i];

}



////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Elem>
struct Heap
{
	Array<Elem> a;
	bool (*IsBefore)(Elem&, Elem&);

	void Initialize(bool (*_IsBefore)(Elem&, Elem&));
	void Destroy();
	int Child(int i);
	int Parent(int i);
	void MoveUp(int ind);
	void MoveDown(int ind);
	void Add(Elem e);
	Elem GetFirst();
	Elem RetrieveFirst();
};

template<class Elem>
void Heap<Elem>::Initialize(bool (*_IsBefore)(Elem&, Elem&)){
    a.Initialize();
    IsBefore=_IsBefore;

}

template<class Elem>
void Heap<Elem>::Destroy() {
    a.Destroy();
}

template<class Elem>
int Heap<Elem>::Child(int i) {
    return 2*i+1;
}

template<class Elem>
int Heap<Elem>::Parent(int i) {
    return (i-1)/2;
}
template<class Elem>
void Heap<Elem>::MoveUp(int ind) {
    if (ind == 0) {
        return;
    }

    int parent = Parent(ind);
    if (IsBefore(a[ind], a[parent])) {
        Elem temp = a[ind];
        a[ind] = a[parent];
        a[parent] = temp;
        MoveUp(parent);
    }
}



template<class Elem>
void Heap<Elem>::MoveDown(int ind) {
    int l=Child(ind);
    int r=l+1;
    int small=ind;
    if(l<a.n && IsBefore(a[l],a[small])){
        small=l;
    }
    if(r<a.n &&IsBefore(a[r],a[small])){
        small=r;
    }
    if(small !=ind){
        Elem x= a[ind];
        a[ind] = a[small];
        a[small] = x;
        MoveDown(small);
    }
}
template<class Elem>
void Heap<Elem>::Add(Elem e) {
    a.AddLast(e);
    MoveUp(a.n-1);
}

template<class Elem>
Elem Heap<Elem>::GetFirst() {
    return a[0];

}
template<class Elem>
Elem Heap<Elem>::RetrieveFirst(){
    Elem f = a[0];
    a[0] = a[a.n - 1];
    a.RemoveLast();
    MoveDown(0);
    return f;
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool IsBeforeInt(int& a, int& b)
{
	return a<b;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
   int main() {
        int f;
        while (true) {
            cin >> f;
            if (f == 0) {
                break;
            }

            Heap<int> h;
            h.Initialize(IsBeforeInt);
            int totalCost = 0;

            for (int i = 0; i < f; i++) {
                int num;
                cin >> num;
                h.Add(num);
            }
            while (h.a.n > 1) {
                int first = h.RetrieveFirst();
                int second = h.RetrieveFirst();
                int cost = first + second;
                totalCost += cost;
                h.Add(cost);
            }

            cout << totalCost << endl;
            h.Destroy();
        }

        return 0;
   }





////////////////////////////////////////////////////////////////////////////////////////////////////////////
