- [Leetcode 853 - Car Fleet](#leetcode-853---car-fleet)
- [Stack](#stack)
  - [Library Function Definitions](#library-function-definitions)
  - [Time \& Space Complexity](#time--space-complexity)
  - [Step-by-Step Strategy for Solving](#step-by-step-strategy-for-solving)
  - [How to Visualize It (Example)](#how-to-visualize-it-example)

# Leetcode 853 - Car Fleet

# Stack
```cpp
class Solution {
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        // Combine position and speed into a single vector of pairs
        vector<pair<int, int>> res(position.size()); 

        for (int i = 0; i < position.size(); i++)
            res[i] = {position[i], speed[i]};

        // Sort by position in descending order (cars closer to target come first)
        sort(res.rbegin(), res.rend());

        // Stack to track time taken by fleets
        stack<double> st;

        for (int i = 0; i < res.size(); i++) {
            // Calculate time taken to reach target
            double time = (double)(target - res[i].first) / res[i].second;

            // If stack is empty or this car takes more time than the fleet on top,
            // it cannot catch up and forms a new fleet
            if (st.empty() || time > st.top()) {
                st.push(time);
            }
            // If time <= st.top(), car catches up and merges into the fleet (do nothing)
        }

        // Remaining entries in stack are distinct fleets
        return st.size();
    }
};
```

---

## Library Function Definitions

* `vector<pair<int, int>>`: Stores `{position, speed}` of each car.
* `sort(res.rbegin(), res.rend())`: Sorts in **descending** order by position.
* `stack<double>`: Stores **arrival times** of fleets to detect merges.
* `(double)(a) / b`: Forces **floating-point division** instead of integer division.

---

## Time & Space Complexity

| Operation         | Complexity             |
| ----------------- | ---------------------- |
| Sorting           | O(n log n)             |
| Loop through cars | O(n)                   |
| Stack operations  | O(n)                   |
| **Total Time**    | **O(n log n)**         |
| **Space**         | O(n) (for res + stack) |

---

## Step-by-Step Strategy for Solving

1. **Pair the position and speed** of each car.
2. **Sort the cars in descending order** of position so we process them from **closest to the target**.
3. **Calculate time** for each car to reach the target.
4. **Use a stack** to track the times of fleets:

   * If the current car takes **more time** than the car ahead (top of stack), it cannot catch up → **new fleet**.
   * If the current car takes **less or equal time**, it **merges** into the fleet ahead.
5. Return the **number of fleets**, which is the **size of the stack**.

---

## How to Visualize It (Example)

🔹 Example Input:

```cpp
target = 12;
position = [10, 8, 0, 5, 3];
speed    = [2, 4, 1, 1, 3];
```

🔹 Pairs (position, speed):

```
[(10,2), (8,4), (0,1), (5,1), (3,3)]
```

🔹 After Sorting by position DESC:

```
[(10,2), (8,4), (5,1), (3,3), (0,1)]
```

🔹 Time to reach target:

```
(12-10)/2 = 1
(12-8)/4 = 1
(12-5)/1 = 7
(12-3)/3 = 3
(12-0)/1 = 12
```

🔹 Stack Simulation:

* Push 1
* 1 merges (skip)
* Push 7
* 3 merges into 7
* Push 12

Final stack: \[1, 7, 12] → **3 fleets**
