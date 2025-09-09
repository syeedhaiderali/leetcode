- [Stack](#stack)
  - [Library Functions Used](#library-functions-used)
  - [Time \& Space Complexity](#time--space-complexity)
    - [Time Complexity: `O(n)`](#time-complexity-on)
    - [Space Complexity: `O(n)`](#space-complexity-on)
  - [Step-by-Step Strategy for Solving](#step-by-step-strategy-for-solving)
  - [How to Visualize It with Example](#how-to-visualize-it-with-example)
    - [Example:](#example)
    - [Step-by-step:](#step-by-step)


# Stack
```cpp
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        // Initialize result array with all zeros
        vector<int> res(temperatures.size(), 0);

        // Stack to store {temperature, index}
        stack<pair<int, int>> stack;

        // Loop through each day
        for (int i = 0; i < temperatures.size(); i++) {
            int t = temperatures[i];

            // While current temperature is greater than temperature on top of the stack
            // We've found a warmer day for the index on top of the stack
            while (!stack.empty() && t > stack.top().first) {
                auto pair = stack.top(); // {temp, index}
                stack.pop();             // Remove it from the stack
                res[pair.second] = i - pair.second; // Days to wait
            }

            // Push current temperature and index onto the stack
            stack.push({t, i});
        }

        return res;
    }
};
```

---

## Library Functions Used

| Function / Class         | Description                                           |
| ------------------------ | ----------------------------------------------------- |
| `std::vector<T>`         | Dynamic array                                         |
| `std::stack<T>`          | LIFO stack (used for storing unresolved temperatures) |
| `stack.empty()`          | Returns `true` if stack is empty                      |
| `stack.top()`            | Accesses the top element of the stack                 |
| `stack.pop()`            | Removes the top element                               |
| `stack.push({val, idx})` | Adds a pair to the top of the stack                   |

---

## Time & Space Complexity

### Time Complexity: `O(n)`

* Each temperature is pushed and popped **at most once**.
* Loop runs for `n` days, so overall time is **linear**.

### Space Complexity: `O(n)`

* In worst case, the stack can hold all elements (strictly decreasing temperature list).

---

## Step-by-Step Strategy for Solving

1. **Goal:** For each day, find how many days to wait until a warmer temperature.
2. **Idea:** Use a **monotonic stack** to keep track of unresolved temperatures.
3. Initialize:

   * `res[]` to 0s
   * A stack to keep `{temp, index}` pairs
4. For each temperature:

   * While the current temp `t` is **greater** than the top of stack:

     * Pop from stack (this means we found a warmer day)
     * Calculate days between current index and stored index → `res[stored_index] = current - stored_index`
   * Push `{t, i}` onto the stack
5. After the loop, any indices still in the stack never get warmer days → `res[]` already has `0`.

---

## How to Visualize It with Example

### Example:

```cpp
Input:  [73, 74, 75, 71, 69, 72, 76, 73]
Output: [1, 1, 4, 2, 1, 1, 0, 0]
```

### Step-by-step:

* Day 0: 73 → Stack: \[73\@0]
* Day 1: 74 > 73 → Pop 73, res\[0] = 1 → Stack: \[74\@1]
* Day 2: 75 > 74 → Pop 74, res\[1] = 1 → Stack: \[75\@2]
* Day 3: 71 < 75 → Stack: \[75\@2, 71\@3]
* Day 4: 69 < 71 → Stack: \[75\@2, 71\@3, 69\@4]
* Day 5: 72 > 69 → Pop 69, res\[4] = 1 → 72 > 71 → Pop 71, res\[3] = 2 → Stack: \[75\@2, 72\@5]
* Day 6: 76 > 72 → Pop 72, res\[5] = 1 → 76 > 75 → Pop 75, res\[2] = 4 → Stack: \[76\@6]
* Day 7: 73 < 76 → Stack: \[76\@6, 73\@7]
* Done.

Final `res = [1, 1, 4, 2, 1, 1, 0, 0]`