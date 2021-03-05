#include <iostream>
#include <vector>
using namespace std;
vector<int> pref;
int range(int l, int r) {
    if (r >= pref.size()) {
        r = pref.size() - 1;
    }
    int pl;
    if (l <= 0) {
        pl = 0;
    } else {
        pl = pref[l - 1];
    }
    return pref[r] - pl;
}
int main() {
    int N;
    cin >> N;
    if (N == 1) {
        int a;
        cin >> a;
        cout << a / 2 + (a % 2 == 1) << endl;
        return 0;
    }
    int arr[N];
    int myMax = 0;
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
        myMax = max(arr[i], myMax);
    }
    pref.resize(myMax + 1);
    for (int i = 0; i <= myMax; i++) {
        pref[i] = 0;
    }
    for (int i = 0; i < N; i++) {
        pref[arr[i]]++;
    }
    for (int i = 1; i <= myMax; i++) {
        pref[i] += pref[i - 1];
    }
    long long ans = 0;
    for (int i = 1; i <= myMax; i++) {
        // this means that we take i from some guy
        long long cntr = 0;
        long long cc = 0;
        for (int x = 0; i * x <= myMax; x++) {
            // we take from something in the range of [i * x, i * (x + 1) - 1]
            int rng = range(i * x, i * (x + 1) - 1);
            int rng1 = range(i * (x - 1), i * x - 1);
            if (rng1 % 2 == 1 && rng % 2 == 1) {
                cntr++;
                cc += rng;
            }
        }
        long long count = 0;
        for (int x = 0; i * x <= myMax; x++) {
            int rng = range(i * x, i * (x + 1) - 1);
            if (rng % 2 == 1) {
                count++;
            }
        }
        //cout << count << endl;
        if (count == 2) {
            ans += cc;
        }
    }
    cout << ans << endl;
}
