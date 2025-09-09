class Solution {
    public:
        vector<int> topKFrequent(vector<int>& nums, int k) {
            unordered_map<int, int> mp;
    
            for (int x : nums)
                mp[x]++;
    
            auto comp = [](pair<int, int>& a, pair<int, int>& b) {
                return a.second < b.second;
            };
    
            priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(comp)>
                pq(comp);
    
            for (auto x : mp)
                pq.push({x.first, x.second});
    
            vector<int> tmp;
            while(k--) {
                tmp.push_back(pq.top().first);
                pq.pop();
            }
    
            return tmp;
        }
    };