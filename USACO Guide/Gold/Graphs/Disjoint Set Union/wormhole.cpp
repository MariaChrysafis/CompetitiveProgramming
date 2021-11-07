#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <algorithm>
#include <unordered_map>
#define maxN 100005
using namespace std;
struct Pair{
    int neighbor;
    int weight;
};
int N;
int M;
int P[maxN];
bool hasVisited[maxN];
int compNum[maxN];
int curComp = 1;
unordered_map<int,vector<Pair>> adj;
void DFS(int x, int maxW){
    hasVisited[x] = true;
    compNum[x] = curComp;
    for(Pair p: adj[x]){
        if(p.weight < maxW || hasVisited[p.neighbor]){
            continue;
        }
        DFS(p.neighbor,maxW);
    }
}
void reset(){
    for(int i = 0; i < N; i++){
        hasVisited[i] = false;
    }
}
bool isValid(int maxW){
    reset();
    for(int j = 0; j < N; j++){
        if(hasVisited[j] == false){
            DFS(j,maxW);
            curComp++;
        }
    }
    for(int i = 0; i < N; i++){
        if(compNum[i] != compNum[P[i]]){
            return false;
        }
    }
    return true;
}
int GetLeftPosition(int l, int r, int key){
    int m;
  
    while( r - l > 1 ){
        m = l + (r - l)/2;
        if(isValid(m) == key)
            r = m;
        else
            l = m;
    }
    return r;
}
int main(){
    freopen("wormsort.in", "r", stdin);
    freopen("wormsort.out", "w", stdout);
    cin >> N >> M;
    for(int i = 0; i < N; i++){
        cin >> P[i];
        P[i]--;
    }
    for(int i = 0; i < M; i++){
        int a,b,c;
        cin >> a >> b >> c;
        a--;
        b--;
        Pair p1 = {b,c};
        Pair p2 = {a,c};
        adj[a].push_back(p1);
        adj[b].push_back(p2);
    }
    int x = GetLeftPosition(0, 1000000001, false);
    if(x == 1000000001){
        cout << -1 << endl;
        return 0;
    }
    cout << x - 1 << endl;
}
