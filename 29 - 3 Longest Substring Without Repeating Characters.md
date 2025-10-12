- [📌 Problem Statement](#-problem-statement)
- [🧠 Hash Set](#-hash-set)
  - [🧾 Library Function Definitions](#-library-function-definitions)
  - [📈 Time \& Space Complexity](#-time--space-complexity)
  - [🪜 Step-by-Step Strategy](#-step-by-step-strategy)
  - [🎯 Visualization with Example](#-visualization-with-example)
  - [🧩 Algorithm Used](#-algorithm-used)
- [Hash Set \*\*\*](#hash-set-)
  - [🧾 Library Function Definitions](#-library-function-definitions-1)
  - [📈 Time and Space Complexity](#-time-and-space-complexity)
  - [🪜 Step-by-Step Strategy](#-step-by-step-strategy-1)
  - [🎯 Visualization with Example](#-visualization-with-example-1)
- [Sliding Window with Hash Map Optimization](#sliding-window-with-hash-map-optimization)
  - [💻 Code with Explanation](#-code-with-explanation)
  - [🧾 Library Function Definitions](#-library-function-definitions-2)
  - [📈 Time and Space Complexity](#-time-and-space-complexity-1)
  - [🪜 Step-by-Step Strategy](#-step-by-step-strategy-2)
  - [🎯 Visualization with Example](#-visualization-with-example-2)


# 📌 Problem Statement

Given a string `s`, find the length of the **longest substring** that **does not contain any repeating characters**.
A substring is a contiguous sequence of characters within a string.
**Example:**

```
Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with a length of 3.
```

---

# 🧠 Hash Set

```cpp
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        // A set to keep track of unique characters in the current window
        set<char> st;

        int longest = 0;  // Result: stores the max length found so far
        int l = 0;        // Left pointer for the sliding window

        // Expand the window with right pointer 'r'
        for (int r = 0; r < s.size(); r++) {

            // If we find a duplicate character s[r],
            // shrink the window from the left until s[r] becomes unique
            while (st.count(s[r])) {
                st.erase(s[l]);
                l++;
            }

            // Insert the new character into the set
            st.insert(s[r]);

            // Update the maximum length found so far
            longest = max(longest, r - l + 1);
        }

        return longest;
    }
};
```

---

## 🧾 Library Function Definitions

| Function       | Purpose                                                                                                     |
| -------------- | ----------------------------------------------------------------------------------------------------------- |
| `set<char>`    | STL container that stores **unique elements** in sorted order. Here it ensures no duplicates in the window. |
| `st.count(x)`  | Returns 1 if `x` is in the set, else 0.                                                                     |
| `st.erase(x)`  | Removes `x` from the set if it exists.                                                                      |
| `st.insert(x)` | Inserts `x` into the set.                                                                                   |
| `max(a,b)`     | Returns the larger of the two numbers.                                                                      |

---

## 📈 Time & Space Complexity

| Complexity Type      | Value                  | Explanation                                                                                                          |
| -------------------- | ---------------------- | -------------------------------------------------------------------------------------------------------------------- |
| **Time Complexity**  | **O(n)**               | Each character is added and removed from the set **at most once**, so total operations = `2n`.                       |
| **Space Complexity** | **O(min(n, charset))** | The set stores at most one of each unique character in the current window. For ASCII, that’s at most 128 characters. |

---

## 🪜 Step-by-Step Strategy

1. **Initialize:**
   Create an empty set and two pointers `l` and `r` representing the window boundaries.

2. **Expand window:**
   Move `r` rightwards to include new characters.

3. **Handle duplicates:**
   If a duplicate character appears, move `l` rightwards (removing characters from the set) until the window has all unique characters again.

4. **Track the maximum:**
   After each step, compute the window size `r - l + 1` and update `longest`.

5. **Continue until `r` reaches the end of string.**

---

## 🎯 Visualization with Example

**Example:**

`s = "pwwkew"`

| Step | l | r | Current Window | Action                                                | Longest |
| ---- | - | - | -------------- | ----------------------------------------------------- | ------- |
| 1    | 0 | 0 | `"p"`          | Add `'p'`                                             | 1       |
| 2    | 0 | 1 | `"pw"`         | Add `'w'`                                             | 2       |
| 3    | 0 | 2 | `"pww"`        | `'w'` repeats → erase `'p'` → erase `'w'` → add `'w'` | 2       |
| 4    | 2 | 3 | `"wk"`         | Add `'k'`                                             | 2       |
| 5    | 2 | 4 | `"wke"`        | Add `'e'`                                             | 3       |
| 6    | 2 | 5 | `"wkew"`       | `'w'` repeats → shrink → `"kew"`                      | 3       |

✅ Final answer: **3** (substring `"kew"`)

---

## 🧩 Algorithm Used

**Sliding Window + Hash Set (Two Pointer Technique)**

This approach efficiently manages the range of unique characters using a **dynamic window**:

* Expand when unique
* Shrink when duplicate found

---

# Hash Set ***

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    /**
     * @brief Finds the length of the longest substring without repeating characters.
     * 
     * @param s Input string
     * @return int Length of the longest substring with all unique characters
     */
    int lengthOfLongestSubstring(string s) {
        unordered_set<char> charSet;  // stores characters currently in the window
        int l = 0;                    // left boundary of sliding window
        int res = 0;                  // stores the maximum length found

        // Expand the right side of the window
        for (int r = 0; r < s.size(); r++) {
            // If the current character already exists, move left pointer
            // until that character is removed from the window
            while (charSet.find(s[r]) != charSet.end()) {
                charSet.erase(s[l]);
                l++;
            }

            // Add the current character to the set
            charSet.insert(s[r]);

            // Update result (window size = r - l + 1)
            res = max(res, r - l + 1);
        }

        return res;
    }
};
```

---

## 🧾 Library Function Definitions

* **`unordered_set`** – A hash-based container storing unique elements with average **O(1)** lookup and erase.
* **`find()`** – Returns iterator to the element if found, else `end()`.
* **`erase()`** – Removes element from the set.
* **`insert()`** – Adds a new unique element.
* **`max(a, b)`** – Returns the larger of two values.

---

## 📈 Time and Space Complexity

| Complexity Type | Explanation                                                   | Big-O                                                     |
| --------------- | ------------------------------------------------------------- | --------------------------------------------------------- |
| **Time**        | Each character is added and removed from the set at most once | **O(n)**                                                  |
| **Space**       | At worst, the set holds all unique characters                 | **O(min(n, charset))**, typically **O(26)** or **O(128)** |

---

## 🪜 Step-by-Step Strategy

1. Initialize two pointers `l = 0` (left) and `r = 0` (right).
2. Move `r` to expand the window while all characters are unique.
3. If a duplicate character appears:

   * Move `l` forward and remove characters from the set until the duplicate is gone.
4. Update the longest substring length each time.
5. Continue until `r` reaches the end.

---

## 🎯 Visualization with Example

**Example Input:**

`s = "abcabcbb"`

| Step | Left (l) | Right (r) | Current Window         | Set Content | Longest |
| ---- | -------- | --------- | ---------------------- | ----------- | ------- |
| 1    | 0        | 0         | "a"                    | {a}         | 1       |
| 2    | 0        | 1         | "ab"                   | {a, b}      | 2       |
| 3    | 0        | 2         | "abc"                  | {a, b, c}   | 3       |
| 4    | 0        | 3         | "abca" → duplicate 'a' | remove 'a'  | still 3 |
| 5    | 1        | 3         | "bca"                  | {b, c, a}   | 3       |
| 6    | 4        | 4         | "b"                    | {b}         | 3       |
| ...  | ...      | ...       | ...                    | ...         | ...     |

✅ **Final Answer:** `3` (substring `"abc"`)


Perfect 👌 Here’s a **complete and easy-to-follow explanation** of your code — including everything you asked for:

---

# Sliding Window with Hash Map Optimization

We use a **Sliding Window** technique along with an **unordered_map** to keep track of the **last index** of each character.

This allows us to:

* **Skip unnecessary checks** (by jumping the left pointer `l` directly to the next valid position),
* Achieve an **O(n)** time complexity.

---

## 💻 Code with Explanation

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    /**
     * @brief Finds the length of the longest substring without repeating characters.
     *
     * @param s Input string
     * @return int Length of the longest substring with all unique characters
     */
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int> mp;  // stores last seen index of each character
        int l = 0;                    // left boundary of the window
        int res = 0;                  // result to store max length

        // Expand the window by moving the right pointer
        for (int r = 0; r < s.size(); r++) {
            // If the character was seen before, move left pointer
            // to one position after the last occurrence of this character
            if (mp.find(s[r]) != mp.end()) {
                l = max(mp[s[r]] + 1, l);
            }

            // Update last seen index of current character
            mp[s[r]] = r;

            // Update result (window size = r - l + 1)
            res = max(res, r - l + 1);
        }

        return res;
    }
};
```

---

## 🧾 Library Function Definitions

| Function                       | Description                                      |
| ------------------------------ | ------------------------------------------------ |
| **`unordered_map<char, int>`** | Hash map storing character → last index          |
| **`find(key)`**                | Returns iterator if the key exists, else `end()` |
| **`max(a, b)`**                | Returns the larger of the two values             |
| **`s.size()`**                 | Returns the length of the string                 |

---

## 📈 Time and Space Complexity

| Type      | Explanation                                                               | Big-O                                                  |
| --------- | ------------------------------------------------------------------------- | ------------------------------------------------------ |
| **Time**  | Each character is processed once, and lookups in `unordered_map` are O(1) | **O(n)**                                               |
| **Space** | At most stores all unique characters                                      | **O(min(n, charset))**, typically **O(128)** for ASCII |

---

## 🪜 Step-by-Step Strategy

1. Start with two pointers:

   * `l` = left side of the current substring window
   * `r` = right side (moves through each character)

2. Maintain an `unordered_map<char, int>` that stores the **last index** where each character appeared.

3. For each character `s[r]`:

   * If it already exists in the map → Move `l` to **one position after** the last occurrence of that character:
     `l = max(l, mp[s[r]] + 1)`
   * Update the character’s index in the map: `mp[s[r]] = r`
   * Update the max window length: `res = max(res, r - l + 1)`

4. Continue this until the end of the string.

5. Return `res`.

---

## 🎯 Visualization with Example

**Example Input:**

`s = "abcabcbb"`

| Step | r | s[r] | l   | Action                        | Map (char → last index) | Window | res |
| ---- | - | ---- | --- | ----------------------------- | ----------------------- | ------ | --- |
| 1    | 0 | 'a'  | 0   | Add 'a'                       | {a→0}                   | "a"    | 1   |
| 2    | 1 | 'b'  | 0   | Add 'b'                       | {a→0, b→1}              | "ab"   | 2   |
| 3    | 2 | 'c'  | 0   | Add 'c'                       | {a→0, b→1, c→2}         | "abc"  | 3   |
| 4    | 3 | 'a'  | 0→1 | Move `l` to 1 (after old 'a') | {a→3, b→1, c→2}         | "bca"  | 3   |
| 5    | 4 | 'b'  | 1→2 | Move `l` to 2                 | {a→3, b→4, c→2}         | "cab"  | 3   |
| 6    | 5 | 'c'  | 2→3 | Move `l` to 3                 | {a→3, b→4, c→5}         | "abc"  | 3   |
| 7    | 6 | 'b'  | 3→5 | Move `l` to 5                 | {a→3, b→6, c→5}         | "cb"   | 3   |
| 8    | 7 | 'b'  | 5→7 | Move `l` to 7                 | {a→3, b→7, c→5}         | "b"    | 3   |

✅ **Final Answer:** `3` (substring `"abc"`)
