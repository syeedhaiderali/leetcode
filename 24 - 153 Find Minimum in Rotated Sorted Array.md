
- [📌 Problem Statement](#-problem-statement)
  - [🧠 Brute Force](#-brute-force)
  - [🧾 Library Function Definitions](#-library-function-definitions)
  - [📈 Time \& Space Complexity](#-time--space-complexity)
  - [🪜 Step-by-Step Strategy (your code’s approach)](#-step-by-step-strategy-your-codes-approach)
  - [🎯 Visualization with Example](#-visualization-with-example)
  - [⚠️ Limitation](#️-limitation)
- [🧠 Binary Search](#-binary-search)
  - [🧾 Library Function Definitions](#-library-function-definitions-1)
  - [📈 Time \& Space Complexity](#-time--space-complexity-1)
  - [🪜 Step-by-Step Strategy](#-step-by-step-strategy)
  - [🎯 Visualization with Example](#-visualization-with-example-1)
- [🧠 Binary Search (Lower Bound)](#-binary-search-lower-bound)
  - [🧾 Library Function Definitions](#-library-function-definitions-2)
  - [📈 Time \& Space Complexity](#-time--space-complexity-2)
  - [🪜 Step-by-Step Strategy](#-step-by-step-strategy-1)
  - [🎯 Visualization with Example](#-visualization-with-example-2)


# 📌 Problem Statement

You are given a **rotated sorted array** (like `[3,4,5,1,2]`).
The task is to find the **minimum element** in O(log n) time.

---

## 🧠 Brute Force

```cpp
class Solution {
public:
    int findMin(vector<int>& nums) {
        // std::min_element returns an iterator pointing
        // to the smallest element in the range
        return *min_element(nums.begin(), nums.end());
    }
};
```

---

## 🧾 Library Function Definitions

* `std::min_element(first, last)` → from `<algorithm>`.

  * Returns an **iterator** pointing to the smallest element in `[first, last)`.
  * Complexity: **O(n)** (linear scan).

---

## 📈 Time & Space Complexity

* **Time:** O(n) → because `min_element` scans the entire array.
* **Space:** O(1) → no extra memory, just uses an iterator.

---

## 🪜 Step-by-Step Strategy (your code’s approach)

1. Use the STL function `min_element`.
2. It scans the whole array.
3. Returns the iterator to the smallest value.
4. Dereference `*iterator` to get the integer.

---

## 🎯 Visualization with Example

Input:

```
nums = [4, 5, 6, 7, 0, 1, 2]
```

Execution:

* Scan through: 4 → 5 → 6 → 7 → 0 → 1 → 2
* Smallest found = `0`
  Output = `0`

---

## ⚠️ Limitation

Although this works, **it does not meet the expected O(log n)** time requirement, because the problem is specifically about applying **binary search on rotated arrays**.


---

Perfect 👍 this is the **optimized O(log n) binary search solution** to find the minimum in a rotated sorted array. Let’s fully break it down with all the details you wanted:

---

# 🧠 Binary Search

```cpp
class Solution {
public:
    int findMin(vector<int> &nums) {
        int res = nums[0];            // Start with the first element as the min
        int l = 0;
        int r = nums.size() - 1;

        while (l <= r) {
            // If the current subarray [l...r] is already sorted
            if (nums[l] < nums[r]) {
                // Then nums[l] is the minimum of this range
                res = min(res, nums[l]);
                break;                 // No need to search further
            }

            int m = l + (r - l) / 2;   // Middle index
            res = min(res, nums[m]);  // Update minimum if needed

            // Decide which half to search
            if (nums[m] >= nums[l]) {
                // Left part [l...m] is sorted, so min must be in right half
                l = m + 1;
            } else {
                // Right part [m...r] is unsorted, min must be in left half
                r = m - 1;
            }
        }
        return res;
    }
};
```

---

## 🧾 Library Function Definitions

* `std::min(a, b)` (from `<algorithm>`)
  → returns the smaller of `a` and `b`.

  * Time: O(1).
  * Space: O(1).

---

## 📈 Time & Space Complexity

* **Time:** O(log n) → because each iteration halves the search space.
* **Space:** O(1) → constant extra space.

---

## 🪜 Step-by-Step Strategy

1. Initialize result `res` with the first element.
2. Use **binary search** between `l` and `r`.
3. If `nums[l] < nums[r]`, the subarray is sorted, so the minimum is `nums[l]`.
4. Otherwise:

   * Check the middle element `nums[m]` and update `res`.
   * If `nums[m] >= nums[l]`, it means the left part `[l...m]` is sorted, so search the **right half**.
   * Else, search the **left half**.
5. Continue until `l > r`.

---

## 🎯 Visualization with Example

Input:

```
nums = [4, 5, 6, 7, 0, 1, 2]
```

Execution:

1. `res = 4`, l=0, r=6
   nums\[l]=4, nums\[r]=2 → not sorted → check mid.
   m=3 → nums\[3]=7 → res = min(4,7)=4.
   nums\[m] >= nums\[l] → search right → l=4.

2. l=4, r=6 → nums\[l]=0, nums\[r]=2 (sorted!)
   res = min(4, 0) = 0 → break.

Answer = `0`.

---

✅ Your code is **already optimal** and correct.
The only minor improvement: you don’t need to store `res` separately, you can directly return `nums[l]` when the sorted case is found, but keeping `res` makes it clearer and safe.

---

Nice 👍 this is another **clean and optimal O(log n) binary search solution** to the "Find Minimum in Rotated Sorted Array" problem. Let me explain it in the structured way you like:

---

# 🧠 Binary Search (Lower Bound)

```cpp
class Solution {
public:
    int findMin(vector<int>& nums) {
        int l = 0, r = nums.size() - 1;

        // Binary search loop
        while (l < r) {
            int m = l + (r - l) / 2;   // mid index

            // If mid element is less than the rightmost element,
            // then the minimum must lie in the left half (including mid)
            if (nums[m] < nums[r]) {
                r = m;                // shrink right bound
            } 
            else {
                // Otherwise, the minimum lies in the right half (excluding mid)
                l = m + 1;            // move left bound up
            }
        }
        // At the end, l == r, which points to the minimum element
        return nums[l];
    }
};
```

---

## 🧾 Library Function Definitions

* No extra libraries are used here beyond `<vector>`.
* `std::vector<int>` → a dynamic array in C++ STL that supports random access and size queries.

---

## 📈 Time & Space Complexity

* **Time:** O(log n) → binary search halves the search space each step.
* **Space:** O(1) → only a few integer variables are used.

---

## 🪜 Step-by-Step Strategy

1. Start with two pointers: `l = 0`, `r = nums.size()-1`.
2. While `l < r`:

   * Find `m = (l+r)/2`.
   * Compare `nums[m]` with `nums[r]`.
   * If `nums[m] < nums[r]`:
     → Minimum is in the left half (including `m`), so move `r = m`.
   * Else:
     → Minimum is in the right half (excluding `m`), so move `l = m+1`.
3. When loop ends, `l == r`, pointing to the **minimum element**.

---

## 🎯 Visualization with Example

Input:

```
nums = [4, 5, 6, 7, 0, 1, 2]
```

Steps:

1. l=0, r=6 → m=3 → nums\[m]=7, nums\[r]=2 → 7 > 2 → search right → l=4.
2. l=4, r=6 → m=5 → nums\[m]=1, nums\[r]=2 → 1 < 2 → search left → r=5.
3. l=4, r=5 → m=4 → nums\[m]=0, nums\[r]=1 → 0 < 1 → r=4.
4. l=4, r=4 → stop.

Answer = `nums[4] = 0`. ✅

---

✅ Compared to your **previous solution with `res`**, this one is:

* Slightly **cleaner** (no extra `res` variable needed).
* Still **O(log n)** and optimal.
* Uses the `nums[m] < nums[r]` trick instead of checking `nums[l]` → easier to reason.

---

Would you like me to also **compare both versions line by line** to show why both work but follow slightly different binary search styles?
