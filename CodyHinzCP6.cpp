class Solution {
public:
    vector<int> getCoprimes(vector<int>& nums, vector<vector<int>>& edges) {
        int n = nums.size();
        
        // Build adjacency list representation of the tree
        vector<vector<int>> g(n);
        for (auto& e : edges) {
            int u = e[0], v = e[1];
            g[u].emplace_back(v);
            g[v].emplace_back(u);
        }
        
        // Precompute coprime pairs for values from 1 to 50
        vector<vector<int>> f(51);
        for (int i = 1; i < 51; ++i) {
            for (int j = 1; j < 51; ++j) {
                if (__gcd(i, j) == 1) {
                    f[i].emplace_back(j);
                }
            }
        }
        
        vector<int> ans(n); // Initialize answer array
        vector<stack<pair<int, int>>> stks(51); // Stacks to store ancestor information
        
        // DFS function to find closest coprime ancestors
        function<void(int, int, int)> dfs = [&](int i, int fa, int depth) {
            int t = -1, k = -1;
            
            // Find the closest coprime ancestor from the stacks
            for (int v : f[nums[i]]) {
                auto& stk = stks[v];
                if (!stk.empty() && stk.top().second > k) {
                    t = stk.top().first;
                    k = stk.top().second;
                }
            }
            
            ans[i] = t; // Update answer for the current node
            
            // Traverse neighbors of the current node
            for (int j : g[i]) {
                if (j != fa) {
                    stks[nums[i]].push({i, depth}); // Store current node and depth in the stack
                    dfs(j, i, depth + 1); // Recursive DFS call
                    stks[nums[i]].pop(); // Remove current node from the stack after processing subtree
                }
            }
        };
        
        dfs(0, -1, 0); // Start DFS from root (node 0)
        
        return ans; // Return the answer array
    }
};