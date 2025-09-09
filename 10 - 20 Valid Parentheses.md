# Leetcode 20: Valid Parentheses

- [Leetcode 20: Valid Parentheses](#leetcode-20-valid-parentheses)
- [Stack](#stack)
  - [Library Function Definitions](#library-function-definitions)
  - [Time \& Space Complexity](#time--space-complexity)
  - [Step-by-Step Strategy to Solve](#step-by-step-strategy-to-solve)
  - [How to Visualize with Input Example](#how-to-visualize-with-input-example)
    - [Example: `"({[]})"`](#example-)


# Stack

```cpp
class Solution {
public:
    bool isValid(string s) {
        std::stack<char> stack;  // Stack to store opening brackets
        std::unordered_map<char, char> closeToOpen = {
            {')', '('},  // Closing to opening map
            {']', '['},
            {'}', '{'}
        };

        for (char c : s) {
            // If it's a closing bracket
            if (closeToOpen.count(c)) {
                // Check if stack is not empty and top matches corresponding opening
                if (!stack.empty() && stack.top() == closeToOpen[c]) {
                    stack.pop();  // Valid pair found, remove opening
                } else {
                    return false; // Either empty stack or mismatched pair
                }
            } else {
                // It's an opening bracket, push to stack
                stack.push(c);
            }
        }

        // Valid if no unmatched opening brackets remain
        return stack.empty();
    }
};
```

---

## Library Function Definitions

| Function / Class         | Purpose                                                          |
| ------------------------ | ---------------------------------------------------------------- |
| `std::stack<char>`       | A stack to keep track of opening brackets (`push`, `pop`, `top`) |
| `std::unordered_map`     | Stores mapping from closing → opening brackets for quick lookup  |
| `stack.empty()`          | Returns `true` if the stack has no elements                      |
| `stack.top()`            | Returns the top element (doesn’t remove it)                      |
| `stack.pop()`            | Removes the top element from the stack                           |
| `unordered_map.count(k)` | Checks if key `k` exists in the map; returns 1 if yes, else 0    |

---

## Time & Space Complexity

| Complexity | Value    | Reason                                                                |
| ---------- | -------- | --------------------------------------------------------------------- |
| Time       | **O(n)** | One pass over the string, stack operations are O(1)                   |
| Space      | **O(n)** | In worst case, all characters are opening brackets → O(n) stack usage |

---

## Step-by-Step Strategy to Solve

1. **Understand the goal**: You must verify that every opening bracket has a corresponding and correctly placed closing bracket.
2. **Choose a tool**: A stack is ideal because it allows **Last-In-First-Out (LIFO)** matching — exactly what we need for balanced brackets.
3. **Track expected matches**: Use a `map` to relate each closing bracket to its matching opening one.
4. **Loop through the string**:

   * If you see an opening bracket, **push** it.
   * If you see a closing bracket:

     * If the stack is empty or the top doesn't match → ❌ Invalid
     * If it matches → ✅ Pop the opening bracket
5. **Finally**, if the stack is empty, all brackets matched correctly.

---

## How to Visualize with Input Example

### Example: `"({[]})"`

Visualize the stack at each step:

| Char | Action          | Stack     |
| ---- | --------------- | --------- |
| `(`  | Push            | `[`       |
| `{`  | Push            | `[, {`    |
| `[`  | Push            | `[, {, [` |
| `]`  | Match & pop `[` | `[, {`    |
| `}`  | Match & pop `{` | `[`       |
| `)`  | Match & pop `(` | (empty) ✅ |

Stack is empty → **Valid**

---

Let me know if you'd like a diagram for this or want a similar explanation for the follow-up: *"minimum removals to make it valid."*
