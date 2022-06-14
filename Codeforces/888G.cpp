#include <bits/stdc++.h>
using namespace std;
struct Node {
    Node* child[2];
    int64_t cost;
    int leaf;
    bool bit;
    Node () {
        child[0] = child[1] = nullptr, cost = 0;
    }
    Node (bool bit) {
        child[0] = child[1] = nullptr, cost = 0;
        this->bit = bit;
    }
};
Node* root;
int depth = 30;
void add_child (Node *cur, int x, int bt, int val) {
    if (bt == 1) {
        cur->child[x % 2] = new Node(x % 2);
        cur->child[x % 2]->leaf = x;
        return;
    }
    bool b = x & (1 << (bt - 1));
    if (cur->child[b] == nullptr) {
        cur->child[b] = new Node(b);
    }
    add_child(cur->child[b], x, bt - 1, val + x & (1 << (bt - 1)));
}
int best_fit (Node *cur, int x, int bt) {
    if (cur->child[0] == nullptr && cur->child[1] == nullptr) {
        return cur->leaf;
    }
    bool b = x & (1 << (bt - 1));
    if (cur->child[b] != nullptr) {
        return best_fit(cur->child[b], x, bt - 1);
    }
    return best_fit(cur->child[!b], x, bt - 1);
}
vector<int> eval (Node *cur, int bt) {
    if (cur->child[0] == nullptr && cur->child[1] == nullptr) {
        return {cur->leaf};
    }
    if (cur->child[0] != nullptr && cur->child[1] != nullptr) {
        vector<int> v1 = eval(cur->child[0], bt - 1);
        vector<int> v2 = eval(cur->child[1], bt - 1);
        cur->cost = cur->child[0]->cost + cur->child[1]-> cost;
        int ans = INT_MAX;
        for (int i: v1) {
            ans = min(ans, i ^ best_fit(cur->child[1], i, bt - 1));
        }
        cur->cost += ans;
        for (int i: v2) {
            v1.push_back(i);
        }
        return v1;
    }
    if (cur->child[1] != nullptr) {
        vector<int> v = eval(cur->child[1], bt - 1);
        cur->cost = cur->child[1]->cost;
        return v;
    }
    if (cur->child[0] != nullptr) {
        vector<int> v = eval(cur->child[0], bt - 1);
        cur->cost = cur->child[0]-> cost;
        return v;
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    root = new Node(0);
    int n;
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        add_child(root, arr[i], depth, 0);
    }
    eval(root, depth);
    cout << root->cost << '\n';
}
