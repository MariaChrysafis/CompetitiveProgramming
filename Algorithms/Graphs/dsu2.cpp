#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <ctime>

using namespace std;

class Node {
public: Node* parent;
public: Node* next;
public: int val;
public: int subtreeSize = 0;

    Node(Node *parent, Node *next, int val, int subtreeSize) : parent(parent), next(next), val(val),
                                                               subtreeSize(subtreeSize) {}

    bool operator < (const Node& n1) const {
        return (n1.val < val);
    }
};


vector<pair<int,int>> generate_random (int size, int max_node) {
    vector<pair<int,int>> vec;
    for (int i = 0; i < size; i++) {
        int u = rand() % max_node;
        int v = rand() % max_node;
        vec.emplace_back(u, v);
    }
    return vec;
}


class DisjointSetUnion {
protected:
    vector<int> parent;
    vector<int> compSize;
    const int n;
    int connectedComponents;
public:
    int getConnectedComponents() const {
        return connectedComponents;
    }

public:
    DisjointSetUnion(int sz) : n(sz), connectedComponents(sz) {
        parent.resize(sz), compSize.resize(sz);
        for (int i = 0; i < n; i++) {
            parent[i] = i, compSize[i] = 1;
        }
    }

    int find_head(int x) const {
        int cur = x;
        while (cur != parent[cur]) {
            cur = parent[cur];
        }
        return cur;
    }

    void join(int x, int y) {
        x = find_head(x);
        y = find_head(y);
        if (x == y) {
            return;
        }
        if (compSize[x] > compSize[y]) {
            swap(x, y);
            //ensures that compSize[x1] <= compSize[y1]
        }
        parent[x] = y;
        compSize[y] += compSize[x];
        connectedComponents--;
    }

    bool comp(int x, int y) {
        return (find_head(x) == find_head(y));
    }
};

class DisjointSetUnionNode : public DisjointSetUnion {
public:
    DisjointSetUnionNode(int sz) : DisjointSetUnion(sz), vec(sz) {
        for (int i = 0; i < sz; i++) {
            Node* tmp = new Node(nullptr, nullptr, i, 1);
            tmp->parent = tmp;
            tmp->next = tmp;
            vec[i] = tmp;
        }
    }

private:
    vector<Node*> vec;
public:

    int find_head(int x) {
        return find_parent(vec[x])->val;
    }

    Node* find_parent (Node* x) {
        Node* cur = x;
        while ((cur->parent) != nullptr) {
            cur = cur->parent;
        }
        Node* par = cur;
        cur = x;
        while ((cur->parent) != nullptr) {
            cur->parent = par;
            cur = cur->parent;
        }
        return (x->parent = par);
    }

    void join (int a, int b) {
        join(vec[a], vec[b]);
    }

    void join (Node* a1, Node* b1) {
        Node* a = find_parent(a1);
        Node* b = find_parent(b1);
        if (a == b) {
            return;
        }
        if (a->subtreeSize > b->subtreeSize) {
            swap(a, b);
        }
        assert(a->subtreeSize <= b->subtreeSize);
        a->parent = b;
        b->subtreeSize += a->subtreeSize;
        Node* b_nxt = b->next;
        b->next = a->next;
        a->next = b_nxt;
        connectedComponents--;
    }

    int getConnectedComponents() const {
        return connectedComponents;
    }


};

class DisjointSetUnionwithCompression : public DisjointSetUnion {
public: DisjointSetUnionwithCompression(int sz) : DisjointSetUnion(sz) {
    }

    int find_head(int x) {
        int cur = x;
        while (cur != parent[cur]) {
            cur = parent[cur];
        }
        int par = cur;
        cur = x;
        while (cur != parent[cur]) {
            parent[cur] = par;
            cur = parent[cur];
        }
        return cur;
    }
};

void tester(vector<pair<int,int>> vec, DisjointSetUnion *pDisjointSetUnion, int sz, string name) {
    cout << name << '\n';
    int cntr = 0;
    srand(time(nullptr));
    auto start = chrono::steady_clock::now();
    while (pDisjointSetUnion->getConnectedComponents() != 1) {
        pDisjointSetUnion->join(vec[cntr].first, vec[cntr].second);
        cntr++;
    }
    auto finish = chrono::steady_clock::now();
    cout << chrono::duration_cast<chrono::milliseconds>(finish - start).count() << "ms\n";
    cout << setprecision(9) << cntr << " " << 0.5f * sz * log(sz) << '\n';
}

int main() {
    int sz = 1000000;
    srand(time(nullptr));
    vector<pair<int,int>> vec(10 * sz);
    for (int i = 0; i < vec.size(); i++) {
        vec[i].first = rand() % sz;
        vec[i].second = rand() % sz;
    }
    unique_ptr<DisjointSetUnion> pDisjointSetUnion = std::unique_ptr<DisjointSetUnion> (new DisjointSetUnion(sz));
    tester(vec, pDisjointSetUnion.get(), sz, "dimitri");

    unique_ptr<DisjointSetUnionwithCompression> disjointSetUnionwithCompression = std::unique_ptr<DisjointSetUnionwithCompression> (new DisjointSetUnionwithCompression(sz));
    tester(vec, disjointSetUnionwithCompression.get(), sz, "maria");

    unique_ptr<DisjointSetUnionNode> disjointSetUnionNode = std::unique_ptr<DisjointSetUnionNode> (new DisjointSetUnionNode(sz));
    tester(vec, disjointSetUnionNode.get(), sz, "christos");
}
