- [📌 Problem Statement](#-problem-statement)
- [🧠 Iterative Binary Search](#-iterative-binary-search)
  - [🧾 Library Function Definitions](#-library-function-definitions)
  - [📈 Time \& Space Complexity](#-time--space-complexity)
  - [🪜 Step-by-Step Strategy](#-step-by-step-strategy)
  - [🎯 Visualization with Example](#-visualization-with-example)
    - [Example 1](#example-1)
    - [Example 2](#example-2)
- [🧠 Lower Bound](#-lower-bound)
  - [🧾 Library Function Definitions Used](#-library-function-definitions-used)
  - [📈 Time \& Space Complexity](#-time--space-complexity-1)
  - [🪜 Step-by-Step Strategy](#-step-by-step-strategy-1)
  - [🎯 Visualization with Example](#-visualization-with-example-1)
    - [Iterations:](#iterations)
- [🧠 Upper Bound](#-upper-bound)
  - [🧾 Library Function Definitions Used](#-library-function-definitions-used-1)
  - [📈 Time \& Space Complexity](#-time--space-complexity-2)
  - [🪜 Step-by-Step Strategy](#-step-by-step-strategy-2)
  - [🎯 Visualization with Example](#-visualization-with-example-2)
  - [✅ Key Insight](#-key-insight)

# 📌 Problem Statement

We are given a sorted array `nums` and a target integer `target`.
Return the index of `target` if it exists, otherwise return `-1`.

This is the **Binary Search** problem (LeetCode 704).



# 🧠 Iterative Binary Search

```cpp
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int l = 0, r = nums.size() - 1;  // inclusive search range [l, r]

        while (l <= r) {  
            int m = l + ((r - l) / 2);   // middle index (safe from overflow)

            if (nums[m] > target) {
                // target is smaller → discard right half
                r = m - 1;
            } else if (nums[m] < target) {
                // target is larger → discard left half
                l = m + 1;
            } else {
                // nums[m] == target → found!
                return m;
            }
        }

        // not found
        return -1;
    }
};
```



## 🧾 Library Function Definitions

* `vector<int>` → dynamic array from STL `<vector>`.
* `.size()` → returns number of elements in the vector.

No external libraries, all C++ built-in.



## 📈 Time & Space Complexity

* **Time Complexity:** O(log n) (because search space halves every iteration).
* **Space Complexity:** O(1) (uses just a few integers).



## 🪜 Step-by-Step Strategy

1. Initialize search boundaries: `l=0`, `r=n-1` (both inclusive).
2. While `l <= r`:

   * Compute `m = l + (r - l)/2`.
   * If `nums[m] > target`, shrink right boundary → `r=m-1`.
   * If `nums[m] < target`, shrink left boundary → `l=m+1`.
   * If `nums[m] == target`, return `m`.
3. If loop ends, `target` not found → return `-1`.



## 🎯 Visualization with Example

### Example 1

```
nums = [-1,0,3,5,9,12], target = 9
```

Steps:

* l=0, r=5 → m=2 → nums\[2]=3 < 9 → l=3
* l=3, r=5 → m=4 → nums\[4]=9 == 9 → ✅ Found

**Output: 4**



### Example 2

```
nums = [-1,0,3,5,9,12], target = 2
```

Steps:

* l=0, r=5 → m=2 → nums\[2]=3 > 2 → r=1
* l=0, r=1 → m=0 → nums\[0]=-1 < 2 → l=1
* l=1, r=1 → m=1 → nums\[1]=0 < 2 → l=2

Now l=2, r=1 → loop ends ❌ Not found.

**Output: -1**



✅ **Key Difference from Your Previous Code (`[l,r) version`)**:

* This version keeps both ends inclusive `[l, r]`.
* Your earlier version kept right end **exclusive** `[l, r)`.
* Both are correct but require slightly different boundary handling.


Nice one 👍
This version you wrote is a **variant of Binary Search** that uses the **lower\_bound pattern** (like in STL). Let’s break it down fully:

---

---

# 🧠 Lower Bound

```cpp
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int l = 0, r = nums.size(); // search range [l, r)

        while (l < r) {
            int m = l + (r - l) / 2; // avoid overflow
            if (nums[m] >= target) {
                // If nums[m] is >= target, shrink right bound
                // because target must be at m or before it
                r = m;
            } else {
                // If nums[m] < target, move left bound forward
                l = m + 1;
            }
        }

        // After loop: l == r, potential candidate index
        return (l < nums.size() && nums[l] == target) ? l : -1;
    }
};
```

---

## 🧾 Library Function Definitions Used

* `vector<int>` → Dynamic array in C++ STL.
* `.size()` → Returns number of elements in vector.
* No other STL functions used here.

---

## 📈 Time & Space Complexity

* **Time Complexity:** `O(log n)` (binary search halves the search space each step).
* **Space Complexity:** `O(1)` (only uses a few integer variables).

---

## 🪜 Step-by-Step Strategy

1. Initialize search range as `[l, r)` where `l = 0` and `r = nums.size()`.

   * This makes `r` exclusive (open interval).
2. Loop while `l < r`:

   * Compute `m` as midpoint.
   * If `nums[m] >= target`, shrink `r = m`.
   * Else, shift left bound `l = m + 1`.
3. Loop ends when `l == r`.

   * At this point, `l` is the **smallest index where `nums[l] >= target`**.
   * This is exactly what `std::lower_bound` does.
4. Finally, check if `nums[l] == target`.

   * If yes, return `l`.
   * Else, return `-1`.

---

## 🎯 Visualization with Example

Input:

```cpp
nums = [-5, -2, 0, 3, 5, 8], target = 3
```

### Iterations:

* Start: `l = 0, r = 6`
* m = 3 → nums\[3] = 3 ≥ 3 → move `r = 3`
* Now: l = 0, r = 3
* m = 1 → nums\[1] = -2 < 3 → move `l = 2`
* Now: l = 2, r = 3
* m = 2 → nums\[2] = 0 < 3 → move `l = 3`
* Now: l = 3, r = 3 → loop stops.

Check `nums[3] == 3` ✅ → return `3`.

---

✅ **This is exactly how `std::lower_bound` works internally**.
It finds the **first index with value ≥ target**, then checks if it equals the target.

---


---

# 🧠 Upper Bound

```cpp
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int l = 0, r = nums.size();   // search space = [l, r)

        while (l < r) {  
            int m = l + (r - l) / 2;  // middle index

            if (nums[m] > target) {
                // If mid value is bigger → shrink right side
                r = m;
            } else {
                // nums[m] <= target
                // Move l forward because we want the last <= target
                l = m + 1;
            }
        }

        // After loop: l points to the first element > target
        // So check l-1 (the last <= target)
        return (l > 0 && nums[l - 1] == target) ? l - 1 : -1;
    }
};
```

---

## 🧾 Library Function Definitions Used

* `vector<int>` → C++ STL dynamic array.
* `size()` → Returns number of elements in the vector.
* No extra library functions used here beyond the standard `vector`.

---

## 📈 Time & Space Complexity

* **Time:** `O(log n)` → Binary search halves the search space each step.
* **Space:** `O(1)` → Only uses a few integer variables.

---

## 🪜 Step-by-Step Strategy

1. Start with the full range `[0, n)`.
2. While `l < r`:

   * Compute middle index `m`.
   * If `nums[m] > target`, then `target` must be on the **left**, so set `r = m`.
   * Otherwise, move `l = m + 1` (keep searching to the right).
3. After the loop:

   * `l` points to the first element **greater than** target.
   * So `l - 1` is the last element ≤ target.
4. Check if `nums[l - 1] == target`:

   * If yes → return `l - 1`.
   * Else → return `-1`.

---

## 🎯 Visualization with Example

Example:
`nums = [1, 3, 5, 7, 9], target = 5`

1. `l = 0, r = 5`
   `m = 2 → nums[2] = 5`
   Since `nums[m] <= target`, set `l = m + 1 = 3`.

2. `l = 3, r = 5`
   `m = 4 → nums[4] = 9`
   Since `nums[m] > target`, set `r = m = 4`.

3. `l = 3, r = 4`
   `m = 3 → nums[3] = 7`
   Since `nums[m] > target`, set `r = 3`.

Now loop ends (`l = 3, r = 3`).

* Check `l - 1 = 2 → nums[2] = 5` ✅ return `2`.

---

## ✅ Key Insight

* This code is essentially using **upper\_bound** logic:

  * After loop, `l` = first index with value `> target`.
  * Check `l-1` for the exact match.

---

👉 So this works correctly, but it’s a bit less intuitive than the classic **while (l ≤ r)** binary search.

Would you like me to also show you how to **unify this with normal / lower / upper bound** into one common reusable function so you don’t confuse them in the future?
