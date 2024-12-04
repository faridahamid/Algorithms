#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iomanip>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Value>
struct Array
{
    int  n, sz;
    Value* arr;

    void Initialize()
    {
        n=0 ; sz = 1 ; arr = new Value [sz] ;
    }
    void Destroy()
    {
        delete [] arr;
    }
    void AddLast(Value v)
    {
        if (n == sz)
        {
            sz *= 2 ;
            Value *new_arr = new Value[sz] ;
            for (int i = 0 ; i < n ; ++i)
                new_arr[i] = arr[i] ;

            delete []arr ;
            arr = new_arr ;
        }
        arr[n++] = v ;
    }
    void RemoveLast()
    {
        if (n==0)
            return;
        n--;
    }
    Value& operator[](int i)
    {
        return arr[i];
    }


};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Edge
{
    int		v;  // id of the adjacent node
    double	w;  // edge weight = distance between the two nodes
};

struct Node
{
    int x,y; // x and y coordinates of the node
    Array<Edge> adj;

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
        n=_n;
        nodes=new Node[n];
        for(int i=0;i<n;i++)
            nodes[i].Initialize();
    }
    void Destroy()
    {
        for(int i=0;i<n;i++)
            nodes[i].Destroy();
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////


double Sqrt(double v, int n=100)
{
    if (v < 0) return -1;
    double a = 0, b = v, m;
    for (int i = 0; i < n; i++) {
        m = (a + b) / 2.0;
        if (m * m > v) {
            b = m;
        } else {
            a = m;
        }
    }
    return (a + b) / 2.0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    Array<int>index;
    Array<double>min_distance;
    int test=1;
    while(true)
    {
        int n;
        cin>>n;
        if(n==0) {
            break;
        }
        Graph graph;
        graph.Initialize(n);
        for(int i=0;i<n;i++) {
            cin >> graph.nodes[i].x >> graph.nodes[i].y;
        }
        string space;
        getline(cin, space);

        for(int i=0;i<n;i++)
        {
            for(int x=0;x<n;x++)
            {
                Edge edge;
                edge.v=x;
                edge.w=Sqrt((graph.nodes[x].x-graph.nodes[i].x)*(graph.nodes[x].x-graph.nodes[i].x)
                            + (graph.nodes[x].y-graph.nodes[i].y)*(graph.nodes[x].y-graph.nodes[i].y));
                graph.nodes[i].adj.AddLast(edge);
            }
        }
        index.Initialize();
        min_distance.Initialize();
        int min_ind_x=-1,min_ind_y=-1;
        double minValue;
        index.AddLast(0);
        while(min_ind_y!=1)
        {
            min_ind_x=min_ind_y=-1;
            minValue=1000.0;
            for(int i=0;i<index.n;i++)
            {
                for(int x=0;x<n;x++)
                {
                    if(graph.nodes[index[i]].adj[x].w<minValue&&graph.nodes[index[i]].adj[x].w!=0)
                    {
                        minValue=graph.nodes[index[i]].adj[x].w;
                        min_ind_x=index[i];
                        min_ind_y=x;
                    }
                }
            }
            graph.nodes[min_ind_x].adj[min_ind_y].w=0;
            graph.nodes[min_ind_y].adj[min_ind_x].w=0;
            min_distance.AddLast(minValue);
            index.AddLast(min_ind_y);
        }
        double maximum=0.000;
        for(int i=0;i<min_distance.n;i++)
        {
            if(maximum<min_distance[i])
                maximum=min_distance[i];
        }
        cout<<"Scenario #"<<test<<endl;
        test++;
        cout<<"Frog Distance = "<<fixed<<setprecision(3)<<maximum<<endl;
        cout<<endl;
        min_distance.Destroy();
        index.Destroy();
        graph.Destroy();
    }
    return 0;
}
