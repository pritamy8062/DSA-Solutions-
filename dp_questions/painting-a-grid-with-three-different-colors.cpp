/*
Problem: 1931. Painting a Grid With Three Different Colors
Link: https://leetcode.com/problems/painting-a-grid-with-three-different-colors/

Explanation in Simple English:

We are given an m x n grid and we need to color each cell using one of 3 colors: R, G, or B.
The coloring should follow two rules:
1. No two adjacent cells in a column can have the same color.
2. No two adjacent cells in a row can have the same color.

Our goal is to count how many valid ways we can color the whole grid, following these rules.

Approach:

1. First, we generate all valid vertical column combinations (states) using recursion:
   - Each column has 'm' cells.
   - Adjacent cells must not have the same color.
   - We store all valid column strings like "RGB", "BRG", etc.

2. Then, we use dynamic programming (with memoization) to build the grid column by column:
   - We pick one valid column as the first column.
   - For every next column, we try all valid columns that don’t clash with the previous column (no same color in same row).
   - We recursively solve for the remaining columns and add up all valid combinations.
   - We use a map to remember already-solved states to avoid recomputation.

3. Finally, we sum up all ways of building the full grid, starting from each valid first column.

Time complexity is high but manageable because:
- The number of valid columns is limited (much fewer than 3^m).
- We use memoization to avoid repeating work.

This is a great use of:
- Bitmasking logic with strings,
- Recursive state generation,
- Dynamic programming with memoization.

*/

class Solution {
public:
    void fill_column_states(int row, int m, string str,
                            vector<string>& states) {
        if (row == m) {
            states.push_back(str);
            return;
        }

        if (str.empty()) {
            fill_column_states(row + 1, m, str + 'R', states);
            fill_column_states(row + 1, m, str + 'G', states);
            fill_column_states(row + 1, m, str + 'B', states);
        }

        else {

            if (str.back() == 'R') {
                fill_column_states(row + 1, m, str + 'G', states);
                fill_column_states(row + 1, m, str + 'B', states);

            } else if (str.back() == 'G') {
                fill_column_states(row + 1, m, str + 'B', states);
                fill_column_states(row + 1, m, str + 'R', states);

            } else {
                fill_column_states(row + 1, m, str + 'R', states);
                fill_column_states(row + 1, m, str + 'G', states);
            }
        }
    }

    unordered_map<string, int> dp;

    const int MOD = 1e9 + 7;

    int solve(string prev_state, int bache_hue_columns,
              vector<string>& column_states) {

        if (bache_hue_columns == 0) {
            return 1;
        }

        string current_dp_state =
            prev_state + " " + to_string(bache_hue_columns);

        if (dp.find(current_dp_state) != dp.end()) {
            return dp[current_dp_state];
        }

        // mai jo prev_state le raha hu wo ek string hai
        // jo column ko represent kar raha hai

        int result = 0;

        for (int i = 0; i < column_states.size(); i++) {
            string curr_column_ = column_states[i];

            // isko check karunga ki possible hai ya nahi

            bool possible = true;

            int len = prev_state.size();
            // isko column_states[i].size() bhi likh sakta hu

            for (int j = 0; j < len; j++) {
                if (curr_column_[j] == prev_state[j]) {
                    possible = false;
                    break;
                }
            }

            if (possible == true) {
                // aage wale columns ko bhi bhar k check karunga
                // aur uske liye prev_state current column ho jayega

                result = (result + solve(curr_column_, bache_hue_columns - 1,
                                         column_states)) %
                         MOD;
            }
        }

        return dp[current_dp_state] = result;
    }

    int colorTheGrid(int m, int n) {
        string str = "";
        vector<string> column_states;
        fill_column_states(0, m, str, column_states);

        // for(int i=0; i<column_states.size(); i++){
        //     cout<<column_states[i]<<" , ";
        // }

        int ans = 0;

        for (int i = 0; i < column_states.size(); i++) {
            int remaining_columns = n - 1;

            ans = (ans +
                   solve(column_states[i], remaining_columns, column_states)) %
                  MOD;
        }

        return ans;
    }
};
