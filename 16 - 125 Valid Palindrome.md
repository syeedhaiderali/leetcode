- [Initial Attempt](#initial-attempt)
  - [Library Function Definitions](#library-function-definitions)
  - [Time \& Space Complexity](#time--space-complexity)
  - [Step-by-Step Strategy for Solving](#step-by-step-strategy-for-solving)
  - [How to Visualize It With Input Examples](#how-to-visualize-it-with-input-examples)
- [Two Pointers Optimized](#two-pointers-optimized)
  - [Library Function Definitions](#library-function-definitions-1)
  - [Time and Space Complexity](#time-and-space-complexity)
  - [Step-by-Step Strategy for Solving](#step-by-step-strategy-for-solving-1)
  - [Visualization with Example](#visualization-with-example)


<!-- A phrase is a palindrome if, after converting all uppercase letters into lowercase letters and removing all non-alphanumeric characters, it reads the same forward and backward. Alphanumeric characters include letters and numbers.

Given a string s, return true if it is a palindrome, or false otherwise.

 

Example 1:

Input: s = "A man, a plan, a canal: Panama"
Output: true
Explanation: "amanaplanacanalpanama" is a palindrome.
Example 2:

Input: s = "race a car"
Output: false
Explanation: "raceacar" is not a palindrome.
Example 3:

Input: s = " "
Output: true
Explanation: s is an empty string "" after removing non-alphanumeric characters.
Since an empty string reads the same forward and backward, it is a palindrome. -->

# Initial Attempt
```cpp
class Solution {
public:
    bool isPalindrome(string s) {
        string tmp = "";  // Temporary string to store only valid lowercase alphanumeric characters

        // Step 1: Filter and normalize the input string
        for (int i = 0; i < s.size(); i++) {
            // Convert uppercase letters to lowercase
            if (s[i] >= 'A' && s[i] <= 'Z'){
                tmp += s[i] - 'A' + 'a';
            }
            // Keep lowercase letters as they are
            if (s[i] >= 'a' && s[i] <= 'z'){
                tmp += s[i];
            }
            // Include digits
            if (s[i] >= '0' && s[i] <= '9'){
                tmp += s[i];
            }
        }

        // Step 2: Check if the cleaned string is a palindrome
        for(int i = 0; i < tmp.size(); i++){
            if(tmp[i] != tmp[tmp.size() - 1 - i]){  // Compare characters from both ends
                return false;  // Mismatch found
            }
        }

        return true;  // All characters matched, it's a palindrome
    }
};
```

---

## Library Function Definitions 
(You *didn't* use standard ones, but here’s what they could have replaced)

| Function     | Purpose                                               | Replacement                          |
| ------------ | ----------------------------------------------------- | ------------------------------------ |
| `tolower(c)` | Converts `c` to lowercase if it's uppercase           | Used instead of `c - 'A' + 'a'`      |
| `isalnum(c)` | Returns true if `c` is alphanumeric (letter or digit) | Used instead of 3 manual `if` checks |

---

## Time & Space Complexity

* **Time Complexity**: `O(n)`
  → where `n` is the length of the input string. The first loop runs `O(n)` and the second loop also runs up to `O(n)`.

* **Space Complexity**: `O(n)`
  → Because a temporary string `tmp` is used to store the filtered characters.

---

## Step-by-Step Strategy for Solving

1. **Understand the question**:
   You need to check if the string is a palindrome **ignoring non-alphanumeric characters and cases**.

2. **Filter**:
   Remove all characters that are not letters or digits.

3. **Normalize**:
   Convert all letters to lowercase.

4. **Palindrome check**:
   Compare the string from front and back to see if it reads the same.

5. **Return result**:
   If any mismatch is found, return false. Otherwise, return true.

---

## How to Visualize It With Input Examples

**Example 1**
Input: `"A man, a plan, a canal: Panama"`

* After filtering and lowercasing: `"amanaplanacanalpanama"`
* Reversed version: `"amanaplanacanalpanama"`
* ✅ Match → return `true`

**Example 2**
Input: `"race a car"`

* After filtering: `"raceacar"`
* Reversed: `"racacear"`
* ❌ Mismatch → return `false`

---


# Two Pointers Optimized
```cpp
#include <cctype>  // includes isalnum() and tolower()

class Solution {
public:
    bool isPalindrome(string s) {
        int l = 0, r = s.length() - 1;

        // Move both pointers toward center
        while (l < r) {
            // Skip any non-alphanumeric characters from the left
            while (l < r && !isalnum(s[l])) l++;

            // Skip any non-alphanumeric characters from the right
            while (l < r && !isalnum(s[r])) r--;

            // Compare the lowercase versions of both characters
            if (tolower(s[l]) != tolower(s[r])) {
                return false;  // Not a palindrome
            }

            l++; r--;  // Move inward
        }

        return true;  // All matched, it's a palindrome
    }
};
```

---

## Library Function Definitions

| Function     | Description                                                               |
| ------------ | ------------------------------------------------------------------------- |
| `isalnum(c)` | Checks if `c` is a letter (`a-z`, `A-Z`) or digit (`0-9`)                 |
| `tolower(c)` | Converts uppercase `A-Z` to lowercase `a-z`, leaves other chars unchanged |

---

## Time and Space Complexity

| Complexity | Value  | Explanation                                 |
| ---------- | ------ | ------------------------------------------- |
| ⏱ Time     | `O(n)` | Each character is checked at most once      |
| 💾 Space   | `O(1)` | No extra space is used (ignores call stack) |

---

## Step-by-Step Strategy for Solving

1. **Understand the problem**:

   * We need to check if a string reads the same forward and backward.
   * Ignore spaces, punctuation, and case.

2. **Choose an approach**:

   * Use **two-pointer technique**: start at both ends and move inward.

3. **Ignore non-alphanumeric characters**:

   * Skip any character that isn’t a digit or letter using `isalnum()`.

4. **Compare characters**:

   * Convert both to lowercase using `tolower()` to make comparison case-insensitive.

5. **Decide the result**:

   * If all matched: return `true`.
   * If any mismatch: return `false`.

---

## Visualization with Example

Input:

```cpp
string s = "A man, a plan, a canal: Panama";
```

Cleaned version (for understanding): `"amanaplanacanalpanama"`

**Pointer Movement**:

| Left Pointer | Right Pointer | Characters | Match? |
| ------------ | ------------- | ---------- | ------ |
| 0 ('a')      | 29 ('a')      | a == a     | ✅      |
| 1 ('m')      | 28 ('m')      | m == m     | ✅      |
| ...          | ...           | ...        | ✅      |
| 14 ('a')     | 15 ('a')      | a == a     | ✅      |

✅ All characters match → return `true`.

