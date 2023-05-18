#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

typedef pair<int, int> iPair;

class Graph
{
private:
    int V;
    vector<vector<iPair>> adj;

public:
    Graph(int V);
    void addEdge(int u, int v, int w);
    void shortestPath(int src);
    void primMST();
    void DFS(int v, vector<bool> &visited);
    void BFS(int src);
};

Graph::Graph(int V)
{
    this->V = V;
    adj.resize(V);
}

void Graph::addEdge(int u, int v, int w)
{
    adj[u].push_back(make_pair(v, w));
    adj[v].push_back(make_pair(u, w));
}

void Graph::shortestPath(int src)
{
    priority_queue<iPair, vector<iPair>, greater<iPair>> pq;
    vector<int> dist(V, INT_MAX);
    pq.push(make_pair(0, src));
    dist[src] = 0;
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        for (auto i : adj[u])
        {
            int v = i.first;
            int weight = i.second;
            if (dist[v] > dist[u] + weight)
            {
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
            }
        }
    }
    cout << "最短路径,起点 " << src << ":" << endl;
    for (int i = 0; i < V; ++i)
        cout << i << "\t\t" << dist[i] << endl;
}

void Graph::primMST()
{
    priority_queue<iPair, vector<iPair>, greater<iPair>> pq;
    int src = 0;
    vector<int> key(V, INT_MAX);
    vector<int> parent(V, -1);
    vector<bool> inMST(V, false);
    pq.push(make_pair(0, src));
    key[src] = 0;
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        inMST[u] = true;
        for (auto i : adj[u])
        {
            int v = i.first;
            int weight = i.second;
            if (inMST[v] == false && key[v] > weight)
            {
                key[v] = weight;
                pq.push(make_pair(key[v], v));
                parent[v] = u;
            }
        }
    }
    cout << "最小支撑树:" << endl;
    for (int i = 1; i < V; ++i)
        cout << parent[i] << " - " << i << endl;
}

void Graph::DFS(int v, vector<bool> &visited)
{
    visited[v] = true;
    cout << v << " ";
    for (auto i : adj[v])
    {
        int u = i.first;
        if (!visited[u])
        {
            DFS(u, visited);
        }
    }
}

void Graph::BFS(int src)
{
    vector<bool> visited(V, false);
    queue<int> q;
    visited[src] = true;
    q.push(src);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        cout << u << " ";
        for (auto i : adj[u])
        {
            int v = i.first;
            if (!visited[v])
            {
                visited[v] = true;
                q.push(v);
            }
        }
    }
}

int main()
{
    int V = 6;
    Graph g(V);
    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 3);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 2);
    g.addEdge(2, 3, 4);
    g.addEdge(3, 4, 2);
    g.addEdge(4, 5, 6);
    cout << "DFS测试,起点为0:" << endl;
    vector<bool> visited(V, false);
    for (int i = 0; i < V; ++i)
    {
        if (!visited[i])
        {
            g.DFS(i, visited);
        }
    }
    cout << "\nBFS测试,起点为4:" << endl;
    g.BFS(4);
    cout << endl;
    cout << endl;
    g.shortestPath(0);
    g.primMST();
    return 0;
}