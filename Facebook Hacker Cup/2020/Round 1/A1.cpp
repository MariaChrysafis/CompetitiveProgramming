#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

const int MOD = 1e9 + 7;

void solve() {
    int N, K, W;
    cin >> N >> K >> W;
    vector<long long> L(N);
    for (int i = 0; i < K; i++) {
        cin >> L[i];
    }
    long long AL, BL, CL, DL;
    cin >> AL >> BL >> CL >> DL;
    vector<long long> H(N);
    for (int i = 0; i < K; i++) {
        cin >> H[i];
    }
    long long AH, BH, CH, DH;
    cin >> AH >> BH >> CH >> DH;
    for (int i = K; i < N; i++) {
        L[i] = ((AL * L[i - 2]) + (BL * L[i - 1]) + CL);
        L[i] %= DL;
        H[i] = ((AH * H[i - 2]) + (BH * H[i - 1]) + CH);
        H[i] %= DH;
        L[i]++, H[i]++;
    }
    long long perim = 2 * H[0] + 2 * W;
    long long ans = perim;
    for (int i = 1; i < N; i++) {
        if (L[i] > L[i - 1] + W) {
            perim += 2 * H[i] + 2 * W;
        } else {
            long long maxHeight = 0;
            for(int j = i - 1; j >= max(0, i - 22); j--){
                if(L[i] <= L[j] + W){
                    maxHeight = max((long long)H[j], maxHeight);
                }else{
                    break;
                }
            }
            if(H[i] > maxHeight){
                perim += 2 * (H[i] - maxHeight);
            }
            perim += 2 * (-L[i - 1] + L[i]);
        }
        ans *= perim;
        ans %= MOD;
    }
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << " ";
        solve();
        cout << '\n';
    }

}
