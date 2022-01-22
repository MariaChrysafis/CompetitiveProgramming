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

Node* root = new Node(0);

void add_node (int x) {
    Node* cur = root;
    for (int i = 18; i >= 0; i--) {
        bool bit = (x & (1 << i));
        if (cur->child[bit] == nullptr) {
            cur->child[bit] = new Node(bit);
        }
        cur = cur->child[bit];
    }
}

int find_best_xor (int x) {
    int ans = 0;
    Node* cur = root;
    for (int i = 18; i >= 0; i--) {
        bool bit = (x & (1 << i));
        assert(cur != nullptr);
        if (cur->child[!bit] != nullptr) {
            cur = cur->child[!bit];
            ans += (1 << i);
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
    int n;
    cin >> n;
    int arr[n];
    int pref = 0;
    add_node(pref);
    int myMax = 0;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        pref ^= arr[i];
        myMax = max(myMax, find_best_xor(pref));
        add_node(pref);
    }
    cout << myMax;
}
