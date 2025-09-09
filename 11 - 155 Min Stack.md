
- [Two Stack](#two-stack)
  - [🧾 Library Function Definitions](#-library-function-definitions)
  - [📈 Time \& Space Complexity](#-time--space-complexity)
  - [🪜 Step-by-Step Strategy](#-step-by-step-strategy)
  - [🎯 Visualization Example](#-visualization-example)
    - [Input:](#input)
    - [Internal Stack (`v`) as vector of pairs:](#internal-stack-v-as-vector-of-pairs)
- [One Stack](#one-stack)
  - [Library Function Definitions](#library-function-definitions)
  - [Time \& Space Complexity](#time--space-complexity)
  - [Step-by-Step Strategy for Solving](#step-by-step-strategy-for-solving)
  - [How to Visualize with Input Example](#how-to-visualize-with-input-example)
    - [Example:](#example)

# Two Stack
```cpp
class MinStack {
    vector<pair<int, int>> v;  // Each element stores (value, min at that point)
public:
    MinStack() {}

    // Push value along with the minimum so far
    void push(int val) {
        // If empty, min is val. Else, min is min(val, previous min)
        int currentMin = v.empty() ? val : std::min(val, v.back().second);
        v.push_back({val, currentMin});
    }

    // Remove the top value
    void pop() {
        v.pop_back();
    }

    // Get the current top element
    int top() {
        return v.back().first;  // Access .first from pair
    }

    // Get the current minimum
    int getMin() {
        return v.back().second;  // Access .second from pair
    }
};
```

---

## 🧾 Library Function Definitions

| Function / Type     | Description                              |
| ------------------- | ---------------------------------------- |
| `std::vector<T>`    | Dynamic array                            |
| `std::pair<T1, T2>` | A pair of values like `(val, min)`       |
| `std::min(a, b)`    | Returns the smaller of `a` and `b`       |
| `.push_back()`      | Adds an element to the end of the vector |
| `.pop_back()`       | Removes the last element                 |
| `.back()`           | Gets reference to the last element       |

---

## 📈 Time & Space Complexity

| Operation   | Time Complexity | Space Complexity                   |
| ----------- | --------------- | ---------------------------------- |
| `push()`    | O(1)            | O(1) extra (stores min)            |
| `pop()`     | O(1)            | O(1)                               |
| `top()`     | O(1)            | O(1)                               |
| `getMin()`  | O(1)            | O(1)                               |
| Total Space | O(n)            | Stores all elements and their mins |

---

## 🪜 Step-by-Step Strategy

1. Use a vector of pairs: `{val, min_so_far}`.
2. On every push:

   * Compute the new `min_so_far`.
   * Store both value and that min in the stack.
3. On `pop`, just remove the top.
4. For `top()`, return `.first`.
5. For `getMin()`, return `.second`.

---

## 🎯 Visualization Example

### Input:

```cpp
MinStack stk;
stk.push(3);
stk.push(5);
stk.push(2);
stk.push(1);
stk.pop();
stk.getMin();  // → 2
stk.top();     // → 2
```

### Internal Stack (`v`) as vector of pairs:

| Value | Min So Far |
| ----- | ---------- |
| 3     | 3          |
| 5     | 3          |
| 2     | 2          |

➡️ `getMin()` → `2`
➡️ `top()` → `2`


# One Stack
```cpp
class MinStack {
private:
    long min;                   // Stores current minimum value
    std::stack<long> stack;     // Stores encoded values (difference from min)

public:
    MinStack() {}

    void push(int val) {
        if (stack.empty()) {
            // First element: store 0 (val - val), and set min
            stack.push(0);
            min = val;
        } else {
            // Push the difference from current min
            stack.push((long)val - min);
            if (val < min) {
                min = val;  // Update min if needed
            }
        }
    }

    void pop() {
        if (stack.empty()) return;

        long diff = stack.top();
        stack.pop();

        // If diff < 0, the popped element was the minimum
        // So we restore the previous min using the encoded difference
        if (diff < 0) {
            min = min - diff;
        }
    }

    int top() {
        long diff = stack.top();
        // If diff > 0, real value is min + diff
        // If diff <= 0, real value is min (because it was the min at that time)
        return (diff > 0) ? (min + diff) : (int)min;
    }

    int getMin() {
        return (int)min;
    }
};
```

---

## Library Function Definitions

| Function/Class  | Description                                  |
| --------------- | -------------------------------------------- |
| `std::stack<T>` | A LIFO stack (`push`, `pop`, `top`, `empty`) |
| `stack.push(x)` | Push element `x` on top of the stack         |
| `stack.pop()`   | Remove the top element                       |
| `stack.top()`   | Get the top element without removing it      |
| `stack.empty()` | Return true if the stack has no elements     |

---

## Time & Space Complexity

| Operation   | Time Complexity | Space Complexity (Auxiliary)       |
| ----------- | --------------- | ---------------------------------- |
| `push()`    | O(1)            | O(1)                               |
| `pop()`     | O(1)            | O(1)                               |
| `top()`     | O(1)            | O(1)                               |
| `getMin()`  | O(1)            | O(1)                               |
| Total space | O(n)            | Just one stack, no extra min-stack |

> 💡 Uses a **mathematical trick** to store the min info in-place using difference.

---

## Step-by-Step Strategy for Solving

1. **Understand the problem:**
   Build a stack that can return the current minimum in O(1) time **without extra stack**.

2. **Why regular stack fails:**
   You can’t get `min` in O(1) time if you don’t track it separately. Using two stacks (normal and minStack) is common but takes extra space.

3. **Core trick:**

   * Store the *difference* between the value and current `min`.
   * If the pushed value is smaller than the current `min`, encode and store the change.
   * Decode it back while popping or getting top.

4. **Handle encoding:**

   * If diff < 0 → new minimum (update min)
   * If popping a diff < 0 → restore previous min from diff

---

## How to Visualize with Input Example

### Example:

```cpp
MinStack stk;
stk.push(3);  // min = 3, push 0
stk.push(5);  // diff = 5 - 3 = 2, push 2
stk.push(2);  // diff = 2 - 3 = -1, push -1, min = 2
stk.push(1);  // diff = 1 - 2 = -1, push -1, min = 1
stk.getMin(); // → 1
stk.pop();    // pop -1, restore min = 1 - (-1) = 2
stk.getMin(); // → 2
```

| Stack (top → bottom) | min |
| -------------------- | --- |
| -1 (for 1)           | 1   |
| -1 (for 2)           | 2   |
| 2  (for 5)           | 3   |
| 0  (for 3)           | 3   |

Each diff contains info to restore previous min after a pop.

---

Let me know if you want to compare this to the **two-stack** version for contrast.
