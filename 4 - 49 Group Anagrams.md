- [📌 Problem Statement — *Group Anagrams*](#-problem-statement--group-anagrams)
    - [Example Input:](#example-input)
    - [Example Output:](#example-output)
- [Hashing with Character Frequency Signature](#hashing-with-character-frequency-signature)
  - [🧠 Algorithm Used](#-algorithm-used)
  - [🧾 Library Function Definitions](#-library-function-definitions)
  - [📈 Time and Space Complexity](#-time-and-space-complexity)
  - [🪜 Step-by-Step Strategy](#-step-by-step-strategy)
  - [🎯 Visualization with Example](#-visualization-with-example)
- [Third attempt](#third-attempt)
- [Second Attempt](#second-attempt)
- [First attempt \<mine, not completed in 30 mins\>](#first-attempt-mine-not-completed-in-30-mins)

# 📌 Problem Statement — *Group Anagrams*

**LeetCode #49**

Given an array of strings `strs`, group the anagrams together.
You can return the answer in any order.

An **anagram** is a word formed by rearranging the letters of another word,
using all the original letters exactly once.

### Example Input:

```cpp
Input: strs = ["eat","tea","tan","ate","nat","bat"]
```

### Example Output:

```cpp
Output: [["bat"],["nat","tan"],["ate","eat","tea"]]
```

# Hashing with Character Frequency Signature
```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        // Hashmap to group words that are anagrams of each other
        // Key → unique frequency signature of the word
        // Value → all words that match that frequency pattern
        unordered_map<string, vector<string>> res;

        // Loop through each word in the input list
        for (const auto& s : strs) {
            // Step 1️⃣: Create a frequency vector for 26 lowercase letters
            vector<int> count(26, 0);

            // Step 2️⃣: Count occurrences of each letter in the current word
            for (char c : s) {
                count[c - 'a']++;
            }

            // Step 3️⃣: Convert the frequency vector into a unique string key
            // Example: for "eat", count might become "1,0,0,0,1,...,1"
            string key = to_string(count[0]);
            for (int i = 1; i < 26; ++i) {
                key += ',' + to_string(count[i]);
            }

            // Step 4️⃣: Group the word into the hashmap using its key
            res[key].push_back(s);
        }

        // Step 5️⃣: Collect all grouped anagrams into a 2D result vector
        vector<vector<string>> result;
        for (const auto& pair : res) {
            result.push_back(pair.second);
        }

        // Step 6️⃣: Return all anagram groups
        return result;
    }
};

```

---

## 🧠 Algorithm Used

Instead of sorting each string (which costs O(k log k)),
we compute a **frequency vector** (size 26 for lowercase letters)
and use it as a **unique key** in a hashmap.

Two words are anagrams if their frequency counts are identical.

---

## 🧾 Library Function Definitions

| Function                                | Description                                      |
| --------------------------------------- | ------------------------------------------------ |
| `unordered_map<string, vector<string>>` | Stores groups of anagrams based on frequency key |
| `vector<int> count(26, 0)`              | Keeps frequency of each character `'a'` to `'z'` |
| `to_string(int)`                        | Converts integer frequency into string           |
| `push_back()`                           | Adds the string to the matching group in the map |

---

## 📈 Time and Space Complexity

| Complexity          | Description                                                                                    |
| ------------------- | ---------------------------------------------------------------------------------------------- |
| **Time:** O(n * k)  | `n` = number of strings, `k` = max string length. For each string, we count characters (O(k)). |
| **Space:** O(n * k) | For storing frequency keys and grouped results in the hashmap.                                 |

---

## 🪜 Step-by-Step Strategy

1. Create an unordered map `res` where:

   * **key** = string representation of letter frequency
   * **value** = list of anagrams with that frequency

2. For each word in `strs`:

   * Initialize a frequency vector of 26 zeros.
   * Increment the count for each letter.
   * Convert this frequency array to a comma-separated string key.
   * Insert the word into `res[key]`.

3. After processing all strings, collect all values from the map into a result vector.

---

## 🎯 Visualization with Example

**Input:**

```
["eat", "tea", "tan", "ate", "nat", "bat"]
```

**Process:**

| Word  | Frequency Vector (a–z)  | Key String        | Group               |
| ----- | ----------------------- | ----------------- | ------------------- |
| "eat" | [1,0,0,0,1,0,...,1,...] | `1,0,0,0,1,...,1` | ["eat"]             |
| "tea" | same as "eat"           | same key          | ["eat","tea"]       |
| "ate" | same as "eat"           | same key          | ["eat","tea","ate"] |
| "tan" | [1,0,0,0,0,...,1,...,1] | unique            | ["tan"]             |
| "nat" | same as "tan"           | same key          | ["tan","nat"]       |
| "bat" | [1,1,0,0,...,1]         | unique            | ["bat"]             |

---

**Final Output:**

```cpp
[["eat","tea","ate"], ["tan","nat"], ["bat"]]
```

---

✅ **Key Insight:**
This avoids sorting every string (O(k log k)) and instead builds a **fixed-size frequency signature** (O(26) ≈ O(1) per string).
Hence, it’s **faster** for large inputs and more scalable.

---

---

# Third attempt
```cpp
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
```

# Second Attempt
```cpp
class Solution
{
public:
    vector<vector<string>> groupAnagrams(vector<string> &strs)
    {
        unordered_map<string, vector<string>> mp = {};
        for (auto x : strs)
        {
            string word = x;
            sort(word.begin(), word.end());
            mp[word].push_back(x);
        }
        vector<vector<string>> ans = {};
        for (auto x : mp)
        {
            ans.push_back(x.second);
        }
        return ans;
    }
};
```

# First attempt <mine, not completed in 30 mins>
```cpp
 class Solution {
     public:
         vector<vector<string>> groupAnagrams(vector<string>& strs) {
             vector<vector<string>> tmp = {};
             vector<string> tmp2 = {};
             if (strs.empty())
                 return tmp;
             int count[26] = {};
             int loop = strs.size();
             string s = strs.at(0);
             while (loop--) {
                 tmp2.push_back(s);
                 strs.erase(strs.begin());
                 string t = strs.at(loop);
                 for (auto x : s)
                     count[x - 'a']++;
                 for (auto x : t)
                     count[x - 'a']--;
                 for (int i = 0; i < 26; i++) {
                     if (count[i] != 0)
                         break;
                     if (i == 25) {
                         tmp2.push_back(t);
                         strs.erase(strs.begin());
                         loop--;
                     }
                 }
             }
             return tmp;
         }
     };
```
