#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <array>
#include <stack>
#include <map>
#include <set>
using namespace std;
const int INF = 1000000000;
int n;
set<pair<int,int>> edges;
vector<int> query(int u){
    cout << "? " << u + 1 << endl;
    vector<int> v(n);
    for(int i = 0; i < n; i++){
        cin >> v[i];
        if(v[i] == 1){
            edges.insert({min(i, u), max(i, u)});
        }
    }
    return v;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    int odd = 0;
    int even = 0;
    vector<int> orig = query(0);
    for(int i = 0; i < n; i++){
        if(orig[i] % 2 == 0){
            even++;
        }else{
            odd++;
        }
    }
    for(int i = 1; i < n; i++){
        if(odd >= even){
            if(orig[i] % 2 == 0){
                query(i);
            }
        }else{
            if(orig[i] % 2 == 1){
                query(i);
            }
        }
    }
    cout << endl;
    cout << "!" << endl;
    for(auto it = edges.begin(); it != edges.end(); it++){
        pair<int,int> p = *it;
        cout << p.first + 1 << " " << p.second + 1 << endl;
    }
}
