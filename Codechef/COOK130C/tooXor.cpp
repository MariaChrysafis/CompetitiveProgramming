#include <iostream>
#include <vector>

using namespace std;

bool good(vector<int> arr) {
    for (int i = 0; i < arr.size(); i++) {
        if (i + 1 < arr.size() && (arr[i] ^ arr[i + 1]) == 0) {
            return false;
        }
        if (i + 2 < arr.size() && arr[i + 2] != arr[i]) {
            return false;
        }
    }
    return true;
}

bool bad(vector<int> arr) {
    for (int i: arr){
        if (i != 0){
            return false;
        }
    }
    return true;
}

struct triple {
    int x, y, z;
};

void print(triple t) {
    cout << t.y << ' ' << t.z << " " << t.x << '\n';
}
vector<triple> compute(vector<int> v) {
    vector<triple> ans;
    int x = 0;
    int y = -1;
    for (int i = 0; i < v.size(); i += 2) {
        if (v[i] != v[x]) {
            y = i;
        }
    }
    if (y == -1) {
        if (v[x] != 0) {
            // if something like 1 ? 1 ? 1 ? 1 ...
            for (int i = 1; i < v.size(); i += 2) {
                ans.push_back({i, 0, 2});
                v[i] = v[0] ^ v[2];
            }
        } else {
            // if something like 0 ? 0 ? 0 ? ...
            int k = 0;
            for (int j = 1; j < v.size(); j += 2) {
                if (v[j] != 0) {
                    k = j;
                    break;
                }
            }
            for (int i = 1; i < v.size(); i+=2) {
                if (i == k) {
                    continue;
                }
                v[i] = v[0] ^ v[k];
                ans.push_back({i, 0, k});
            }
        }
        /*
        for(int i: v){
            cout << i << " ";
        }
        cout << endl;
         */
        for (int i = 0; i < ans.size(); i++) {
            ans[i].x++, ans[i].y++, ans[i].z++;
        }
        return ans;
    }
    for (int i = 1; i < v.size(); i += 2) {
        v[i] = v[x] ^ v[y];
        ans.push_back({i, x, y});
    }
    for (int i = 0; i < v.size(); i += 2) {
        v[i] = v[1] ^ v[3];
        ans.push_back({i, 1, 3});
    }
    for (int i = 0; i < ans.size(); i++) {
        ans[i].x++, ans[i].y++, ans[i].z++;
    }
    /*
    for(int i: v){
        cout << i << " ";
    }
     */
    cout << endl;

    return ans;
}

void solve() {
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    if (good(arr)) {
        cout << "0 \n";
    } else if(bad(arr) || n == 2) {
        cout << "-1 \n";
    } else if (n == 3) {
        if(arr[0] == arr[1] && arr[1] == arr[2]){
            cout << 1 << endl;
            cout << "1 3 2" << endl;
        }else if(arr[1] == 0){
            cout << 1 << endl;
            if(arr[0]) cout << "1 2 3" << endl;
            else cout << "3 2 1" << endl;
        }else{
            cout << "-1 \n";
        }
    }else {
        //cout << "YES"; return;
        vector<triple> ans = compute(arr);
        cout << ans.size() << endl;
        for (triple t: ans) {
            print(t);
        }
        return;
    }
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
