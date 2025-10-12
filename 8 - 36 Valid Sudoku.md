#ifdef _Bitmask_
class Solution {
    public:
        bool isValidSudoku(vector<vector<char>>& board) {
            int rows[9] = {0};     // 9-bit masks to track seen digits in rows
            int cols[9] = {0};     // 9-bit masks to track seen digits in columns
            int squares[9] = {0};  // 9-bit masks to track seen digits in 3x3 boxes
    
            // Traverse each cell in the 9x9 board
            for (int r = 0; r < 9; ++r) {
                for (int c = 0; c < 9; ++c) {
                    if (board[r][c] == '.') continue; // skip empty cells
    
                    int val = board[r][c] - '1';  // Convert '1'-'9' to 0-8
    
                    // Check if val has already been seen in row, col, or square
                    if ((rows[r] & (1 << val)) || 
                        (cols[c] & (1 << val)) || 
                        (squares[(r / 3) * 3 + (c / 3)] & (1 << val))) {
                        return false;  // Duplicate found
                    }
    
                    // Mark val as seen in row, col, and square
                    rows[r] |= (1 << val);
                    cols[c] |= (1 << val);
                    squares[(r / 3) * 3 + (c / 3)] |= (1 << val);
                }
            }
            return true; // No conflicts found
        }
    };
/*
    🧠 How It Works
    Each of rows[r], cols[c], and squares[k] is a 9-bit integer, where each bit tracks whether a digit 1–9 has been seen.
    
    For example:
    If row 0 has already seen digits 1, 3, and 5,
    rows[0] might look like 001010101 (in binary), meaning:
    
    Bit 0 (1) → set
    
    Bit 2 (3) → set
    
    Bit 4 (5) → set
    
    🖼️ Visualizing It
    Imagine you have three 9x9 binary grids:
    
    1. Row tracker
    rows[0] = 000000000
    rows[1] = 000000001  ← saw '1'
    ...

    2. Column tracker
    cols[0] = 000000000
    cols[1] = 000001000  ← saw '4'
    ...
    3. 3×3 Box tracker (indexed as below):
    +---+---+---+
    | 0 | 1 | 2 |
    +---+---+---+
    | 3 | 4 | 5 |
    +---+---+---+
    | 6 | 7 | 8 |
    +---+---+---+
    Each box is tracked as squares[box_index]
    Where box_index = (r / 3) * 3 + (c / 3)
    
    🧠 Why use bitmasking?
    Fast: All operations are O(1)
    
    Memory-efficient: 27 integers (32-bit) only
    
    Easy to check & update digit presence with bitwise operators
    
    ⏱️ Time and Space Complexity
    Metric	Value
    Time	O(81) = O(1)
    Space	O(1)
    
    Because it's always 9×9.
*/
    
#endif

class Solution {
    public:
        bool isValidSudoku(vector<vector<char>>& board) {
            unordered_map<char, int> mp, mp2;
    
            for (int i = 0; i < board.size(); i++) {
                mp = {};
                mp2 = {};
                for (int j = 0; j < board[i].size(); j++){
                    mp[board[i][j]]++;
                    mp2[board[j][i]]++;
                }
    
                for (auto x : mp) {
                    cout << x.first << " " << x.second << endl;
                    if (x.first > '9') {
                        cout << "1 :>" << endl;
                        cout << x.first << " " << x.second << endl;
                        return false;
                    }
    
                    if (x.second > 1) {
                        cout << "2 :>" << endl;
                        return false;
                    }
                }
    
                for (auto x : mp2) {
                    cout << x.first << " " << x.second << endl;
                    if (x.first != '.' && x.first > '9') {
                        cout << "3 :>" << endl;
                        cout << x.first << " " << x.second << endl;
                        return false;
                    }
    
                    if (x.first != '.' && x.second > 1) {
                        cout << "4 :>" << endl;
                        return false;
                    }
                }
            }
    
          
            return true;
        }
    };