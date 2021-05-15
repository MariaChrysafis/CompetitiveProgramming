#include <iostream>
#include <map>
#include <vector>
using namespace std;
int n, m;
vector<vector<vector<int>>> myMap;
vector<vector<int>> v1;
vector<vector<int>> v2;
const int INF = 100000000;
bool inBounds(int x1, int y1){
    if(x1 < 0 || x1 >= n || y1 < 0 || y1 >= m) return false;
    return true;
}
int Dist(pair<int,int> p, pair<int,int> p1){
    if(!inBounds(p.first, p.second) || !inBounds(p1.first,p1.second)) return INF;
    if(p.first == p1.first){
        if(p.second < p1.second) return v1[p.first][p.second];
        else return v1[p1.first][p1.second];
    }else{
        if(p.first < p1.first) return v2[p.first][p.second];
        else return v2[p1.first][p.second];
    }
}
int solve(pair<int,int> cur, int dist){
    if(!inBounds(cur.first,cur.second)) return INF;
    if(myMap[cur.first][cur.second][dist]) return myMap[cur.first][cur.second][dist];
    if(dist == 0){
        return 0;
    }
    int myMin = INF;
    for(int i = -1; i <= 1; i++){
        for(int j = -1; j <= 1; j++){
            if(abs(i) == abs(j)) continue;
            pair<int,int> to = {cur.first + i, cur.second + j};
            if(!inBounds(to.first,to.second)) continue;
            myMin = min(myMin, solve({cur.first + i, cur.second + j},dist - 1) + Dist(to,cur));
        }
    }
    myMap[cur.first][cur.second][dist] = myMin;
    return myMin;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;
    int k;
    cin >> k;
    v1.resize(n);
    myMap.resize(n);
    for(int i = 0; i < n; i++){
        myMap[i].resize(m);
        for(int j = 0; j < m; j++){
            myMap[i][j].resize(k);
            for(int a = 0; a < k; a++){
                myMap[i][j][a] = 0;
            }
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m - 1; j++){
            pair<int,int> cur = {i, j};
            pair<int,int> to = {i, j + 1};
            int w;
            cin >> w;
            v1[i].push_back(w);
        }
    }
    v2.resize(n - 1);
    for(int i = 0; i < n - 1; i++){
        for(int j = 0; j < m; j++){
            pair<int,int> cur = {i, j};
            pair<int,int> to = {i + 1, j};
            int w;
            cin >> w;
            v2[i].push_back(w);
        }
    }
    if(k % 2 == 1){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                cout << "-1 ";
            }
            cout << endl;
        }
        return 0;
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            pair<int,int> curNode = {i,j};
            int x = solve(curNode,k/2);
            cout << x * 2 << " ";
        }
        cout << endl;
    }
}
