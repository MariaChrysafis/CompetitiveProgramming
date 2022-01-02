#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <algorithm>
#include <set>
#include <cmath>
#include <queue>
#include <deque>
#include <cassert>
#include <map>

using namespace std;

typedef int64_t ll;
const int MAX = 1000005;
//const int MAX = 300;
vector<int> primes;
void sieve () {
    vector<bool> isPrime(sqrt(MAX) + 1);
    for (int i = 0; i < isPrime.size(); i++) {
        isPrime[i] = true;
    }
    isPrime[0] = isPrime[1] = false;
    for (int i = 0; i < isPrime.size(); i++) {
        if (isPrime[i]) {
            primes.push_back(i);
            for (int j = 2 * i; j < isPrime.size(); j += i) {
                isPrime[j] = false;
            }
        }
    }
}
vector<int> factorize (int x) {
    vector<int> v;
    for (int i: primes) {
        if (x % i == 0) {
            v.push_back(i);
            x /= i;
        }
    }
    if (x != 1) {
        v.push_back(x);
    }
    return v;
}

int reduce (int x) {
    int val = x;
    for (int i: primes) {
        while (val % (i * i) == 0) {
            val /= (i * i);
        }
    }
    return val;
}

vector<bool> isolated(MAX);

struct graph{
    vector<vector<int>> adj;
    int bfs (int src) {
        int ans = (int)1e9;
        queue<int> q;
        vector<int> dist;
        dist.assign(adj.size(), -1);
        q.push(src);
        dist[src] = 0;
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            if (isolated[x] && isolated[src] && x != src) {
                ans = min(ans, dist[x] + 2);
            }
            for (int i: adj[x]) {
                if (dist[i] >= dist[x]){
                    ans = min(ans, dist[i] + dist[x] + 1);
                }
                if (dist[i] == -1) {
                    dist[i] = dist[x] + 1;
                    q.push(i);
                }
            }
        }
        return ans;
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    sieve();
    int N;
    cin >> N;
    vector<int> v(N);
    vector<int> oc(MAX + 1);
    for (int i = 0; i < N; i++) {
        cin >> v[i];
        v[i] = reduce(v[i]);
        oc[v[i]]++;
    }
    if (oc[1]) {
        cout << 1;
        return 0;
    }
    for (int i = 0; i < MAX; i++) {
        if (oc[i] >= 2) {
            cout << 2;
            return 0;
        }
    }
    graph g;
    g.adj.resize(MAX);
    for (int i = 0; i < N; i++) {
        vector<int> vec = factorize(v[i]);
        assert(vec.size() <= 2);
        if (vec.size() == 1) {
            g.adj[1].push_back(vec[0]);
            g.adj[vec[0]].push_back(1);
            continue;
        }
        for (int j: vec) {
            g.adj[j].push_back(v[i]/j);
        }
    }
    int ans = 1e9;
    for (int i = 0; i < sqrt(MAX); i++) {
        ans = min(ans, g.bfs(i));
    }
    if (ans == 1e9) {
        ans = -1;
    }
    cout << ans;


}
