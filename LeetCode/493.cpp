class Solution {
public:
    template<class T> struct Seg { // comb(ID,b) = b
	const T ID = 0; T comb(T a, T b) { return a + b; }
	    int n; vector<T> seg;
	    void init(int _n) { n = _n; seg.assign(2*n,ID); }
	    void pull(int p) { seg[p] = comb(seg[2*p],seg[2*p+1]); }
	    void upd(int p, T val) { // set val at position p
		seg[p += n] = val; for (p /= 2; p; p /= 2) pull(p); }
	    T query(int l, int r) {	// min on interval [l, r]
		    T ra = ID, rb = ID;
		    for (l += n, r += n+1; l < r; l /= 2, r /= 2) {
			if (l&1) ra = comb(ra,seg[l++]);
			    if (r&1) rb = comb(seg[--r],rb);
		    }
		    return comb(ra,rb);
	    }
    };
    long long reversePairs(vector<int>& nums) {
        Seg<long long> st;
        st.init(nums.size() + 5);
        vector<pair<long long,long long>> vec; //(val, ind)
        for(int i = 0; i < nums.size(); i++){
            vec.push_back(make_pair(nums[i], i));
        }
        sort(vec.begin(), vec.end());
        long long last = -1;
        long long ans = 0;
        //cout << 2 * vec[last + 1].first + 1 << " " << vec[0].first << endl;
        for(int i = 0; i < nums.size(); i++){
            //how many pairs {x, y} are there such that y < i and 2 * nums[x] < nums[y];
            while(last != nums.size() - 1 && 2 * vec[last + 1].first + 1 <= vec[i].first){
                last++;
                st.upd(vec[last].second, 1);
                //cout << vec[last].second << " ";
            }
            long long delta = st.query(vec[i].second + 1, vec.size() - 1);
            ans += delta;
            cout << delta << " "; 
        }
        //return last;
        return ans;
    }
};
