#include <iostream>
#include <vector>
using namespace std;
vector<bool> hasVisited;
vector<vector<int>> adj;
vector<vector<char>> resp;
void dfs(int x, int orig){
    hasVisited[x] = true;
    resp[orig][x] = 'Y';
    for(int i = max(x - 1, 0); i < min(x + 2, (int)adj.size()); i++){
        if(adj[x][i] && !hasVisited[i]){
            dfs(i, orig);
        }
    }
}
void solve(bool lastTestCase){
    int n;
    cin >> n;
    string s1, s2;
    cin >> s1 >> s2;
    adj.resize(n);
    for(int i = 0; i < n; i++){
        adj[i].resize(n);
        for(int j = 0; j < n; j++){
            if(abs(i - j) == 1){
                adj[i][j] = 1;
            }else{
                adj[i][j] = 0;
            }
        }
    }
    for(int i = 0; i < n; i++){
        if(s1[i] == 'N'){
            if(i + 1 < n) adj[i + 1][i] = 0;
            if(i >= 1) adj[i - 1][i] = 0;
        }
    }
    for(int i = 0; i < n; i++){
        if(s2[i] == 'N'){
            if(i + 1 < n) adj[i][i + 1] = 0;
            if(i >= 1) adj[i][i - 1] = 0;
        }
    }
    resp.resize(n);
    for(int i = 0; i < n; i++){
        resp[i].resize(n);
        for(int j = 0; j < n; j++){
            resp[i][j] = 'N';
        }
    }
    hasVisited.resize(n);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            hasVisited[j] = false;
        }
        dfs(i, i);
    }
    for(int i = 0; i < resp.size(); i++){
        for(int j = 0; j < resp.size(); j++){
            cout << resp[i][j];
        }
        if(!lastTestCase || i != resp.size() - 1) cout << endl;
    }
}
int main(){
    int t;
    cin >> t;
    for(int i = 0; i < t; i++){
        cout << "Case #" << i + 1 << ":\n";
        solve((i == t - 1));
    }
}
