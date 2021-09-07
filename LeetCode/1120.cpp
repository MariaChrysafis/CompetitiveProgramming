/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<int> st;
    vector<int> st_sum;
    vector<int> val;
    int subTreeSize(TreeNode* rt, int x){
        //cout << x << endl;
        int l = 0;
        if(rt->left != nullptr){
            val.push_back(val.back() + 1);
            l = subTreeSize(rt->left, val.back());
        }
        int r = 0;
        if(rt->right != nullptr){
            val.push_back(val.back() + 1);
            r = subTreeSize(rt->right, val.back());
        }
        return (st[x] = l + r + 1);
    }
    int subTreeSum(TreeNode* rt, int x){
        int l = 0;
        if(rt->left != nullptr){
            val.push_back(val.back() + 1);
            l = subTreeSum(rt->left, val.back());
        }
        int r = 0;
        if(rt->right != nullptr){
            val.push_back(val.back() + 1);
            r = subTreeSum(rt->right, val.back());
        }
        return (st_sum[x] = l + r + rt->val);
    }
    double maximumAverageSubtree(TreeNode* root) {
        st.resize((int)2e5 + 3);
        st_sum.resize((int)2e5 + 3);
        val = {0};
        subTreeSize(root, 0);
        val = {0};
        subTreeSum(root, 0);
        double myMax = 0;
        for(int i = 0; i < st.size(); i++){
            if(st_sum[i] == 0) continue;
            myMax = max(myMax, (double)st_sum[i]/double(st[i]));
        }
        return myMax;
    }
};
