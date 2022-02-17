class Intervals {
public:
    set<pair<int64_t,int64_t>> intervals;
    void print () {
        for (auto& p: intervals) {
            cout << p.first << " " << p.second << '\n';
        }
        cout << '\n';
    }
    pair<int64_t,int64_t> leftIntersect (pair<int64_t,int64_t> p) {
        auto it = intervals.upper_bound({p.first + 1, -1});
        if (it == intervals.begin()) {
            return {-1, -1};
        }
        it--;
        pair<int64_t,int64_t> q = *it;
        if (q.second < p.first) {
            return {-1, -1};
        }
        return q;
    }
    pair<int64_t,int64_t> rightIntersect (pair<int64_t,int64_t> p) {
        auto it = intervals.upper_bound({p.second + 1, -1});
        if (it == intervals.begin()) {
            return {-1, -1};
        }
        it--;
        pair<int64_t,int64_t> q = *it;
        if (q.first > p.second) {
            return {-1, -1};
        }
        if (q.first < p.first) {
            return {-1, -1};
        }
        return q;
    }
    bool willChange (pair<int64_t,int64_t> p) {
        pair<int64_t,int64_t> q = leftIntersect(p);
        if (q.first < 0 && q.second < 0) {
            return true;
        }
        if (q.first <= p.first && q.second >= p.second) {
            return false;
        }
        return true;
    }
    pair<int64_t,int64_t> update_left (pair<int64_t,int64_t> p) {
        pair<int64_t,int64_t> q = leftIntersect(p);
        if (q.first == -1 && q.second == -1) {
            return p;
        }
        if (q.second < p.first) {
            return p;
        }
        if (intervals.count(q)) intervals.erase(q);
        return {q.first, p.second};
    }
    pair<int64_t,int64_t> update_right (pair<int64_t,int64_t> p) {
        pair<int64_t,int64_t> q = rightIntersect(p);
        if (q.first == -1 && q.second == -1) {
            return p;
        }
        if (q.first > p.second) {
            return p;
        }
        if (intervals.count(q)) intervals.erase(q);
        return {p.first, q.second};
    }
    void erase_in_between (pair<int64_t,int64_t> p) {
        auto it = intervals.lower_bound({p.first, -1});
        set<pair<int64_t,int64_t>> to_erase;
        while (it != intervals.end()) {
            if ((*it).second < p.second) {
                to_erase.insert(*it);
            } else {
                break;
            }
            it++;
        }
        for (auto& q: to_erase) {
            intervals.erase(q);
        }
    }
    void add_interval (pair<int64_t,int64_t> p) {
        if (!willChange(p)) {
            return;
        }
        erase_in_between(p);
        pair<int64_t,int64_t> new_p = update_left(p);
        pair<int64_t,int64_t> new_p1 = update_right(new_p);
        intervals.insert(new_p1);
    }
};
