#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <climits>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <iomanip>
using namespace std;
struct dsu{
    vector<int> parent;
    vector<int> compSize;
    int cc;
    int myMax = 1;
    int n;
    void fill(){
        parent.resize(n), compSize.resize(n);
        cc = n;
        for(int i = 0; i < n; i++){
            parent[i] = i, compSize[i] = 1;
        }
    }
    int find_head(int x){
        if(x == parent[x]){
            return x;
        }
        return find_head(parent[x]);
    }
    void join(int x, int y){
        x = find_head(x);
        y = find_head(y);
        if(x == y){
            return;
        }
        if(compSize[x] > compSize[y]){
            swap(x,y);
        }
        parent[x] = y;
        compSize[y] += compSize[x];
        myMax = max(myMax, compSize[y]);
        cc--;
    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M;
    cin >> N >> M;
    dsu d;
    d.n = N;
    d.fill();
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        d.join(a, b);
        cout << d.cc << " " << d.myMax << '\n';
    }
}
