- [📌 **Problem Statement**](#-problem-statement)
- [Dynamic Programming](#dynamic-programming)
  - [🧾 **Library Function Definitions**](#-library-function-definitions)
  - [📈 **Time and Space Complexity**](#-time-and-space-complexity)
  - [🪜 **Step-by-Step Strategy**](#-step-by-step-strategy)
  - [🎯 **Visualization with Example**](#-visualization-with-example)
    - [Example Input:](#example-input)

# 📌 **Problem Statement**

You are given an array `prices` where `prices[i]` represents the price of a stock on the *i-th* day.
You want to maximize your profit by choosing **one day to buy** and **another day in the future to sell** that stock.
Return the **maximum profit** you can achieve from this transaction.
If no profit is possible, return `0`.

---

# Dynamic Programming

```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int minPrice = INT_MAX;  // 🧩 Track the minimum stock price seen so far
        int maxP = 0;            // 🧩 Track the maximum profit possible

        for (auto price : prices) {
            // Update minimum price if current price is smaller
            if (price < minPrice) {
                minPrice = price;
            }

            // Calculate profit if sold today, and update max profit
            maxP = max(maxP, price - minPrice);
        }

        return maxP;  // ✅ Return maximum profit found
    }
};
```

---

## 🧾 **Library Function Definitions**

* `INT_MAX`: Defined in `<climits>`. Represents the largest possible integer value.
* `max(a, b)`: Returns the greater of two values `a` and `b`. Defined in `<algorithm>`.

---

## 📈 **Time and Space Complexity**

| Complexity Type | Value    | Explanation                                       |
| --------------- | -------- | ------------------------------------------------- |
| ⏱️ **Time**     | **O(n)** | We loop through the prices once.                  |
| 💾 **Space**    | **O(1)** | Only two variables (`minPrice`, `maxP`) are used. |

---

## 🪜 **Step-by-Step Strategy**

1. **Initialize:**

   * Start with `minPrice = INT_MAX` (so any price is lower).
   * Start with `maxP = 0`.

2. **Iterate through prices:**

   * For each `price`, check if it’s smaller than `minPrice`. If yes, update it.
   * Compute profit = `price - minPrice` → potential profit if you sell now.
   * Keep the maximum of all computed profits in `maxP`.

3. **Return the result:**

   * After scanning all prices, `maxP` holds the maximum achievable profit.

---

## 🎯 **Visualization with Example**

### Example Input:

```
prices = [7, 1, 5, 3, 6, 4]
```

| Day | Price | minPrice | Profit (price - minPrice) | maxP |
| --- | ----- | -------- | ------------------------- | ---- |
| 1   | 7     | 7        | 0                         | 0    |
| 2   | 1     | 1        | 0                         | 0    |
| 3   | 5     | 1        | 4                         | 4    |
| 4   | 3     | 1        | 2                         | 4    |
| 5   | 6     | 1        | 5                         | 5    |
| 6   | 4     | 1        | 3                         | 5    |

✅ **Maximum Profit = 5 (Buy at 1, Sell at 6)**

---

Would you like me to also include a diagram showing how the algorithm tracks min price and profit over time?
