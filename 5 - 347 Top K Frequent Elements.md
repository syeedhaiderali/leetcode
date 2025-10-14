- [📌 **Problem Statement**](#-problem-statement)
- [Bucket Sort + Hash Map](#bucket-sort--hash-map)
  - [🧠 Code with Full Comments](#-code-with-full-comments)
  - [🧾 Library Function Definitions](#-library-function-definitions)
  - [📈 Time \& Space Complexity](#-time--space-complexity)
  - [🪜 Step-by-Step Strategy](#-step-by-step-strategy)
  - [🎯 Visualization with Example](#-visualization-with-example)
- [Heap / Priority Queue Approach\*\*](#heap--priority-queue-approach)
  - [🧩 Code with Full Comments](#-code-with-full-comments-1)
  - [🧾 Library Function Definitions](#-library-function-definitions-1)
  - [📈 Time \& Space Complexity](#-time--space-complexity-1)
  - [🪜 Step-by-Step Strategy](#-step-by-step-strategy-1)
  - [🎯 Visualization with Example](#-visualization-with-example-1)


# 📌 **Problem Statement**

Given an integer array `nums` and an integer `k`, return the `k` most frequent elements.
You may return the answer in **any order**.

**Example:**

```
Input: nums = [1,1,1,2,2,3], k = 2  
Output: [1,2]
```

---

# Bucket Sort + Hash Map
Instead of sorting all elements (which costs O(n log n)), we use:

* A **hash map** to count occurrences.
* A **bucket array** where each index stores elements with that frequency.
* Finally, traverse from highest to lowest frequency to pick top `k` items.

---

## 🧠 Code with Full Comments

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        // Step 1️⃣: Count frequency of each number
        unordered_map<int, int> count;
        for (auto num : nums) {
            count[num]++;  // increment occurrence
        }

        // Step 2️⃣: Create a frequency bucket
        // freq[i] will contain all numbers appearing 'i' times
        vector<vector<int>> freq(nums.size() + 1);

        // Fill frequency buckets
        for (const auto& entry : count) {
            freq[entry.second].push_back(entry.first);
        }

        // Step 3️⃣: Traverse from highest frequency to lowest
        vector<int> res;
        for (int i = freq.size() - 1; i >= 0; i--) {
            for (auto n : freq[i]) {
                res.push_back(n);   // Add numbers with current frequency
                if (res.size() == k)
                    return res;     // Stop once top k found
            }
        }

        return res;
    }
};
```

---

## 🧾 Library Function Definitions

* `unordered_map<int,int>` → Hash map for counting occurrences.
* `vector<vector<int>>` → 2D vector (buckets by frequency).
* `push_back()` → Adds elements to end of vector.
* `size()` → Returns number of elements in vector.

---

## 📈 Time & Space Complexity

| Operation            | Complexity | Explanation                  |
| -------------------- | ---------- | ---------------------------- |
| Counting frequencies | O(n)       | One scan of nums             |
| Bucket creation      | O(n)       | Each number placed once      |
| Collecting top K     | O(n)       | At most scanning all buckets |
| **Total Time**       | **O(n)**   | Linear overall               |
| **Space**            | **O(n)**   | For hash map + buckets       |

---

## 🪜 Step-by-Step Strategy

1. Count how often each number appears using a hash map.
2. Create a frequency bucket list `freq[i]` to store numbers that appear `i` times.
3. Start from the highest frequency bucket (most frequent).
4. Collect elements until `k` numbers are gathered.

---

## 🎯 Visualization with Example

**Input:**

```
nums = [1,1,1,2,2,3], k = 2
```

**Step 1:** Frequency map →

```
{1:3, 2:2, 3:1}
```

**Step 2:** Frequency buckets →

```
Index: 0  1      2      3
freq:  [] [3]   [2]   [1]
```

**Step 3:** Traverse from end (index 3 → 0)

* i=3 → add [1]
* i=2 → add [2]
  ✅ Top 2 = [1, 2]

---

**✅ Final Output:**

```
[1, 2]
```

# Heap / Priority Queue Approach**

Max-Heap (Priority Queue) based frequency counting

1. Use a **hash map** to count the frequency of each number.
2. Use a **priority queue (max-heap)** to store pairs of `{number, frequency}`.
3. Pop the top `k` elements from the heap — those are the most frequent numbers.

---

## 🧩 Code with Full Comments

```cpp
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        // Step 1: Count frequency of each number
        unordered_map<int, int> mp;
        for (int x : nums)
            mp[x]++;  // Increment the count for each number

        // Step 2: Define a comparator for max-heap (priority queue)
        // It sorts pairs by frequency in descending order
        auto comp = [](pair<int, int>& a, pair<int, int>& b) {
            return a.second < b.second; // higher frequency = higher priority
        };

        // Step 3: Create a max-heap using the comparator
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(comp)> pq(comp);

        // Step 4: Push all (number, frequency) pairs into the heap
        for (auto x : mp)
            pq.push({x.first, x.second});

        // Step 5: Extract top k frequent elements
        vector<int> tmp;
        while (k--) {
            tmp.push_back(pq.top().first); // take the number
            pq.pop(); // remove from heap
        }

        return tmp; // return the result
    }
};
```

---

## 🧾 Library Function Definitions

| Function / Class | Description                                                                                        |
| ---------------- | -------------------------------------------------------------------------------------------------- |
| `unordered_map`  | Stores key-value pairs with average O(1) lookup and insertion.                                     |
| `priority_queue` | A max-heap by default in C++, used to get the element with the highest priority (here: frequency). |
| `pair`           | A simple structure to hold two values together, e.g., `{number, frequency}`.                       |
| `vector`         | A dynamic array used for storing the result.                                                       |

---

## 📈 Time & Space Complexity

| Complexity Type      | Explanation                                                                                 | Big-O          |
| -------------------- | ------------------------------------------------------------------------------------------- | -------------- |
| **Time Complexity**  | Counting frequencies = O(N), Building heap = O(N log N), Extracting K elements = O(K log N) | **O(N log N)** |
| **Space Complexity** | Hash map stores N elements, Heap stores N elements                                          | **O(N)**       |

---

## 🪜 Step-by-Step Strategy

1. **Frequency Count:**
   Count how many times each number appears using a hash map.
2. **Build Max-Heap:**
   Push all numbers with their frequencies into a max-heap.
3. **Extract Top K:**
   Pop from the heap `k` times to get the most frequent numbers.

---

## 🎯 Visualization with Example

**Example Input:**
`nums = [1, 1, 1, 2, 2, 3], k = 2`

**Step 1 – Frequency Count:**

```
mp = {
  1 → 3,
  2 → 2,
  3 → 1
}
```

**Step 2 – Push into Heap (sorted by frequency):**

```
Heap content (top = highest frequency):
[(1,3), (2,2), (3,1)]
```

**Step 3 – Extract top 2:**

* Pop (1,3) → add `1` to result
* Pop (2,2) → add `2` to result

✅ **Output:** `[1, 2]`
