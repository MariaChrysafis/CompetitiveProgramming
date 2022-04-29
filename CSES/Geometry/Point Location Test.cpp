#include <bits/stdc++.h>
using namespace std;
//tested on https://cses.fi/problemset/task/2189/
template <typename T>
struct Point {
    Point (T x, T y) { this->x = x, this->y = y;}
    Point () {this->x = -1, this->y = -1;}
    T x, y;
    Point operator + (const Point& p) const {return Point(p.x + x, p.y + y);}
    Point operator - (const Point& p) const {return Point(x - p.x, y - p.y);}
    T operator * (const Point& p) const {return x * p.y - y * p.x;}
    void operator += (const Point& p) {x += p.x, y += p.y;}
    void operator -= (const Point& p) {x -= p.x, y -= p.y;}
    void operator *= (T c) {x *= c, y *= c;}
    void read() { cin >> x >> y;}
    T cross (const Point& a, const Point& b) const { return (b - *this) * (a - *this);}
};
template <typename T>
struct Line {
    Point<T> a, b;
    Line read() { a.read(), b.read();};
    int orientation (Point<T> p) {
        if (p.cross(a, b) == 0) return 0; //on
        else if (p.cross(a, b) < 0) return -1; //left
        return 1; //right
    }
};
int main() {
    int t;
    cin >> t;
    while (t--) {
        Line<int64_t> l;
        l.read();
        Point<int64_t> p;
        p.read();
        if (l.orientation(p) == -1) {
            cout << "LEFT\n";
        } else if (l.orientation(p) == 1) {
            cout << "RIGHT\n";
        } else {
            cout << "TOUCH\n";
        }
    }
}
