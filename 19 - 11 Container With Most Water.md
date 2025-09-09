- [Two Pointers](#two-pointers)
- [Problem Statement](#problem-statement)
- [Code with Full Comments](#code-with-full-comments)
- [Library Function Definitions](#library-function-definitions)
- [Time \& Space Complexity](#time--space-complexity)
- [Step-by-Step Strategy](#step-by-step-strategy)
- [Visualization with Example](#visualization-with-example)

# Two Pointers

# Problem Statement

We are given an array `height` of size `n`, where each element represents the height of a vertical line drawn on the x-axis at index `i`.
We need to choose two lines such that together with the x-axis they form a **container**.
The goal is to **find the maximum area of water the container can hold**.

👉 Formula for area between lines at index `i` and `j`:

$$
\text{Area} = \min(height[i], height[j]) \times (j - i)
$$

---

# Code with Full Comments

```cpp
class Solution {
public:
    int maxArea(vector<int>& height) {
        // Two pointers: start at both ends
        int l = 0;                      // left pointer
        int r = height.size() - 1;      // right pointer
        int area = 0;                   // variable to store max area found so far

        // Continue until the two pointers meet
        while (l < r) {
            // Calculate current area using shorter height * width
            int tmp = min(height[l], height[r]) * (r - l);

            // Update maximum area
            area = max(area, tmp);

            // Move the pointer with the smaller height
            // (because moving the taller one cannot help increase area)
            if (height[l] < height[r]) {
                l++;
            } else {
                r--;
            }
        }

        // Return the maximum area found
        return area;
    }
};
```

---

# Library Function Definitions

* **`min(a, b)`**
  From `<algorithm>`
  Returns the smaller of two values.
  Example: `min(3, 7) → 3`.

* **`max(a, b)`**
  From `<algorithm>`
  Returns the larger of two values.
  Example: `max(3, 7) → 7`.

---

# Time & Space Complexity

* **Time Complexity:**

  * Each iteration moves **one pointer** (`l` or `r`) closer.
  * At most `n-1` iterations.
  * **O(n)**.

* **Space Complexity:**

  * Uses only a few variables (`l, r, area, tmp`).
  * **O(1)**.

---

# Step-by-Step Strategy

1. Start with **two pointers**: `l=0`, `r=n-1`.
2. Calculate the area between them.
3. Store the maximum so far.
4. Decide which pointer to move:

   * Move the **shorter line** inward.
   * Why? Because area is limited by the shorter line; moving the taller line won’t increase height.
5. Repeat until `l >= r`.
6. Return the maximum area.

---

# Visualization with Example

Input:

```
height = [1,8,6,2,5,4,8,3,7]
```

---

Step 1:

* l=0, r=8
* min(1,7) \* (8-0) = 1 \* 8 = 8
* max area = 8
* Move `l++` (since 1 < 7)

---

Step 2:

* l=1, r=8
* min(8,7) \* (7) = 7 \* 7 = 49 ✅
* max area = 49
* Move `r--` (since 8 > 7)

---

Step 3:

* l=1, r=7
* min(8,3) \* (6) = 3 \* 6 = 18
* max area = 49
* Move `r--`

---

Step 4:

* l=1, r=6
* min(8,8) \* (5) = 8 \* 5 = 40
* max area = 49
* Move `r--`

---

Continue…

Eventually all pairs are checked via this strategy.
Final **max area = 49**.

---

**Summary**:

* **Efficient two-pointer approach**
* **O(n) time, O(1) space**
* **Always correct** because we never miss the optimal pair
