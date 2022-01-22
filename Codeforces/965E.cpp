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
    Node (char c, bool term) {
        for (int i = 0; i < 27; i++) {
            child[i] = nullptr;
        }
        val = c;
        this->term = term;
    }
    char val;
    Node* child[27];
    bool term;
};

vector<ll> powr;

Node* root = new Node('?', false);

void add_node (string s) {
    Node* cur = root;
    for (int i = 0; i < s.length(); i++) {
        if (cur->child[s[i] - 'a'] == nullptr) {
            cur->child[s[i] - 'a'] = new Node(s[i], false);
        }
        cur = cur->child[s[i] - 'a'];
    }
    cur->term = true;
}

vector<int> merge (vector<int> a, vector<int> b) {
    for (int i: b) {
        a.push_back(i);
    }
    return a;
}
int n;

vector<int> find_length (Node* st) {
    if (st == nullptr) {
        assert(false);
    }
    vector<int> vec;
    for (int i = 0; i < 26; i++) {
        if (st->child[i] == nullptr) {
            continue;
        }
        vector<int> v1 = find_length(st->child[i]);
        for (int j: v1) {
            //cout << "?" << j + 1;
            vec.push_back(j + 1);
        }
        //cout << '\n';
    }
    if (vec.empty()) {
        vector<int> ans; ans.push_back(1);
        return ans;
    }
    if (st->term) {
        vec.push_back(1);
    } else {
        sort(vec.begin(), vec.end());
        vec.pop_back();
        vec.push_back(1);
    }
    return vec;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    string arr[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        //arr[i] += '{';
        add_node(arr[i]);
        //cout << arr[i] << '\n';
    }
    vector<int> vec;
    for (int i = 0; i < 27; i++) {
        if (root->child[i] != nullptr) {
            //cout << "YES\n";
            vector<int> v1 = (find_length(root->child[i]));
            for (int j: v1) {
                vec.push_back(j);
            }
        }
    }
    int ans = 0;
    for (int i: vec) {
        ans += i;
    }
    cout << ans;
}
