---
LeetCode 128: Longest Consecutive Sequence
---

- [3. Hash Set](#3-hash-set)
  - [Library Function Breakdown](#library-function-breakdown)
  - [Time and Space Complexity](#time-and-space-complexity)
  - [Steps to Solve the Problem (Think Like This)](#steps-to-solve-the-problem-think-like-this)
    - [Strategy: Use Set to Quickly Check Existence](#strategy-use-set-to-quickly-check-existence)
  - [Visualization With Example](#visualization-with-example)
    - [Example: `nums = [100, 4, 200, 1, 3, 2]`](#example-nums--100-4-200-1-3-2)
    - [Iteration:](#iteration)
    - [Example 2: `nums = [0,3,7,2,5,8,4,6,0,1]`](#example-2-nums--0372584601)
    - [Example 3: `nums = [1,0,1,2]`](#example-3-nums--1012)
- [4. Hash Map](#4-hash-map)
  - [Library Function Definitions](#library-function-definitions)
  - [Time \& Space Complexity](#time--space-complexity)
  - [Step-by-Step Strategy for Solving](#step-by-step-strategy-for-solving)
  - [How to Visualize It with Example](#how-to-visualize-it-with-example)
    - [Example:](#example)
    - [Step-by-step visualization:](#step-by-step-visualization)
    - [Final `mp` contents:](#final-mp-contents)

# 3. Hash Set
```cpp
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> numSet(nums.begin(), nums.end());
        int longest = 0;

        for (int num : numSet) {
            if (numSet.find(num - 1) == numSet.end()) {
                int length = 1;
                while (numSet.find(num + length) != numSet.end()) {
                    length++;
                }
                longest = max(longest, length);
            }
        }
        return longest;
    }
};
```

```cpp
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        // 1. Create a hash set of all numbers for O(1) lookup
        unordered_set<int> numSet(nums.begin(), nums.end());

        int longest = 0;  // Track the longest streak found

        // 2. Loop through each number in the set
        for (int num : numSet) {
            // 3. Only start a sequence if current num is the start (no num-1 in set)
            if (numSet.find(num - 1) == numSet.end()) {
                int length = 1;

                // 4. Count how long the sequence continues (num+1, num+2, ...)
                while (numSet.find(num + length) != numSet.end()) {
                    length++;
                }

                // 5. Update longest if this streak is longer
                longest = max(longest, length);
            }
        }
        return longest;
    }
};
```
## Library Function Breakdown

| Function                   | Definition                                                               |
| -------------------------- | ------------------------------------------------------------------------ |
| `unordered_set<T>`         | Hash-based set. All lookups, insertions, deletions: **O(1)** on average. |
| `nums.begin(), nums.end()` | Used to construct the set from a vector (range constructor).             |
| `numSet.find(x)`           | Returns iterator to `x` if found, or `end()` if not. O(1).               |
| `max(a, b)`                | Returns the larger of the two values.                                    |

## Time and Space Complexity

| Metric | Value                              |
| ------ | ---------------------------------- |
| Time   | O(n) — each number is visited once |
| Space  | O(n) — for the unordered\_set      |

* Why linear time?

  * Each number is checked once.
  * We **only start** a sequence at numbers that are the **start of a new sequence**.


## Steps to Solve the Problem (Think Like This)

> You can use these steps to brainstorm before coding similar problems:

### Strategy: Use Set to Quickly Check Existence

1. **Store all numbers** in a hash set for O(1) lookups.
2. **Loop through** the set:

   * If the number **is the start** of a sequence (i.e. `num - 1` doesn't exist), then:

     * Count the sequence by checking `num + 1`, `num + 2`, ...
     * Keep a `length` counter.
3. Track the **maximum length** of any such sequence.
4. Return the result.

This avoids **sorting (O(n log n))** or repeatedly scanning the array (O(n²)).


## Visualization With Example

### Example: `nums = [100, 4, 200, 1, 3, 2]`

* Set: `{100, 4, 200, 1, 3, 2}`

### Iteration:

* 100 → not start of a sequence (no 99) ✅ start, but only 100 exists → length = 1
* 4   → has 3 → ❌ not start
* 200 → has no 199 → ✅ start, length = 1
* 1   → no 0 → ✅ start
  → has 2 → length 2
  → has 3 → length 3
  → has 4 → length 4
  ✅ Update `longest = 4`
* 3, 2 → not starts of sequence → skip

**✅ Output: 4**

---

### Example 2: `nums = [0,3,7,2,5,8,4,6,0,1]`

* Set: `{0,1,2,3,4,5,6,7,8}`

* 0 is start
  → 1, 2, ..., 8 → length = 9
  ✅ Output: 9

---

### Example 3: `nums = [1,0,1,2]`

* Set: `{0,1,2}`
* Start from 0
  → 1, 2 → length = 3
  ✅ Output: 3

---

# 4. Hash Map

```cpp
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_map<int, int> mp;
        int res = 0;

        for (int num : nums) {
            if (!mp[num]) {
                mp[num] = mp[num - 1] + mp[num + 1] + 1;
                mp[num - mp[num - 1]] = mp[num];
                mp[num + mp[num + 1]] = mp[num];
                res = max(res, mp[num]);
            }
        }
        return res;
    }
};
```

```cpp
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_map<int, int> mp; // Map from number to the length of the sequence it belongs to
        int res = 0; // To track the maximum length found

        for (int num : nums) {
            // Only process if 'num' is not already in the map (avoid duplicates)
            if (!mp[num]) {
                // Get the lengths of adjacent sequences
                int left = mp[num - 1];
                int right = mp[num + 1];

                // The total length of the current sequence including num
                int total = left + right + 1;

                // Assign total length to the current number
                mp[num] = total;

                // Update the sequence length at the boundaries
                mp[num - left] = total;
                mp[num + right] = total;

                // Update result if a longer sequence is found
                res = max(res, total);
            }
        }
        return res;
    }
};
```

---

## Library Function Definitions

| Function / Type        | Description                                                                 |
| ---------------------- | --------------------------------------------------------------------------- |
| `unordered_map<K, V>`  | Hash table that stores key-value pairs. Average O(1) insert/find operations |
| `mp[num]`              | Access or insert `num` in the map. If it doesn't exist, initializes to 0    |
| `max(a, b)`            | Returns the maximum of two values                                           |
| `for (int num : nums)` | Range-based loop (C++11+)                                                   |

---

## Time & Space Complexity

| Metric | Complexity | Notes                                                   |
| ------ | ---------- | ------------------------------------------------------- |
| Time   | **O(n)**   | Each number is visited once, each map operation is O(1) |
| Space  | **O(n)**   | At most, one entry per unique number in the map         |

---

## Step-by-Step Strategy for Solving

1. **Avoid duplicates** by only processing a number if it’s not already in the map.
2. For each number, look at the **left and right** neighbors:

   * `left = mp[num - 1]`
   * `right = mp[num + 1]`
3. The new streak is `left + right + 1`
4. Update:

   * `mp[num] = total` (this number's value)
   * `mp[num - left] = total` (left boundary of sequence)
   * `mp[num + right] = total` (right boundary of sequence)
5. Keep updating `res` with the longest seen so far.

This works like a **merge of streaks**, updating only the **ends** of sequences to keep map small and fast.

---

## How to Visualize It with Example

### Example:

**Input:** `nums = [100, 4, 200, 1, 3, 2]`

### Step-by-step visualization:

| Num | Left | Right | Total | mp\[num] | mp\[num - left] | mp\[num + right] | res |
| --- | ---- | ----- | ----- | -------- | --------------- | ---------------- | --- |
| 100 | 0    | 0     | 1     | 1        | 100             | 100              | 1   |
| 4   | 0    | 0     | 1     | 1        | 4               | 4                | 1   |
| 200 | 0    | 0     | 1     | 1        | 200             | 200              | 1   |
| 1   | 0    | 0     | 1     | 1        | 1               | 1                | 1   |
| 3   | 0    | 1     | 2     | 2        | 3               | 4                | 2   |
| 2   | 1    | 2     | 4     | 4        | 1               | 4                | 4   |

### Final `mp` contents:

```cpp
mp = {
    100: 1,
    4: 4,
    3: 2,
    2: 4,
    1: 4,
    200: 1
}
```

✅ Final Answer: **4**

The sequence `[1,2,3,4]` is the longest consecutive sequence.


<!---


/*
128. Longest Consecutive Sequence

Given an unsorted array of integers nums, return the length of the longest consecutive elements sequence.

You must write an algorithm that runs in O(n) time.

Example 1:

Input: nums = [100,4,200,1,3,2]
Output: 4
Explanation: The longest consecutive elements sequence is [1, 2, 3, 4]. Therefore its length is 4.

Example 2:
Input: nums = [0,3,7,2,5,8,4,6,0,1]
Output: 9
Example 3:

Input: nums = [1,0,1,2]
Output: 3
 

Constraints:
0 <= nums.length <= 105
-109 <= nums[i] <= 109
*/

// class Solution {
//     public:
//         int longestConsecutive(vector<int>& nums) {
//             int longest = 0, index = 1;
//             unordered_set<int> numSet(nums.begin(), nums.end());
    
//             for (auto num : numSet) {
//                 index = 1;
//                 if (numSet.find(num - 1) == numSet.end()) {
//                     while (numSet.find(num + index) != numSet.end())
//                         index++;
//                 }
//                 longest = max(index, longest);
//             }
    
//             return longest;
//         }
//     };

//     public:
//         int longestConsecutive(vector<int>& nums) {
//             int i = 1, j = 1;
//             unordered_map<int, int> ordered_s;
    
//             for(auto num : nums)
//                 ordered_s[num]++;
    
//             for(int k = ordered_s.size() - 1; k >= 0; k--){
                
//                 if(ordered_s[k] == (ordered_s[k-1] + 1))
//                     i++;
//                 else
//                     j = i;
//             }
    
//             return i > j ? i : j;
            
//         }
//     };
--->