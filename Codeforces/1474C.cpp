#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <unordered_map>
using namespace std;
void print(vector<pair<int,int>> v){
    cout << v[0].first + v[0].second << endl;
    for(pair<int,int> p: v){
        cout << p.first << " " << p.second << endl;
    }
}
pair<int,int> tr(pair<int,int> p){
    return {max(p.first, p.second), min(p.first, p.second)};
}
vector<pair<int,int>> valid(vector<int> arr, int x){
    if(x == arr.size() - 1){
        return {};
    }
    //starting spot is (arr.back() & arr[x])
    //find the largest untaken spot index
    vector<pair<int,int>> ans;
    ans.push_back({arr[arr.size() - 1], arr[x]});
    int strt = arr.size() - 1;
    unordered_map<int,int> oc;
    for(int i: arr) oc[i]++;
    unordered_map<int,int> done;
    done[arr[x]]++;
    done[arr[arr.size() - 1]]++;
    for(int i = 0; i < arr.size()/2 - 1; i++){
        while(oc[arr[strt]] == done[arr[strt]]){
            strt--;
            //cout << strt << endl;
            //if(strt < 0) break;
        }
        //cout << strt << endl;
        ans.push_back(tr({arr[strt],ans[ans.size() - 1].first - arr[strt]}));
        done[ans.back().first]++, done[ans.back().second]++;
    }
    //print(ans);
    //return {};
    for(int i = 0; i < arr.size(); i++){
        //cout << oc[arr[i]] << " " << done[arr[i]] << endl;
        if(oc[arr[i]] != done[arr[i]]){
            //cout << arr[i] << endl;
            return {};
        }
    }
    //cout << "YES" << endl;
    return ans;
}
void solve(){
    int n;
    cin >> n;
    vector<int> arr(2 * n);
    for(int i = 0; i < n * 2; i++){
        cin >> arr[i];
    }
    sort(arr.begin(), arr.end());
    for(int i = 0; i < arr.size(); i++){
        if(valid(arr, i).size() != 0){
            cout << "YES" << endl;
            print(valid(arr, i));
            return;
        }
    }
    cout << "NO" << endl;
}
int main() {
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
