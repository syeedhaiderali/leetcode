- [📌 Problem Statement](#-problem-statement)
- [Brute-force solution](#brute-force-solution)
  - [🧾 Library Function Definitions](#-library-function-definitions)
  - [📈 Time \& Space Complexity](#-time--space-complexity)
  - [🪜 Step-by-Step Strategy](#-step-by-step-strategy)
  - [🎯 Visualization with Example](#-visualization-with-example)
- [Hash map](#hash-map)
  - [🧾 Library Function Definitions](#-library-function-definitions-1)
  - [📈 Time \& Space Complexity](#-time--space-complexity-1)
  - [🪜 Step-by-Step Strategy](#-step-by-step-strategy-1)
  - [🎯 Visualization with Example](#-visualization-with-example-1)
- [Hash Set](#hash-set)
  - [🧾 Library Function Definitions](#-library-function-definitions-2)
  - [📈 Time \& Space Complexity](#-time--space-complexity-2)
  - [🪜 Step-by-Step Strategy](#-step-by-step-strategy-2)
  - [🎯 Visualization with Example](#-visualization-with-example-2)

# 📌 Problem Statement

You are given an integer array `nums`.
Return **true** if any value appears **at least twice**, otherwise return **false**.

---

# Brute-force solution

```cpp
// Brute Force solution for Contains Duplicate
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        bool flag = false;

        // Compare each element with every other element
        for (int i = 0; i < nums.size(); i++) {
            for (int j = i + 1; j < nums.size(); j++) {
                // If a duplicate is found, return true immediately
                if (nums[i] == nums[j]) 
                    return true;
            }
        }

        // If no duplicate was found
        return flag; // always false here, since we return true inside loop if found
    }
};
```

---

## 🧾 Library Function Definitions

* `vector<int>` → Dynamic array from C++ STL that allows random access and dynamic resizing.
* `nums.size()` → Returns the number of elements in the vector.
* `return true/false` → Boolean return value to indicate presence of duplicates.

---

## 📈 Time & Space Complexity

* **Time Complexity**:

  * Outer loop runs `n` times.
  * Inner loop runs up to `n-1` times.
  * Worst case = **O(n²)**.
* **Space Complexity**:

  * Only a flag variable → **O(1)**.

---

## 🪜 Step-by-Step Strategy

1. Loop through each number (`i`).
2. For each number, check all following numbers (`j > i`).
3. If `nums[i] == nums[j]`, immediately return **true** (duplicate found).
4. If no duplicates found after all checks, return **false**.

---

## 🎯 Visualization with Example

Example: `nums = [1, 2, 3, 1]`

* i=0 → nums\[0]=1

  * j=1 → compare 1 and 2 → not equal
  * j=2 → compare 1 and 3 → not equal
  * j=3 → compare 1 and 1 → ✅ duplicate found → return true

Output: **true**

---

⚡ Brute-force works but is inefficient for large input sizes (`n` up to 10⁵).
👉 Optimized approaches use **HashSet (`unordered_set`)** or **sorting** → O(n) or O(n log n).

---

# Hash map

```cpp
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        // Hash map to count frequency of each number
        unordered_map<int, int> dup;

        // Count occurrences of each number
        for (int i = 0; i < nums.size(); i++) {
            dup[nums[i]]++;
        }

        // Check if any number occurs more than once
        for (auto a : dup) {
            if (a.second > 1)
                return true;
        }

        // No duplicates found
        return false;
    }
};
```

---

## 🧾 Library Function Definitions

* `unordered_map<int,int>` → Hash table that maps a key (`int`) to a value (`int`).
* `dup[nums[i]]++` → Increments the frequency count for the number `nums[i]`.
* `for (auto a : dup)` → Range-based loop iterating through all key-value pairs in the map.

  * `a.first` → the key (the number).
  * `a.second` → the value (frequency count).

---

## 📈 Time & Space Complexity

* **Time Complexity**:

  * Building the map → O(n).
  * Iterating over map → O(n) in worst case (all unique).
  * Overall → **O(n)**.

* **Space Complexity**:

  * Stores up to `n` elements in the hash map.
  * Worst case (all numbers unique) → **O(n)**.

---

## 🪜 Step-by-Step Strategy

1. Create a hash map `dup` to store frequency of each number.
2. Traverse through `nums`:

   * Increment count of each number in the map.
3. Loop through the map:

   * If any number has count > 1 → return **true**.
4. If no number has frequency > 1 → return **false**.

---

## 🎯 Visualization with Example

Input: `nums = [1, 2, 3, 1]`

* Step 1: `dup` = {} initially
* Step 2: Fill frequencies:

  * `1 → 2`
  * `2 → 1`
  * `3 → 1`
    → `dup = {1:2, 2:1, 3:1}`
* Step 3: Iterate map:

  * key=1, value=2 → ✅ return true

Output: **true**

---

⚡ **Comparison with brute-force**:

* Brute force → O(n²), no extra space.
* Hash map → O(n) time, O(n) space.
* Much faster for large inputs.


--- 

# Hash Set
```cpp
#include <vector>
#include <unordered_set>
using namespace std;

class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        // Hash set to store unique numbers
        unordered_set<int> dup;

        // Traverse through nums
        for (auto num : nums) {
            // If num is already in set -> duplicate found
            if (dup.count(num))
                return true;

            // Otherwise insert into set
            dup.insert(num);
        }

        // No duplicates found
        return false;
    }
};
```

---

## 🧾 Library Function Definitions

* `unordered_set<int>` → Hash table that stores only **unique** elements.
* `dup.count(num)` → Returns `1` if `num` exists in the set, otherwise `0`.
* `dup.insert(num)` → Inserts `num` into the set if it’s not already present.

---

## 📈 Time & Space Complexity

* **Time Complexity**:

  * For each number: `count()` + `insert()` → **O(1)** average case.
  * For `n` numbers → **O(n)** overall.

* **Space Complexity**:

  * In worst case (all unique numbers), the set stores `n` elements → **O(n)**.

---

## 🪜 Step-by-Step Strategy

1. Create an empty set `dup`.
2. For each number in `nums`:

   * If number is already in the set → return **true**.
   * Otherwise insert it into the set.
3. If loop finishes with no duplicates → return **false**.

---

## 🎯 Visualization with Example

Input: `nums = [1, 2, 3, 1]`

* Start: `dup = {}`
* num=1 → not found → insert → `dup={1}`
* num=2 → not found → insert → `dup={1,2}`
* num=3 → not found → insert → `dup={1,2,3}`
* num=1 → found in set ✅ → return true

Output: **true**

---

⚡ **Why this is optimal**:

* Brute force → O(n²).
* Hash map → O(n) but extra loop.
* Hash set → O(n), one loop, minimal code.

---