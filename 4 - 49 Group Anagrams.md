// Third attempt
class Solution
{
public:
    // Custom hash function for array<int, 26>
    struct ArrayHash
    {
        size_t operator()(const array<int, 26> &a) const
        {
            size_t hash = 0;
            for (int x : a)
                hash = hash * 31 + x;
            return hash;
        }
    };

    vector<vector<string>> groupAnagrams(vector<string> &strs)
    {
        unordered_map<array<int, 26>, vector<string>, ArrayHash> mp;

        for (const string &s : strs)
        {
            array<int, 26> count = {}; // all zero by default
            for (char c : s)
                count[c - 'a']++;
            mp[count].push_back(s);
        }

        vector<vector<string>> result;
        for (const auto &pair : mp)
            result.push_back(pair.second);

        return result;
    }
};

// second attempt
// class Solution
// {
// public:
//     vector<vector<string>> groupAnagrams(vector<string> &strs)
//     {
//         unordered_map<string, vector<string>> mp = {};

//         for (auto x : strs)
//         {
//             string word = x;
//             sort(word.begin(), word.end());
//             mp[word].push_back(x);
//         }

//         vector<vector<string>> ans = {};
//         for (auto x : mp)
//         {
//             ans.push_back(x.second);
//         }

//         return ans;
//     }
// };

// First attempt <mine, not completed in 30 mins>
// class Solution {
//     public:
//         vector<vector<string>> groupAnagrams(vector<string>& strs) {
//             vector<vector<string>> tmp = {};
//             vector<string> tmp2 = {};

//             if (strs.empty())
//                 return tmp;

//             int count[26] = {};

//             int loop = strs.size();

//             string s = strs.at(0);

//             while (loop--) {
//                 tmp2.push_back(s);
//                 strs.erase(strs.begin());

//                 string t = strs.at(loop);

//                 for (auto x : s)
//                     count[x - 'a']++;
//                 for (auto x : t)
//                     count[x - 'a']--;

//                 for (int i = 0; i < 26; i++) {
//                     if (count[i] != 0)
//                         break;
//                     if (i == 25) {
//                         tmp2.push_back(t);
//                         strs.erase(strs.begin());
//                         loop--;
//                     }
//                 }
//             }
//             return tmp;
//         }
//     };