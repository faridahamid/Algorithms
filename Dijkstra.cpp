// GROUP:   X
// ID:      XXXXXXXX
// Assign:  07
// Assign:  Dijkstra
// UVA:     10986
// Name:    XXX MY FULL NAME

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

    void Initialize() {
        n = 0;
        sz = 1;
        arr = new Value[sz];
    }

    void Destroy() {
        delete[] arr;
    }

    void AddLast(Value v) {
        if (n == sz) {
            sz *= 2;
            Value* new_arr = new Value[sz];
            for (int i = 0; i < n; ++i)
                new_arr[i] = arr[i];
            delete[] arr;
            arr = new_arr;
        }
        arr[n++] = v;
    }

    void RemoveLast() {
        if (n == 0) return;
        n--;
    }

    Value& operator[](int i) {
        return arr[i];
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Elem>
struct Heap
{
    int* pos;
    Array<Elem> a;
    bool (*IsBefore)(Elem&, Elem&);
    int case_num;
    int result;

    void Initialize(bool (*_IsBefore)(Elem&, Elem&), int n) {
        IsBefore = _IsBefore;
        a.Initialize();
        pos = new int[n];
        for (int i = 0; i < n; i++){
            pos[i] = -1;
        }
    }

    void Destroy() {
        delete[] pos;
        a.Destroy();
    }

    int Child(int i) {
        return 2 * i + 1;
    }

    int Parent(int i) {
        return (i - 1) / 2;
    }

    Elem GetFirst() {
        return a[0];
    }

    Elem RetrieveFirst() {
        Elem f = a[0];
        a[0] = a[a.n - 1];
        a.RemoveLast();
        MoveDown(0);
        return f;
    }

    void Add(Elem e) {
        a.AddLast(e);
        MoveUp(a.n - 1);
    }

    void MoveUp(int ind) {
        if (ind == 0) return;
        int parent = Parent(ind);
        if (IsBefore(a[ind], a[parent])) {
            Elem temp = a[ind];
            a[ind] = a[parent];
            a[parent] = temp;
            MoveUp(parent);
        }
    }

    void MoveDown(int ind) {
        int l = Child(ind);
        int r = l + 1;
        int small = ind;
        if (l < a.n && IsBefore(a[l], a[small])) small = l;
        if (r < a.n && IsBefore(a[r], a[small])) small = r;
        if (small != ind) {
            Elem x = a[ind];
            a[ind] = a[small];
            a[small] = x;
            MoveDown(small);
        }
    }


    void Print() {
        if (result == -1)
            cout << "Case #" << case_num << ": unreachable" << endl;
        else
            cout << "Case #" << case_num << ": " << result << endl;
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Edge
{
    int v;
    int w;
};

struct Node
{
    Array<Edge> adj;

    void Initialize() {
        adj.Initialize();
    }

    void Destroy() {
        adj.Destroy();
    }
};

struct Graph
{
    int n;
    Node* nodes;

    void Initialize(int _n) {
        n = _n;
        nodes = new Node[n];
        for (int i = 0; i < n; i++)
            nodes[i].Initialize();
    }

    void Destroy() {
        for (int i = 0; i < n; i++)
            nodes[i].Destroy();
        delete[] nodes;
    }


    void add_e(int u, int v, int w) {
        Edge e;
        e.v = v;
        e.w = w;
        nodes[u].adj.AddLast(e);
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool IsBefore(Edge& a, Edge& b) {
    return a.w < b.w;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Dijkstra(Graph& g, int s, int e, Heap<Edge>& heap) {
    int infinity=1000000;
    Array<int> distances;
    distances.Initialize();
    for (int i = 0; i < g.n; i++){
        distances.AddLast(infinity);
    }
    distances[s] = 0;

    Edge start_edge = { s, 0 };
    heap.Add(start_edge);

    while (heap.a.n > 0) {
        Edge min_edge = heap.RetrieveFirst();
        int f = min_edge.v;

        if (f == e) {
            heap.result = distances[e];
            distances.Destroy();
            return;
        }

        for (int i = 0; i < g.nodes[f].adj.n; i++) {
            Edge e = g.nodes[f].adj[i];
            int v = e.v;
            int weight = e.w;

            if (distances[f] != infinity && distances[f] + weight < distances[v]) {
                distances[v] = distances[f] + weight;
                Edge new_edge = { v, distances[v] };
                heap.Add(new_edge);
            }
        }
    }

    heap.result = -1;
    distances.Destroy();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    int test;
    cin >> test;
    for (int i = 1; i <= test; i++) {
        int n, s, e, m;
        cin >> n >> m >> s >> e;
        Graph g;
        g.Initialize(n);

        for (int j = 0; j < m; j++) {
            int u, v, w;
            cin >> u >> v >> w;
            g.add_e(u, v, w);
            g.add_e(v, u, w);
        }

        Heap<Edge> heap;
        heap.Initialize(IsBefore, n);
        heap.case_num = i;

        Dijkstra(g, s, e, heap);

        heap.Print();

        heap.Destroy();
        g.Destroy();
    }

    return 0;
}
