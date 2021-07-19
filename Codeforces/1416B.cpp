#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
 
struct solve{
    long long sum = 0;
    struct triple{
        long long a, b, c;
    };
    void print(vector<long long> v){
        for(long long x: v) cout << x << " "; cout << endl;
    }
    void read(){
        int n;
        cin >> n;
        vector<long long> v(n);
        vector<long long> des;
        vector<triple> ans;
        for(int i = 0; i < n; i++){
            cin >> v[i], sum += v[i];
        }
        if(sum % n != 0){
            cout << "-1\n";
            return;
        }
        sum /= n;
        for(int i = 1; i < n; i++){
            if(v[i] % (i + 1) != 0) {
                int x = i + 1 - v[i] % (i + 1);
                ans.push_back({0, i, x});
                v[0] -= x;
                v[i] += x;
            }
            int x = v[i]/(i + 1);
            ans.push_back({i, 0, x});
            v[i] -= (i + 1) * x;
            v[0] += (i + 1) * x;
        }
        for(int i = 1; i < n; i++){
            ans.push_back({0, i, sum});
            v[0] -= sum;
            v[i] += sum;
        }
        cout << ans.size() << endl;
        for(triple t: ans){
            cout << t.a + 1 << " " << t.b + 1 << " " << t.c << endl;
        }
    }
};
int main(){
    int t;
    cin >> t;
    while(t--) {
        solve s;
        s.read();
    }
}
