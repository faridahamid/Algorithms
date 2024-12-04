// GROUP:   03 Data science DS2
// ID:      20227020
// Assign:  05
// Assign:  Kruskal
// UVA:     11631
// Name:    Farida Hamid Mohamed Fathi Hamid

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct DisjointSets
{
    int n;
    int* parent;
    int* num_nodes;

    void Initialize(int _n){
        n=_n;
        parent=new int [n];
        num_nodes=new int [n];
        for(int i=0;i< n;i++){
            parent[i]=i;
            num_nodes[i]=1;
        }


    }
    void Destroy(){
        delete[]num_nodes;
        delete[]parent;

    }
    int Find(int i){
        if (parent[i]==i){
            return i;
        }
        else{
            int result = Find(parent[i]);
            parent[i] = result;
            return result;
        }
    }
    bool Union(int i, int j){
        int root_fn=Find(i);
        int root_sn=Find(j);
        if (root_fn==root_sn){
            return false;
        }
        if (num_nodes[root_fn] < num_nodes[root_sn]) {
            parent[root_fn] = root_sn;
            num_nodes[root_sn] += num_nodes[root_fn];
        } else {
            parent[root_sn] = root_fn;
            num_nodes[root_fn] += num_nodes[root_sn];
        }

        return true;

    }
};

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

struct Edge
{
    int u, v;
    int w;
};

bool IsBeforeEdge(Edge& a, Edge& b)
{
    return a.w<b.w;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    int m, n;
    while (true) {
        cin >> m >> n;
        if (m == 0 && n == 0){
            break;
        }

        Edge* edges = new Edge[n];
        int total_cost = 0;

        for (int i = 0; i < n; i++) {
            cin >> edges[i].u >> edges[i].v >> edges[i].w;
            total_cost += edges[i].w;
        }


        MergeSort(edges, n, IsBeforeEdge);
        DisjointSets d;
        d.Initialize(m);

        int min_cost = 0;
        for (int i = 0; i < n; i++) {
            if (d.Union(edges[i].u, edges[i].v)) {
                min_cost += edges[i].w;
            }
        }


        d.Destroy();
        delete[] edges;
        int max = total_cost - min_cost;
        cout << max << endl;
    }
    return 0;
}
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////

