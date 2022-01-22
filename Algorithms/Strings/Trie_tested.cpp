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
    Node (bool b) {
        this->val = b;
        this->child[0] = this->child[1] = nullptr;
        //child[0] = child[1] = nullptr;
    }

    Node* child[2];
    bool val;
};

vector<ll> powr;

Node* root = new Node(0);

void add_node (ll x) {
    Node* cur = root;
    for (int i = 41; i >= 0; i--) {
        bool bit = (x & powr[i]);
        if (cur->child[bit] == nullptr) {
            cur->child[bit] = new Node(bit);
        }
        cur = cur->child[bit];
    }
}

ll find_best_xor (ll x) {
    ll ans = 0;
    Node* cur = root;
    for (int i = 41; i >= 0; i--) {
        bool bit = (x & powr[i]);
        assert(cur != nullptr);
        if (cur->child[!bit] != nullptr) {
            cur = cur->child[!bit];
            ans += powr[i];
            continue;
        } else {
            if (cur->child[bit] != nullptr) {
                cur = cur->child[bit];
                continue;
            }
            break;
        }
    }
    return ans;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    powr = {1};
    while (powr.size() <= 50) {
        powr.push_back(powr.back() * 2);
    }
    ll n;
    cin >> n;
    ll arr[n];
    ll tot = 0;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        tot ^= arr[i];
    }
    ll pref = 0;
    add_node(pref);
    ll myMax = tot;
    for (int i = 0; i < n; i++) {
        pref ^= arr[i];
        myMax = max(myMax, find_best_xor(pref ^ tot));
        add_node(pref);
    }
    cout << myMax;
}
