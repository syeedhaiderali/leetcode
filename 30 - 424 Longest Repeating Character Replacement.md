- [📌 Problem Statement](#-problem-statement)
- [Sliding Window with Frequency Tracking](#sliding-window-with-frequency-tracking)
  - [🧾 Library Function Definitions](#-library-function-definitions)
  - [🧩 Code with Full Comments](#-code-with-full-comments)
  - [📈 Time and Space Complexity](#-time-and-space-complexity)
  - [🪜 Step-by-Step Strategy](#-step-by-step-strategy)
  - [🎯 Visualization with Example](#-visualization-with-example)

# 📌 Problem Statement

You are given a string `s` and an integer `k`.
You can replace **at most `k` characters** in the string so that all characters in a substring are the same.
Return the **length of the longest possible substring** where all letters are the same after replacements.

**Example:**

```cpp
Input: s = "AABABBA", k = 1  
Output: 4  
Explanation: Replace one 'B' → "AABA" or "ABBB", longest same-letter substring = 4
```

# Sliding Window with Frequency Tracking

We use the **Sliding Window Technique** to efficiently track the longest valid substring.

***Key Idea:***

* Use a window `[l, r]` that slides across the string.
* Keep count of character frequencies.
* Track the most frequent character (`maxf`) inside the current window.
* The condition `(window size - maxf) <= k` ensures we can make all letters same by replacing at most `k` others.
* If condition breaks → shrink the window from the left.

---

## 🧾 Library Function Definitions

| Function / Concept | Description                                                       |
| ------------------ | ----------------------------------------------------------------- |
| `count[26]`        | Array used to store frequency of uppercase English letters (A–Z). |
| `max()`            | Returns the maximum of two numbers.                               |
| `s.size()`         | Returns the number of characters in string `s`.                   |

---

## 🧩 Code with Full Comments

```cpp
class Solution {
public:
    int characterReplacement(string s, int k) {
        int count[26] = {};      // Stores count of each letter (A–Z)
        int maxf = 0;            // Max frequency of any letter in the current window
        int l = 0;               // Left pointer of window
        int longest = 0;         // Stores longest valid substring length

        // Expand the window using the right pointer
        for(int r = 0; r < s.size(); r++) {
            count[s[r] - 'A']++;               // Increase frequency of current char
            maxf = max(maxf, count[s[r] - 'A']); // Update max frequency seen

            // If replacements needed > k, shrink window
            while((r - l + 1) - maxf > k) {
                count[s[l] - 'A']--;   // Remove leftmost char
                l++;                   // Move left pointer
            }

            // Update longest substring length
            longest = max(longest, r - l + 1);
        }

        return longest;
    }
};
```

---

## 📈 Time and Space Complexity

| Type                 | Explanation                                                     | Big-O    |
| -------------------- | --------------------------------------------------------------- | -------- |
| **Time Complexity**  | Each character visited at most twice (once by `r`, once by `l`) | **O(N)** |
| **Space Complexity** | 26-element array for uppercase letters                          | **O(1)** |

---

## 🪜 Step-by-Step Strategy

1. Initialize frequency array `count[26] = {0}`.
2. Expand the window by moving `r` (right pointer).
3. Update frequency and track `maxf` (most frequent char count).
4. If `(window_size - maxf) > k`, shrink window from the left (`l++`).
5. Keep updating `longest` as the maximum valid window size.
6. Return `longest`.

---

## 🎯 Visualization with Example

**Example:**
`s = "AABABBA", k = 1`

| Step | l | r | Window  | maxf | Replacements Needed | Action |
| ---- | - | - | ------- | ---- | ------------------- | ------ |
| 1    | 0 | 0 | "A"     | 1    | 0                   | OK     |
| 2    | 0 | 1 | "AA"    | 2    | 0                   | OK     |
| 3    | 0 | 2 | "AAB"   | 2    | 1                   | OK     |
| 4    | 0 | 3 | "AABA"  | 3    | 1                   | OK     |
| 5    | 0 | 4 | "AABAB" | 3    | 2                   | SHRINK |
| 6    | 1 | 4 | "ABAB"  | 2    | 2                   | SHRINK |
| 7    | 2 | 5 | "BABB"  | 3    | 1                   | OK     |
| 8    | 2 | 6 | "BABBA" | 3    | 2                   | SHRINK |

✅ **Longest substring = 4** (e.g., “AABA” or “ABBB”)
