#include <iostream>

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Problem3SquarePasture {
public:
    class MyPair {
    public:
        MyPair(int x, int y) : x(x), y(y) {}

    public:
        int x;
        int y;
    };
    
    vector<MyPair> v1;

    static int min4(int a, int b, int c, int d) {
        return min(min(a, b), min(c, d));
    }

    static int max4(int a, int b, int c, int d) {
        return max(max(a, b), max(c, d));
    }

    static int min3(int a, int b, int c) {
        return min(min(a, b), c);
    }

    static int max3(int a, int b, int c) {
        return max(max(a, b), c);
    }

    static bool comp(MyPair p1, MyPair p2) {
        return p1.y < p2.y;
    }

    static bool inRange(int l, int r, int x) {
        return (x >= l && x <= r);
    }

    static int iWantABetterName(int x1, int x2, int y1, int y2, MyPair p1) {
        return (p1.y == y1 || p1.y == y2) + (p1.x == x1 || p1.x == x2);
    }

    int doubleCount(vector<MyPair> v) {
        int n = v.size();
        int counter = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                for (int k = j + 1; k < n; k++) {
                    int x1 = min3(v[i].x, v[j].x, v[k].x);
                    int x2 = max3(v[i].x, v[j].x, v[k].x);
                    int y1 = min3(v[i].y, v[j].y, v[k].y);
                    int y2 = max3(v[i].y, v[j].y, v[k].y);
                    if (iWantABetterName(x1, x2, y1, y2, v[i]) == 0 || iWantABetterName(x1, x2, y1, y2, v[j]) == 0 ||
                            iWantABetterName(x1, x2, y1, y2, v[k]) == 0) {
                        continue;
                    }
                    if (x2 - x1 == y2 - y1) {
                        counter++;
                    }
                }
            }
        }
        return counter;
    }

    int overCount(vector<MyPair> v) {
        int n = v.size();
        int counter = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                for (int k = j + 1; k < n; k++) {
                    for (int l = k + 1; l < n; l++) {
                        int x1 = min4(v[i].x, v[j].x, v[k].x, v[l].x);
                        int x2 = max4(v[i].x, v[j].x, v[k].x, v[l].x);
                        int y1 = min4(v[i].y, v[j].y, v[k].y, v[l].y);
                        int y2 = max4(v[i].y, v[j].y, v[k].y, v[l].y);
                        if (iWantABetterName(x1, x2, y1, y2, v[i]) != 1 || iWantABetterName(x1, x2, y1, y2, v[j]) != 1) {
                            continue;
                        }
                        if (iWantABetterName(x1, x2, y1, y2, v[k]) != 1 || iWantABetterName(x1, x2, y1, y2, v[l]) != 1) {
                            continue;
                        }
                        if (x2 - x1 == y2 - y1) {
                            counter++;
                        }
                    }
                }
            }
        }
        return counter;
    }

    int zerocount(vector<MyPair> v) {
        int counter = 0;
        int n = v.size();
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int width = max(v[i].x, v[j].x) - min(v[i].x, v[j].x);
                int height = max(v[i].y, v[j].y) - min(v[i].y, v[j].y);
                if (width == height) {
                    counter++;
                }
            }
        }
        return counter;
    }

    vector<MyPair> interval(int y1, int y2, int x1, int x2) {
        vector<MyPair> vec;
        for (int i = 0; i < v1.size(); i++) {
            if (inRange(y1, y2, v1[i].y) && inRange(x1, x2, v1[i].x)) {
                vec.push_back(v1[i]);
            }
        }
        return vec;
    }

    vector<MyPair> merge(vector<MyPair> v2, vector<MyPair> v3) {
        vector<MyPair> vec;
        sort(v2.begin(), v2.end(), comp);
        sort(v3.begin(), v3.end(), comp);
        int i2 = 0;
        int i3 = 0;
        while (i2 != v2.size() || i3 != v3.size()) {
            if (i2 == v2.size()) {
                vec.push_back(v3[i3]);
                i3++;
                continue;
            }
            if (i3 == v3.size()) {
                vec.push_back(v2[i2]);
                i2++;
                continue;
            }
            if (v2[i2].y < v3[i3].y) {
                vec.push_back(v2[i2]);
                i2++;
            } else if (v2[i2].y > v3[i3].y) {
                vec.push_back(v3[i3]);
                i3++;
            } else {
                vec.push_back(v2[i2]);
                i2++;
                i3++;
            }
        }
        return vec;
    }

    int ans(std::istream &in, std::ostream &out, int n, vector<MyPair> v) {
        v1 = v;
        sort(v1.begin(), v1.end(), comp);
        int sum = 0;
        for (int i = 0; i < n; i++) {
            auto current = v[i];
            for (int j = i + 1; j < n; j++) {
                auto next = v[j];
                int x1 = min(current.x, next.x);
                int x2 = max(current.x, next.x);
                int y1 = min(current.y, next.y);
                int y2 = max(current.y, next.y);
                int width = x2 - x1;
                int height = y2 - y1;
                if (height >= width) {
                    continue;
                }
                vector<MyPair> a = interval(y2 - width, y1 - 1, x1, x2); /* lower */
                vector<MyPair> b = interval(y2 + 1, y1 + width, x1, x2); /* upper */
                for (int i = 0; i < b.size(); i++) {
                    b[i].y -= width;
                }
                for (int i = 0; i < a.size(); i++) {
                    a[i].y++;
                }
                vector<MyPair> vec = merge(a, b);
                sum += vec.size() + 1;
            }
        }
        return sum;
    }

    void solve(std::istream &in, std::ostream &out) {
        int n;
        in >> n;
        vector<MyPair> v;
        for (int i = 0; i < n; i++) {
            int a, b;
            in >> a >> b;
            v.push_back(MyPair(a, b));
        }
        int x = ans(in, out, n, v);
        for (int i = 0; i < n; i++) {
            swap(v[i].x, v[i].y);
        }
        //out << '-' << endl;
        int y = ans(in, out, n, v);
        out << y + x + n + 1 + zerocount(v) - overCount(v) - doubleCount(v) << endl;
    }
};
