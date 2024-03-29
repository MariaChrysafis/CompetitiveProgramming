struct Hasher {
    vector<int> s;
    vector<long long> pref;
    vector<long long> powr;
    const int MOD = 1000003579;
    int base = 29;
    long long add (long long x, long long y) {
        return (x + y) % MOD;
    }
    long long mult (long long x, long long y) {
        return (x * y) % MOD;
    }
    long long sub (long long x, long long y) {
        return (x % MOD - y % MOD + MOD) % MOD;
    }
    long long query (int l, int r) {
        return sub(pref[r + 1], mult(pref[l], powr[r - l + 1]));
    }
    void add (int x) {
        pref.push_back(add(mult(pref.back(), base), x));
        powr.push_back(mult(powr.back(), base));
        s.push_back(x);
    }
    Hasher (vector<int> s) {
        this->s = s;
        this-> pref = {0};
        this-> powr = {1};
        for (int i = 0; i < s.size(); i++) {
            pref.push_back(add(mult(pref.back(), base), s[i]));
            powr.push_back(mult(powr.back(), base));
        }
    }
};
