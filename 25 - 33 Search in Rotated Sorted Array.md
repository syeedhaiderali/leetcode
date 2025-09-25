Perfect 👍 You’ve written the **“Search in Rotated Sorted Array”** solution.
Here’s the full documentation breakdown with **problem statement + explanation**:

---

## 📌 Problem Statement

You are given an integer array `nums` sorted in **ascending order**, but it was rotated at some unknown pivot index `k` (e.g. `[0,1,2,4,5,6,7]` becomes `[4,5,6,7,0,1,2]`).

* The array has **no duplicate elements**.
* Given the array `nums` and an integer `target`, return the **index of target** if it is in the array, otherwise return `-1`.
* You must design an algorithm with **O(log n)** runtime complexity.

---

## 🧠 Code with Full Comments

```cpp
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int l = 0, r = nums.size() - 1;

        // Step 1: Find pivot (index of smallest element)
        while (l < r) {
            int m = (l + r) / 2;
            if (nums[m] > nums[r]) {
                // Pivot lies in the right half
                l = m + 1;
            } else {
                // Pivot lies at m or left half
                r = m;
            }
        }

        int pivot = r;  // pivot index (r = l)
        l = 0; 
        r = nums.size() - 1;

        // Step 2: Choose which sorted half to binary search
        if (target >= nums[pivot] && target <= nums[r]) {
            l = pivot;        // search right half
        } else {
            r = pivot - 1;    // search left half
        }

        // Step 3: Standard binary search
        while (l <= r) {
            int m = (l + r) / 2;
            if (target < nums[m]) {
                r = m - 1;
            } else if (target > nums[m]) {
                l = m + 1;
            } else {
                return m;   // target found
            }
        }

        return -1;  // target not found
    }
};
```

---

## 🧾 Library Functions Used

* `nums.size()` → gives number of elements in vector.
* `nums[m]` → O(1) random access to elements.

---

## 📈 Time & Space Complexity

* **Pivot search (Step 1):** O(log n)
* **Choosing half (Step 2):** O(1)
* **Binary search (Step 3):** O(log n)
* ✅ **Total = O(log n)**
* Space: O(1)

---

## 🪜 Step-by-Step Strategy

1. Use binary search to find the pivot (smallest element index).

   * If `nums[m] > nums[r]`, pivot lies right of `m`.
   * Else, pivot lies at `m` or left side.
2. Based on pivot, decide which sorted half may contain `target`.
3. Run normal binary search in that half.
4. Return index if found, else return `-1`.

---

## 🎯 Visualization with Example

Input:

```
nums = [4,5,6,7,0,1,2], target = 0
```

Step 1: Find pivot

* l=0, r=6 → m=3 → nums\[3]=7 > nums\[6]=2 → move l=4
* l=4, r=6 → m=5 → nums\[5]=1 <= nums\[6]=2 → move r=5
* l=4, r=5 → m=4 → nums\[4]=0 <= nums\[5]=1 → move r=4
* ✅ pivot = 4 (smallest element `0`)

Step 2: Choose half

* target=0 is in range `[nums[4]=0 ... nums[6]=2]`
* Search in right half (l=4, r=6)

Step 3: Binary search

* l=4, r=6 → m=5 → nums\[5]=1 > 0 → r=4
* l=4, r=4 → m=4 → nums\[4]=0 → found

Output:

```
Index = 4
```

---

✅ This is an **optimal O(log n) solution**.

Would you like me to also show you the **alternative one-pass approach** (without explicitly finding the pivot first) so you can compare both styles?
