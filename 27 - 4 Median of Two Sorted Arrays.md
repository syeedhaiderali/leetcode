- [📝 Problem Statement](#-problem-statement)
- [(Merge Method)](#merge-method)
  - [📈 Complexity](#-complexity)
  - [🎯 Step-by-step Example](#-step-by-step-example)
  - [⚡️ Note](#️-note)
- [🧠 Optimized binary search solution](#-optimized-binary-search-solution)
  - [🪜 Step-by-Step Strategy](#-step-by-step-strategy)
  - [🎯 Example 1](#-example-1)
    - [📈 Complexity](#-complexity-1)
  - [🧩 Example 2](#-example-2)
    - [📊 Visualization Summary](#-visualization-summary)
    - [🧠 How to Think About It Visually](#-how-to-think-about-it-visually)
    - [📈 Complexity Recap](#-complexity-recap)

# 📝 Problem Statement

We are given two sorted arrays `nums1` and `nums2` of size `m` and `n` respectively.
Return the **median** of the two sorted arrays.
The overall run time complexity should be **O(log(min(m,n)))** ideally, but a simpler O(m+n) merge-based solution is also accepted.

---

# (Merge Method)

We are **merging both arrays into a single sorted array** (`num`) and then finding the median.

```cpp
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int i = 0, j = 0;
        vector<int> num;  // merged sorted array
        
        // Merge process (like merge step in merge sort)
        while (i < nums1.size() || j < nums2.size()) {
            
            // Case 1: Both arrays still have elements
            if (i < nums1.size() && j < nums2.size()) {
                if (nums1[i] < nums2[j]) {
                    num.push_back(nums1[i]);
                    i++;
                }
                else if (nums1[i] > nums2[j]) {
                    num.push_back(nums2[j]);
                    j++;
                }
                else { 
                    // Both equal -> push both
                    num.push_back(nums2[j]);
                    num.push_back(nums1[i]);
                    i++;
                    j++;
                }
            }
            // Case 2: only nums1 has remaining
            else if (i < nums1.size()) {
                num.push_back(nums1[i]);
                i++;
            }
            // Case 3: only nums2 has remaining
            else if (j < nums2.size()) {
                num.push_back(nums2[j]);
                j++;
            }
        }

        // Find median
        int m1 = num.size() >> 1;  // middle index
        int m2 = (num.size() & 1) ? m1 : (m1 - 1);  // if even -> pick two middle
        
        return (num[m1] + num[m2]) / 2.0;
    }
};
```

---

## 📈 Complexity

* **Time:** `O(m + n)` (since we merge both arrays fully)
* **Space:** `O(m + n)` (extra space for merged vector)

---

## 🎯 Step-by-step Example

Input:

```
nums1 = [1, 3]
nums2 = [2]
```

Steps:

* Merge → `[1, 2, 3]`
* Size = 3 (odd)
* `m1 = 1`, `m2 = 1`
* Median = `(2 + 2) / 2 = 2.0` ✅

---

## ⚡️ Note

This solution is **correct but not optimal**.
The LeetCode problem **wants O(log(min(m,n)))** solution using **binary search** partitioning.
But this approach passes if constraints aren’t too big.

---

# 🧠 Optimized binary search solution

```cpp
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        vector<int>& A = nums1;
        vector<int>& B = nums2;
        int total = A.size() + B.size();
        int half = (total + 1) / 2;  // Half point for partition

        // Ensure A is the smaller array (so binary search runs on smaller size)
        if (B.size() < A.size()) {
            swap(A, B);
        }

        int l = 0;
        int r = A.size();

        // Binary search on array A
        while (l <= r) {
            int i = (l + r) / 2;       // Partition index in A
            int j = half - i;          // Partition index in B (so total left = total right)

            // Get boundaries around the partitions
            int Aleft  = i > 0 ? A[i - 1] : INT_MIN; // left part of A
            int Aright = i < A.size() ? A[i] : INT_MAX; // right part of A
            int Bleft  = j > 0 ? B[j - 1] : INT_MIN; // left part of B
            int Bright = j < B.size() ? B[j] : INT_MAX; // right part of B

            // Check if correct partition found
            if (Aleft <= Bright && Bleft <= Aright) {
                // Odd total length → median is max of left parts
                if (total % 2 != 0) {
                    return max(Aleft, Bleft);
                }
                // Even total length → median is avg of middle two
                return (max(Aleft, Bleft) + min(Aright, Bright)) / 2.0;
            }
            // Shift search space
            else if (Aleft > Bright) {
                r = i - 1; // Too many elements in A's left → move left
            } else {
                l = i + 1; // Too few elements in A's left → move right
            }
        }
        return -1; // Should never happen if inputs are valid
    }
};
```

---

## 🪜 Step-by-Step Strategy

1. **Pick the smaller array (`A`)** to do binary search on (for efficiency).
2. **Partition** both arrays into left and right halves such that:

   * Total elements on the left side = total elements on the right (or one more if odd total).
3. Check if the partition is correct:

   * `Aleft <= Bright` and `Bleft <= Aright`.
4. If partition is correct → median =

   * odd → `max(Aleft, Bleft)`
   * even → `(max(Aleft, Bleft) + min(Aright, Bright)) / 2.0`
5. If not correct → adjust `l` and `r` accordingly.

---

## 🎯 Example 1

**Input:**

```
nums1 = [1, 3]
nums2 = [2]
```

**Steps:**

* total = 3, half = 2
* i = 1 → Aleft = 1, Aright = 3
* j = 1 → Bleft = 2, Bright = ∞
* Check: Aleft (1) ≤ Bright (∞) ✅ and Bleft (2) ≤ Aright (3) ✅
  → correct partition

Since total is odd → median = max(Aleft, Bleft) = max(1, 2) = **2.0**

---

### 📈 Complexity

* **Time:** `O(log(min(m, n)))`
* **Space:** `O(1)`

---

## 🧩 Example 2

Let’s take

```
nums1 = [1, 3, 8]
nums2 = [7, 9, 10, 11]
```

**Goal:** Find the median of these two sorted arrays.

**Total elements:** 3 + 4 = 7
**Half = (7 + 1) / 2 = 4** → We need **4 elements** on the *left side* of the partition.

We’ll binary search on the smaller array — `nums1`.

---

**🎨 Step 1: Start the Binary Search on nums1**

```
nums1 = [1, 3, 8]
nums2 = [7, 9, 10, 11]
```

We define:

```
l = 0, r = 3 (size of nums1)
```

---

**🪜 Step 2: Try First Partition**

```
i = (l + r) / 2 = (0 + 3) / 2 = 1
j = half - i = 4 - 1 = 3
```

Partition:

```
nums1: [1 | 3, 8]
nums2: [7, 9, 10 | 11]
```

Now, define borders:

| Name   | Value | Meaning                     |
| ------ | ----- | --------------------------- |
| Aleft  | 1     | last element on left of A   |
| Aright | 3     | first element on right of A |
| Bleft  | 10    | last element on left of B   |
| Bright | 11    | first element on right of B |

Check condition:

```
Aleft <= Bright ? 1 <= 11 ✅
Bleft <= Aright ? 10 <= 3 ❌
```

So not correct — we need **more elements in A’s right** (increase i).

Move right:

```
l = i + 1 = 2
r = 3
```

---

**🪜 Step 3: Next Partition**

```
i = (2 + 3) / 2 = 2
j = 4 - 2 = 2
```

Partitions:

```
nums1: [1, 3 | 8]
nums2: [7, 9 | 10, 11]
```

Borders:

| Name   | Value |
| ------ | ----- |
| Aleft  | 3     |
| Aright | 8     |
| Bleft  | 9     |
| Bright | 10    |

Check:

```
Aleft <= Bright ? 3 <= 10 ✅
Bleft <= Aright ? 9 <= 8 ❌
```

Still not correct → need **more elements from A** (move right).

```
l = 3
r = 3
```

---

**🪜 Step 4: Next Partition**

```
i = (3 + 3) / 2 = 3
j = 4 - 3 = 1
```

Partitions:

```
nums1: [1, 3, 8 | ]
nums2: [7 | 9, 10, 11]
```

Borders:

| Name   | Value                     |
| ------ | ------------------------- |
| Aleft  | 8                         |
| Aright | ∞ (no element right side) |
| Bleft  | 7                         |
| Bright | 9                         |

Check:

```
Aleft <= Bright ? 8 <= 9 ✅
Bleft <= Aright ? 7 <= ∞ ✅
```

✅ Both true → we found correct partition!

---

**🎯 Step 5: Compute Median**

Now total = 7 (odd)
Median = `max(Aleft, Bleft)`
→ `max(8, 7)` = **8**

✅ **Final Median = 8**

---

### 📊 Visualization Summary 

```
A = [1,   3,   8]
          ↑
          i = 3

B = [7 | 9, 10, 11]
      ↑
      j = 1
```

Left side has 4 elements: `[1, 3, 8, 7]`
Right side has 3 elements: `[9, 10, 11]`
→ median = largest of left = **8**

---

### 🧠 How to Think About It Visually

Think of both arrays laid side-by-side as one sorted list.
We’re “cutting” both arrays such that:

```
LEFT  | RIGHT
--------------------
All(left) ≤ All(right)
```

We adjust the cut in A using binary search so that:

* `Aleft <= Bright`
* `Bleft <= Aright`

When both are true, we found the perfect cut.

---

### 📈 Complexity Recap

| Aspect | Value             |
| ------ | ----------------- |
| Time   | O(log(min(m, n))) |
| Space  | O(1)              |

---