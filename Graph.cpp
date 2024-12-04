
// GROUP:   Data Science DS2
// ID:      20227020
// Assign:  03
// Assign:  Graphs
// UVA:     924
// Name:  Farida Hamid Mohamed Fathi

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

    void Initialize()
    {
        n = 0;
        sz = 10;
        arr = new Value[sz];
    }

    void Destroy()
    {
        delete[] arr;
    }

    void AddLast(Value v)
    {
        if(n == sz)
        {
            sz*=2;
            Value* new_arr = new Value[sz];
            for(int i = 0; i < n; i++)
            {
                new_arr[i] = arr[i];
            }
            delete[] arr;
            arr = new_arr;
        }
        arr[n++] = v;
    }

    void RemoveLast()
    {
        if(n>0) {
            n--;
        }
    }

    Value& operator[](int i)
    {
        return arr[i];
    }
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct Node
{
    Array<int> adj;

    void Initialize()
    {
        adj.Initialize();
    }

    void Destroy()
    {
        adj.Destroy();
    }
};

struct Graph
{
    int n;
    Node* nodes;

    void Initialize(int _n)
    {
        n = _n;
        nodes = new Node[n];
        for(int i = 0; i < n; i++)
        {
            nodes[i].Initialize();
        }
    }

    void Destroy()
    {
        for(int i = 0; i < n; i++)
        {
            nodes[i].Destroy();

        }
        delete[] nodes;
    }
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class Type>
struct Queue
{
    int f, n;
    Type* elems;

    void Initialize(int size)
    {
        f = n = 0;
        elems = new Type[size];
    }

    void Destroy()
    {
        delete[] elems;
    }

    void Add(Type t)
    {
        elems[n++] = t;
    }

    Type Pop()
    {
        if(f == n)
        {
            return -1;
        }
        return elems[f++];
    }

    Type Peek()
    {
        return elems[f];
    }

    int Num()
    {
        return n-f;
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    int e;
    cin >> e;
    Graph graph;
    graph.Initialize(e);

    for (int i = 0; i < e; i++) {
        int f_num;
        cin >> f_num;
        for (int j = 0; j < f_num; j++) {
            int f;
            cin >> f;
            graph.nodes[i].adj.AddLast(f);
        }
    }

    int test;
    cin >> test;

    while (test > 0) {
        Queue<int> que;
        que.Initialize(e);
        int *visit = new int[e];
        int *count = new int[e];
        for (int k = 0; k < e; k++) {
            visit[k] = 0;
            count[k] = 0;
        }

        int s;
        cin >> s;
        que.Add(s);
        visit[s] = 1;
        int max_s = 0;
        int first_day;

        while (que.Num() > 0) {
            int pop = que.Pop();
            for (int i = 0; i < graph.nodes[pop].adj.n; i++) {
                int f = graph.nodes[pop].adj[i];
                if (visit[f] == 0) {
                    visit[f] = visit[pop] + 1;
                    que.Add(f);
                    count[visit[f]] += 1;
                    if (max_s < count[visit[f]]) {
                        max_s = count[visit[f]];
                        first_day = visit[f];
                    }
                }
            }
        }

        if (graph.nodes[s].adj.n < 1) {
            cout << 0 << endl;
        }
        else
        {
            cout << max_s << " " << first_day - 1 << endl;
        }

        que.Destroy();
        test--;
    }

    graph.Destroy();
}

