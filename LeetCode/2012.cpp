class Solution {
public:
    template<class T> struct SegMin { // comb(ID,b) = b
	const T ID = 1e9; T comb(T a, T b) { return min(a,b); }
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
    template<class T> struct SegMax { // comb(ID,b) = b
	const T ID = 0; T comb(T a, T b) { return max(a,b); }
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
    int sumOfBeauties(vector<int>& nums) {
        SegMax<int> s1;
        SegMin<int> s2;
        s1.init(nums.size() + 2);
        s2.init(nums.size() + 2);
        for(int i = 0; i < nums.size(); i++){
            s1.upd(i, nums[i]);
            s2.upd(i, nums[i]);
        }
        int cntr = 0;
        for(int i = 1; i < (int)nums.size() - 1; i++) {
            if(s1.query(0, i - 1) < nums[i] && nums[i] < s2.query(i + 1, nums.size() - 1)){
                //cout << 2 << " ";
                cntr += 2;
            }else if(nums[i - 1] < nums[i] && nums[i] < nums[i + 1]){
                //cout << 1 << " ";
                cntr += 1;
            }
        }
        //cout << endl;
        return cntr;
        
    }
};
