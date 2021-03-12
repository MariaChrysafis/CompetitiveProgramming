#include <iostream>
#include <stack>
#include <vector>
#include <map>
using namespace std;
const int INF = 10000000;
int solve(vector<int> v){
    stack<int> s;
    int n = v.size();
    map<int,int> oc, noc;
    for(int i = 0; i < n; i++){
        //cin >> v[i];
        oc[v[i]]++;
    }
    int myMax = 0;
    for(int i = 0; i < n; i++){
        noc[v[i]]++;
        if(oc[v[i]] == 1){
            myMax = max(myMax, (int)s.size() + 1);
        }else if(oc[v[i]] == noc[v[i]]){
            //cout << s.size() << endl;
            if(s.size() == 0 || s.top() != v[i]){
                return INF;
            }
            s.pop();
        }else if(noc[v[i]] == 1){
            s.push(v[i]);
        }
        myMax = max(myMax, (int)s.size());
    }
    return myMax;
}
int main(){
    freopen("art2.in", "r", stdin);
    freopen("art2.out", "w", stdout);
    //cout << "HELLO" << endl;
    int n;
    cin >> n;
    stack<int> s;
    vector<int> v(n);
    vector<vector<int>> vec;
    for(int i = 0; i < n; i++){
        cin >> v[i];
        if(v[i] == 0){
            vec.push_back({});
        }else{
            if(vec.size() == 0){
                vec.resize(1), vec[0].push_back(v[i]);
                continue;
            }
            vec[vec.size() - 1].push_back(v[i]);
        }
    }
    //return 0;
    int ans = 0;
    for(vector<int> vv: vec){
        int x = solve(vv);
        //cout << x << endl;
        ans = max(ans, x);
    }
    if(ans == INF){
        cout << -1 << endl;
        return 0;
    }
    cout << ans << endl;
}
