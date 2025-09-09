- [Stack](#stack)
  - [🧾 Library Functions Used](#-library-functions-used)
  - [📈 Time \& Space Complexity](#-time--space-complexity)
  - [🪜 Step-by-Step Strategy](#-step-by-step-strategy)
  - [🎯 Visualization with Example](#-visualization-with-example)


# Stack
```cpp
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> stack;  // Used to store operands during evaluation
        int a, b;

        for (auto token : tokens) {
            if (token == "+") {
                a = stack.top(); stack.pop();   // Second operand
                b = stack.top(); stack.pop();   // First operand
                stack.push(b + a);
            }
            else if (token == "-") {
                a = stack.top(); stack.pop();   // Second operand
                b = stack.top(); stack.pop();   // First operand
                stack.push(b - a);              // Order matters: first - second
            }
            else if (token == "/") {
                a = stack.top(); stack.pop();
                b = stack.top(); stack.pop();
                stack.push(b / a);              // Integer division
            }
            else if (token == "*") {
                a = stack.top(); stack.pop();
                b = stack.top(); stack.pop();
                stack.push(b * a);
            }
            else {
                stack.push(stoi(token));        // Convert operand from string to int
            }
        }
        return stack.top();  // Final result
    }
};
```

---

## 🧾 Library Functions Used

| Function        | Description                          |
| --------------- | ------------------------------------ |
| `stack<T>`      | Standard LIFO stack container        |
| `stack.top()`   | Returns the top element of the stack |
| `stack.pop()`   | Removes the top element              |
| `stack.push(x)` | Pushes a new element                 |
| `std::stoi(s)`  | Converts string `s` to integer       |

---

## 📈 Time & Space Complexity

| Aspect | Complexity                                                      |
| ------ | --------------------------------------------------------------- |
| Time   | **O(n)** – Each token is processed once                         |
| Space  | **O(n)** – In worst case, all tokens are numbers (no operators) |

* `n = number of tokens`

---

## 🪜 Step-by-Step Strategy

1. **Initialize** an empty stack.
2. Loop through the tokens:

   * If the token is an operator (`+`, `-`, `*`, `/`):

     * Pop **2** numbers from the stack.
     * Perform the operation in **correct order**: `b op a`.
     * Push the result back to the stack.
   * Else:

     * Convert string to integer and push onto the stack.
3. After the loop, the result is at the **top of the stack**.

---

## 🎯 Visualization with Example

**Input:**

```cpp
tokens = ["2", "1", "+", "3", "*"]
```

**Expression:**

`((2 + 1) * 3) = 9`

**Stack Trace:**

| Step | Token | Stack   |
| ---- | ----- | ------- |
| 1    | "2"   | \[2]    |
| 2    | "1"   | \[2, 1] |
| 3    | "+"   | \[3]    |
| 4    | "3"   | \[3, 3] |
| 5    | "\*"  | \[9] ✅  |

Return: `9`