#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <ctime>

using namespace std;

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

class DisjointSetUnionwithCompression : public DisjointSetUnion {
public: DisjointSetUnionwithCompression(int sz) : DisjointSetUnion(sz) {
    }

    int find_head(int x) {
        int cur = x;
        while (cur != parent[cur]) {
            cur = parent[cur];
        }
        return parent[x] = cur;
    }
};

void tester(DisjointSetUnion *pDisjointSetUnion, int sz, string name) {
    cout << name << '\n';
    int cntr = 0;
    srand(time(nullptr));
    auto start = chrono::steady_clock::now();
    while (pDisjointSetUnion->getConnectedComponents() != 1) {
        int u = rand() % sz;
        int v = rand() % sz;
        pDisjointSetUnion->join(u, v);
        cntr++;
    }
    auto finish = chrono::steady_clock::now();
    cout << chrono::duration_cast<chrono::milliseconds>(finish - start).count() << "ms\n";
    cout << setprecision(9) << cntr << " " << 0.5f * sz * log(sz) << '\n';
}

int main() {
    int sz = 3000000;
    unique_ptr<DisjointSetUnion> pDisjointSetUnion = std::unique_ptr<DisjointSetUnion> (new DisjointSetUnion(sz));
    tester(pDisjointSetUnion.get(), sz, "dimitri");

    unique_ptr<DisjointSetUnionwithCompression> disjointSetUnionwithCompression = std::unique_ptr<DisjointSetUnionwithCompression> (new DisjointSetUnionwithCompression(sz));
    tester(disjointSetUnionwithCompression.get(), sz, "maria");
}
