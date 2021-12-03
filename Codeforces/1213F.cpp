#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <cstdint>
#include <cassert>
#include <bit>
#include <bitset>
#include <map>
#include <list>
#include <stack>
#include <algorithm>

#define ll long long
using namespace std;

class Graph {
    int V;
    list<int> *adj;

    void fillOrder(int v, bool visited[], stack<int> &Stack);

    void DFSUtil(int v, bool visited[]);

public:
    Graph(int V);

    void addEdge(int v, int w);

    void printSCCs();

    Graph getTranspose();
};

Graph::Graph(int V) {
    this->V = V;
    adj = new list<int>[V];
}

vector<vector<int>> dum = {{}};

void Graph::DFSUtil(int v, bool visited[]) {
    visited[v] = true;
    dum.back().push_back(v);
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            DFSUtil(*i, visited);
}

Graph Graph::getTranspose() {
    Graph g(V);
    for (int v = 0; v < V; v++) {
        list<int>::iterator i;
        for (i = adj[v].begin(); i != adj[v].end(); ++i) {
            g.adj[*i].push_back(v);
        }
    }
    return g;
}

void Graph::addEdge(int v, int w) {
    adj[v].push_back(w); // Add w to v’s list.
}

void Graph::fillOrder(int v, bool visited[], stack<int> &Stack) {
    visited[v] = true;
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            fillOrder(*i, visited, Stack);
    Stack.push(v);
}

void Graph::printSCCs() {
    stack<int> Stack;
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;
    for (int i = 0; i < V; i++)
        if (visited[i] == false)
            fillOrder(i, visited, Stack);
    Graph gr = getTranspose();
    for (int i = 0; i < V; i++)
        visited[i] = false;

    while (Stack.empty() == false) {
        int v = Stack.top();
        Stack.pop();

        if (visited[v] == false) {
            gr.DFSUtil(v, visited);
            dum.push_back({});
        }
    }
}

vector<int> topoSort(vector<vector<int>> adj) {
    vector<int> inDeg;
    inDeg.assign(adj.size(), 0);
    for (int i = 0; i < adj.size(); i++) {
        for (int j: adj[i]) {
            //i -> j
            inDeg[j]++;
        }
    }
    queue<int> q;
    for (int i = 0; i < adj.size(); i++) {
        if (!inDeg[i]) {
            q.push(i);
        }
    }
    vector<int> ans;
    while (!q.empty()) {
        int curNode = q.front();
        ans.push_back(curNode);
        q.pop();
        for (int i: adj[curNode]) {
            inDeg[i]--;
            if (!inDeg[i]) {
                q.push(i);
            }
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, k;
    cin >> n >> k;
    Graph g(n);
    vector<int> p1(n), p2(n);
    for (int i = 0; i < n; i++) {
        cin >> p1[i];
        p1[i]--;
    }
    for (int i = 0; i < n; i++) {
        cin >> p2[i];
        p2[i]--;
    }
    for (int i = 1; i < n; i++) {
        g.addEdge(p1[i], p1[i - 1]);
        g.addEdge(p2[i], p2[i - 1]);
    }
    g.printSCCs();
    map<int, int> myMap;
    for (int i = 0; i < dum.size(); i++) {
        for (int j = 0; j < dum[i].size(); j++) {
            myMap[dum[i][j]] = i;
        }
    }
    char arr[n];
    for (int i = 0; i < n; i++) arr[i] = '?';
    char cur = 'a';
    for (int i = 0; i < p1.size(); i++) {
        if (arr[p1[i]] == '?') {
            for (int j: dum[myMap[p1[i]]]) {
                arr[j] = cur;
            }
            cur++;
            cur = min(cur, 'z');
        }
    }
    if (dum.size() > k) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
        return 0;
    }
    for (char c: arr) {
        cout << c;
    }
    cout << endl;

}
