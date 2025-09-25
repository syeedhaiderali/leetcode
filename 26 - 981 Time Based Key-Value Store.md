- [Initial Implementation](#initial-implementation)
- [🧠 3. Binary Search (Array)](#-3-binary-search-array)
  - [🧾 Library Function Definitions](#-library-function-definitions)
  - [📈 Time \& Space Complexity](#-time--space-complexity)
  - [🪜 Step-by-Step Strategy](#-step-by-step-strategy)
  - [🎯 Visualization with Example](#-visualization-with-example)


## 📌 Problem Statement

Design a data structure that stores multiple values for the same key at different timestamps and allows retrieval of the value at a specific timestamp.

* `set(key, value, timestamp)`: Stores the key along with the value and timestamp.
* `get(key, timestamp)`: Returns the value for `key` at the **largest timestamp ≤ given timestamp**. If none exists, return an empty string `""`.

Constraints:

* All `set` calls for the same key will have timestamps **strictly increasing**.
* Number of operations ≤ 2 × 10⁵

---

# Initial Implementation

```cpp

/** Wrong Answer
 * 
 * Input
 * ["TimeMap","set","set","get","get","get","get","get"]
 * [[],["love","high",10],["love","low",20],["love",5],["love",10],["love",15],["love",20],["love",25]]
 * Output
 * [null,null,null,"low","high","low","low","low"]
 * Expected
 * [null,null,null,"","high","high","low","low"]
 * Contribute a testcase
 */


class TimeMap {
    unordered_map<string, unordered_map<int, string>> mp;
    int timestamp_max = 0;
public:
    TimeMap() {
        
    }
    
    void set(string key, string value, int timestamp) {
        mp[key][timestamp] = value;
        timestamp_max = max(timestamp_max, timestamp);
    }
    
    string get(string key, int timestamp) {
        if(mp[key][timestamp] != "")
            return mp[key][timestamp];
        
        return mp[key][timestamp_max];
    }
};

/**
 * Your TimeMap object will be instantiated and called as such:
 * TimeMap* obj = new TimeMap();
 * obj->set(key,value,timestamp);
 * string param_2 = obj->get(key,timestamp);
 */
 ```



# 🧠 3. Binary Search (Array)

```cpp
class TimeMap {
    // Hash map: key -> vector of (timestamp, value) pairs
    unordered_map<string, vector<pair<int, string>>> mp;

public:
    TimeMap() {
        // Constructor: no special initialization required
    }
    
    // Store a (timestamp, value) for the given key
    void set(string key, string value, int timestamp) {
        mp[key].push_back({timestamp, value});
    }
    
    // Retrieve the value with the largest timestamp <= given timestamp
    string get(string key, int timestamp) {
        auto& values = mp[key];  // reference to vector of (timestamp, value) pairs

        int l = 0, r = values.size() - 1;
        string res = "";  // default if not found

        while (l <= r) {
            int m = (l + r) / 2;

            if (timestamp >= values[m].first) {
                // candidate found, try searching right for closer timestamp
                res = values[m].second;
                l = m + 1;
            } else {
                // too large, move left
                r = m - 1;
            }
        }

        return res;
    }
};
```

---

## 🧾 Library Function Definitions

* `unordered_map<K, V>` → Hash table for average **O(1)** lookup and insert.
* `vector<T>` → Dynamic array for storing `(timestamp, value)` pairs in sorted order.
* `push_back()` → Appends to vector in O(1).

---

## 📈 Time & Space Complexity

* **set**: O(1) (amortized for vector insertion).
* **get**: O(log n) per query due to binary search on timestamps.
* Space: O(n) for storing all `(timestamp, value)` pairs.

---

## 🪜 Step-by-Step Strategy

1. Use `unordered_map` to group values by `key`.
2. Each key maps to a `vector<pair<int, string>>`, storing `(timestamp, value)`.
3. Since timestamps for a given key are always **increasing**, the vector is naturally sorted.
4. For `get`, do **binary search** on timestamps:

   * If `values[m].first <= timestamp`, store candidate and move right.
   * Otherwise, move left.
5. Return the best candidate found (or `""` if none exists).

---

## 🎯 Visualization with Example

**Input**

```cpp
TimeMap* obj = new TimeMap();
obj->set("foo", "bar", 1);
obj->get("foo", 1);   // "bar"
obj->get("foo", 3);   // "bar"
obj->set("foo", "bar2", 4);
obj->get("foo", 4);   // "bar2"
obj->get("foo", 5);   // "bar2"
```

**Execution**

* After `set("foo","bar",1)` → mp = { "foo" : [(1,"bar")] }
* `get("foo",1)` → binary search finds exact timestamp → "bar"
* `get("foo",3)` → binary search finds last ≤ 3 → "bar"
* After `set("foo","bar2",4)` → mp = { "foo" : [(1,"bar"), (4,"bar2")] }
* `get("foo",4)` → finds "bar2"
* `get("foo",5)` → finds last ≤ 5 → "bar2"

**Output**

```
"bar"
"bar"
"bar2"
"bar2"
```
