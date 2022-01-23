#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <map>
#include <algorithm>
#include <set>
#include <queue>
#include <stack>
#include <list>
#include <cstring>

using namespace std;
typedef long long ll;

struct Node {
    Node () {
        this->sub = 0;
        this->child[0] = this->child[1] = nullptr;
    }

    Node* child[2];
    int sub;
    bool full = true;
    int val = -1;
};

vector<ll> powr;

Node* root = new Node();

void add_node (ll x) {
    Node* cur = root;
    for (int i = 40; i >= 0; i--) {
        bool bit = (x & powr[i]);
        if (cur->child[bit] == nullptr) {
            cur->child[bit] = new Node();
            cur->child[bit]->val = bit;
        }
        cur = cur->child[bit];
    }
}

int fill_sub (Node* rt = root) {
    for (int i = 0; i < 2; i++) {
        if (rt->child[i] != nullptr) {
            rt->sub += fill_sub(rt->child[i]);
        }
    }
    if (!(rt->sub)) {
        rt->sub = 1;
    }
    return rt->sub;
}

bool fill_full (Node* rt = root) {
    if (rt->child[0] == nullptr && rt->child[1] == nullptr) {
        return (rt->full = true);
    }
    bool fine = true;
    for (int i = 0; i < 2; i++) {
        if (rt->child[i] == nullptr || !fill_full(rt->child[i])) {
            fine = false;
        }
    }
    //cout << "YES\n";
    return (rt->full = fine);
}

int rec (Node* cur, ll x, int depth) {
    //cout << cur->val;
    assert(depth >= 1);
    vector<int> trav = {0, 1};
    if (x & powr[depth - 1]) {
        swap(trav[0], trav[1]);
    }
    if (cur->child[trav[0]] == nullptr) {
        //cout << "YES\n";
        return 0;
    }
    if (cur->child[trav[0]]->full) {
        //cout << depth << '\n';
        if (cur->child[trav[1]] == nullptr) {
            return cur-> child[trav[0]]->sub;
        } else {
            return rec(cur->child[trav[1]], x, depth - 1) + cur->child[trav[0]]->sub;
        }
    }
    return rec(cur->child[trav[0]], x, depth - 1);
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    powr = {1};
    while (powr.size() <= 50) {
        powr.push_back(powr.back() * 2);
    }
    int DEPTH = 41;
    int N, M;
    cin >> N >> M;
    int arr[N];
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
        add_node(arr[i]);
    }
    fill_sub();
    fill_full();
    int pref = 0;
    while (M--) {
        int x;
        cin >> x;
        pref ^= x;
        cout << rec(root, pref, DEPTH) << '\n';
    }
}
