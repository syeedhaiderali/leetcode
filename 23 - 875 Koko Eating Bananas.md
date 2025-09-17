- [📌 Problem Statement](#-problem-statement)
- [Brute-Force Solution](#brute-force-solution)
  - [🧠 Code with Full Comments](#-code-with-full-comments)
  - [🧾 Library Function Definitions](#-library-function-definitions)
  - [📈 Time \& Space Complexity](#-time--space-complexity)
  - [🪜 Step-by-Step Strategy](#-step-by-step-strategy)
  - [🎯 Visualization with Example](#-visualization-with-example)
- [Optimal binary search solution](#optimal-binary-search-solution)
  - [🧾 Library Function Definitions](#-library-function-definitions-1)
  - [📈 Time \& Space Complexity](#-time--space-complexity-1)
  - [🪜 Step-by-Step Strategy](#-step-by-step-strategy-1)
  - [🎯 Visualization with Example](#-visualization-with-example-1)


# 📌 Problem Statement

Koko loves bananas.

* She has `piles` of bananas, where `piles[i]` is the number of bananas in the `i-th` pile.
* She can eat bananas at a speed of `k` bananas/hour.
* In one hour, she eats from exactly one pile. If the pile has fewer than `k`, she eats the whole pile.
* Koko wants to finish all the bananas within `h` hours.

👉 Find the **minimum eating speed** `k` that allows her to finish within `h`.

---

# Brute-Force Solution
**brute-force solution** for the "Koko Eating Bananas" problem. It’s correct but **very inefficient**. Let’s break it down fully.

## 🧠 Code with Full Comments

```cpp
#include <vector>
using namespace std;

class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int speed = 1; // Start testing from speed = 1 (slowest possible)

        while (true) {
            long long totalTime = 0;

            // Calculate total hours needed if she eats at 'speed'
            for (int pile : piles) {
                // Equivalent to ceil(pile / speed)
                totalTime += (pile + speed - 1) / speed;
            }

            // If she can finish in <= h hours, return this speed
            if (totalTime <= h) {
                return speed;
            }

            // Otherwise, increase speed and try again
            speed++;
        }
    }
};
```

---

## 🧾 Library Function Definitions

* `vector<int>` → dynamic array to hold banana piles.
* `(pile + speed - 1) / speed` → integer trick to compute `ceil(pile/speed)` without using floating point.

---

## 📈 Time & Space Complexity

* **Time Complexity**:

  * For each `speed`, we scan all piles → O(n).
  * Worst case, speed goes from `1` to `max(piles)` → O(maxPile \* n).
  * If `maxPile = 10^9` and `n = 10^4`, this is impossible in practice. ❌

* **Space Complexity**:

  * Only variables → O(1).

---

## 🪜 Step-by-Step Strategy

1. Start from speed = 1.
2. For each speed:

   * Compute total hours needed by summing ceil(pile/speed).
   * If hours ≤ h → return speed.
   * Else increase speed.
3. Continue until a valid speed is found.

---

## 🎯 Visualization with Example

Input:
`piles = [3,6,7,11], h = 8`

* speed=1 → time=3+6+7+11=27 > 8 ❌
* speed=2 → time=2+3+4+6=15 > 8 ❌
* speed=3 → time=1+2+3+4=10 > 8 ❌
* speed=4 → time=1+2+2+3=8 ✅ → return 4

Output: `4` ✅

---

⚠️ **Issue with your code**:
It’s **too slow** for large inputs. On LeetCode, this brute force will **Time Limit Exceed (TLE)**.

✅ **Optimal solution**: Use **binary search** between `1` and `max(piles)`.
That reduces complexity to **O(n log(maxPile))**, which is fast enough.

---
# Optimal binary search solution

```cpp
#include <vector>
#include <algorithm> // for max_element
using namespace std;

class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        // Lower bound = 1 (slowest speed)
        // Upper bound = max(piles) (fastest speed needed)
        int l = 1, r = *max_element(piles.begin(), piles.end());
        int result = r; // initialize with max speed

        while (l <= r) {
            int mid = l + (r - l) / 2; // candidate eating speed
            long long totalTime = 0;

            // Calculate time for this speed
            for (int pile : piles) {
                // ceil(pile / mid) = (pile + mid - 1) / mid
                totalTime += (pile + mid - 1) / mid;
            }

            if (totalTime <= h) {
                // Koko can finish with this speed, try slower
                result = mid;
                r = mid - 1;
            } else {
                // Too slow, must eat faster
                l = mid + 1;
            }
        }

        return result;
    }
};
```

---

## 🧾 Library Function Definitions

* `max_element(piles.begin(), piles.end())`: Returns an iterator to the maximum element in `piles`.
* `(pile + mid - 1) / mid`: Integer trick for `ceil(pile / mid)`.

---

## 📈 Time & Space Complexity

* **Time Complexity**:

  * Each binary search step → O(n) to compute total time.
  * Number of steps = O(log(maxPile)).
  * Total = **O(n log(maxPile))** ✅ (much faster than brute force).

* **Space Complexity**: O(1) (just variables).

---

## 🪜 Step-by-Step Strategy

1. **Set search range**: `[1, max(piles)]`.

   * Minimum speed = 1 (very slow).
   * Maximum speed = largest pile (eat a whole pile in 1 hour).

2. **Binary search**:

   * Compute `mid` speed.
   * Calculate total hours needed.
   * If hours ≤ h → store `mid` as candidate and try smaller speed.
   * If hours > h → increase speed.

3. Return the smallest valid speed.

---

## 🎯 Visualization with Example

Input:
`piles = [3, 6, 7, 11], h = 8`

* Search range: l=1, r=11
* mid=6 → time=1+1+2+2=6 ≤ 8 ✅ → try smaller (r=5)
* mid=3 → time=1+2+3+4=10 > 8 ❌ → increase (l=4)
* mid=4 → time=1+2+2+3=8 ≤ 8 ✅ → try smaller (r=3)

Loop ends, answer = **4** ✅

---

⚡ This binary search version is the **optimal solution accepted on LeetCode**.