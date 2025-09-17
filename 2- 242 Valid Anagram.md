- [📌 Problem Statement](#-problem-statement)
- [🧠 Sort](#-sort)
  - [🧾 Library Function Definitions](#-library-function-definitions)
  - [📈 Time \& Space Complexity](#-time--space-complexity)
  - [🪜 Step-by-Step Strategy](#-step-by-step-strategy)
  - [🎯 Visualization with Example](#-visualization-with-example)
- [🧠 Hash Map](#-hash-map)
  - [🧾 Library Function Definitions](#-library-function-definitions-1)
  - [📈 Time \& Space Complexity](#-time--space-complexity-1)
  - [🪜 Step-by-Step Strategy](#-step-by-step-strategy-1)
  - [🎯 Visualization with Example](#-visualization-with-example-1)
  - [⚡ Comparison with Hashmap Approach](#-comparison-with-hashmap-approach)
- [🧠 Hash Table (Using Array)](#-hash-table-using-array)
  - [🧾 Library Function Definitions](#-library-function-definitions-2)
  - [📈 Time \& Space Complexity](#-time--space-complexity-2)
  - [🪜 Step-by-Step Strategy](#-step-by-step-strategy-2)
  - [🎯 Visualization with Example](#-visualization-with-example-2)
  - [⚡ Comparison of All 3 Approaches](#-comparison-of-all-3-approaches)


# 📌 Problem Statement

You are given two strings `s` and `t`.
An **anagram** is a word formed by rearranging the letters of another (e.g., `"listen"` → `"silent"`).

**Task:** Return `true` if `t` is an anagram of `s`, and `false` otherwise.

---

# 🧠 Sort

```cpp
class Solution {
public:
    bool isAnagram(string s, string t) {
        // Step 1: If lengths differ, can't be anagrams
        if (s.length() != t.length()) {
            return false;
        }

        // Step 2: Sort both strings alphabetically
        sort(s.begin(), s.end());
        sort(t.begin(), t.end());

        // Step 3: If sorted strings are identical → anagram
        return s == t;
    }
};
```

---

## 🧾 Library Function Definitions

* `sort(s.begin(), s.end())` → Sorts the characters in `s` in ascending order (lexicographically).
* `s == t` → Returns `true` if both strings are exactly the same after sorting.

---

## 📈 Time & Space Complexity

* **Time Complexity:**

  * Sorting each string: `O(n log n)` (where `n = s.length()`).
  * Comparing strings: `O(n)`.
  * Overall: **O(n log n)**.

* **Space Complexity:**

  * Sorting is **in-place** (no extra memory apart from a few variables).
  * Overall: **O(1)** (ignoring sorting stack overhead).

---

## 🪜 Step-by-Step Strategy

1. If `s` and `t` have different lengths → immediately return `false`.
2. Sort both strings alphabetically.
3. Compare sorted results:

   * If they match → return `true`.
   * Otherwise → return `false`.

---

## 🎯 Visualization with Example

Input:

```
s = "anagram"
t = "nagaram"
```

After sorting:

* s → `"aaagmnr"`
* t → `"aaagmnr"`
  Since they match → `true`. ✅

Input:

```
s = "rat"
t = "car"
```

After sorting:

* s → `"art"`
* t → `"acr"`
  Not equal → `false`. ❌

---

# 🧠 Hash Map

```cpp
class Solution {
public:
    bool isAnagram(string s, string t) {
        // If lengths differ, cannot be anagrams
        if (s.length() != t.length()) {
            return false;
        }

        // Frequency counters for both strings
        unordered_map<char, int> countS;
        unordered_map<char, int> countT;

        // Count frequency of characters in both strings
        for (int i = 0; i < s.length(); i++) {
            countS[s[i]]++;
            countT[t[i]]++;
        }

        // Compare the two maps: if equal → anagram
        return countS == countT;
    }
};
```

---

## 🧾 Library Function Definitions

* `unordered_map<char, int>` → Hash map that stores character counts in **O(1)** average time per insert/lookup.
* `countS[s[i]]++` → Increments the frequency of character `s[i]`.
* `operator==` for `unordered_map` → Returns `true` if both maps have identical key-value pairs.

---

## 📈 Time & Space Complexity

* **Time Complexity:**

  * Counting frequencies → O(n), where `n = s.length()`.
  * Comparing maps → O(k), where `k` is the alphabet size (max 26 for lowercase letters, 256 for extended ASCII).
  * Overall → **O(n)**.

* **Space Complexity:**

  * Two hash maps storing up to `k` unique characters.
  * **O(k)** extra space.

---

## 🪜 Step-by-Step Strategy

1. If lengths differ → immediately return `false`.
2. Initialize two hash maps to count character frequencies.
3. Traverse both strings simultaneously, updating counts.
4. Compare maps:

   * If counts match for every character → `true`.
   * Else → `false`.

---

## 🎯 Visualization with Example

Input:

```
s = "anagram"
t = "nagaram"
```

Steps:

* CountS = { a:3, n:1, g:1, r:1, m:1 }
* CountT = { n:1, a:3, g:1, r:1, m:1 }
* Maps equal → return `true`. ✅

Input:

```
s = "rat"
t = "car"
```

* CountS = { r:1, a:1, t:1 }
* CountT = { c:1, a:1, r:1 }
* Not equal → return `false`. ❌

---

## ⚡ Comparison with Hashmap Approach

| Approach                   | Time Complexity | Space Complexity                  | Notes                   |
| -------------------------- | --------------- | --------------------------------- | ----------------------- |
| **Hash Map / Array Count** | O(n)            | O(1) (26 letters) or O(k) general | Faster for large inputs |
| **Sorting**                | O(n log n)      | O(1)                              | Shorter & simpler       |

✅ Sorting is **cleaner**,
⚡ Hashmap (or fixed array) is **faster** when `n` is large.


✅ Your hash map solution is **correct and efficient**.
⚡ But it can be optimized:

* Since the problem usually assumes lowercase English letters, you can replace the maps with a **fixed-size array of 26 integers** → faster and less memory overhead.


---

# 🧠 Hash Table (Using Array)

```cpp
class Solution {
public:
    bool isAnagram(string s, string t) {
        // Step 1: Different lengths → can't be anagrams
        if (s.length() != t.length()) {
            return false;
        }

        // Step 2: Create frequency counter for 26 letters
        vector<int> count(26, 0);

        // Step 3: Traverse both strings at the same time
        for (int i = 0; i < s.length(); i++) {
            // Increment count for char in s
            count[s[i] - 'a']++;
            // Decrement count for char in t
            count[t[i] - 'a']--;
        }

        // Step 4: If any count ≠ 0 → not an anagram
        for (int val : count) {
            if (val != 0) {
                return false;
            }
        }

        // Step 5: All balanced → valid anagram
        return true;
    }
};
```

---

## 🧾 Library Function Definitions

* `vector<int> count(26, 0)` → Creates an integer array of size 26 (for letters `a–z`), initialized to 0.
* `s[i] - 'a'` → Maps a character like `'c'` → index `2`.
* Range-based `for (int val : count)` → iterates through all frequency counts.

---

## 📈 Time & Space Complexity

* **Time Complexity:**

  * One pass over `s` and `t`: `O(n)`.
  * One pass over `count`: `O(26)` ≈ `O(1)`.
  * ✅ Overall: **O(n)**.

* **Space Complexity:**

  * Uses a fixed-size array of length 26.
  * ✅ **O(1)** extra space (constant).

This is **faster** than the sorting solution (`O(n log n)`).

---

## 🪜 Step-by-Step Strategy

1. If lengths differ → return false.
2. Create a frequency array of size 26.
3. For each character:

   * Increment for `s`.
   * Decrement for `t`.
4. If after traversal all counts are 0 → strings are anagrams.
5. Otherwise → not anagrams.

---

## 🎯 Visualization with Example

Input:

```
s = "anagram"
t = "nagaram"
```

Frequency updates:

```
s: a → +1, n → +1, a → +1, g → +1, r → +1, a → +1, m → +1
t: n → -1, a → -1, g → -1, a → -1, r → -1, a → -1, m → -1
```

Net result:

```
All counts = 0 → return true ✅
```

Another Example:

```
s = "rat"
t = "car"
```

Updates:

```
rat → {r:+1, a:+1, t:+1}
car → {c:-1, a:-1, r:-1}
```

Net result:

```
t = +1, c = -1 → not all zero → return false ❌
```

---

## ⚡ Comparison of All 3 Approaches

| Approach                      | Time Complexity | Space    | Notes                           |
| ----------------------------- | --------------- | -------- | ------------------------------- |
| Brute Force                   | O(n²)           | O(1)     | Not practical                   |
| Sorting                       | O(n log n)      | O(1)     | Clean, simple                   |
| Hashmap (unordered\_map)      | O(n)            | O(k)     | Works for Unicode/general chars |
| **Array Counting (this one)** | **O(n)**        | **O(1)** | ✅ Fastest for lowercase English |

---

👉 So your current solution is the **most optimal one** for LeetCode’s constraints (`only lowercase English letters`).

Do you want me to also show you how to **extend this to handle Unicode / any characters**, not just `a–z`?
