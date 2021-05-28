#include <iostream>
#include <vector>
#include <stack>
using namespace std;
//code stolen (mostly) from https://cp-algorithms.com/graph/euler_path.html
int main() {
    int len;
    cin >> len;
    int n;
    cin >> n;
    vector<vector<int>> g(n, vector<int>(n));
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) g[i][j] = 1;
    vector<int> deg(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            deg[i] += g[i][j];
    }
    stack<int> st;
    st.push(0);
    vector<int> res;
    while (!st.empty()) {
        int v = st.top();
        int i;
        for (i = 0; i < n; ++i)
            if (g[v][i])
                break;
        if (i == n) {
            res.push_back(v);
            st.pop();
        } else {
            --g[v][i];
            st.push(i);
        }
    }
    res.pop_back();
    for(int i = 0; i < len; i++){
        putchar(res[i % res.size()] + 97);
    }
}
