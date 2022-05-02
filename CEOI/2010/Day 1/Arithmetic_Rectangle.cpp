#include <bits/stdc++.h>

using namespace std;

int64_t gcd(int64_t a, int64_t b) {
    if (!a || !b) return max(a, b);
    return gcd(max(a, b) % min(a, b), min(a, b));
}

struct Frac {
    int64_t a, b;

    Frac(int64_t a, int64_t b) {
        this->a = a, this->b = b;
        this->reduce();
    }

    Frac() {
        this->a = 1, this->b = 1;
    }

    Frac operator+(const Frac &f) {
        return reduce(Frac(a * f.b + b * f.a, b * f.b));
    }

    Frac operator-(const Frac &f) {
        return reduce(Frac(-f.a, f.b) + Frac(a, b));
    }

    Frac operator*(const int &x) {
        Frac g = Frac(a * x, b);
        return reduce(g);
    }

    Frac operator*(const Frac &f) {
        Frac g = Frac(f.a * a, f.b * b);
        return reduce(g);
    }

    Frac operator/(int x) {
        return reduce(Frac(a, b * x));
    }

    void operator-=(const Frac &f) {
        Frac dum = Frac(a, b) - f;
        a = dum.a, b = dum.b;
    }

    void operator+=(const Frac &f) {
        Frac dum = Frac(a, b) + f;
        a = dum.a, b = dum.b;
    }

    void operator*=(const Frac &x) {
        Frac dum = Frac(a, b) * x;
        a = dum.a, b = dum.b;
    }

    void operator*=(const int &x) {
        Frac dum = Frac(a * x, b);
        a = dum.a, b = dum.b;
    }

    void operator/=(int x) {
        Frac dum = Frac(a, b) / x;
        a = dum.a, b = dum.b;
    }

    void reduce() {
        if (a == 0) {
            b = 1;
            return;
        }
        if (b < 0) b = -b, a = -a;
        int g = gcd(abs(a), abs(b));
        a /= g, b /= g;
    }

    Frac reduce(Frac f) {
        f.reduce();
        return f;
    }

    bool operator==(Frac f) const {
        return (f.a == a && f.b == b);
    }

    void print() {
        cout << a << " " << b;
    }

    void println() {
        print();
        cout << '\n';
    }
};

struct Quadruple {
    vector <int64_t> arr;

    Quadruple(int64_t x) {
        arr.assign(4, x);
    }

    Quadruple(vector <int64_t> arr) {
        this->arr = arr;
    }

    Quadruple operator+(const Quadruple &q) {
        Quadruple ans(0);
        for (int i = 0; i < 4; i++) {
            ans.arr[i] = q.arr[i] + arr[i];
        }
        return ans;
    }

    Quadruple operator*(int x) {
        Quadruple ans(0);
        for (int i = 0; i < 4; i++) {
            ans.arr[i] = x * arr[i];
        }
        return ans;
    }

    Quadruple operator-(const Quadruple &q) {
        Quadruple ans(0);
        for (int i = 0; i < 4; i++) {
            ans.arr[i] = arr[i] - q.arr[i];
        }
        return ans;
    }

    void operator+=(const Quadruple &q) {
        Quadruple dum = Quadruple(this->arr) + q;
        arr = dum.arr;
    }

    void operator*=(int x) {
        Quadruple dum = Quadruple(this->arr) * x;
        arr = dum.arr;
    }

    void operator-=(const Quadruple &q) {
        Quadruple dum = Quadruple(this->arr) - q;
        arr = dum.arr;
    }

    void print() {
        for (int i: arr) {
            cout << i << ' ';
        }
        cout << '\n';
    }
};

vector <vector<Quadruple>> solve(vector <vector<int>> arr) {
    vector <vector<Quadruple>> v;
    v.resize(arr.size());
    for (int i = 0; i < (int) arr.size(); i++) {
        v[i].assign(arr[0].size(), Quadruple(0));
        for (int j = 0; j < (int) arr[0].size(); j++) {
            if (i == 0 && j == 0) v[i][j].arr[0] = 1;
            else if (i == 0 && j == 1) v[i][j].arr[1] = 1;
            else if (i == 1 && j == 0) v[i][j].arr[2] = 1;
            else if (i == 1 && j == 1) v[i][j].arr[3] = 1;
            if (j - 2 >= 0 && v[i][j - 1].arr[0] != INT_MAX && v[i][j - 2].arr[0] != INT_MAX) {
                v[i][j] = v[i][j - 1] * 2 - v[i][j - 2];
            }
            if (i - 2 >= 0 && v[i - 1][j].arr[0] != INT_MAX && v[i - 2][j].arr[0] != INT_MAX) {
                v[i][j] = v[i - 1][j] * 2 - v[i - 2][j];
            }
        }
    }
    return v;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector <vector<int> > arr(n);
    for (int i = 0; i < n; i++) {
        arr[i].resize(m);
        for (int j = 0; j < m; j++) {
            string s;
            cin >> s;
            if (s == ".") arr[i][j] = INT_MAX;
            else arr[i][j] = stoi(s);
        }
    }
    if (n == 1 && m == 1) {
        if (arr[0][0] == INT_MAX) cout << 0;
        else cout << arr[0][0];
        return 0;
    }
    vector <vector<Quadruple> > v = solve(arr);
    vector <vector<int64_t> > eq;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (arr[i][j] != INT_MAX) {
                vector <int64_t> eqn = v[i][j].arr;
                eqn.push_back(arr[i][j]);
                eq.push_back(eqn);
            }
        }
    }
    //gaussian elimination (taken from official implementation)
    for (int c = 0; c < 4; ++c) {
        for (int r = c; r < int(eq.size()); ++r)
            if (eq[r][c] != 0) {
                swap(eq[c], eq[r]);
                break;
            }
        if (c == int(eq.size()) || eq[c][c] == 0) {
            vector <int64_t> eqn(5, 0);
            eqn[c] = 1;
            eq.push_back(eqn);
            swap(eq[c], eq[(int) eq.size() - 1]);
        }
        for (int r = c + 1; r < int(eq.size()); ++r) {
            long long m1 = eq[r][c], m2 = eq[c][c];
            for (int c2 = 0; c2 <= 4; ++c2) eq[r][c2] = m1 * eq[c][c2] - m2 * eq[r][c2];
        }
    }
    for (int r = 4; r < int(eq.size()); r++) {
        if (eq[r][4] != 0) {
            cout << "No solution.\n";
            return 0;
        }
    }
    Frac x4 = Frac(eq[3][4], eq[3][3]);
    Frac x3 = (Frac(eq[2][4], 1) - x4 * eq[2][3]) / eq[2][2];
    Frac x2 = (Frac(eq[1][4], 1) - x4 * eq[1][3] - x3 * eq[1][2]) / eq[1][1];
    Frac x1 = (Frac(eq[0][4], 1) - x4 * eq[0][3] - x3 * eq[0][2] - x2 * eq[0][1]) / eq[0][0];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            Frac res = x1 * v[i][j].arr[0] + x2 * v[i][j].arr[1] + x3 * v[i][j].arr[2] + x4 * v[i][j].arr[3];
            if (res.b != 1) cout << res.a << "/" << res.b << ' ';
            else cout << res.a << ' ';
        }
        cout << '\n';
    }

}
