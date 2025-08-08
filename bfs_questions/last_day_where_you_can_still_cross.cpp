/*
Problem: 1970. Last Day Where You Can Still Cross  
Link: https://leetcode.com/problems/last-day-where-you-can-still-cross/

Approach:
This problem asks us to find the **latest possible day** on which we can still cross
a grid from the **top row to the bottom row** before water fills up the cells 
(each day, some cell gets flooded).

We solve this using **Binary Search + BFS**:

1. **Binary Search**:
   - We binary search over the number of days (from 1 to row * col).
   - For each `mid` (day), we simulate flooding for the first `mid` cells.
   - Then check if we can still cross from top to bottom.

2. **BFS**:
   - We start BFS from all un-flooded cells in the top row.
   - We explore 4 directions from each cell.
   - If we reach the last row, we can cross on this day.

This approach gives an efficient solution due to the logarithmic nature of binary search 
and linear scanning using BFS for each check.

Time Complexity: O(log(row*col) * (row*col)) — due to binary search + BFS for each mid.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool bfs(vector<vector<bool>>& water, int r, int c) {

        queue<pair<int, int>> q;
        vector<vector<bool>> visited(r, vector<bool>(c, false));

        for (int col = 0; col < c; col++) {
            if (water[0][col] == false) {
                q.push({0, col});
                visited[0][col] = true;
            }
        }

        // now run bfs

        vector<vector<int>> direxns = {{+1, 0}, {-1, 0}, {0, +1}, {0, -1}};

        while (!q.empty()) {
            int curr_row = q.front().first;
            int curr_col = q.front().second;
            q.pop();

            if (curr_row == r - 1) {
                // we reached last column
                return true;
            }

            for (int i = 0; i < 4; i++) {
                int new_r = curr_row + direxns[i][0];
                int new_c = curr_col + direxns[i][1];

                // out of bound cell
                if (new_r < 0 or new_r >= r or new_c >= c or new_c < 0) {
                    continue;
                }

                // when there is no water and the cell is still not visited
                if (water[new_r][new_c] == false and
                    visited[new_r][new_c] == false) {
                    visited[new_r][new_c] = true;
                    q.push({new_r, new_c});
                }
            }
        }

        return false;
    }

    bool is_possible_to_cross(int mid, int r, int c,
                              vector<vector<int>>& cells) {

        vector<vector<bool>> water(r, vector<bool>(c, false));

        // suppose mid =1 so fill upto cells of 0
        for (int i = 0; i < mid; i++) {
            int row = cells[i][0] - 1;
            int col = cells[i][1] - 1;
            water[row][col] = true;
        }

        return bfs(water, r, c);
    }

    int latestDayToCross(int row, int col, vector<vector<int>>& cells) {

        int ans = 1;

        int low = 1;
        int high = row * col;

        while (low <= high) {
            int mid = (low + high) / 2;

            if (is_possible_to_cross(mid, row, col, cells)) {
                ans = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        return ans;
    }
};

