# 📌 Problem Statement

**Given two strings `s1` and `s2`,** return `true` if any permutation of `s1` exists as a substring in `s2`, otherwise return `false`.

🧩 **In short:**
Does `s2` contain a substring that is a rearrangement (permutation) of `s1`?

**Example:**

```cpp
Input: s1 = "ab", s2 = "eidbaooo"
Output: true
Explanation: s2 contains "ba" → which is a permutation of "ab".
```

---

# Sliding Window with Frequency Counting

We use a **fixed-size sliding window** over `s2` with window size equal to `s1.length()`
and compare **frequency counts** of letters in the current window with those in `s1`.

---

## 🧾 Library Function Definitions

| Function / Concept        | Description                                                    |
| ------------------------- | -------------------------------------------------------------- |
| `vector<int>(26, 0)`      | Creates a frequency array of size 26 (for lowercase letters).  |
| `countS1 == countS2`      | Checks if both arrays are identical (all letter counts match). |
| `s1.size()` / `s2.size()` | Returns string length.                                         |
| `'a'`                     | Used to map characters to indices 0–25.                        |

---

## 🧩 Code with Full Comments

```cpp
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        // If s1 is longer, s2 can't contain its permutation
        if (s1.size() > s2.size()) return false;

        // Frequency arrays for 'a' to 'z'
        vector<int> countS1(26, 0);
        vector<int> countS2(26, 0);
        
        // Step 1: Count frequency of first window in s2 (same size as s1)
        for (int r = 0; r < s1.size(); r++) {
            countS1[s1[r] - 'a']++;
            countS2[s2[r] - 'a']++;
        }

        // Step 2: Check if first window matches s1 frequency
        if (countS1 == countS2)
            return true;

        // Step 3: Slide the window across s2
        for (int r = s1.size(); r < s2.size(); r++) {
            // Remove the leftmost char (move window forward)
            countS2[s2[r - s1.size()] - 'a']--;
            // Add the new rightmost char
            countS2[s2[r] - 'a']++;

            // Compare frequency arrays after each slide
            if (countS1 == countS2)
                return true;
        }

        // No permutation found
        return false;
    }
};
```

---

## 📈 Time and Space Complexity

| Type                 | Explanation                                                 | Big-O    |
| -------------------- | ----------------------------------------------------------- | -------- |
| **Time Complexity**  | Each char visited once (O(N)), comparison is O(26) constant | **O(N)** |
| **Space Complexity** | Two 26-element arrays                                       | **O(1)** |

---

## 🪜 Step-by-Step Strategy

1. If `s1` is longer than `s2`, return false.
2. Create two frequency arrays for all lowercase letters:

   * `countS1` → frequencies of `s1`.
   * `countS2` → frequencies of current window in `s2`.
3. Fill both arrays for the first window (size = `s1.size()`).
4. If equal → found a permutation → return true.
5. Slide the window:

   * Subtract the count of the outgoing (leftmost) character.
   * Add the incoming (new rightmost) character.
   * Compare arrays each time.
6. If no match found till end → return false.

---

## 🎯 Visualization with Example

**Example:**
`s1 = "ab"`, `s2 = "eidbaooo"`

| Step | Window in s2 | countS2 (non-zero) | Matches countS1? | Result            |
| ---- | ------------ | ------------------ | ---------------- | ----------------- |
| Init | "ei"         | e:1, i:1           | ❌                | continue          |
| 1    | "id"         | i:1, d:1           | ❌                | continue          |
| 2    | "db"         | d:1, b:1           | ❌                | continue          |
| 3    | "ba"         | b:1, a:1           | ✅                | found permutation |

✅ The substring `"ba"` is a permutation of `"ab"`.
Hence, **output = true**.

---
